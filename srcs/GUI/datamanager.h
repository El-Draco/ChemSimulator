#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QQuaternion>
#include <QString>
#include <QVector3D>
#include <QSharedPointer>

struct Atom {
    int uniqueID;
    int entityID;
    QString name;
    int atomicNumber;
    QVector3D position;
};

struct Bond {
    int uniqueID;
    int entityID;
    int sourceAtomID;
    int targetAtomID;
    int bondType;
};

struct Molecule {
    int uniqueID;
    int entityID;
    QList<Atom> atoms;
    QList<Bond> bonds;
    QVector3D position;
    QQuaternion rotation;
    QString name;
};

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager(QObject *parent = nullptr);

    QSharedPointer<QList<Molecule>> getPtrToData() const;

    Molecule *getMoleculeByUniqueID(int);
    Atom *getAtomByUniqueID(int, Molecule &);
    Bond *getBondByUniqueID(int, Molecule &);

public slots:
    void dataChangeListener();

    void setNextDataForAnimation();

signals:
    void dataUpdated();

private:
    QSharedPointer<QList<Molecule>> ptrToData;
    void testData();
};

#endif // DATAMANAGER_H
