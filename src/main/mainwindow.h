#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline void saveState();
    inline void loadState();
};

#endif // MAINWINDOW_H
