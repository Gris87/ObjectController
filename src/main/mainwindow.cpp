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

    QObject *aNewObject=0;

    if (aNewObjectName=="QObject")
    {
        aNewObject=new QObject(this);
    }

    if (aNewObject==0)
    {
        return;
    }

    if (aNewObject->inherits("QWidget"))
    {
        QWidget *aNewWidget = (QWidget *)aNewObject;

        QRect r = aNewWidget->geometry();

        r.setSize(aNewWidget->sizeHint());
        r.setWidth(qMax(r.width(), 200));
        r.setHeight(qMax(r.height(), 100));
        r.moveCenter(QApplication::desktop()->geometry().center());

        aNewWidget->setGeometry(r);
        aNewWidget->setWindowTitle(aNewObjectName);
        aNewWidget->show();
    }

    ui->controlledListWidget->addItem(aNewObjectName);

    QObjectList aObjects=ui->objectController->objects();
    aObjects.append(aNewObject);

    qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();
    ui->objectController->setObjects(aObjects);
    ui->timeLabel->setText("Time: "+QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
}

void MainWindow::on_clearButton_clicked()
{
    ui->controlledListWidget->clear();

    QObjectList aObjects=ui->objectController->objects();

    for (int i=0; i<aObjects.length(); ++i)
    {
        delete aObjects.at(i);
    }

    ui->objectController->clear();
}
