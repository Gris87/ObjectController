#include "iconeditdialog.h"
#include "ui_iconeditdialog.h"

IconEditDialog::IconEditDialog(QIcon aIcon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    QList<QIcon::Mode> aModes;

    aModes.append(QIcon::Normal);
    aModes.append(QIcon::Disabled);
    aModes.append(QIcon::Active);
    aModes.append(QIcon::Selected);

    QList<QIcon::State> aStates;

    aStates.append(QIcon::Off);
    aStates.append(QIcon::On);

    for (int i=0; i<aModes.length(); ++i)
    {
        for (int j=0; j<aStates.length(); ++j)
        {
            PageEntry aEntry;

            aEntry.mode=aModes.at(i);
            aEntry.state=aStates.at(j);



            QWidget *aWidget=new QWidget(this);

            QVBoxLayout* aLayout = new QVBoxLayout(aWidget);
            aEntry.checkbox      = new QCheckBox(tr("Use this pixmap"), aWidget);
            aEntry.paintframe    = new PaintFrame(aIcon.pixmap(128, 128, aEntry.mode, aEntry.state), false, aWidget);

            aEntry.checkbox->setChecked(aIcon.availableSizes(aEntry.mode, aEntry.state).length()>0);

            aLayout->setContentsMargins(4, 4, 4, 4);
            aLayout->addWidget(aEntry.checkbox);
            aLayout->addWidget(aEntry.paintframe);
            aWidget->setLayout(aLayout);

            ui->iconTabWidget->addTab(aWidget, modeToString(aEntry.mode)+" ("+stateToString(aEntry.state)+")");

            mPages.append(aEntry);
        }
    }
}

IconEditDialog::~IconEditDialog()
{
    delete ui;
}

QIcon IconEditDialog::resultValue() const
{
    QIcon aIcon;

    for (int i=0; i<mPages.length(); ++i)
    {
        if (mPages.at(i).checkbox->isChecked())
        {
            aIcon.addPixmap(mPages.at(i).paintframe->image(), mPages.at(i).mode, mPages.at(i).state);
        }
    }

    return aIcon;
}

void IconEditDialog::on_okButton_clicked()
{
    accept();
}

void IconEditDialog::on_cancelButton_clicked()
{
    reject();
}

QString IconEditDialog::modeToString(const QIcon::Mode &aMode) const
{
    switch (aMode)
    {
        case QIcon::Normal:   return "Normal";
        case QIcon::Disabled: return "Disabled";
        case QIcon::Active:   return "Active";
        case QIcon::Selected: return "Selected";
    }

    return "Unknown";
}

QString IconEditDialog::stateToString(const QIcon::State &aState) const
{
    switch (aState)
    {
        case QIcon::On:  return "ON";
        case QIcon::Off: return "OFF";
    }

    return "Unknown";
}
