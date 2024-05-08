#include "atomentity.h"
#include <QApplication>
#include <QCursor>
#include <QPickEvent>


AtomEntity::AtomEntity(Qt3DCore::QNode *parent, Atom atom)
    : Qt3DCore::QEntity(parent), m_atomData(atom)
{
    m_color = AtomEntity::CPKcolorScheme(m_atomData.atomicNumber);

    //Mesh
    atomMesh = new Qt3DExtras::QSphereMesh(this);
    atomMesh->setRings(30);
    atomMesh->setSlices(30);
    atomMesh->setRadius((atom.atomicNumber/118)*2 + 0.3);

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
        atomMaterial->setAmbient(QColor(QRgb(0x0000FA)));
        atomMaterial->setSpecular(QColor(QRgb(0xF0F0FF)));
        atomMaterial->setShininess(0.6f);
    } else {
        QApplication::restoreOverrideCursor();
        atomMaterial->setAmbient(m_color);
        atomMaterial->setShininess(0.0f);
    }
}

void AtomEntity::handleDrag(Qt3DRender::QPickEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        emit draggingChanged(true, event->worldIntersection());
    } else {
        emit draggingChanged(false,  event->worldIntersection());
    }
}

QColor AtomEntity::CPKcolorScheme(int atomicNumber) {
    switch(atomicNumber) {
    case 1:
        return Qt::white;
        break;
    case 6:
        return Qt::black;
        break;
    case 7:
        return Qt::blue;
        break;
    case 8:
        return Qt::red;
        break;
    case 9:
    case 17:
        return Qt::green;
        break;
    case 35:
        return Qt::darkRed;
        break;
    case 53:
        return Qt::darkMagenta;
        break;
    case 2:
    case 10:
    case 18:
    case 36:
    case 54:
        return Qt::cyan;
        break;
    case 15:
        return QRgb(0xffa500);
        break;
    case 16:
        return Qt::yellow;
        break;
    case 5:
        return QRgb(0xf5f5dc);
        break;
    case 3:
    case 11:
    case 19:
    case 37:
    case 55:
    case 87:
        return Qt::magenta;
        break;
    case 4:
    case 12:
    case 20:
    case 38:
    case 56:
    case 88:
        return Qt::darkGreen;
        break;
    case 22:
        return Qt::gray;
        break;
    case 26:
        return QRgb(0xff8c00);
        break;
    default:
        return QRgb(0xffc0cb);
        break;
    }
}

