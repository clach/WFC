#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QObject>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionCamera_Controls_triggered();

//public slots:
    // user can use radio button to toggle build mode
    void slot_setBuildMode(bool);

    void slot_setVisualizeEmptyTiles(bool);

    // user can use spin boxes to edit grid dimensions
    void slot_setDimX(int);
    void slot_setDimY(int);
    void slot_setDimZ(int);

    // user can use check boxes to set boundary conditions
    void slot_setPeriodic(bool);
    void slot_setSky(bool);

    // user can press button to clear current WFC output
    void slot_clearTileGrid();

    // user can press button to clear non-user placed tiles
    void slot_clearNonUserTiles();

    // user can press button to run WFC
    void slot_runWFC();

    // user can select tileset from list
    void slot_setTileset();

    void slot_setTileset2();

    // user can select tile from list
    void slot_setTile();


private:
    Ui::MainWindow *ui;

    void populateTilesetList();
    void populateTilesetList2();
    void populateTileList(std::string tileset);


signals:
};


#endif // MAINWINDOW_H
