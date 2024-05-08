#include "graphicsview.h"
#include "atomentity.h"
#include "moleculeentity.h"

#include "bondentity.h"

#include <QMouseEvent>
#include <QMutableVectorIterator>
#include <QMutableListIterator>
#include <QParallelAnimationGroup>
#include <QPointLight>
#include <QPlaneMesh>
#include <Qt3DRender/QRenderSettings>

GraphicsView::GraphicsView(QWidget *parent, DataManager* dm)
    : m_dm(dm)
{
    ptrToModel = m_dm->getPtrToData();
    scene = new Qt3DCore::QEntity();
    defaultFrameGraph()->setClearColor(QColor(QRgb(0xf3f6f4)));

    drawFromData();

    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(scene);
    light->setIntensity(0.0f);

    cameraController = new OrbitCameraController(scene);
    cameraController->setCamera(camera());
    cameraController->setLinearSpeed(300.0f);
    cameraController->setLookSpeed(100.0f);

    connect(camera(),
            &Qt3DRender::QCamera::viewCenterChanged,
            cameraController,
            &OrbitCameraController::updateCenterPoint);

    setRootEntity(scene);
}

void GraphicsView::drawFromData()
{
    draggingEntity = nullptr;
    int numEntities = molEntities.size();
    for (int i = numEntities - 1; i >= 0; --i) {
        MoleculeEntity* ent = molEntities.at(i);
        delete ent;
    }
    molEntities.clear();

    for(Molecule& mol : *ptrToModel.data()) {
        MoleculeEntity *molEntity = new MoleculeEntity(scene, mol);
        //molecule entity id
        molEntities.append(molEntity);
        mol.entityID = molEntity->id().id();

        //build atom entities
        for(Atom& atom : mol.atoms) {
            AtomEntity *atomEntity = new AtomEntity(molEntity, atom);
            atom.entityID = atomEntity->id().id();
            atomEntity->molID = mol.uniqueID;
            //dragging
            connect(atomEntity,
                    &AtomEntity::draggingChanged,
                    this,
                    &GraphicsView::changeDraggingEntity);
        }

        //build bond entities
        for(Bond& bond : mol.bonds) {
            QVector3D source = m_dm->getAtomByUniqueID(bond.sourceAtomID, mol)->position;
            QVector3D target = m_dm->getAtomByUniqueID(bond.targetAtomID, mol)->position;
            BondEntity *bondEntity = new BondEntity(molEntity, bond, source, target);
            bond.entityID = bondEntity->id().id();
            bondEntity->molID = mol.uniqueID;
        }
    }
}

void GraphicsView::showMolecule(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(selected.empty()) return;
    camera()->viewEntity(molEntities.at(selected.indexes().first().row()));
}

void GraphicsView::changeDraggingEntity(bool dragging, QVector3D position)
{
    if(draggingEntity) {
        if(qobject_cast<Qt3DCore::QEntity*>(sender()) == draggingEntity) {
            worldIntersection = position;
            if (!dragging) draggingEntity = nullptr;
            return;
        }
    }
    if(!draggingEntity) {
        if(dragging) draggingEntity = qobject_cast<Qt3DCore::QEntity*>(sender());
        else draggingEntity = nullptr;
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton) {
        if(!draggingEntity) return;

        Qt3DCore::QTransform* transform;
        if(event->modifiers() & Qt::ControlModifier) {
            auto transformList = draggingEntity->parentEntity()->componentsOfType<Qt3DCore::QTransform>();
            transform = transformList.first();
            if(!transform) return;
        } else {
            auto transformList = draggingEntity->componentsOfType<Qt3DCore::QTransform>();
            transform = transformList.first();
            if(!transform) return;
        }

        float posY = height() - event->position().y() - 0.0f;
        QVector3D screenCoordinates = QVector3D(event->position().x(),
                                                posY,
                                                0.0f);

        qDebug() << worldIntersection;
        QVector3D projected = transform->translation().project(camera()->viewMatrix(),
                                                               camera()->projectionMatrix(),
                                                               QRect(0, 0, width(), height()));
        screenCoordinates.setZ(projected.z());

        QVector3D mouseIn3D = screenCoordinates.unproject(camera()->viewMatrix(),
                                                          camera()->projectionMatrix(),
                                                          QRect(0, 0, width(), height()));
        QVector3D adjustment = transform->translation() - worldIntersection;
        qDebug() << "adj" << adjustment;
        qDebug() << mouseIn3D + adjustment;
        transform->setTranslation(mouseIn3D);

        if(!(event->modifiers() & Qt::ControlModifier)) {
            //redraw bonds
            AtomEntity* draggingAtom = qobject_cast<AtomEntity*>(draggingEntity);
            int atomIndex = draggingAtom->atomData().uniqueID;
            for(Qt3DCore::QNode *node : draggingAtom->parentNode()->childNodes()) {
                if(BondEntity *bondEntity = qobject_cast<BondEntity*>(node)) {
                    int sourceAtom = bondEntity->bondData().sourceAtomID;
                    int targetAtom = bondEntity->bondData().targetAtomID;
                    if(sourceAtom == atomIndex) {
                        bondEntity->redraw(1, mouseIn3D);
                    } else if(targetAtom == atomIndex) {
                        bondEntity->redraw(0, mouseIn3D);
                    }
                }
            }

            updateData(draggingEntity);
        } else {
            updateData(draggingEntity->parentEntity());
        }
    }
}

