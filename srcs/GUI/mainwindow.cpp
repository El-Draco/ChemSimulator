#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QVariant>

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

    //setup qt3dwindow for drawing graphics
    graphicsView = new GraphicsView(this, dataManager);
    QWidget *container = QWidget::createWindowContainer(graphicsView);
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

    //setup list view
    ui->listView->setModel(moleculeListModel);
    ui->listView->setAlternatingRowColors(true);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->listView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::setupAtomTableWidget);

    ui->listView->selectionModel()->select(moleculeListModel->index(0), QItemSelectionModel::Select);  // Line 45
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupAtomTableWidget(const QItemSelection &selected, const QItemSelection &deselected)
{
    currentSelectedMolecule = selected.indexes().first();
    auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::AtomsRole);
    QList<Atom> atoms = qvariant.value<QList<Atom>>();

    currentAtomTableModel = new AtomTableModel(nullptr, atoms);
    currentAtomTableModel->molUniqueID = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole).toInt();
    connect(currentAtomTableModel,
            &AtomTableModel::dataChanged,
            dataManager,
            &DataManager::dataChangeListener);

    ui->tableView->setModel(currentAtomTableModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::resetViewsAndModels(bool from3d)
{
    moleculeListModel->resetModel();

    if(currentAtomTableModel) {
        auto qvariant = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::AtomsRole);
        QList<Atom> atoms = qvariant.value<QList<Atom>>();
        currentAtomTableModel->setAtoms(atoms);
        currentAtomTableModel->molUniqueID = moleculeListModel->data(currentSelectedMolecule, MoleculeListModel::UniqueIDRole).toInt();
    }

    if(!from3d)
        graphicsView->drawFromData();
}

// void MainWindow::on_actionOpen_triggered()
// {
//     QString fileName = QFileDialog::getOpenFileName(this, tr("Open XYZ File"), "", tr("XYZ Files (*.xyz)"));
//     if (!fileName.isEmpty()) {
//         QFile file(fileName);
//         if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//             QList<Molecule> molecules;

//             QTextStream in(&file);
//             while (!in.atEnd()) {
//                 QString line = in.readLine();
//                 // Parse XYZ file line by line and extract molecule data
//                 //QStringList tokens = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
//                 if (true) {//tokens.size() >= 4) {
//                     Molecule molecule;
//                     //molecule.setName(tokens[0]);
//                     //molecule.setPosition(QVector3D(tokens[1].toFloat(), tokens[2].toFloat(), tokens[3].toFloat()));
//                     molecules.append(molecule);
//                 }
//             }
//             file.close();
//             //populateMoleculeModel();
//         }
//     }
// }




