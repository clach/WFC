#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QObject>

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
    // user can press button and choose OBJ to import as mesh
    void slot_importOBJ();

    // user can press button and choose JSON to import as skeleton
    void slot_importJSON();

private:
    Ui::MainWindow *ui;


signals:
};


#endif // MAINWINDOW_H
