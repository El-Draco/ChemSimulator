#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"
#include "graphicsview.h"
#include "moleculelistmodel.h"
#include "atomtablemodel.h"
#include "bondtablemodel.h"

#include <QItemSelection>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MoleculeListModel *moleculeListModel;
    AtomTableModel *currentAtomTableModel;
    BondTableModel *currentBondTableModel;
    GraphicsView *graphicsView;
    Ui::MainWindow *ui;
    DataManager *dataManager;

    QModelIndex currentSelectedMolecule;

public slots:
    void setupAtomTableView(const QItemSelection &, const QItemSelection &);

    void resetViewsAndModels(bool from3d);

    void setupBondTableView(const QItemSelection &selected, const QItemSelection &deselected);

private slots:
    void on_viewAllButton_clicked();
    void on_addBond_clicked();
    void on_deleteBond_clicked();
    void on_addAtom_clicked();
    void on_deleteAtom_clicked();
    void on_addMolecule_clicked();
    void on_deleteMolecule_clicked();
    void on_actionAdd_Molecule_From_File_triggered();
};
#endif // MAINWINDOW_H
