#include "atomentity.h"
#include <QApplication>
#include <QCursor>
#include <QPickEvent>


AtomEntity::AtomEntity(Qt3DCore::QNode *parent, Atom atom)
    : Qt3DCore::QEntity(parent), m_atomData(atom)
{
    //Mesh
    atomMesh = new Qt3DExtras::QSphereMesh(this);
    atomMesh->setRings(20);
    atomMesh->setSlices(20);
    atomMesh->setRadius((atom.atomicNumber/118)*2 + 0.2);

    //Material
    atomMaterial = AtomEntity::originalMaterial();

    // Transform
    transform = new Qt3DCore::QTransform(this);
    transform->setScale(1.3f);
    transform->setTranslation(atom.position);

    //Input
    objectPicker = new Qt3DRender::QObjectPicker(this);
    objectPicker->setHoverEnabled(true);
    objectPicker->setDragEnabled(true);
    objectPicker->setEnabled(true);
    connect(objectPicker,
            SIGNAL(containsMouseChanged(bool)),
            this,
            SLOT(onHover(bool)));
    connect(objectPicker,
            SIGNAL(moved(Qt3DRender::QPickEvent*)),
            this,
            SLOT(handleDrag(Qt3DRender::QPickEvent*)));

    animation = new QPropertyAnimation(transform);
    animation->setTargetObject(transform);
    animation->setPropertyName("translation");
    animation->setLoopCount(1);

    addComponent(objectPicker);
    addComponent(atomMesh);
    addComponent(transform);
    addComponent(atomMaterial);
}

QPropertyAnimation *AtomEntity::getNewAnimation() {
    animation->setStartValue(QVariant::fromValue(transform->translation()));
    animation->setEndValue(QVariant::fromValue(m_atomData.position));
    return animation;
}

Qt3DCore::QTransform *AtomEntity::getTransform() const
{
    return transform;
}

const Atom AtomEntity::atomData() const
{
    return m_atomData;
}

void AtomEntity::setAtomData(const Atom newAtomData)
{
    m_atomData = newAtomData;
}

void AtomEntity::onHover(bool containsMouse) {
    if (containsMouse) {

        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        removeComponent(atomMaterial);
        atomMaterial = AtomEntity::highlightMaterial();
        addComponent(atomMaterial);
    } else {
        QApplication::restoreOverrideCursor();
        removeComponent(atomMaterial);
        atomMaterial = AtomEntity::originalMaterial();
        addComponent(atomMaterial);
    }
}

void AtomEntity::handleDrag(Qt3DRender::QPickEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        emit draggingChanged(true);
    } else {
        emit draggingChanged(false);
    }
}

Qt3DExtras::QDiffuseSpecularMaterial *AtomEntity::originalMaterial()
{
    Qt3DExtras::QDiffuseSpecularMaterial *material = nullptr;
    if (!material) {
        material = new Qt3DExtras::QDiffuseSpecularMaterial();
        material->setDiffuse(QColor(QRgb(0xFF0F00)));
        material->setShininess(0.0f);
    }
    return material;
}

Qt3DExtras::QDiffuseSpecularMaterial *AtomEntity::highlightMaterial()
{
    Qt3DExtras::QDiffuseSpecularMaterial *material = nullptr;
    if (!material) {
        material = new Qt3DExtras::QDiffuseSpecularMaterial();
        material->setDiffuse(QColor(QRgb(0xFFFF00)));
        material->setSpecular(QColor(QRgb(0xFFFFFF)));
        material->setShininess(1.0f);
    }
    return material;
}

