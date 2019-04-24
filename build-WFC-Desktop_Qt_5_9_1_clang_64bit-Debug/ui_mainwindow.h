/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "mygl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionCamera_Controls;
    QWidget *centralWidget;
    MyGL *mygl;
    QLabel *dimLabel;
    QLabel *dimXLabel;
    QLabel *dimYLabel;
    QLabel *dimZLabel;
    QSpinBox *dimX;
    QSpinBox *dimY;
    QSpinBox *dimZ;
    QLabel *tilesetLabel;
    QPushButton *runWFCButton;
    QListWidget *tilesetList;
    QPushButton *clearButton;
    QLabel *tileLabel;
    QListWidget *tileList;
    QPushButton *clearNonUserTilesButton;
    QLabel *boundaryConditionsLabel;
    QCheckBox *visualizeEmptiesCheckBox;
    QLabel *errorLabel;
    QRadioButton *periodicRadioButton;
    QRadioButton *cleanRadioButton;
    QRadioButton *noneRadioButton;
    QCheckBox *buildModeCheckBox;
    QCheckBox *showPreviewCheckBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1087, 727);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionCamera_Controls = new QAction(MainWindow);
        actionCamera_Controls->setObjectName(QStringLiteral("actionCamera_Controls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QStringLiteral("mygl"));
        mygl->setGeometry(QRect(11, 11, 711, 681));
        mygl->setFocusPolicy(Qt::ClickFocus);
        dimLabel = new QLabel(centralWidget);
        dimLabel->setObjectName(QStringLiteral("dimLabel"));
        dimLabel->setGeometry(QRect(750, 110, 81, 16));
        dimXLabel = new QLabel(centralWidget);
        dimXLabel->setObjectName(QStringLiteral("dimXLabel"));
        dimXLabel->setGeometry(QRect(750, 130, 16, 16));
        dimYLabel = new QLabel(centralWidget);
        dimYLabel->setObjectName(QStringLiteral("dimYLabel"));
        dimYLabel->setGeometry(QRect(750, 160, 16, 16));
        dimZLabel = new QLabel(centralWidget);
        dimZLabel->setObjectName(QStringLiteral("dimZLabel"));
        dimZLabel->setGeometry(QRect(750, 190, 16, 16));
        dimX = new QSpinBox(centralWidget);
        dimX->setObjectName(QStringLiteral("dimX"));
        dimX->setGeometry(QRect(770, 130, 48, 24));
        dimX->setMinimum(1);
        dimX->setMaximum(30);
        dimX->setValue(2);
        dimY = new QSpinBox(centralWidget);
        dimY->setObjectName(QStringLiteral("dimY"));
        dimY->setGeometry(QRect(770, 160, 48, 24));
        dimY->setMinimum(1);
        dimY->setMaximum(30);
        dimY->setValue(2);
        dimZ = new QSpinBox(centralWidget);
        dimZ->setObjectName(QStringLiteral("dimZ"));
        dimZ->setGeometry(QRect(770, 190, 48, 24));
        dimZ->setMinimum(1);
        dimZ->setMaximum(30);
        dimZ->setValue(2);
        tilesetLabel = new QLabel(centralWidget);
        tilesetLabel->setObjectName(QStringLiteral("tilesetLabel"));
        tilesetLabel->setGeometry(QRect(740, 260, 60, 16));
        runWFCButton = new QPushButton(centralWidget);
        runWFCButton->setObjectName(QStringLiteral("runWFCButton"));
        runWFCButton->setGeometry(QRect(742, 660, 141, 32));
        tilesetList = new QListWidget(centralWidget);
        tilesetList->setObjectName(QStringLiteral("tilesetList"));
        tilesetList->setGeometry(QRect(740, 280, 141, 121));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setEnabled(true);
        clearButton->setGeometry(QRect(742, 580, 141, 32));
        tileLabel = new QLabel(centralWidget);
        tileLabel->setObjectName(QStringLiteral("tileLabel"));
        tileLabel->setGeometry(QRect(740, 420, 60, 16));
        tileList = new QListWidget(centralWidget);
        tileList->setObjectName(QStringLiteral("tileList"));
        tileList->setGeometry(QRect(740, 440, 141, 121));
        clearNonUserTilesButton = new QPushButton(centralWidget);
        clearNonUserTilesButton->setObjectName(QStringLiteral("clearNonUserTilesButton"));
        clearNonUserTilesButton->setEnabled(true);
        clearNonUserTilesButton->setGeometry(QRect(740, 620, 141, 32));
        boundaryConditionsLabel = new QLabel(centralWidget);
        boundaryConditionsLabel->setObjectName(QStringLiteral("boundaryConditionsLabel"));
        boundaryConditionsLabel->setGeometry(QRect(900, 110, 131, 16));
        visualizeEmptiesCheckBox = new QCheckBox(centralWidget);
        visualizeEmptiesCheckBox->setObjectName(QStringLiteral("visualizeEmptiesCheckBox"));
        visualizeEmptiesCheckBox->setGeometry(QRect(760, 50, 311, 20));
        errorLabel = new QLabel(centralWidget);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setGeometry(QRect(930, 670, 131, 16));
        QPalette palette;
        QBrush brush(QColor(252, 0, 9, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(252, 0, 6, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        errorLabel->setPalette(palette);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        errorLabel->setFont(font);
        periodicRadioButton = new QRadioButton(centralWidget);
        periodicRadioButton->setObjectName(QStringLiteral("periodicRadioButton"));
        periodicRadioButton->setGeometry(QRect(910, 160, 100, 20));
        cleanRadioButton = new QRadioButton(centralWidget);
        cleanRadioButton->setObjectName(QStringLiteral("cleanRadioButton"));
        cleanRadioButton->setGeometry(QRect(910, 130, 100, 20));
        cleanRadioButton->setChecked(true);
        noneRadioButton = new QRadioButton(centralWidget);
        noneRadioButton->setObjectName(QStringLiteral("noneRadioButton"));
        noneRadioButton->setGeometry(QRect(910, 190, 100, 20));
        buildModeCheckBox = new QCheckBox(centralWidget);
        buildModeCheckBox->setObjectName(QStringLiteral("buildModeCheckBox"));
        buildModeCheckBox->setGeometry(QRect(740, 30, 87, 20));
        showPreviewCheckBox = new QCheckBox(centralWidget);
        showPreviewCheckBox->setObjectName(QStringLiteral("showPreviewCheckBox"));
        showPreviewCheckBox->setGeometry(QRect(910, 220, 171, 20));
        showPreviewCheckBox->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1087, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionCamera_Controls);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenGLDemo", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCamera_Controls->setText(QApplication::translate("MainWindow", "Camera Controls", Q_NULLPTR));
        dimLabel->setText(QApplication::translate("MainWindow", "Dimensions", Q_NULLPTR));
        dimXLabel->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        dimYLabel->setText(QApplication::translate("MainWindow", "y", Q_NULLPTR));
        dimZLabel->setText(QApplication::translate("MainWindow", "z", Q_NULLPTR));
        tilesetLabel->setText(QApplication::translate("MainWindow", "Tileset", Q_NULLPTR));
        runWFCButton->setText(QApplication::translate("MainWindow", "Run WFC", Q_NULLPTR));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        tileLabel->setText(QApplication::translate("MainWindow", "Tiles", Q_NULLPTR));
        clearNonUserTilesButton->setText(QApplication::translate("MainWindow", "Clear non-user tiles", Q_NULLPTR));
        boundaryConditionsLabel->setText(QApplication::translate("MainWindow", "Boundary Conditions", Q_NULLPTR));
        visualizeEmptiesCheckBox->setText(QApplication::translate("MainWindow", "Visualize user-placed empty tiles in build mode", Q_NULLPTR));
        errorLabel->setText(QString());
        periodicRadioButton->setText(QApplication::translate("MainWindow", "Periodic", Q_NULLPTR));
        cleanRadioButton->setText(QApplication::translate("MainWindow", "Clean", Q_NULLPTR));
        noneRadioButton->setText(QApplication::translate("MainWindow", "None", Q_NULLPTR));
        buildModeCheckBox->setText(QApplication::translate("MainWindow", "Build mode", Q_NULLPTR));
        showPreviewCheckBox->setText(QApplication::translate("MainWindow", "Repeat structure", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
