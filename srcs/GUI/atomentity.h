#ifndef ATOMENTITY_H
#define ATOMENTITY_H

#include "datamanager.h"

#include <QDiffuseSpecularMaterial>
#include <QEntity>
#include <QObjectPicker>
#include <QSphereMesh>
#include <Qt3DCore/QTransform>
#include <QPropertyAnimation>

class AtomEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    AtomEntity(Qt3DCore::QNode *parent, Atom atom);

    static QList<QColor> colorScheme;

    const Atom atomData() const;
    void setAtomData(const Atom newAtomData);

    QPropertyAnimation *getNewAnimation();
    Qt3DCore::QTransform *getTransform() const;

    int molID = -1;

    static QColor CPKcolorScheme(int atomicNumber);
private:
    Qt3DExtras::QSphereMesh *atomMesh;
    Qt3DExtras::QDiffuseSpecularMaterial *atomMaterial;
    Qt3DRender::QObjectPicker *objectPicker;
    Qt3DCore::QTransform *transform;
    QPropertyAnimation *animation;

    Atom m_atomData;

    QColor m_color;

signals:
    void draggingChanged(bool, QVector3D);

private slots:
    void onHover(bool);
    void handleDrag(Qt3DRender::QPickEvent*);
};

#endif // ATOMENTITY_H
