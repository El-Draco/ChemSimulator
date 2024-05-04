#ifndef BONDTABLEMODEL_H
#define BONDTABLEMODEL_H

#include <QAbstractTableModel>
#include "datamanager.h"

class BondTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BondTableModel(QObject *parent, QList<Bond> bonds);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setBonds(QList<Bond>);

    QList<Bond> bonds() const;

    int molUniqueID = -1;

private:
    QList<Bond> m_bonds;
};

#endif // BONDTABLEMODEL_H
