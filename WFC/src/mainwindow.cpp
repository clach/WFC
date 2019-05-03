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

    // connect build mode check box
    connect(ui->buildModeCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_setBuildMode(bool)));
    slot_setBuildMode(ui->buildModeCheckBox->isChecked());

    // connect grid dimension spin boxes
    connect(ui->dimX, SIGNAL(valueChanged(int)), this, SLOT(slot_setDimX(int)));
    connect(ui->dimY, SIGNAL(valueChanged(int)), this, SLOT(slot_setDimY(int)));
    connect(ui->dimZ, SIGNAL(valueChanged(int)), this, SLOT(slot_setDimZ(int)));

    // set default dim values in mygl based on spinboxes
    slot_setDimX(ui->dimX->value());
    slot_setDimY(ui->dimY->value());
    slot_setDimZ(ui->dimZ->value());

    // connect periodic check box
    connect(ui->periodicRadioButton, SIGNAL(toggled(bool)), this, SLOT(slot_setPeriodic(bool)));
    slot_setPeriodic(ui->periodicRadioButton->isChecked());

    connect(ui->showPreviewCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_setPeriodicPreview(bool)));

    // connect sky/clean boundary check box
    connect(ui->cleanRadioButton, SIGNAL(toggled(bool)), this, SLOT(slot_setClean(bool)));
    slot_setClean(ui->cleanRadioButton->isChecked());

    // connect no boundary conditions check box
    connect(ui->noneRadioButton, SIGNAL(toggled(bool)), this, SLOT(slot_setNone(bool)));
    slot_setClean(ui->cleanRadioButton->isChecked());

    // connect tileset list view
    connect(ui->tilesetList, SIGNAL(currentRowChanged(int)), this, SLOT(slot_setTileset()));

    // connect tileset tree view
    //connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(slot_setTileset2(QTreeWidgetItem*)));

    // populate tileset list view
    populateTilesetList();
    //populateTilesetList2();

    // connect tile list view
    connect(ui->tileList, SIGNAL(currentRowChanged(int)), this, SLOT(slot_setTile()));

    // connect clear button
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(slot_clearTileGrid()));

    // connect clear non-user placed tiles button
    connect(ui->clearNonUserTilesButton, SIGNAL(clicked(bool)), this, SLOT(slot_clearNonUserTiles()));

    // connect run WFC button
    connect(ui->runWFCButton, SIGNAL(clicked(bool)), this, SLOT(slot_runWFC()));

    // connect run iterative WFC button
    connect(ui->runIterButton, SIGNAL(clicked(bool)), this, SLOT(slot_runIterativeWFC()));

    connect(ui->mygl, SIGNAL(wfcConvergenceError(bool)), this, SLOT(slot_setErrorLabel(bool)));
    connect(ui->mygl, SIGNAL(wfcIterationInProgress(bool)), this, SLOT(slot_disableControls(bool)));

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

void MainWindow::slot_setBuildMode(bool buildMode) {
    ui->mygl->setBuildMode(buildMode);
    ui->clearNonUserTilesButton->setEnabled(buildMode);
}

void MainWindow::slot_setDimX(int x) {
    ui->mygl->setDimX(x);
}

void MainWindow::slot_setDimY(int y) {
    ui->mygl->setDimY(y);
}

void MainWindow::slot_setDimZ(int z) {
    ui->mygl->setDimZ(z);
}

void MainWindow::slot_setPeriodic(bool periodic) {
    ui->mygl->setPeriodic(periodic);
    ui->mygl->setSky(!periodic);
}

void MainWindow::slot_setClean(bool clean) {
    ui->mygl->setSky(clean);
    ui->mygl->setPeriodic(!clean);
}

void MainWindow::slot_setNone(bool none) {
    ui->mygl->setSky(!none);
    ui->mygl->setPeriodic(!none);
}

void MainWindow::slot_setPeriodicPreview(bool preview) {
    ui->mygl->showPeriodicPreview(preview);
}

void MainWindow::slot_setTileset() {
    if (ui->tilesetList->currentItem() != nullptr) {
        std::string tileset = ui->tilesetList->currentItem()->text().toStdString();
        ui->mygl->setTileset(tileset);
        populateTileList(tileset);
    }
}

void MainWindow::slot_setTileset2() {
    //if (ui->treeWidget->currentItem() != nullptr) {
      //  std::string tileset = ui->tilesetList->currentItem()->text().toStdString();
        //ui->mygl->setTileset(tileset);
        //populateTileList(tileset);
    //}
}

void MainWindow::slot_setTile() {
    if (ui->tileList->currentItem() != nullptr) {
        std::string tile = ui->tileList->currentItem()->text().toStdString();
        ui->mygl->setSelectedTile(tile);
    }

}

void MainWindow::slot_runWFC() {
    ui->mygl->runWFC();
}

void MainWindow::slot_runIterativeWFC(){
    ui->mygl->startIterativeWFC();
}

void MainWindow::slot_clearTileGrid() {
    ui->mygl->clearTileGrid();
}

void MainWindow::slot_clearNonUserTiles() {
    ui->mygl->clearNonUserTiles();
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

    // automatically select the first item
    if (ui->tilesetList->count() > 0) {
        ui->tilesetList->setCurrentRow(0);
    }
}

void MainWindow::populateTilesetList2() {
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
        //ui->treeWidget->addTopLevelItem(filename);
    }
}

void MainWindow::populateTileList(std::string tileset) {
    ui->tileList->clearSelection();
    ui->tileList->clear();
    // TODO: this code is copied from WFC class, maybe make separate util class or something
    // parse json file
    QString jsonString;
    QFile jsonFile;
    std::string jsonFilename = ":/json/" + tileset + ".json";
    jsonFile.setFileName(QString::fromStdString(jsonFilename));
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonString = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    QJsonObject jsonTilesetObject = jsonObject["tileset"].toObject();
    QJsonArray tilesArray = jsonTilesetObject["tiles"].toArray();

    for (int i = 0; i < tilesArray.size(); i++) {
        QJsonObject jsonTile = tilesArray[i].toObject();
        QString tileName = jsonTile["name"].toString();
        ui->tileList->addItem(tileName);
    }
}

void MainWindow::slot_setErrorLabel(bool error) {
    if (error) {
        ui->errorLabel->setText(QString("No convergence!"));
    } else {
        ui->errorLabel->setText(QString(""));
    }
}

void MainWindow::slot_disableControls(bool iterationInProgress) {
    ui->buildModeCheckBox->setEnabled(!iterationInProgress);
    ui->dimX->setEnabled(!iterationInProgress);
    ui->dimY->setEnabled(!iterationInProgress);
    ui->dimZ->setEnabled(!iterationInProgress);
    ui->cleanRadioButton->setEnabled(!iterationInProgress);
    ui->periodicRadioButton->setEnabled(!iterationInProgress);
    ui->noneRadioButton->setEnabled(!iterationInProgress);
    ui->showPreviewCheckBox->setEnabled(!iterationInProgress);
    ui->tilesetList->setEnabled(!iterationInProgress);
    ui->tileList->setEnabled(!iterationInProgress);
    ui->runWFCButton->setEnabled(!iterationInProgress);
    ui->runIterButton->setEnabled(!iterationInProgress);
    ui->clearButton->setEnabled(!iterationInProgress);
    ui->clearNonUserTilesButton->setEnabled(!iterationInProgress);
}


