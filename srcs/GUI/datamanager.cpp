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

void DataManager::resetID() {
    int x = 0;
    for(Molecule& mol : *ptrToData.data()) {
        mol.uniqueID = x;
        x++;

        int y = 0;
        int z = 0;
        for(Atom& atom : mol.atoms) {
            atom.uniqueID = y;
            y++;
        }
        for(Bond& bond : mol.bonds) {
            bond.uniqueID = z;
            z++;
        }
    }
}

bool DataManager::deleteAtom(int id, int molId) {
    Molecule* mol = getMoleculeByUniqueID(molId);
    if (!mol) return false;

    int ind = -1;
    for (int i = 0; i < mol->atoms.size(); i++) {
        if(mol->atoms.at(i).uniqueID == id) {
            ind = i;
            break;
        }
    }

    if(ind == -1) return false;
    mol->atoms.removeAt(ind);

    int j = mol->bonds.size();
    for(int i = 0; i < j; i++) {
        if((mol->bonds.at(i).sourceAtomID == id) || (mol->bonds.at(i).targetAtomID == id)) {
            mol->bonds.removeAt(i);
            i--;
            j--;
        }
    }
    for(int i = 0; i < mol->bonds.size(); i++) {
        if(mol->bonds.at(i).sourceAtomID > id) {
            mol->bonds[i].sourceAtomID -= 1;
        }
        if(mol->bonds.at(i).targetAtomID > id) {
            mol->bonds[i].targetAtomID -= 1;
        }
    }

    resetID();
    emit dataUpdated(false);
    return true;
}

bool DataManager::addAtom(int molId) {
    Molecule* mol = getMoleculeByUniqueID(molId);
    if (!mol) return false;

    mol->atoms.append({-1, -1, 1, QVector3D( 0.0, 0.0, 0.0) });
    resetID();
    emit dataUpdated(false);
    return true;
}

bool DataManager::deleteBond(int id, int molId) {
    Molecule* mol = getMoleculeByUniqueID(molId);
    if (!mol) return false;

    int ind = -1;
    for (int i = 0; i < mol->bonds.size(); i++) {
        if(mol->bonds.at(i).uniqueID == id) {
            ind = i;
            break;
        }
    }

    if(ind == -1) return false;
    mol->bonds.removeAt(ind);

    resetID();
    emit dataUpdated(false);
}

bool DataManager::addBond(int molId) {
    Molecule* mol = getMoleculeByUniqueID(molId);
    if (!mol) return false;

    if(mol->atoms.size() < 2) return false;

    mol->bonds.append({ -1, -1, 0, 0, 0 });
    resetID();
    emit dataUpdated(false);
    return true;
}

bool DataManager::deleteMolecule(int id) {
    int ind = -1;
    for(int i = 0; i < (*ptrToData.data()).size(); i++) {
        if ((*ptrToData.data()).at(i).uniqueID == id) {
            ind = i;
            break;
        }
    }
    if (ind == -1) return false;

    (*ptrToData.data()).removeAt(ind);
    if ((*ptrToData.data()).empty()) {
        return addMolecule();
    }

    resetID();
    emit dataUpdated(false);
    return true;
}

bool DataManager::addMolecule() {
    Molecule m1;
    m1.position = QVector3D(0.0, 0.0, 0.0);
    m1.rotation = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 45.0);
    m1.name = "Empty Molecule";
    m1.uniqueID = -1;
    m1.entityID = -1;

    ptrToData.data()->append(m1);
    resetID();
    emit dataUpdated(false);
    return true;
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


