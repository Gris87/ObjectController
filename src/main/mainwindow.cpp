#include "src/other/global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createButton_clicked()
{
    QString aNewObjectName=ui->objectsComboBox->currentText();
    ui->controlledListWidget->addItem(aNewObjectName);

    qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();

    ui->timeLabel->setText("Time: "+QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
}

void MainWindow::on_clearButton_clicked()
{
    ui->controlledListWidget->clear();
}
