#include "paletteeditdialog.h"
#include "ui_paletteeditdialog.h"

#include <QMetaEnum>
#include <QTimer>

#include "../widgets/colorarea.h"
#include "../widgets/palettedemowidget.h"

PaletteEditDialog::PaletteEditDialog(QPalette aPalette, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaletteEditDialog)
{
    ui->setupUi(this);



    ColorArea *aFastArea=new ColorArea(aAttributes, this);
    aFastArea->setColor(aPalette.color(QPalette::Active, QPalette::Button));
    aFastArea->setMinimumSize(90, 16);
    aFastArea->setMaximumSize(90, 16);
    aFastArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->optionsLayout->insertWidget(1, aFastArea);

    connect(aFastArea, SIGNAL(colorChanged(QColor)), this, SLOT(fastColorChanged(QColor)));



    QMetaEnum aGroupEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorGroup"));
    QMetaEnum aRoleEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorRole"));

    ui->colorsTableWidget->setRowCount(QPalette::NColorRoles);
    ui->colorsTableWidget->setColumnCount(QPalette::NColorGroups);

    for (int i=0; i<QPalette::NColorGroups; ++i)
    {
        ui->colorsTableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromLatin1(aGroupEnum.key(i))));
    }

    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        ui->colorsTableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromLatin1(aRoleEnum.key(i))));

        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            ColorArea *aArea=new ColorArea(aAttributes, this);
            aArea->setColor(aPalette.color((QPalette::ColorGroup)j, (QPalette::ColorRole)i));

            ui->colorsTableWidget->setCellWidget(i, j, aArea);

            connect(aArea, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
        }
    }



#ifdef CONTROLLER_APP
    // TODO: Add easter egg
#endif
    mDemoWidget=ui->demoMdiArea->addSubWindow(new PaletteDemoWidget(this), Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    mDemoWidget->setWindowState(Qt::WindowMaximized);



    if (aAttributes)
    {
        bool aAllowFastColor=aAttributes->boolValue("allowFastColor", true);
        bool aAllowChangeDetails=aAttributes->boolValue("allowChangeDetails", true);
        bool aShowDetails=aAttributes->boolValue("showDetails", true);

        if (aAllowFastColor || aAllowChangeDetails)
        {
            ui->fastLabel->setVisible(aAllowFastColor);
            aFastArea->setVisible(aAllowFastColor);
            ui->calculateDetailsRadioButton->setVisible(aAllowChangeDetails);
            ui->showDetailsRadioButton->setVisible(aAllowChangeDetails);
        }
        else
        {
            ui->optionsWidget->setVisible(false);
        }

        if (aShowDetails)
        {
            ui->showDetailsRadioButton->blockSignals(true);
            ui->showDetailsRadioButton->setChecked(true);
            ui->showDetailsRadioButton->blockSignals(false);
        }
        else
        {
            ui->calculateDetailsRadioButton->blockSignals(true);
            ui->calculateDetailsRadioButton->setChecked(true);
            ui->calculateDetailsRadioButton->blockSignals(false);
        }

        ui->demoMdiArea->setVisible(aAttributes->boolValue("preview", true));
    }



    QTimer::singleShot(0, this, SLOT(updateColumns()));
    updateDemo();
}

PaletteEditDialog::~PaletteEditDialog()
{
    delete ui;
}

void PaletteEditDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    updateColumns();
}

QPalette PaletteEditDialog::resultValue() const
{
    QPalette aPalette;

    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            aPalette.setColor((QPalette::ColorGroup)j, (QPalette::ColorRole)i, ((ColorArea *)ui->colorsTableWidget->cellWidget(i, j))->color());
        }
    }

    return aPalette;
}

void PaletteEditDialog::on_okButton_clicked()
{
    accept();
}

void PaletteEditDialog::on_cancelButton_clicked()
{
    reject();
}

void PaletteEditDialog::on_calculateDetailsRadioButton_toggled(bool checked)
{
    if (checked)
    {
        updateColumns();
    }
}

void PaletteEditDialog::on_showDetailsRadioButton_toggled(bool checked)
{
    if (checked)
    {
        updateColumns();
    }
}

void PaletteEditDialog::on_enabledRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->demoMdiArea->setActiveSubWindow(mDemoWidget);
        mDemoWidget->setEnabled(true);
    }
}

void PaletteEditDialog::on_disabledRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->demoMdiArea->setActiveSubWindow(mDemoWidget);
        mDemoWidget->setEnabled(false);
    }
}

void PaletteEditDialog::on_inactiveRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->demoMdiArea->setActiveSubWindow(0);
        mDemoWidget->setEnabled(true);
    }
}

void PaletteEditDialog::fastColorChanged(QColor aColor)
{
    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            ui->colorsTableWidget->cellWidget(i, j)->blockSignals(true);
        }
    }


    calculateColor(QPalette::Button,        aColor);
    calculateColor(QPalette::Light,         aColor.lighter(150));
    calculateColor(QPalette::Midlight,      aColor.lighter(125));
    calculateColor(QPalette::Dark,          aColor.darker(200));
    calculateColor(QPalette::Mid,           aColor.darker(150));
    calculateColor(QPalette::Window,        aColor);
    calculateColor(QPalette::Shadow,        QColor(0, 0, 0));
    calculateColor(QPalette::AlternateBase, aColor.lighter(150));

    ((ColorArea *)ui->colorsTableWidget->cellWidget(QPalette::AlternateBase, QPalette::Disabled))->setColor(aColor);



    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            ui->colorsTableWidget->cellWidget(i, j)->blockSignals(false);
        }
    }



    updateDemo();
}

