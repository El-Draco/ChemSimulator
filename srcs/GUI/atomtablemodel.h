#ifndef ATOMTABLEMODEL_H
#define ATOMTABLEMODEL_H

#include <QAbstractTableModel>
#include "datamanager.h"

class AtomTableModel : public QAbstractTableModel {
    Q_OBJECT

public:

    explicit AtomTableModel(QObject* parent, QList<Atom> atoms);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setAtoms(QList<Atom>);

    QList<Atom> atoms() const;

    int molUniqueID = -1;

private:
    QList<Atom> m_atoms;
};


#endif // ATOMTABLEMODEL_H
