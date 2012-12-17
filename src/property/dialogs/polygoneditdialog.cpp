#include "polygoneditdialog.h"
#include "ui_polygoneditdialog.h"

#include <QScrollBar>

#include "../widgets/pointframe.h"

PolygonEditDialog::PolygonEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolygonEditDialog)
{
    init(QPolygon(), 0);
}

PolygonEditDialog::PolygonEditDialog(QPolygon aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolygonEditDialog)
{
    init(aValue, 0);
}

PolygonEditDialog::PolygonEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolygonEditDialog)
{
    init(QPolygon(), aAttributes);
}

PolygonEditDialog::PolygonEditDialog(QPolygon aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolygonEditDialog)
{
    init(aValue, aAttributes);
}

void PolygonEditDialog::init(QPolygon aValue, const PropertyAttributes *aAttributes)
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

    setPolygon(aValue);
}

PolygonEditDialog::~PolygonEditDialog()
{
    delete ui;
}

QPolygon PolygonEditDialog::resultValue() const
{
    QPolygon res;

    for (int i=0; i<ui->itemsLayout->count(); ++i)
    {
        res.append(((PointFrame *)ui->itemsLayout->itemAt(i)->widget())->value());
    }

    return res;
}

void PolygonEditDialog::setPolygon(const QPolygon &aValue)
{
    while (ui->itemsLayout->count()>0)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    for (int i=0; i<aValue.count(); ++i)
    {
        on_addButton_clicked();
        ((PointFrame *)ui->itemsLayout->itemAt(i)->widget())->setValue(aValue.at(i));
    }

    updateCountButtons();
}

void PolygonEditDialog::updateCountButtons()
{
    if (minCount>0)
    {
        if (ui->itemsLayout->count()<=minCount)
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((PointFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(false);
            }

            ui->clearButton->setEnabled(false);
        }
        else
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((PointFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(true);
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

void PolygonEditDialog::on_okButton_clicked()
{
    accept();
}

void PolygonEditDialog::on_cancelButton_clicked()
{
    reject();
}

void PolygonEditDialog::on_addButton_clicked()
{
    PointFrame *aFrame=new PointFrame(mAttributes, this);

    if (ui->itemsLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((PointFrame *)ui->itemsLayout->itemAt(ui->itemsLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),     this, SLOT(itemUp()));
    connect(aFrame, SIGNAL(downPressed()),   this, SLOT(itemDown()));
    connect(aFrame, SIGNAL(deletePressed()), this, SLOT(itemDelete()));

    ui->itemsLayout->addWidget(aFrame);
    ui->mainScrollArea->verticalScrollBar()->setValue(ui->mainScrollArea->verticalScrollBar()->maximum());

    updateCountButtons();
}

void PolygonEditDialog::itemUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==1)
    {
        ((PointFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((PointFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-1)
    {
        ((PointFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((PointFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index-1, aWidget);
}

void PolygonEditDialog::itemDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==0)
    {
        ((PointFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((PointFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-2)
    {
        ((PointFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((PointFrame *)ui->itemsLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index+1, aWidget);
}

void PolygonEditDialog::itemDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->itemsLayout->count()>1)
    {
        int index=ui->itemsLayout->indexOf(aWidget);

        if (index==0)
        {
            ((PointFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->itemsLayout->count()-1)
        {
            ((PointFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;

    updateCountButtons();
}

void PolygonEditDialog::on_clearButton_clicked()
{
    while (ui->itemsLayout->count()>minCount)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    if (ui->itemsLayout->count()>0)
    {
        ((PointFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(false);
    }

    updateCountButtons();
}
