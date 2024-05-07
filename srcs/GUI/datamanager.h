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
    int atomicNumber;
    int neutrons;
    int electrons;
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

    bool deleteAtom(int id, int molId);
    bool deleteBond(int id, int molId);
    void resetID();
    bool addBond(int molId);
    bool addAtom(int molId);
    bool deleteMolecule(int id);
    bool addMolecule();
    void fromXYZ(QString filepath);
    void toXYZ(QString filePath, QList<int> molSelectionOrder);
public slots:
    void dataChangeListener();

    void setNextDataForAnimation();

signals:
    void dataUpdated(bool from3d);

private:
    QSharedPointer<QList<Molecule>> ptrToData;
    void testData();
};

#endif // DATAMANAGER_H
