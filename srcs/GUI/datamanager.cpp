#include "datamanager.h"
#include "elements.h"
#include "atomtablemodel.h"
#include "bondtablemodel.h"
#include "graphicsview.h"
#include <QString>
#include <QHash>
#include <QFile>
#include <QFileInfo>
#include <QDir>

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

    mol->atoms.append({-1, -1, 1, 0, 0, QVector3D( 0.0, 0.0, 0.0) });
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

void DataManager::fromXYZ(QString filepath) {
    QList<Molecule> molecules;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList tokens = line.split(",");
        int numAtoms = tokens[0].toInt();

        Molecule molecule;
        molecule.uniqueID = -1;
        molecule.name = "M";
        molecule.atoms.reserve(numAtoms);


        // Read atom data
        for (int i = 0; i < numAtoms; ++i) {
            line = file.readLine();
            QStringList tokens = line.split(",");

            Atom atom;
            atom.uniqueID = i;
            atom.entityID = -1;
            atom.atomicNumber = tokens[1].toInt();
            atom.neutrons = tokens[2].toInt();
            atom.electrons = tokens[3].toInt();
            atom.position = QVector3D(tokens[4].toFloat(),
                                     tokens[5].toFloat(),
                                     tokens[6].toFloat());
            molecule.atoms.append(atom);
        }

        //Bonds
        int x = 0;
        for (int j = 0; j < numAtoms; ++j) {
            line = file.readLine();
            QStringList bondList = line.split(",");
            for (int k = j; k < numAtoms; ++k) {
                if (bondList[k].toInt() == 1) {
                    Bond bond;
                    bond.uniqueID = x;
                    x++;
                    bond.entityID = -1;
                    bond.sourceAtomID = j;
                    bond.targetAtomID = k;
                    bond.bondType = 1;
                    molecule.bonds.append(bond);
                }
            }
        }

        molecules.append(molecule);
    }

    file.close();
    ptrToData.data()->append(molecules);
    resetID();
    emit dataUpdated(false);
}

void DataManager::toXYZ(QString filePath, QList<int> molSelectionOrder) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QFileInfo fileInfo(filePath);
        QDir().mkpath(fileInfo.absolutePath());
        file.setFileName(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to create and open file for writing:" << filePath;
            return;
        }
    }

    QTextStream out(&file);


    for (int i: molSelectionOrder) {
        const Molecule& molecule = (*ptrToData.data()).at(i);
        out << molecule.atoms.size() << ", " << "0" << "\n";

        for (const Atom& atom : molecule.atoms) {
            out << getAtomicSymbol(atom.atomicNumber) << ", "
                << atom.atomicNumber << ", "
                << atom.neutrons << ", "
                << atom.electrons << ", "
                << atom.position.x() << ", " << atom.position.y() << ", " << atom.position.z() << "\n";
        }

        for (int i = 0; i < molecule.atoms.size(); ++i) {
            QStringList bondList;
            bondList.reserve(molecule.atoms.size());
            for (int j = 0; j < molecule.atoms.size(); ++j) {
                bool hasBond = false;
                for (const Bond& bond : molecule.bonds) {
                    if ((bond.sourceAtomID == i && bond.targetAtomID == j) ||
                        (bond.sourceAtomID == j && bond.targetAtomID == i)) {
                        hasBond = true;
                        break;
                    }
                }
                bondList << (hasBond ? "1" : "0");
            }
            out << bondList.join(", ") << "\n";
        }
    }

    file.close();
}



void DataManager::testData() {
    Molecule m1;
    m1.position = QVector3D(0.0, 0.0, 0.0);
    m1.rotation = QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 45.0);
    m1.name = "C2H5F";
    m1.uniqueID = 0;
    m1.entityID = -1;
    // Adding atoms to the test molecule
    m1.atoms.append({0, -1, 9, 0, 0, QVector3D( 1.2237000754, -0.1026271600,  0.0000000000) });
    m1.atoms.append({1, -1, 6, 0, 0, QVector3D(-0.0018701877,  0.5587356376,  0.0000000000) });
    m1.atoms.append({2, -1, 6, 0, 0, QVector3D(-1.1229785086, -0.4514445368,  0.0000000000) });
    m1.atoms.append({3, -1, 1, 0, 0, QVector3D(-2.0841665028,  0.0651911794,  0.0000000000) });
    m1.atoms.append({4, -1, 1, 0, 0, QVector3D(-0.0272678953,  1.1910421183,  0.8884701640) });
    m1.atoms.append({5, -1, 1, 0, 0, QVector3D(-0.0272678953,  1.1910421183, -0.8884701640) });
    m1.atoms.append({6, -1, 1, 0, 0, QVector3D(-1.0678055429, -1.0828676784,  0.8859444674) });
    m1.atoms.append({7, -1, 1, 0, 0, QVector3D(-1.0678055429, -1.0828676784, -0.8859444674) });

    // Adding bonds to the test molecule
    m1.bonds.append({ 0, -1, 0, 1, 1 });
    m1.bonds.append({ 1, -1, 1, 2, 1 });
    m1.bonds.append({ 2, -1, 1, 5, 1 });
    m1.bonds.append({ 3, -1, 1, 4, 1 });
    m1.bonds.append({ 4, -1, 2, 3, 1 });
    m1.bonds.append({ 5, -1, 2, 6, 1 });
    m1.bonds.append({ 6, -1, 2, 7, 1 });

    // Adding the test molecule to the data
    ptrToData.data()->append(m1);
}


