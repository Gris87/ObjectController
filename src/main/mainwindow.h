#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QTabWidget>
#include <QComboBox>
#include <QFontComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QDial>
#include <QSlider>
#include <QLabel>
#include <QCalendarWidget>
#include <QProgressBar>

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

    void closeEvent(QCloseEvent *event);

private slots:
    void setFocutToObjectsComboBox();

    void on_createButton_clicked();
    void on_clearButton_clicked();
    void on_objectsComboBox_enterPressed();
};

#endif // MAINWINDOW_H
