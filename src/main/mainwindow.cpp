#include "src/other/global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadState();
}

MainWindow::~MainWindow()
{
    saveState();

    delete ui;
}

void MainWindow::saveState()
{
    QDir(dir).mkpath(dir+"data");
    QFile::remove(dir+"data/Config.ini");
    QSettings aSettings(dir+"data/Config.ini",QSettings::IniFormat);

    aSettings.beginGroup("States");
    aSettings.setValue("Geometry",saveGeometry());
    aSettings.endGroup();
}

void MainWindow::loadState()
{
    QSettings aSettings(dir+"data/Config.ini",QSettings::IniFormat);

    aSettings.beginGroup("States");
    restoreGeometry(aSettings.value("Geometry").toByteArray());
    aSettings.endGroup();
}
