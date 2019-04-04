#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    // set up UI connections

    // connect build mode radio button
    connect(ui->buildModeButton, SIGNAL(toggled(bool)), this, SLOT(slot_selectBuildMode(bool)));

    // connect grid dimension spin boxes
    connect(ui->dimX, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimX(int)));
    connect(ui->dimY, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimY(int)));
    connect(ui->dimZ, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimZ(int)));

    // set default dim values in mygl based on spinboxes
    slot_changeDimX(ui->dimX->value());
    slot_changeDimY(ui->dimY->value());
    slot_changeDimZ(ui->dimZ->value());

    // connect tileset list view
    connect(ui->tilesetList, SIGNAL(currentRowChanged(int)), this, SLOT(slot_changeTileset()));

    // populate tileset list view
    populateTilesetList();

    // select second item // TODO fix later
    ui->tilesetList->setCurrentRow(1);
    slot_changeTileset();

    // connect clear button
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(slot_clearWFC()));

    // connect run WFC button
    connect(ui->runWFCButton, SIGNAL(clicked(bool)), this, SLOT(slot_runWFC()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::slot_selectBuildMode(bool buildMode) {
    ui->mygl->setBuildMode(buildMode);
    ui->runWFCButton->setEnabled(!buildMode);
}

void MainWindow::slot_changeDimX(int x) {
    ui->mygl->setDimX(x);
}

void MainWindow::slot_changeDimY(int y) {
    ui->mygl->setDimY(y);
}

void MainWindow::slot_changeDimZ(int z) {
    ui->mygl->setDimZ(z);
}

void MainWindow::slot_changeTileset() {
    std::string tileset = ui->tilesetList->currentItem()->text().toStdString();
    ui->mygl->setTileset(tileset);
}

void MainWindow::slot_runWFC() {
    ui->mygl->runWFC();
}

void MainWindow::slot_clearWFC() {
    ui->mygl->clearWFC();
}

void MainWindow::populateTilesetList() {
    // populate list view with jsons in json folder
    // TODO: why did I do this
    QDir currPath = QDir::currentPath();
    currPath.cdUp();
    currPath.cdUp();
    currPath.cdUp();
    currPath.cdUp();
    QDir dir = QDir(currPath.absolutePath() + "/WFC/json");
    QStringList jsons = dir.entryList(QStringList() << "*.json", QDir::Files);

    foreach (QString filename, jsons) {
        filename.chop(5); // remove ".json" from end
        ui->tilesetList->addItem(filename);
    }
}

