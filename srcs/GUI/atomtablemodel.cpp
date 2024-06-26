#include "atomtablemodel.h"

#include <QModelIndex>

AtomTableModel::AtomTableModel(QObject* parent, QList<Atom> atoms)
    : QAbstractTableModel(parent), m_atoms(atoms) {}

int AtomTableModel::rowCount(const QModelIndex& parent) const {
    return m_atoms.size();
}

int AtomTableModel::columnCount(const QModelIndex& parent) const {
    return 7;
}

QVariant AtomTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_atoms.size() || index.row() < 0) {
        return QVariant();
    }

    const Atom& atom = m_atoms.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        if (index.column() == 0) {
            return atom.uniqueID;
        } else if (index.column() == 1) {
            return atom.atomicNumber;
        } else if (index.column() == 2) {
            return atom.neutrons;
        } else if (index.column() == 3) {
            return atom.electrons;
        } else if (index.column() == 4) {
            return QString::number(atom.position.x(), 'f', 2);
        } else if (index.column() == 5) {
            return QString::number(atom.position.y(), 'f', 2);
        } else if (index.column() == 6) {
            return QString::number(atom.position.z(), 'f', 2);
        }
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant AtomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return "ID";
        } else if (section == 1) {
            return "Protons";
        }else if (section == 2) {
            return "Neutrons";
        } else if (section == 3) {
            return "Electrons";
        } else if (section == 4) {
            return "X";
        }else if (section == 5) {
            return "Y";
        }else if (section == 6) {
            return "Z";
        }
    }
    return QVariant();
}

bool AtomTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid()) return false;
    if (role != Qt::EditRole) return false;

    if(index.column() == 1) {
        if (!value.canConvert<int>()) return false;
        const int newAtomicNumber = value.toInt();
        if((newAtomicNumber < 1) | (newAtomicNumber > 118)) return false;

        m_atoms[index.row()].atomicNumber = newAtomicNumber;
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 2) {
        if (!value.canConvert<int>()) return false;

        const int newNeutrons = value.toInt();
        if((newNeutrons < 0) | (newNeutrons > (118+72))) return false;
        m_atoms[index.row()].neutrons = newNeutrons;
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 3) {
        if (!value.canConvert<int>()) return false;

        const int newElectrons = value.toInt();
        if((newElectrons < 0) | (newElectrons > (118+72))) return false;
        m_atoms[index.row()].electrons = newElectrons;
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 4) {
        if (!value.canConvert<float>()) return false;

        const float newX = value.toFloat();
        m_atoms[index.row()].position.setX(newX);
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 5) {
        if (!value.canConvert<float>()) return false;

        const float newY = value.toFloat();
        m_atoms[index.row()].position.setY(newY);
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 6) {
        if (!value.canConvert<float>()) return false;

        const float newZ = value.toFloat();
        m_atoms[index.row()].position.setZ(newZ);
        emit dataChanged(index, index);
        return true;
    }


    return false;
}

Qt::ItemFlags AtomTableModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid() && index.column() != 0) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void AtomTableModel::setAtoms(QList<Atom> newAtoms)
{
    beginResetModel();
    m_atoms = newAtoms;
    endResetModel();
}

QList<Atom> AtomTableModel::atoms() const
{
    return m_atoms;
}
