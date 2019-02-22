#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();
}

void MainWindow::slot_importOBJ() {

    // bring up dialogue for user to open file, .obj's only
    QString filename = QFileDialog::getOpenFileName(0, QString("Load OBJ"), QString(":/"), tr("*.obj"));
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // start reading file
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line= in.readLine(); // read file one line at a time

            char name[2];
            float x, y, z;
        }

        // finished reading file, now have all the vertices, faces, and half edges


    }
}

void MainWindow::slot_importJSON() {

    // bring up dialogue for user to open file, .jsons's only
    QString filename = QFileDialog::getOpenFileName(0, QString("Load JSON"), QString(":/"), tr("*.json"));
    QFile file(filename);

    // parse the JSON file
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString fileContents = file.readAll();
        file.close();

        QJsonDocument json = QJsonDocument::fromJson(fileContents.toUtf8());
        QJsonObject jsonObject = json.object();

        // get root joint
        QJsonObject root = jsonObject["root"].toObject();
    }

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
