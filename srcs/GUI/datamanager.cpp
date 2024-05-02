#include "datamanager.h"

#include "atomtablemodel.h"
#include "graphicsview.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    ptrToData = QSharedPointer<QList<Molecule>>(new QList<Molecule>());

    testData();
}

QSharedPointer<QList<Molecule>> DataManager::getPtrToData() const
{
    return ptrToData;
}

Molecule *DataManager::getMoleculeByUniqueID(int id)
{
    for(Molecule& mol : *ptrToData.data()) {
        if (mol.uniqueID == id) return &mol;
    }
    return nullptr;
}

Atom *DataManager::getAtomByUniqueID(int id, Molecule &mol)
{
    for(Atom& atom : getMoleculeByUniqueID(mol.uniqueID)->atoms) {
        if (atom.uniqueID == id) return &atom;
    }
    return nullptr;
}

Bond *DataManager::getBondByUniqueID(int id, Molecule &mol)
{
    for(Bond& bond : getMoleculeByUniqueID(mol.uniqueID)->bonds) {
        if (bond.uniqueID == id) return &bond;
    }
    return nullptr;
}

void DataManager::dataChangeListener()
{
    if(auto blame = qobject_cast<AtomTableModel*>(sender())) {
        for(Molecule& mol : *ptrToData.data()) {
            if(mol.uniqueID == blame->molUniqueID) {
                mol.atoms = blame->atoms();
            }
        }
    }
    if(qobject_cast<GraphicsView*>(sender()))
        emit dataUpdated(true);
    else
        emit dataUpdated(false);
}

void DataManager::setNextDataForAnimation()
{

}

void DataManager::testData() {
    Molecule m1;
    m1.position = QVector3D(0.0, 0.0, 0.0);
    m1.rotation = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 45.0);
    m1.name = "Molecule 1";
    m1.uniqueID = 0;
    m1.entityID = -1;
    // Adding atoms to the test molecule
    m1.atoms.append({0, -1, 6, QVector3D(0.0, 0.0, 0.0) });
    m1.atoms.append({1, -1, 1, QVector3D(1.0, 0.0, 0.0) });
    m1.atoms.append({2, -1, 1, QVector3D(0.0, 1.0, 0.0) });
    m1.atoms.append({3, -1, 1, QVector3D(0.0, 0.0, 1.0) });

    // Adding bonds to the test molecule
    m1.bonds.append({ 0, -1, 0, 1, 0 }); // Carbon - Hydrogen bond
    m1.bonds.append({ 1, -1, 0, 2, 1 }); // Carbon - Hydrogen bond
    m1.bonds.append({ 2, -1, 0, 3, 2 }); // Carbon - Hydrogen bond

    Molecule m2;
    m2.rotation = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 45.0);
    m2.position = QVector3D(0.0, 2.0, 2.0);
    m2.name = "Hello2";
    m2.uniqueID = 1;
    m2.entityID = -1;
    // Adding atoms to the test molecule
    m2.atoms.append({-1, -1, 6, QVector3D(0.0, 0.0, 0.0) });
    m2.atoms.append({-1, -1, 1, QVector3D(1.0, 0.0, 0.0) });
    m2.atoms.append({-1, -1, 1, QVector3D(0.0, 1.0, 0.0) });
    m2.atoms.append({-1, -1, 1, QVector3D(0.0, 0.0, 1.0) });

    // Adding bonds to the test molecule
    m2.bonds.append({ 0, -1, 0, 1, 1 }); // Carbon - Hydrogen bond
    m2.bonds.append({ 1, -1, 0, 2, 1 }); // Carbon - Hydrogen bond
    m2.bonds.append({ 2, -1, 0, 3, 1 }); // Carbon - Hydrogen bond

    // Adding the test molecule to the data
    ptrToData.data()->append(m1);
    //ptrToData.data()->append(m2);
}

