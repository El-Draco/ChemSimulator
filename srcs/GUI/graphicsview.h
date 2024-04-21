#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QEntity>
#include <Qt3DWindow>
#include <QCamera>
#include <QForwardRenderer>
#include "moleculeentity.h"

#include "datamanager.h"

class GraphicsView : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget*, DataManager*);

    void mouseMoveEvent(QMouseEvent *) override;

    //draw Molecules
    void drawFromData();

private:
    Qt3DCore::QEntity *scene;
    Qt3DCore::QEntity *draggingEntity = nullptr;
    QSharedPointer<QList<Molecule>> ptrToModel;

    int selectedMolEntity = 0;
    QList<MoleculeEntity*> molEntities;
    QList<int> existingEntityIDs;

    DataManager* m_dm;

    void updateData(Qt3DCore::QEntity* blame = nullptr);

signals:
    //signal data manager for changes in data
    void potentialDataChange();

public slots:
    //sets the current entity that is being dragged
    void changeDraggingEntity(bool);

    void animateDataUpdate();

    void atomEntityRemoved(Atom);



};

#endif // GRAPHICSVIEW_H
