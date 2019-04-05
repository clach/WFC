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

public slots:    
    // user can use radio button to toggle build mode
    void slot_selectBuildMode(bool);

    // user can use spin boxes to edit grid dimensions
    void slot_changeDimX(int);
    void slot_changeDimY(int);
    void slot_changeDimZ(int);

    // user can press button to clear current WFC output
    void slot_clearWFC();

    // user can press button to run WFC
    void slot_runWFC();

    // user can select tileset from list
    void slot_changeTileset();

    // user can select tile from list
    void slot_changeTile();


private:
    Ui::MainWindow *ui;

    void populateTilesetList();
    void populateTileList(std::string tileset);


signals:
};


#endif // MAINWINDOW_H
