#include "paintdialog.h"
#include "ui_paintdialog.h"

PaintDialog::PaintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(QPixmap(32, 32), true, 0);
}

PaintDialog::PaintDialog(QPixmap aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(aValue, true, 0);
}

PaintDialog::PaintDialog(QPixmap aValue, bool aMono, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(aValue, aMono, 0);
}

PaintDialog::PaintDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(QPixmap(32, 32), true, aAttributes);
}

PaintDialog::PaintDialog(bool aMono, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(QPixmap(32, 32), aMono, 0);
}

PaintDialog::PaintDialog(bool aMono, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(QPixmap(32, 32), aMono, aAttributes);
}

PaintDialog::PaintDialog(QPixmap aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(aValue, true, aAttributes);
}

PaintDialog::PaintDialog(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    init(aValue, aMono, aAttributes);
}

void PaintDialog::init(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mPaintFrame=new PaintFrame(aValue, aMono, aAttributes, this);
    ui->mainLayout->insertWidget(0, mPaintFrame);

    addAction(ui->actionOpen);
    addAction(ui->actionResize);
    addAction(ui->actionPlus);
    addAction(ui->actionMinus);
    addAction(ui->actionUndo);
    addAction(ui->actionRedo);
}

PaintDialog::~PaintDialog()
{
    delete ui;
}

QPixmap PaintDialog::resultValue() const
{
    return mPaintFrame->image();
}

void PaintDialog::on_okButton_clicked()
{
    accept();
}

void PaintDialog::on_cancelButton_clicked()
{
    reject();
}

void PaintDialog::on_actionOpen_triggered()
{
    mPaintFrame->on_openButton_clicked();
}

void PaintDialog::on_actionResize_triggered()
{
    mPaintFrame->on_resizeButton_clicked();
}

void PaintDialog::on_actionPlus_triggered()
{
    mPaintFrame->getImageView()->increaseLineWidth();
}

void PaintDialog::on_actionMinus_triggered()
{
    mPaintFrame->getImageView()->decreaseLineWidth();
}

void PaintDialog::on_actionUndo_triggered()
{
    mPaintFrame->getImageView()->undo();
}

void PaintDialog::on_actionRedo_triggered()
{
    mPaintFrame->getImageView()->redo();
}
