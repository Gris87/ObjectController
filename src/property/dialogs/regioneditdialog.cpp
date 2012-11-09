#include "regioneditdialog.h"
#include "ui_regioneditdialog.h"

#include <QScrollBar>

#include "../widgets/rectframe.h"

RegionEditDialog::RegionEditDialog(QRegion aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegionEditDialog)
{
    ui->setupUi(this);

    setRegion(aValue);
}

RegionEditDialog::~RegionEditDialog()
{
    delete ui;
}

QRegion RegionEditDialog::resultValue() const
{
    QVector<QRect> aRects;

    for (int i=0; i<ui->itemsLayout->count(); ++i)
    {
        aRects.append(((RectFrame *)ui->itemsLayout->itemAt(i)->widget())->value());
    }

    QRegion res;
    res.setRects(aRects.data(), aRects.count());
    return res;
}

void RegionEditDialog::setRegion(const QRegion &aValue)
{
    on_clearButton_clicked();

    QVector<QRect> aRects=aValue.rects();

    for (int i=0; i<aRects.count(); ++i)
    {
        on_addButton_clicked();
        ((RectFrame *)ui->itemsLayout->itemAt(i)->widget())->setValue(aRects.at(i));
    }
}

void RegionEditDialog::on_okButton_clicked()
{
    accept();
}

void RegionEditDialog::on_cancelButton_clicked()
{
    reject();
}

void RegionEditDialog::on_addButton_clicked()
{
    RectFrame *aFrame=new RectFrame(this);

    if (ui->itemsLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((RectFrame *)ui->itemsLayout->itemAt(ui->itemsLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),     this, SLOT(itemUp()));
    connect(aFrame, SIGNAL(downPressed()),   this, SLOT(itemDown()));
    connect(aFrame, SIGNAL(deletePressed()), this, SLOT(itemDelete()));

    ui->itemsLayout->addWidget(aFrame);
    ui->mainScrollArea->verticalScrollBar()->setValue(ui->mainScrollArea->verticalScrollBar()->maximum());
}

void RegionEditDialog::itemUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==1)
    {
        ((RectFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((RectFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-1)
    {
        ((RectFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((RectFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index-1, aWidget);
}

void RegionEditDialog::itemDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==0)
    {
        ((RectFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((RectFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-2)
    {
        ((RectFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((RectFrame *)ui->itemsLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index+1, aWidget);
}

void RegionEditDialog::itemDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->itemsLayout->count()>1)
    {
        int index=ui->itemsLayout->indexOf(aWidget);

        if (index==0)
        {
            ((RectFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->itemsLayout->count()-1)
        {
            ((RectFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;
}

void RegionEditDialog::on_clearButton_clicked()
{
    while (ui->itemsLayout->count()>0)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }
}
