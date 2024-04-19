#include "graphicsview.h"
#include "atomentity.h"
#include "moleculeentity.h"
#include "orbitcameracontroller.h"
#include "bondentity.h"

#include <QMouseEvent>
#include <QParallelAnimationGroup>
#include <QPointLight>

GraphicsView::GraphicsView(QWidget *parent, DataManager* dm)
    : m_dm(dm)
{
    ptrToModel = m_dm->getPtrToData();
    scene = new Qt3DCore::QEntity();
    defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));

    drawFromData();
    selectedMolEntity = molEntities.first();

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(scene);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1.0f);
    lightEntity->addComponent(light);
    auto t = new Qt3DCore::QTransform(lightEntity);
    t->setTranslation(QVector3D(0.0, 0.0, 50.0));
    lightEntity->addComponent(t);

    Qt3DCore::QEntity *lightEntity2 = new Qt3DCore::QEntity(scene);
    Qt3DRender::QPointLight *light2 = new Qt3DRender::QPointLight(lightEntity2);
    light2->setColor("white");
    light2->setIntensity(1.0f);
    lightEntity2->addComponent(light2);
    auto t2 = new Qt3DCore::QTransform(lightEntity2);
    t2->setTranslation(QVector3D(0.0, 0.0, -50.0));
    lightEntity2->addComponent(t2);

    OrbitCameraController *cameraController = new OrbitCameraController(scene);
    cameraController->setCamera(camera());
    cameraController->setLinearSpeed(300.0f);
    cameraController->setLookSpeed(100.0f);

    setRootEntity(scene);
}


void GraphicsView::drawFromData()
{
    draggingEntity = nullptr;
    for(MoleculeEntity* ent : molEntities) {
        delete ent;
    }
    molEntities.clear();

    for(Molecule& mol : *ptrToModel.data()) {
        MoleculeEntity *molEntity = new MoleculeEntity(scene, mol);
        //molecule entity id
        molEntities.append(molEntity);

        //build atom entities
        for(Atom& atom : mol.atoms) {
            AtomEntity *atomEntity = new AtomEntity(molEntity, atom);

            //dragging
            connect(atomEntity,
                    SIGNAL(draggingChanged(bool)),
                    this,
                    SLOT(changeDraggingEntity(bool)));
        }

        //build bond entities
        for(Bond& bond : mol.bonds) {
            QVector3D source = mol.atoms.at(bond.sourceAtomIndex).position;
            QVector3D target = mol.atoms.at(bond.targetAtomIndex).position;
            BondEntity *bondEntity = new BondEntity(molEntity, bond, source, target);
        }
    }
}

void redrawBonds() {

}

void GraphicsView::changeDraggingEntity(bool dragging)
{
    if(draggingEntity) {
        if(qobject_cast<Qt3DCore::QEntity*>(sender()) == draggingEntity) {
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

        auto transformList = draggingEntity->componentsOfType<Qt3DCore::QTransform>();
        auto *transform = transformList.first();
        if(!transform) return;

        float posY = height() - event->pos().y() - 0.0f;
        QVector3D screenCoordinates = QVector3D(event->pos().x(),
                                                posY,
                                                0.0f);

        QVector3D projected = transform->translation().project(camera()->viewMatrix(),
                                                               camera()->projectionMatrix(),
                                                               QRect(0, 0, width(), height()));
        screenCoordinates.setZ(projected.z());

        QVector3D mouseIn3D = screenCoordinates.unproject(camera()->viewMatrix(),
                                                          camera()->projectionMatrix(),
                                                          QRect(0, 0, width(), height()));
        transform->setTranslation(mouseIn3D);
        updateData(draggingEntity);
    }
}

void GraphicsView::updateData(Qt3DCore::QEntity* blame)
{
    //if entity is an atom
    if (auto atomEntity = qobject_cast<AtomEntity*>(blame)) {
        int atomUniqueID = atomEntity->atomData().uniqueID;

    }
}

void GraphicsView::animateDataUpdate()
{
    int DURATION = 500;
    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
    connect(animationGroup,
            &QParallelAnimationGroup::finished,
            m_dm,
            &DataManager::setNextDataForAnimation);

    for(MoleculeEntity* molEntity : molEntities) {
        Molecule *mol = m_dm->getMoleculeByUniqueID(molEntity->molData().uniqueID);
        if (!mol) {
            delete molEntity;
            molEntities.removeOne(molEntity);
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
                QVector3D source = mol->atoms.at(bond->sourceAtomIndex).position;
                QVector3D target = mol->atoms.at(bond->targetAtomIndex).position;
                animationGroup->addAnimation(entity->getNewLengthAnimation(source, target, DURATION));
                animationGroup->addAnimation(entity->getNewPositionAnimation(source, target, DURATION));
                animationGroup->addAnimation(entity->getNewRotationAnimation(source, target, DURATION));
            }
        }
    }
    animationGroup->start();
}


























