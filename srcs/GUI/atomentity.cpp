#include "atomentity.h"
#include <QApplication>
#include <QCursor>
#include <QPickEvent>


AtomEntity::AtomEntity(Qt3DCore::QNode *parent, Atom atom)
    : Qt3DCore::QEntity(parent), m_atomData(atom)
{
    if(m_atomData.atomicNumber == 9)
        m_color = Qt::green;
    else if(m_atomData.atomicNumber == 6)
        m_color = QColor(QRgb(0x222222));
    else if(m_atomData.atomicNumber == 1)
        m_color = Qt::gray;

    //Mesh
    atomMesh = new Qt3DExtras::QSphereMesh(this);
    atomMesh->setRings(20);
    atomMesh->setSlices(20);
    atomMesh->setRadius((atom.atomicNumber/118)*2 + 0.2);

    //Material
    atomMaterial = new Qt3DExtras::QDiffuseSpecularMaterial(this);
    atomMaterial->setAmbient(m_color);
    atomMaterial->setShininess(0.0f);

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
        atomMaterial->setAmbient(QColor(QRgb(0xFFFF00)));
        atomMaterial->setSpecular(QColor(QRgb(0xFFFFFF)));
        atomMaterial->setShininess(1.0f);
    } else {
        QApplication::restoreOverrideCursor();
        atomMaterial->setAmbient(m_color);
        atomMaterial->setShininess(0.0f);
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
