#include "bondentity.h"
#include <QPropertyAnimation>

inline QQuaternion calcRotation(QVector3D source, QVector3D target) {
    QVector3D direction = target - source;
    return QQuaternion::rotationTo(QVector3D(0, 1, 0), direction.normalized());
}

BondEntity::BondEntity(Qt3DCore::QNode *parent, Bond bond, QVector3D sourcePosition, QVector3D targetPosition)
    : Qt3DCore::QEntity(parent), m_bondData(bond), m_sourceAtomPosition(sourcePosition), m_targetAtomPosition(targetPosition)
{
    float separation = 0.125f;
    float readjustment = (m_bondData.bondType * separation) / 2;

    for(int i = 0; i <= m_bondData.bondType; i++) {
        Qt3DCore::QEntity* ent = new Qt3DCore::QEntity(this);

        //Mesh
        bondMesh = new Qt3DExtras::QCylinderMesh(ent);
        bondMesh->setLength(1.0f);
        bondMesh->setRadius(0.05f);

        //Material
        bondMaterial = new Qt3DExtras::QDiffuseSpecularMaterial(ent);
        bondMaterial->setAmbient(QColor(QRgb(0x808080)));
        bondMaterial->setShininess(0.0f);

        // Transform
        Qt3DCore::QTransform* bondTransform = new Qt3DCore::QTransform(ent);
        bondTransform->setTranslation(QVector3D(0.0f, 0.0f, ((float)i*separation) - readjustment ));

        ent->addComponent(bondMesh);
        ent->addComponent(bondTransform);
        ent->addComponent(bondMaterial);

        entList.append(ent);
    }

    m_length = (m_targetAtomPosition - m_sourceAtomPosition).length();
    // Transform
    transform = new Qt3DCore::QTransform(this);
    transform->setScale3D(QVector3D(1.0f, 1.0f, m_length));
    transform->setTranslation((m_sourceAtomPosition + m_targetAtomPosition) * 0.5f);
    transform->setRotation(calcRotation(m_sourceAtomPosition, m_targetAtomPosition));

    positionAnimation = new QPropertyAnimation(transform);
    positionAnimation->setTargetObject(transform);
    positionAnimation->setPropertyName("translation");
    positionAnimation->setLoopCount(1);

    rotationAnimation = new QPropertyAnimation(transform);
    rotationAnimation->setTargetObject(transform);
    rotationAnimation->setPropertyName("rotation");
    rotationAnimation->setLoopCount(1);

    lengthAnimation = new QPropertyAnimation(transform);
    lengthAnimation->setTargetObject(transform);
    lengthAnimation->setPropertyName("scale3D");
    lengthAnimation->setLoopCount(1);

    addComponent(transform);
}

void BondEntity::redraw(bool source, QVector3D newPosition)
{
    if(source)
        m_sourceAtomPosition = newPosition;
    else
        m_targetAtomPosition = newPosition;

    auto length = (m_targetAtomPosition - m_sourceAtomPosition).length();
    transform->setScale3D(QVector3D(1.0f, length, 1.0f));
    transform->setTranslation((m_sourceAtomPosition + m_targetAtomPosition) * 0.5f);
    transform->setRotation(calcRotation(m_sourceAtomPosition, m_targetAtomPosition));
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
    rotationAnimation->setEndValue(QVariant::fromValue(calcRotation(sourcePosition, targetPosition)));
    rotationAnimation->setDuration(duration);
    return rotationAnimation;
}

QPropertyAnimation *BondEntity::getNewLengthAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration)
{
    lengthAnimation->setStartValue(QVariant::fromValue(transform->scale3D()));
    lengthAnimation->setEndValue(QVariant::fromValue(QVector3D(1.0f, 1.0f, (targetPosition - sourcePosition).length())));
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


