#ifndef BONDENTITY_H
#define BONDENTITY_H

#include "datamanager.h"
#include <QCylinderMesh>
#include <QDiffuseSpecularMaterial>
#include <QEntity>
#include <QNode>
#include <Qt3DCore/QTransform>
#include <QPropertyAnimation>

class BondEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    BondEntity(Qt3DCore::QNode*, Bond, QVector3D, QVector3D);

    void redraw(bool, QVector3D);

    Bond bondData() const;
    void setBondData(const Bond newBondData);

    QPropertyAnimation *getNewLengthAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration);
    QPropertyAnimation *getNewRotationAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration);
    QPropertyAnimation *getNewPositionAnimation(QVector3D sourcePosition, QVector3D targetPosition, int duration);

    int molID = -1;

private:
    Qt3DExtras::QCylinderMesh *bondMesh;
    Qt3DExtras::QDiffuseSpecularMaterial *bondMaterial;
    Qt3DCore::QTransform *transform;
    QPropertyAnimation *positionAnimation;
    QPropertyAnimation *rotationAnimation;
    QPropertyAnimation *lengthAnimation;

    QList<Qt3DCore::QEntity*> entList;

    QVector3D m_sourceAtomPosition;
    QVector3D m_targetAtomPosition;

    Bond m_bondData;
    float m_length;
};

#endif // BONDENTITY_H
