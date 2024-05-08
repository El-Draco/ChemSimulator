#include "moleculeentity.h"

MoleculeEntity::MoleculeEntity(Qt3DCore::QNode* parent, Molecule mol)
    : QEntity(parent), m_molData(mol)
{
    transform = new Qt3DCore::QTransform(this);
    addComponent(transform);
}

const Molecule MoleculeEntity::molData() const
{
    return m_molData;
}

Qt3DCore::QTransform *MoleculeEntity::getTransform() const
{
    return transform;
}