void PaletteEditDialog::colorChanged(QColor aColor)
{
    if (ui->calculateDetailsRadioButton->isChecked())
    {
        QObject *aSender=sender();

        int index=-1;

        for (int i=0; i<QPalette::NColorRoles; ++i)
        {
            if (ui->colorsTableWidget->cellWidget(i, 0)==aSender)
            {
                index=i;
                break;
            }
        }

        if (index>=0)
        {
            for (int i=0; i<QPalette::NColorRoles; ++i)
            {
                for (int j=0; j<QPalette::NColorGroups; ++j)
                {
                    ui->colorsTableWidget->cellWidget(i, j)->blockSignals(true);
                }
            }



            calculateColor(index, aColor);



            for (int i=0; i<QPalette::NColorRoles; ++i)
            {
                for (int j=0; j<QPalette::NColorGroups; ++j)
                {
                    ui->colorsTableWidget->cellWidget(i, j)->blockSignals(false);
                }
            }
        }
    }

    updateDemo();
}

void PaletteEditDialog::calculateColor(int aRow, QColor aColor)
{
    QColor aDisabledColor;
    QColor aInactiveColor;



    switch (aRow)
    {
        case QPalette::WindowText:
        case QPalette::Text:
        case QPalette::ButtonText:
        case QPalette::Base:
        case QPalette::Highlight:
            aInactiveColor=aColor;
        break;
        case QPalette::Button:
        case QPalette::Light:
        case QPalette::Midlight:
        case QPalette::Dark:
        case QPalette::Mid:
        case QPalette::BrightText:
        case QPalette::Window:
        case QPalette::Shadow:
        case QPalette::HighlightedText:
        case QPalette::Link:
        case QPalette::LinkVisited:
        case QPalette::AlternateBase:
        case QPalette::NoRole:
        case QPalette::ToolTipBase:
        case QPalette::ToolTipText:
            aDisabledColor=aColor;
            aInactiveColor=aColor;
        break;
    }



    ((ColorArea *)ui->colorsTableWidget->cellWidget(aRow, QPalette::Active))->setColor(aColor);

    if (aDisabledColor.isValid())
    {
        ((ColorArea *)ui->colorsTableWidget->cellWidget(aRow, QPalette::Disabled))->setColor(aDisabledColor);

        if (aRow==QPalette::Dark)
        {
            ((ColorArea *)ui->colorsTableWidget->cellWidget(QPalette::WindowText, QPalette::Disabled))->setColor(aDisabledColor);
            ((ColorArea *)ui->colorsTableWidget->cellWidget(QPalette::Text,       QPalette::Disabled))->setColor(aDisabledColor);
            ((ColorArea *)ui->colorsTableWidget->cellWidget(QPalette::ButtonText, QPalette::Disabled))->setColor(aDisabledColor);
        }
        else
        if (aRow==QPalette::Window)
        {
            ((ColorArea *)ui->colorsTableWidget->cellWidget(QPalette::Base, QPalette::Disabled))->setColor(aDisabledColor);
        }
    }

    if (aInactiveColor.isValid())
    {
        ((ColorArea *)ui->colorsTableWidget->cellWidget(aRow, QPalette::Inactive))->setColor(aInactiveColor);
    }
}

void PaletteEditDialog::updateColumns()
{
    if (ui->calculateDetailsRadioButton->isChecked())
    {
        ui->colorsTableWidget->setColumnHidden(1, true);
        ui->colorsTableWidget->setColumnHidden(2, true);
    }
    else
    if (ui->showDetailsRadioButton->isChecked())
    {
        int aColumnWidth=(ui->colorsTableWidget->viewport()->width())/3-1;

        ui->colorsTableWidget->setColumnHidden(1, false);
        ui->colorsTableWidget->setColumnHidden(2, false);

        ui->colorsTableWidget->setColumnWidth(0, aColumnWidth);
        ui->colorsTableWidget->setColumnWidth(1, aColumnWidth);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void PaletteEditDialog::updateDemo()
{
    QPalette aDefaultPalette;
    QPalette aDemoPalette=resultValue();



    QFont aDefaultFont=ui->colorsTableWidget->verticalHeaderItem(0)->font();
    aDefaultFont.setBold(false);

    QFont aBoldFont=ui->colorsTableWidget->verticalHeaderItem(0)->font();
    aBoldFont.setBold(true);



    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        bool good=true;

        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            if (aDefaultPalette.color((QPalette::ColorGroup)j, (QPalette::ColorRole)i)!=aDemoPalette.color((QPalette::ColorGroup)j, (QPalette::ColorRole)i))
            {
                good=false;
                break;
            }
        }

        if (good)
        {
            ui->colorsTableWidget->verticalHeaderItem(i)->setFont(aDefaultFont);
        }
        else
        {
            ui->colorsTableWidget->verticalHeaderItem(i)->setFont(aBoldFont);
        }
    }



    mDemoWidget->setPalette(aDemoPalette);
}
