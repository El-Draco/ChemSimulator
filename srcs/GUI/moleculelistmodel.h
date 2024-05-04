#ifndef MOLECULELISTMODEL_H
#define MOLECULELISTMODEL_H

#include <QAbstractListModel>
#include <Qt3DCore/QTransform>
#include <QList>

#include "datamanager.h"

class MoleculeListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit MoleculeListModel(QObject*parent, QSharedPointer<QList<Molecule>> ptr);

    enum MoleculeRoles {
        PositionRole = Qt::UserRole + 1,
        RotationRole,
        UniqueIDRole,
        AtomsRole,
        BondsRole
    };

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QModelIndex* currentSelected;

    void resetModel();


private:
    QSharedPointer<QList<Molecule>> ptrToData;
};

#endif // MOLECULELISTMODEL_H
