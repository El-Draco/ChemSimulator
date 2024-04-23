#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"
#include "graphicsview.h"
#include "moleculelistmodel.h"
#include "atomtablemodel.h"

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
    AtomTableModel *currentAtomTableModel = nullptr;
    GraphicsView *graphicsView;
    Ui::MainWindow *ui;
    DataManager *dataManager;

    QModelIndex currentSelectedMolecule;

public slots:
    void setupAtomTableWidget(const QItemSelection &, const QItemSelection &);

    void resetViewsAndModels(bool from3d);

};
#endif // MAINWINDOW_H
