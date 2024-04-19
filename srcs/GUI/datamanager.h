#ifndef DATAMANAGER_H
#define DATAMANAGER_H

    
#include <QQuaternion>
#include <QString>
#include <QVector3D>
#include <QSharedPointer>

struct Atom {
    int uniqueID;
    int entityID;
    QString name;
    int atomicNumber;
    double mass;
    QVector3D position;
};

struct Bond {
    int uniqueID;
    int entityID;
    int sourceAtomIndex;
    int targetAtomIndex;
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

Q_DECLARE_METATYPE(Atom)
Q_DECLARE_METATYPE(Molecule)


#endif // DATAMANAGER_H
