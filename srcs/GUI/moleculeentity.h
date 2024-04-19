#ifndef MOLECULEENTITY_H
#define MOLECULEENTITY_H

#include "datamanager.h"
#include "atomentity.h"
#include "bondentity.h"
#include <QEntity>
#include <QNode>

class MoleculeEntity : public Qt3DCore::QEntity
{
public:
    MoleculeEntity(Qt3DCore::QNode *parent, Molecule mol);

    const Molecule molData() const;

private:
    Molecule m_molData;
};

#endif // MOLECULEENTITY_H
