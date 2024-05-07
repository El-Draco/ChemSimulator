#include "bondtablemodel.h"

BondTableModel::BondTableModel(QObject *parent, QList<Bond> bonds)
    : QAbstractTableModel{parent}, m_bonds(bonds)
{}

int BondTableModel::rowCount(const QModelIndex& parent) const {
    return m_bonds.size();
}

int BondTableModel::columnCount(const QModelIndex& parent) const {
    return 3;
}

QVariant BondTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_bonds.size() || index.row() < 0) {
        return QVariant();
    }

    const Bond& bond = m_bonds.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        if (index.column() == 0) {
            return bond.sourceAtomID;
        } else if (index.column() == 1) {
            return bond.targetAtomID;
        } else if (index.column() == 2) {
            return bond.bondType;
        }
        break;
    case Qt::UserRole:
        if (index.column() == 0) {
            return bond.uniqueID;
        }
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant BondTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return "Source Atom";
        } else if (section == 1) {
            return "Target Atom";
        }else if (section == 2) {
            return "Bond Weight";
        }
    }
    return QVariant();
}

bool BondTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid()) return false;
    if (role != Qt::EditRole) return false;

    if(index.column() == 0) {
        if (!value.canConvert<int>()) return false;
        const int newSourceAtom = value.toInt();
        m_bonds[index.row()].sourceAtomID = newSourceAtom;
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 1) {
        if (!value.canConvert<int>()) return false;
        const int newTargetAtom = value.toInt();
        m_bonds[index.row()].targetAtomID = newTargetAtom;
        emit dataChanged(index, index);
        return true;
    }
    else if(index.column() == 2) {
        if (!value.canConvert<int>()) return false;
        const int newBondType = value.toInt();
        if((newBondType < 1) or (newBondType > 3)) return false;
        m_bonds[index.row()].bondType = newBondType;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags BondTableModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void BondTableModel::setBonds(QList<Bond> newBonds)
{
    beginResetModel();
    m_bonds = newBonds;
    endResetModel();
}

QList<Bond> BondTableModel::bonds() const
{
    return m_bonds;
}




