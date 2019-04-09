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
    QRadioButton *buildModeButton;
    QLabel *tileLabel;
    QListWidget *tileList;
    QPushButton *clearNonUserTilesButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(932, 676);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionCamera_Controls = new QAction(MainWindow);
        actionCamera_Controls->setObjectName(QStringLiteral("actionCamera_Controls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QStringLiteral("mygl"));
        mygl->setGeometry(QRect(11, 11, 711, 631));
        mygl->setFocusPolicy(Qt::ClickFocus);
        dimLabel = new QLabel(centralWidget);
        dimLabel->setObjectName(QStringLiteral("dimLabel"));
        dimLabel->setGeometry(QRect(760, 80, 81, 16));
        dimXLabel = new QLabel(centralWidget);
        dimXLabel->setObjectName(QStringLiteral("dimXLabel"));
        dimXLabel->setGeometry(QRect(760, 100, 16, 16));
        dimYLabel = new QLabel(centralWidget);
        dimYLabel->setObjectName(QStringLiteral("dimYLabel"));
        dimYLabel->setGeometry(QRect(760, 130, 16, 16));
        dimZLabel = new QLabel(centralWidget);
        dimZLabel->setObjectName(QStringLiteral("dimZLabel"));
        dimZLabel->setGeometry(QRect(760, 160, 16, 16));
        dimX = new QSpinBox(centralWidget);
        dimX->setObjectName(QStringLiteral("dimX"));
        dimX->setGeometry(QRect(780, 100, 48, 24));
        dimX->setMaximum(30);
        dimX->setValue(2);
        dimY = new QSpinBox(centralWidget);
        dimY->setObjectName(QStringLiteral("dimY"));
        dimY->setGeometry(QRect(780, 130, 48, 24));
        dimY->setMaximum(30);
        dimY->setValue(2);
        dimZ = new QSpinBox(centralWidget);
        dimZ->setObjectName(QStringLiteral("dimZ"));
        dimZ->setGeometry(QRect(780, 160, 48, 24));
        dimZ->setMaximum(30);
        dimZ->setValue(2);
        tilesetLabel = new QLabel(centralWidget);
        tilesetLabel->setObjectName(QStringLiteral("tilesetLabel"));
        tilesetLabel->setGeometry(QRect(740, 210, 60, 16));
        runWFCButton = new QPushButton(centralWidget);
        runWFCButton->setObjectName(QStringLiteral("runWFCButton"));
        runWFCButton->setGeometry(QRect(760, 610, 141, 32));
        tilesetList = new QListWidget(centralWidget);
        tilesetList->setObjectName(QStringLiteral("tilesetList"));
        tilesetList->setGeometry(QRect(740, 230, 171, 121));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setEnabled(false);
        clearButton->setGeometry(QRect(760, 530, 141, 32));
        buildModeButton = new QRadioButton(centralWidget);
        buildModeButton->setObjectName(QStringLiteral("buildModeButton"));
        buildModeButton->setGeometry(QRect(740, 30, 131, 20));
        tileLabel = new QLabel(centralWidget);
        tileLabel->setObjectName(QStringLiteral("tileLabel"));
        tileLabel->setGeometry(QRect(740, 370, 60, 16));
        tileList = new QListWidget(centralWidget);
        tileList->setObjectName(QStringLiteral("tileList"));
        tileList->setGeometry(QRect(740, 390, 171, 121));
        clearNonUserTilesButton = new QPushButton(centralWidget);
        clearNonUserTilesButton->setObjectName(QStringLiteral("clearNonUserTilesButton"));
        clearNonUserTilesButton->setGeometry(QRect(758, 570, 141, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 932, 22));
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
        buildModeButton->setText(QApplication::translate("MainWindow", "Build mode", Q_NULLPTR));
        tileLabel->setText(QApplication::translate("MainWindow", "Tiles", Q_NULLPTR));
        clearNonUserTilesButton->setText(QApplication::translate("MainWindow", "Clear non-user tiles", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
