/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Molecule_From_File;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *deleteMolecule;
    QPushButton *addMolecule;
    QListView *listView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *deleteAtom;
    QPushButton *addAtom;
    QTableView *atomView;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *deleteBond;
    QPushButton *addBond;
    QTableView *bondView;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QWidget *graphicsWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *controlsWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *viewAllButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(834, 600);
        MainWindow->setAutoFillBackground(true);
        actionAdd_Molecule_From_File = new QAction(MainWindow);
        actionAdd_Molecule_From_File->setObjectName(QString::fromUtf8("actionAdd_Molecule_From_File"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(300, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        deleteMolecule = new QPushButton(widget_2);
        deleteMolecule->setObjectName(QString::fromUtf8("deleteMolecule"));

        horizontalLayout_3->addWidget(deleteMolecule);

        addMolecule = new QPushButton(widget_2);
        addMolecule->setObjectName(QString::fromUtf8("addMolecule"));

        horizontalLayout_3->addWidget(addMolecule);


        verticalLayout_3->addWidget(widget_2);

        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_3->addWidget(listView);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        widget_3 = new QWidget(groupBox_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        deleteAtom = new QPushButton(widget_3);
        deleteAtom->setObjectName(QString::fromUtf8("deleteAtom"));

        horizontalLayout_4->addWidget(deleteAtom);

        addAtom = new QPushButton(widget_3);
        addAtom->setObjectName(QString::fromUtf8("addAtom"));

        horizontalLayout_4->addWidget(addAtom);


        verticalLayout_4->addWidget(widget_3);

        atomView = new QTableView(groupBox_2);
        atomView->setObjectName(QString::fromUtf8("atomView"));

        verticalLayout_4->addWidget(atomView);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 5, 5, 5);
        widget_4 = new QWidget(groupBox_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_5 = new QHBoxLayout(widget_4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        deleteBond = new QPushButton(widget_4);
        deleteBond->setObjectName(QString::fromUtf8("deleteBond"));

        horizontalLayout_5->addWidget(deleteBond);

        addBond = new QPushButton(widget_4);
        addBond->setObjectName(QString::fromUtf8("addBond"));

        horizontalLayout_5->addWidget(addBond);


        verticalLayout_5->addWidget(widget_4);

        bondView = new QTableView(groupBox_3);
        bondView->setObjectName(QString::fromUtf8("bondView"));

        verticalLayout_5->addWidget(bondView);


        verticalLayout->addWidget(groupBox_3);


        horizontalLayout->addWidget(widget);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        graphicsWidget = new QWidget(groupBox_4);
        graphicsWidget->setObjectName(QString::fromUtf8("graphicsWidget"));
        graphicsWidget->setMinimumSize(QSize(550, 0));
        verticalLayout_2 = new QVBoxLayout(graphicsWidget);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        controlsWidget = new QWidget(graphicsWidget);
        controlsWidget->setObjectName(QString::fromUtf8("controlsWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlsWidget->sizePolicy().hasHeightForWidth());
        controlsWidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(controlsWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        viewAllButton = new QPushButton(controlsWidget);
        viewAllButton->setObjectName(QString::fromUtf8("viewAllButton"));

        horizontalLayout_2->addWidget(viewAllButton);

        horizontalSpacer = new QSpacerItem(460, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(controlsWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addWidget(controlsWidget);


        verticalLayout_6->addWidget(graphicsWidget);


        horizontalLayout->addWidget(groupBox_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 834, 21));
        menubar->setAutoFillBackground(true);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setAutoFillBackground(true);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionAdd_Molecule_From_File);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ChemSim", nullptr));
        actionAdd_Molecule_From_File->setText(QCoreApplication::translate("MainWindow", "Add Molecule From File", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Molecules", nullptr));
        deleteMolecule->setText(QCoreApplication::translate("MainWindow", "Delete Molecule", nullptr));
        addMolecule->setText(QCoreApplication::translate("MainWindow", "Add Molecule", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Atoms", nullptr));
        deleteAtom->setText(QCoreApplication::translate("MainWindow", "Delete Atom", nullptr));
        addAtom->setText(QCoreApplication::translate("MainWindow", "Add Atom", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Bonds", nullptr));
        deleteBond->setText(QCoreApplication::translate("MainWindow", "Delete Bond", nullptr));
        addBond->setText(QCoreApplication::translate("MainWindow", "Add Bond", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
        viewAllButton->setText(QCoreApplication::translate("MainWindow", "View All", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start \342\217\265", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