void GraphicsView::updateData(Qt3DCore::QEntity* blame)
{
    //if entity is an atom
    if (auto atomEntity = qobject_cast<AtomEntity*>(blame)) {
        int atomUniqueID = atomEntity->atomData().uniqueID;
        Molecule* mol = m_dm->getMoleculeByUniqueID(atomEntity->molID);
        Atom* atomToUpdate = m_dm->getAtomByUniqueID(atomUniqueID, *mol);

        atomToUpdate->position = atomEntity->getTransform()->translation();
    } else if(auto molEntity = qobject_cast<MoleculeEntity*>(blame)) {
        int molUniqueID = molEntity->molData().uniqueID;
        Molecule* mol = m_dm->getMoleculeByUniqueID(molUniqueID);

        mol->position = molEntity->getTransform()->translation();
    }
    emit potentialDataChange();
}

void GraphicsView::viewAll()
{
    camera()->viewAll();
}

void GraphicsView::animateDataUpdate()
{
    int DURATION = 500;
    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
    connect(animationGroup,
            &QParallelAnimationGroup::finished,
            m_dm,
            &DataManager::setNextDataForAnimation);

    QMutableListIterator<MoleculeEntity*> it(molEntities);
    while(it.hasNext()) {
        it.next();
        MoleculeEntity *molEntity = it.value();
        Molecule *mol = m_dm->getMoleculeByUniqueID(molEntity->molData().uniqueID);
        if (!mol) {
            delete molEntity;
            it.remove();
            continue;
        }

        for(Qt3DCore::QNode* node : molEntity->childNodes()) {
            if(auto entity = qobject_cast<AtomEntity*>(node)) {
                Atom *atom = m_dm->getAtomByUniqueID(entity->atomData().uniqueID, *mol);
                if (!atom) {
                    delete entity;
                    continue;
                }

                entity->setAtomData(*atom);
                QPropertyAnimation *animation = entity->getNewAnimation();
                animation->setDuration(500);
                animationGroup->addAnimation(animation);
            }
            if(auto entity = qobject_cast<BondEntity*>(node)) {
                Bond *bond = m_dm->getBondByUniqueID(entity->bondData().uniqueID, *mol);
                if (!bond) {
                    delete entity;
                    continue;
                }

                entity->setBondData(*bond);
                QVector3D source = m_dm->getAtomByUniqueID(bond->sourceAtomID, *mol)->position;
                QVector3D target = m_dm->getAtomByUniqueID(bond->targetAtomID, *mol)->position;
                animationGroup->addAnimation(entity->getNewLengthAnimation(source, target, DURATION));
                animationGroup->addAnimation(entity->getNewPositionAnimation(source, target, DURATION));
                animationGroup->addAnimation(entity->getNewRotationAnimation(source, target, DURATION));
            }
        }
    }
    animationGroup->start();
}
