#include "moleculelistmodel.h"
#include <QVariant>

MoleculeListModel::MoleculeListModel(QObject *parent, QSharedPointer<QList<Molecule>> ptr)
    : QAbstractListModel(parent), ptrToData(ptr)
{}

int MoleculeListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return ptrToData.data()->size();
}

Qt::ItemFlags MoleculeListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MoleculeListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= ptrToData.data()->size() || index.row() < 0)
        return false;

    Molecule molecule = ptrToData.data()->at(index.row());

    if (role == PositionRole) {
        if (value.canConvert<QVector3D>()) {
            molecule.position = value.value<QVector3D>();
            emit dataChanged(index, index, {role});
            return true;
        }
    } else if (role == RotationRole) {
        if (value.canConvert<QQuaternion>()) {
            molecule.rotation = value.value<QQuaternion>();
            emit dataChanged(index, index, {role});
            return true;
        }
    } else if (role == UniqueIDRole) {
        if (value.canConvert<int>()) {
            molecule.uniqueID = value.value<int>();
            emit dataChanged(index, index, {role});
            return true;
        }
    }

    return false;
}

QVariant MoleculeListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= ptrToData.data()->size() || index.row() < 0)
        return QVariant();

    Molecule molecule = ptrToData.data()->at(index.row());

    if (role == PositionRole)
        return QVariant::fromValue(molecule.position);
    else if (role == RotationRole)
        return QVariant::fromValue(molecule.rotation);
    else if (role == UniqueIDRole)
        return QVariant::fromValue(molecule.uniqueID);
    else if (role == AtomsRole)
        return QVariant::fromValue(molecule.atoms);
    else if (role == Qt::DisplayRole)
        return QVariant::fromValue(molecule.name);

    return QVariant();
}

QHash<int, QByteArray> MoleculeListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[UniqueIDRole] = "uniqueID";
    roles[PositionRole] = "position";
    roles[RotationRole] = "rotation";
    roles[AtomsRole] = "atoms";
    return roles;
}

void MoleculeListModel::resetModel()
{
    beginResetModel();
    endResetModel();
}

