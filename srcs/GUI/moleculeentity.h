#ifndef MOLECULEENTITY_H
#define MOLECULEENTITY_H

#include "datamanager.h"
#include "atomentity.h"
#include "bondentity.h"
#include <QEntity>
#include <QNode>
#include <Qt3DCore/QTransform>

class MoleculeEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    MoleculeEntity(Qt3DCore::QNode *parent, Molecule mol);

    const Molecule molData() const;

    Qt3DCore::QTransform* transform;

    Qt3DCore::QTransform *getTransform() const;

private:
    Molecule m_molData;
};

#endif // MOLECULEENTITY_H
