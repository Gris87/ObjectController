#include "stringlisteditdialog.h"
#include "ui_stringlisteditdialog.h"

#include <QScrollBar>

#include "../widgets/stringframe.h"

StringListEditDialog::StringListEditDialog(QStringList aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StringListEditDialog)
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

    setList(aValue);
}

StringListEditDialog::~StringListEditDialog()
{
    delete ui;
}

QStringList StringListEditDialog::resultValue() const
{
    QStringList res;

    for (int i=0; i<ui->itemsLayout->count(); ++i)
    {
        res.append(((StringFrame *)ui->itemsLayout->itemAt(i)->widget())->value());
    }

    return res;
}

void StringListEditDialog::setList(const QStringList &aValue)
{
    while (ui->itemsLayout->count()>0)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    for (int i=0; i<aValue.length(); ++i)
    {
        on_addButton_clicked();
        ((StringFrame *)ui->itemsLayout->itemAt(i)->widget())->setValue(aValue.at(i));
    }

    updateCountButtons();
}

void StringListEditDialog::updateCountButtons()
{
    if (minCount>0)
    {
        if (ui->itemsLayout->count()<=minCount)
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((StringFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(false);
            }

            ui->clearButton->setEnabled(false);
        }
        else
        {
            for (int i=0; i<ui->itemsLayout->count(); ++i)
            {
                ((StringFrame *)ui->itemsLayout->itemAt(i)->widget())->setDelEnabled(true);
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

void StringListEditDialog::on_okButton_clicked()
{
    accept();
}

void StringListEditDialog::on_cancelButton_clicked()
{
    reject();
}

void StringListEditDialog::on_addButton_clicked()
{
    StringFrame *aFrame=new StringFrame(mAttributes, this);

    if (ui->itemsLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((StringFrame *)ui->itemsLayout->itemAt(ui->itemsLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),     this, SLOT(itemUp()));
    connect(aFrame, SIGNAL(downPressed()),   this, SLOT(itemDown()));
    connect(aFrame, SIGNAL(deletePressed()), this, SLOT(itemDelete()));

    ui->itemsLayout->addWidget(aFrame);
    ui->mainScrollArea->verticalScrollBar()->setValue(ui->mainScrollArea->verticalScrollBar()->maximum());

    updateCountButtons();
}

void StringListEditDialog::itemUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==1)
    {
        ((StringFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((StringFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-1)
    {
        ((StringFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((StringFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index-1, aWidget);
}

void StringListEditDialog::itemDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->itemsLayout->indexOf(aWidget);

    if (index==0)
    {
        ((StringFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((StringFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->itemsLayout->count()-2)
    {
        ((StringFrame *)ui->itemsLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((StringFrame *)ui->itemsLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->itemsLayout->removeWidget(aWidget);
    ui->itemsLayout->insertWidget(index+1, aWidget);
}

void StringListEditDialog::itemDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->itemsLayout->count()>1)
    {
        int index=ui->itemsLayout->indexOf(aWidget);

        if (index==0)
        {
            ((StringFrame *)ui->itemsLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->itemsLayout->count()-1)
        {
            ((StringFrame *)ui->itemsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;

    updateCountButtons();
}

void StringListEditDialog::on_sortButton_clicked()
{
    QStringList aList=resultValue();
    aList.sort();
    setList(aList);
}

void StringListEditDialog::on_clearButton_clicked()
{
    while (ui->itemsLayout->count()>minCount)
    {
        delete ui->itemsLayout->takeAt(0)->widget();
    }

    if (ui->itemsLayout->count()>0)
    {
        ((StringFrame *)ui->itemsLayout->itemAt(0)->widget())->setUpEnabled(false);
    }

    updateCountButtons();
}
