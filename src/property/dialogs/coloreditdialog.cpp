#include "coloreditdialog.h"
#include "ui_coloreditdialog.h"

ColorEditDialog::ColorEditDialog(QColor aColor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorEditDialog)
{
    ui->setupUi(this);

    QList<QColor> aColors;

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            ColorArea *aArea=new ColorArea(this);
            aArea->setColor(aColors.at(i*8+j));
            aArea->setMinimumSize(22, 18);
            aArea->setMaximumSize(22, 18);
            aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            aArea->selectAllowed=false;
            aArea->popupAllowed=false;

            ui->basicGridLayout->addWidget(aArea, i, j, 1, 1);
        }
    }

    // --------------------------------------------------------------------------------------------

    aColors.clear();

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));
    aColors.append(QColor(255, 255, 255));

    for (int i=0; i<2; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            ColorArea *aArea=new ColorArea(this);
            aArea->setColor(aColors.at(i*8+j));
            aArea->setMinimumSize(22, 18);
            aArea->setMaximumSize(22, 18);
            aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            aArea->selectAllowed=false;
            aArea->popupAllowed=false;

            ui->customGridLayout->addWidget(aArea, i, j, 1, 1);
        }
    }

    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------

    mMainColorArea=new ColorArea(this);
    mMainColorArea->setMinimumSize(60, 78);
    mMainColorArea->setMaximumSize(60, 78);
    mMainColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mMainColorArea->selectAllowed=false;
    mMainColorArea->popupAllowed=false;

    ui->propertiesLayout->insertWidget(0, mMainColorArea);

    setColor(aColor);
}

ColorEditDialog::~ColorEditDialog()
{
    delete ui;
}

QColor ColorEditDialog::resultValue() const
{
    return QColor();
}

void ColorEditDialog::on_okButton_clicked()
{
    accept();
}

void ColorEditDialog::on_cancelButton_clicked()
{
    reject();
}

void ColorEditDialog::setColor(QColor aColor)
{
    ui->hueSpinBox->blockSignals(true);
    ui->satSpinBox->blockSignals(true);
    ui->valSpinBox->blockSignals(true);
    ui->redSpinBox->blockSignals(true);
    ui->greenSpinBox->blockSignals(true);
    ui->blueSpinBox->blockSignals(true);



    mMainColorArea->setColor(aColor);

    ui->hueSpinBox->setValue(aColor.hue());
    ui->satSpinBox->setValue(aColor.saturation());
    ui->valSpinBox->setValue(aColor.value());

    ui->redSpinBox->setValue(aColor.red());
    ui->greenSpinBox->setValue(aColor.green());
    ui->blueSpinBox->setValue(aColor.blue());



    ui->hueSpinBox->blockSignals(false);
    ui->satSpinBox->blockSignals(false);
    ui->valSpinBox->blockSignals(false);
    ui->redSpinBox->blockSignals(false);
    ui->greenSpinBox->blockSignals(false);
    ui->blueSpinBox->blockSignals(false);
}

void ColorEditDialog::on_hueSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(aValue,                  ui->satSpinBox->value(), ui->valSpinBox->value()));
}

void ColorEditDialog::on_satSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(ui->hueSpinBox->value(), aValue,                  ui->valSpinBox->value()));
}

void ColorEditDialog::on_valSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(ui->hueSpinBox->value(), ui->satSpinBox->value(), aValue));
}

void ColorEditDialog::on_redSpinBox_valueChanged(int aValue)
{
    setColor(QColor(aValue,                  ui->greenSpinBox->value(), ui->blueSpinBox->value()));
}

void ColorEditDialog::on_greenSpinBox_valueChanged(int aValue)
{
    setColor(QColor(ui->redSpinBox->value(), aValue,                    ui->blueSpinBox->value()));
}

void ColorEditDialog::on_blueSpinBox_valueChanged(int aValue)
{
    setColor(QColor(ui->redSpinBox->value(), ui->greenSpinBox->value(), aValue));
}
