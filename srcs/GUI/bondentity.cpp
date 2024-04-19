#include "bondentity.h"

#include <QPropertyAnimation>

BondEntity::BondEntity(Qt3DCore::QNode *parent, Bond bond, QVector3D sourcePosition, QVector3D targetPosition)
    : Qt3DCore::QEntity(parent), m_bondData(bond)
{
    //Mesh
    bondMesh = new Qt3DExtras::QCylinderMesh(this);
    bondMesh->setLength((targetPosition - sourcePosition).length());
    bondMesh->setRadius(0.1f);

    //Material
    bondMaterial = new Qt3DExtras::QDiffuseSpecularMaterial(this);
    bondMaterial->setDiffuse(QColor(QRgb(0x808080)));
    bondMaterial->setShininess(0.0f);

    // Transform
    transform = new Qt3DCore::QTransform(this);
    transform->setScale(1.0f);
    transform->setTranslation((sourcePosition + targetPosition) * 0.5f);
    // Set orientation towards target
    QVector3D direction = targetPosition - sourcePosition;
    QQuaternion rotation = QQuaternion::rotationTo(QVector3D(0, 1, 0), direction.normalized());
    transform->setRotation(rotation);

    positionAnimation = new QPropertyAnimation(transform);
    positionAnimation->setTargetObject(transform);
    positionAnimation->setPropertyName("translation");
    positionAnimation->setLoopCount(1);

    rotationAnimation = new QPropertyAnimation(transform);
    rotationAnimation->setTargetObject(transform);
    rotationAnimation->setPropertyName("rotation");
    rotationAnimation->setLoopCount(1);

    lengthAnimation = new QPropertyAnimation(bondMesh);
    lengthAnimation->setTargetObject(bondMesh);
    lengthAnimation->setPropertyName("length");
    lengthAnimation->setLoopCount(1);

    addComponent(bondMesh);
    addComponent(transform);
    addComponent(bondMaterial);
}

QPropertyAnimation *BondEntity::getNewPositionAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration)
{
    positionAnimation->setStartValue(QVariant::fromValue(transform->translation()));
    positionAnimation->setEndValue(QVariant::fromValue((sourcePosition + targetPosition) * 0.5f));
    positionAnimation->setDuration(duration);
    return positionAnimation;
}

QPropertyAnimation *BondEntity::getNewRotationAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration)
{
    rotationAnimation->setStartValue(QVariant::fromValue(transform->rotation()));
    QVector3D direction = targetPosition - sourcePosition;
    QQuaternion newRotation = QQuaternion::rotationTo(QVector3D(0, 1, 0), direction.normalized());
    rotationAnimation->setEndValue(QVariant::fromValue(newRotation));
    rotationAnimation->setDuration(duration);
    return rotationAnimation;
}

QPropertyAnimation *BondEntity::getNewLengthAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration)
{
    lengthAnimation->setStartValue(QVariant::fromValue(bondMesh->length()));
    lengthAnimation->setEndValue(QVariant::fromValue((targetPosition - sourcePosition).length()));
    lengthAnimation->setDuration(duration);
    return lengthAnimation;
}

Bond BondEntity::bondData() const
{
    return m_bondData;
}

void BondEntity::setBondData(const Bond newBondData)
{
    m_bondData = newBondData;
}


