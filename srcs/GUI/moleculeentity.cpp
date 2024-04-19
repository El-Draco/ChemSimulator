#include "moleculeentity.h"

MoleculeEntity::MoleculeEntity(Qt3DCore::QNode* parent, Molecule mol)
    : QEntity(parent), m_molData(mol)
{

}

const Molecule MoleculeEntity::molData() const
{
    return m_molData;
}


