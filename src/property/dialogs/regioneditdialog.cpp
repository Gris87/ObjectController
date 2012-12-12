#include "regioneditdialog.h"
#include "ui_regioneditdialog.h"

#include <QScrollBar>

#include "../widgets/rectframe.h"

RegionEditDialog::RegionEditDialog(QRegion aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegionEditDialog)
{
    ui->setupUi(this);

    minCount=0;
    maxCount=INT_MAX;

    mAttributes=aAttributes;

    if (aAttributes)
    {
        minCount=aAttributes->intValue("minCount", minCount);
        maxCount=aAttributes->intValue("maxCount", maxCount);

        if (minCount<0)
        {
            minCount=0;
        }

        if (maxCount<minCount)
        {
            maxCount=minCount;
        }
    }

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
    while (ui->itemsLayout->count()>0)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    QVector<QRect> aRects=aValue.rects();

    for (int i=0; i<aRects.count(); ++i)
    {
        on_addButton_clicked();
        ((RectFrame *)ui->itemsLayout->itemAt(i)->widget())->setValue(aRects.at(i));
    }

    updateCountButtons();
}

void RegionEditDialog::updateCountButtons()
{
    if (minCount>0)
    {
        if (ui->itemsLayout->count()<=minCount)
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((RectFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(false);
            }

            ui->clearButton->setEnabled(false);
        }
        else
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((RectFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(true);
            }

            ui->clearButton->setEnabled(true);
        }
    }

    if (maxCount!=INT_MAX)
    {
        if (ui->itemsLayout->count()>=maxCount)
        {
            ui->addButton->setEnabled(false);
        }
        else
        {
            ui->addButton->setEnabled(true);
        }
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
    RectFrame *aFrame=new RectFrame(mAttributes, this);

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

    updateCountButtons();
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

    updateCountButtons();
}

void RegionEditDialog::on_clearButton_clicked()
{
    while (ui->itemsLayout->count()>minCount)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    if (ui->itemsLayout->count()>0)
    {
        ((RectFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(false);
    }

    updateCountButtons();
}
