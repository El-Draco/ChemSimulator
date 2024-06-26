#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QVariant>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataManager = new DataManager(nullptr);
    connect(dataManager,
            &DataManager::dataUpdated,
            this,
            &MainWindow::resetViewsAndModels);

    ui->simTypeComboBox->insertItem(0, "SN1");
    ui->simTypeComboBox->insertItem(1, "SN2");

    //setup qt3dwindow for drawing graphics
    graphicsView = new GraphicsView(this, dataManager);
    QWidget *container = QWidget::createWindowContainer(graphicsView);
    container->setMinimumHeight(400);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->graphicsWidget->layout()->addWidget(container);
    connect(graphicsView,
            &GraphicsView::potentialDataChange,
            dataManager,
            &DataManager::dataChangeListener);

    //set up list model for list view
    moleculeListModel = new MoleculeListModel(nullptr, dataManager->getPtrToData());
    connect(moleculeListModel,
            &MoleculeListModel::dataChanged,
            dataManager,
            &DataManager::dataChangeListener);

    ui->substrateComboBox->setModel(moleculeListModel);
    ui->nucleoComboBox->setModel(moleculeListModel);
    ui->solventComboBox->setModel(moleculeListModel);

    //setup list view
    ui->listView->setModel(moleculeListModel);
    ui->listView->setAlternatingRowColors(true);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->listView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::setupAtomTableView);
    connect(ui->listView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::setupBondTableView);
    connect(ui->listView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            graphicsView,
            &GraphicsView::showMolecule);


    ui->listView->selectionModel()->select(moleculeListModel->index(0), QItemSelectionModel::Select);  // Line 45
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::validateMoleculeSelection(int index) {

}

void MainWindow::setupAtomTableView(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(selected.empty()) {
        ui->listView->selectionModel()->select(moleculeListModel->index(0), QItemSelectionModel::Select);
        return;
    }
    currentSelectedMolecule = selected.indexes().first();

    auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::AtomsRole);
    QList<Atom> atoms = qvariant.value<QList<Atom>>();

    currentAtomTableModel = new AtomTableModel(nullptr, atoms);
    currentAtomTableModel->molUniqueID = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole).toInt();
    connect(currentAtomTableModel,
            &AtomTableModel::dataChanged,
            dataManager,
            &DataManager::dataChangeListener);

    ui->atomView->setModel(currentAtomTableModel);
    ui->atomView->setAlternatingRowColors(true);
    ui->atomView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->atomView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->atomView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::setupBondTableView(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(selected.empty()) {
        ui->listView->selectionModel()->select(moleculeListModel->index(0), QItemSelectionModel::Select);
        return;
    }
    auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::BondsRole);
    QList<Bond> bonds = qvariant.value<QList<Bond>>();

    currentBondTableModel = new BondTableModel(nullptr, bonds);
    currentBondTableModel->molUniqueID = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole).toInt();
    connect(currentBondTableModel,
            &BondTableModel::dataChanged,
            dataManager,
            &DataManager::dataChangeListener);

    ui->bondView->setModel(currentBondTableModel);
    ui->bondView->setAlternatingRowColors(true);
    ui->bondView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->bondView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bondView->setSelectionMode(QAbstractItemView::SingleSelection);
}


void MainWindow::resetViewsAndModels(bool from3d)
{
    moleculeListModel->resetModel();


    if(currentAtomTableModel) {
        auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::AtomsRole);
        QList<Atom> atoms = qvariant.value<QList<Atom>>();
        currentAtomTableModel->setAtoms(atoms);
    }

    if(currentBondTableModel) {
        auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::BondsRole);
        QList<Bond> bonds = qvariant.value<QList<Bond>>();
        currentBondTableModel->setBonds(bonds);
    }

    if(!from3d)
        graphicsView->drawFromData();
}


void MainWindow::on_viewAllButton_clicked()
{
    graphicsView->viewAll();
}

void MainWindow::on_addBond_clicked()
{
    QVariant molid = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole);
    dataManager->addBond(molid.value<int>());
}

void MainWindow::on_deleteBond_clicked()
{
    QItemSelectionModel* selectionModel = ui->bondView->selectionModel();
    if (!selectionModel->hasSelection()) return;

    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    QModelIndex index = selectedIndexes.at(0);
    QVariant bondid = currentBondTableModel->data(index, Qt::UserRole);

    QVariant molid = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole);

    qDebug() << bondid << molid;

    dataManager->deleteBond(bondid.value<int>(), molid.value<int>());
}


void MainWindow::on_addAtom_clicked()
{
    QVariant molid = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole);
    dataManager->addAtom(molid.value<int>());
}


void MainWindow::on_deleteAtom_clicked()
{
    QItemSelectionModel* selectionModel = ui->atomView->selectionModel();
    if (!selectionModel->hasSelection()) return;

    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    QModelIndex index = selectedIndexes.at(0);
    QVariant atomid = index.model()->data(index.model()->index(index.row(), 0));

    QVariant molid = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole);

    dataManager->deleteAtom(atomid.value<int>(), molid.value<int>());
}


void MainWindow::on_addMolecule_clicked()
{
    dataManager->addMolecule();
}


void MainWindow::on_deleteMolecule_clicked()
{
    QVariant molid = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole);
    dataManager->deleteMolecule(molid.value<int>());
}


void MainWindow::on_actionAdd_Molecule_From_File_triggered()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filepath = QFileDialog::getOpenFileName(this, "Add Molecule From File", desktopPath);
    dataManager->fromXYZ(filepath);
}


void MainWindow::on_startButton_clicked()
{
    int substrate = ui->substrateComboBox->currentIndex();
    int nucleo = ui->nucleoComboBox->currentIndex();
    int solvent = ui->solventComboBox->currentIndex();

    if (substrate == nucleo) {
        ui->statusbar->showMessage("Error: The substrate and neuclophilic molecule can not be the same.");
        QPalette errorPalette;
        errorPalette.setColor(QPalette::WindowText, Qt::red);
        auto originalPalatte = ui->statusbar->palette();
        ui->statusbar->setPalette(errorPalette);

        auto statusTimer = new QTimer(this);
        connect(statusTimer, &QTimer::timeout, this, [this, originalPalatte]() {
            ui->statusbar->clearMessage();
            ui->statusbar->setPalette(originalPalatte);
        });

        statusTimer->setInterval(5000);
        statusTimer->start();

        return;
    }

    //int doMonteCarlo = ui->monteCarloCheckBox;
    //int
}


void MainWindow::on_actionExport_Molecules_To_File_triggered()
{
    QList<int> molSelectionOrder;
    molSelectionOrder.append(ui->substrateComboBox->currentIndex());
    molSelectionOrder.append(ui->nucleoComboBox->currentIndex());
    molSelectionOrder.append(ui->solventComboBox->currentIndex());

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filepath = QFileDialog::getSaveFileName(this, "Export Molecules To File", desktopPath);

    dataManager->toXYZ(filepath, molSelectionOrder);
}

