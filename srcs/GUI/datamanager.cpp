#include "datamanager.h"

#include "atomtablemodel.h"
#include "bondtablemodel.h"
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
    else if(auto blame = qobject_cast<BondTableModel*>(sender())) {
        for(Molecule& mol : *ptrToData.data()) {
            if(mol.uniqueID == blame->molUniqueID) {
                mol.bonds = blame->bonds();
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
    m1.name = "C2H5F";
    m1.uniqueID = 0;
    m1.entityID = -1;
    // Adding atoms to the test molecule
    m1.atoms.append({0, -1, 9, QVector3D( 1.2237000754, -0.1026271600,  0.0000000000) });
    m1.atoms.append({1, -1, 6, QVector3D(-0.0018701877,  0.5587356376,  0.0000000000) });
    m1.atoms.append({2, -1, 6, QVector3D(-1.1229785086, -0.4514445368,  0.0000000000) });
    m1.atoms.append({3, -1, 1, QVector3D(-2.0841665028,  0.0651911794,  0.0000000000) });
    m1.atoms.append({4, -1, 1, QVector3D(-0.0272678953,  1.1910421183,  0.8884701640) });
    m1.atoms.append({5, -1, 1, QVector3D(-0.0272678953,  1.1910421183, -0.8884701640) });
    m1.atoms.append({6, -1, 1, QVector3D(-1.0678055429, -1.0828676784,  0.8859444674) });
    m1.atoms.append({7, -1, 1, QVector3D(-1.0678055429, -1.0828676784, -0.8859444674) });

    // Adding bonds to the test molecule
    m1.bonds.append({ 0, -1, 0, 1, 0 });
    m1.bonds.append({ 1, -1, 1, 2, 0 });
    m1.bonds.append({ 2, -1, 1, 5, 0 });
    m1.bonds.append({ 3, -1, 1, 4, 0 });
    m1.bonds.append({ 4, -1, 2, 3, 0 });
    m1.bonds.append({ 5, -1, 2, 6, 0 });
    m1.bonds.append({ 6, -1, 2, 7, 0 });

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

