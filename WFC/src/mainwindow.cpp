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

    // connect grid dimension spin boxes
    connect(ui->dimX, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimX(int)));
    connect(ui->dimY, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimY(int)));
    connect(ui->dimZ, SIGNAL(valueChanged(int)), this, SLOT(slot_changeDimZ(int)));

    // set default dim values in mygl based on spinboxes
    slot_changeDimX(ui->dimX->value());
    slot_changeDimY(ui->dimY->value());
    slot_changeDimZ(ui->dimZ->value());

    // connect tileset list view
    connect(ui->tilesetList, SIGNAL(itemClicked(QListWidgetItem*, int)), this, SLOT(slot_changeTileset(QListWidgetItem*)));

    // populate tileset list view
    populateTilesetList();

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

void MainWindow::slot_changeDimX(int x) {
    ui->mygl->setDimX(x);
}

void MainWindow::slot_changeDimY(int y) {
    ui->mygl->setDimY(y);
}

void MainWindow::slot_changeDimZ(int z) {
    ui->mygl->setDimZ(z);
}

// TODO: fix this
void MainWindow::slot_changeTileset(QListWidgetItem* tileset) {
    int i = 1;
    //ui->mygl->setTileset((std::string) tileset);
}

void MainWindow::slot_runWFC() {
    ui->mygl->runWFC();
}

void MainWindow::populateTilesetList() {
    // populate list view with jsons in json folder

    // TODO: fix hard coding
    //QDir dir1 = QDir::currentPath();
    QDir dir = QDir("/Users/carolinelachanski/Documents/WFC/WFC/json");
    QStringList jsons = dir.entryList(QStringList() << "*.json", QDir::Files);

    QStringListModel* model = new QStringListModel(this);
    QStringList list;
    foreach (QString filename, jsons) {
        list << filename;
    }
    model->setStringList(list);
    ui->tilesetList->setModel(model);
}

