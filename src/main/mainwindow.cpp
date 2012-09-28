#include "src/other/global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot(0, this, SLOT(on_createButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    on_clearButton_clicked();

    event->accept();
}

void MainWindow::on_createButton_clicked()
{
    QTimer::singleShot(0, this, SLOT(setFocusToObjectsComboBox()));

    QString aNewObjectName=ui->objectsComboBox->currentText();

    QObject *aNewObject=0;

    if (aNewObjectName=="QObject")
    {
        aNewObject=new QObject();
    }
    else
    if (aNewObjectName=="TestObject")
    {
        aNewObject=new TestObject();
    }
    else
    if (aNewObjectName=="QWidget")
    {
        aNewObject=new QWidget();
    }
    else
    if (aNewObjectName=="QFrame")
    {
        aNewObject=new QFrame();
    }
    else
    if (aNewObjectName=="QPushButton")
    {
        aNewObject=new QPushButton("Button");
    }
    else
    if (aNewObjectName=="QToolButton")
    {
        aNewObject=new QToolButton();
    }
    else
    if (aNewObjectName=="QRadioButton")
    {
        aNewObject=new QRadioButton("Radio button");
    }
    else
    if (aNewObjectName=="QCheckBox")
    {
        aNewObject=new QCheckBox("CheckBox");
    }
    else
    if (aNewObjectName=="QListWidget")
    {
        aNewObject=new QListWidget();
    }
    else
    if (aNewObjectName=="QTreeWidget")
    {
        aNewObject=new QTreeWidget();
    }
    else
    if (aNewObjectName=="QTableWidget")
    {
        aNewObject=new QTableWidget(5, 3);
    }
    else
    if (aNewObjectName=="QGroupBox")
    {
        aNewObject=new QGroupBox("GroupBox");
    }
    else
    if (aNewObjectName=="QTabWidget")
    {
        aNewObject=new QTabWidget();
    }
    else
    if (aNewObjectName=="QComboBox")
    {
        aNewObject=new QComboBox();
    }
    else
    if (aNewObjectName=="QFontComboBox")
    {
        aNewObject=new QFontComboBox();
    }
    else
    if (aNewObjectName=="QLineEdit")
    {
        aNewObject=new QLineEdit("LineEdit");
    }
    else
    if (aNewObjectName=="QTextEdit")
    {
        aNewObject=new QTextEdit("TextEdit");
    }
    else
    if (aNewObjectName=="QPlainTextEdit")
    {
        aNewObject=new QPlainTextEdit("PlainTextEdit");
    }
    else
    if (aNewObjectName=="QSpinBox")
    {
        aNewObject=new QSpinBox();
    }
    else
    if (aNewObjectName=="QDoubleSpinBox")
    {
        aNewObject=new QDoubleSpinBox();
    }
    else
    if (aNewObjectName=="QTimeEdit")
    {
        aNewObject=new QTimeEdit();
    }
    else
    if (aNewObjectName=="QDateEdit")
    {
        aNewObject=new QDateEdit();
    }
    else
    if (aNewObjectName=="QDateTimeEdit")
    {
        aNewObject=new QDateTimeEdit();
    }
    else
    if (aNewObjectName=="QDial")
    {
        aNewObject=new QDial();
    }
    else
    if (aNewObjectName=="QSlider")
    {
        aNewObject=new QSlider();
    }
    else
    if (aNewObjectName=="QLabel")
    {
        aNewObject=new QLabel("Label");
    }
    else
    if (aNewObjectName=="QCalendarWidget")
    {
        aNewObject=new QCalendarWidget();
    }
    else
    if (aNewObjectName=="QProgressBar")
    {
        aNewObject=new QProgressBar();
    }

    if (aNewObject==0)
    {
        QMessageBox::warning(this, "Creating object", "Unknown object type: "+aNewObjectName);
        return;
    }

    if (aNewObject->inherits("QWidget"))
    {
        QWidget *aNewWidget = (QWidget *)aNewObject;

        QRect r = aNewWidget->geometry();

        r.setSize(aNewWidget->sizeHint());
        r.setWidth(qMax(r.width(), 200));
        r.setHeight(qMax(r.height(), 30));
        r.moveTopLeft(geometry().topRight());
        r.translate(8, 0);

        aNewWidget->setGeometry(r);
        aNewWidget->setWindowTitle(aNewObjectName);
        aNewWidget->show();
    }

    ui->controlledListWidget->addItem(aNewObjectName);

    QObjectList aObjects=ui->objectController->objects();
    aObjects.append(aNewObject);

    qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();
    ui->objectController->setObjects(aObjects);
    ui->timeLabel->setText("Time to set objects: "+QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
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

void MainWindow::on_resetButton_clicked()
{
    qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();
    ui->objectController->reset();
    ui->timeLabel->setText("Time to reset: "+QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
}

void MainWindow::on_updateButton_clicked()
{
    qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();
    ui->objectController->update();
    ui->timeLabel->setText("Time to update: "+QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
}

void MainWindow::on_objectsComboBox_enterPressed()
{
    on_createButton_clicked();
}

void MainWindow::setFocusToObjectsComboBox()
{
    QApplication::setActiveWindow(this);
    ui->objectsComboBox->setFocus();
}
