#include "coloreditdialog.h"
#include "ui_coloreditdialog.h"

#include <QSettings>

ColorEditDialog::ColorEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorEditDialog)
{
    init(QColor(0, 0, 0), 0);
}

ColorEditDialog::ColorEditDialog(QColor aColor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorEditDialog)
{
    init(aColor, 0);
}

ColorEditDialog::ColorEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorEditDialog)
{
    init(QColor(0, 0, 0), aAttributes);
}

ColorEditDialog::ColorEditDialog(QColor aColor, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorEditDialog)
{
    init(aColor, aAttributes);
}

void ColorEditDialog::init(QColor aColor, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    QList<QColor> aColors;

    aColors.append(QColor(255, 128, 128));
    aColors.append(QColor(255, 255, 128));
    aColors.append(QColor(128, 255, 128));
    aColors.append(QColor(0,   255, 128));
    aColors.append(QColor(128, 255, 255));
    aColors.append(QColor(0,   128, 255));
    aColors.append(QColor(255, 128, 192));
    aColors.append(QColor(255, 128, 255));

    aColors.append(QColor(255, 0,   0));
    aColors.append(QColor(255, 255, 0));
    aColors.append(QColor(128, 255, 0));
    aColors.append(QColor(0,   255, 64));
    aColors.append(QColor(0,   255, 255));
    aColors.append(QColor(0,   128, 192));
    aColors.append(QColor(128, 128, 192));
    aColors.append(QColor(255, 0,   255));

    aColors.append(QColor(128, 64,  64));
    aColors.append(QColor(255, 128, 64));
    aColors.append(QColor(0,   255, 0));
    aColors.append(QColor(0,   128, 128));
    aColors.append(QColor(0,   64,  128));
    aColors.append(QColor(128, 128, 255));
    aColors.append(QColor(128, 0,   64));
    aColors.append(QColor(255, 0,   128));

    aColors.append(QColor(128, 0,   0));
    aColors.append(QColor(255, 128, 0));
    aColors.append(QColor(0,   128, 0));
    aColors.append(QColor(0,   128, 64));
    aColors.append(QColor(0,   0,   255));
    aColors.append(QColor(0,   0,   160));
    aColors.append(QColor(128, 0,   128));
    aColors.append(QColor(128, 0,   255));

    aColors.append(QColor(64,  0,   0));
    aColors.append(QColor(128, 64,  0));
    aColors.append(QColor(0,   64,  0));
    aColors.append(QColor(0,   64,  64));
    aColors.append(QColor(0,   0,   128));
    aColors.append(QColor(0,   0,   64));
    aColors.append(QColor(64,  0,   64));
    aColors.append(QColor(64,  0,   128));

    aColors.append(QColor(0,   0,   0));
    aColors.append(QColor(128, 128, 0));
    aColors.append(QColor(128, 128, 64));
    aColors.append(QColor(128, 128, 128));
    aColors.append(QColor(64,  128, 128));
    aColors.append(QColor(192, 192, 192));
    aColors.append(QColor(64,  0,   64));
    aColors.append(QColor(255, 255, 255));

    if (aAttributes)
    {
        for (int i=0; i<aColors.length(); ++i)
        {
            aColors[i]=aAttributes->colorValue("standardColor"+QString::number(i+1), aColors.at(i));
        }
    }

    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            ColorArea *aArea=new ColorArea(0, this);
            aArea->setColor(aColors.at(i*8+j));
            aArea->setFixedSize(26, 22);
            aArea->setFrameRect(QRect(2, 2, 22, 18));
            aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            aArea->setTransparentBlockSize(4);
            aArea->setSelectAllowed(false);
            aArea->setPopupAllowed(false);

            ui->basicGridLayout->addWidget(aArea, i, j, 1, 1);

            connect(aArea, SIGNAL(clicked()), this, SLOT(basicColorClicked()));
        }
    }

    mSelectedBasicColorArea=0;

    // --------------------------------------------------------------------------------------------

    aColors.clear();

    QSettings aSettings(QSettings::UserScope, QLatin1String("Trolltech"));

    for (int i=0; i<2*8; ++i)
    {
        QVariant v=aSettings.value(QLatin1String("Qt/customColors/A")+QString::number(i));

        if (v.isValid())
        {
            QRgb rgb=v.toUInt();
            aColors.append(QColor::fromRgba(rgb));
        }
        else
        {
            aColors.append(QColor(255, 255, 255));
        }
    }

    for (int i=0; i<2; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            ColorArea *aArea=new ColorArea(0, this);
            aArea->setColor(aColors.at(i*8+j));
            aArea->setFixedSize(26, 22);
            aArea->setFrameRect(QRect(2, 2, 22, 18));
            aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            aArea->setTransparentBlockSize(4);
            aArea->setSelectAllowed(false);
            aArea->setPopupAllowed(false);

            ui->customGridLayout->addWidget(aArea, i, j, 1, 1);

            connect(aArea, SIGNAL(clicked()), this, SLOT(customColorClicked()));
        }
    }

    mSelectedCustomColorArea=(ColorArea *)ui->customGridLayout->itemAtPosition(0, 0)->widget();
    mSelectedCustomColorArea->setSelected(true);

    // --------------------------------------------------------------------------------------------

    mColorSpectrum = new ColorSpectrum(this);

    mColorSpectrum->setFixedSize(222, 202);
    mColorSpectrum->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->colorSelectionLayout->addWidget(mColorSpectrum);

    connect(mColorSpectrum, SIGNAL(colorChanged(QColor)), this, SLOT(spectrumColorChanged(QColor)));



    mValueColorBar = new ColorBar(this);

    mValueColorBar->setFixedSize(20, 208);
    mValueColorBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->colorSelectionLayout->addWidget(mValueColorBar);

    connect(mValueColorBar, SIGNAL(valueChanged(int)), this, SLOT(on_valSpinBox_valueChanged(int)));



    mTransparencyColorBar = new ColorBar(this);

    mTransparencyColorBar->setFixedSize(20, 208);
    mTransparencyColorBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->colorSelectionLayout->addWidget(mTransparencyColorBar);

    connect(mTransparencyColorBar, SIGNAL(valueChanged(int)), this, SLOT(on_alphaSpinBox_valueChanged(int)));

    // --------------------------------------------------------------------------------------------

    mMainColorArea=new ColorArea(0, this);
    mMainColorArea->setFixedSize(60, 78);
    mMainColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mMainColorArea->setSelectAllowed(false);
    mMainColorArea->setPopupAllowed(false);

    ui->propertiesLayout->insertWidget(0, mMainColorArea);

    setColor(aColor);

    if (aAttributes)
    {
        if (!aAttributes->boolValue("alphaEnabled", true))
        {
            mTransparencyColorBar->setVisible(false);
            ui->alphaLabel->setVisible(false);
            ui->alphaSpinBox->setVisible(false);
        }
    }
}

ColorEditDialog::~ColorEditDialog()
{
    QSettings aSettings(QSettings::UserScope, QLatin1String("Trolltech"));

    for (int i=0; i<2; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            aSettings.setValue(QLatin1String("Qt/customColors/A")+QString::number(i*8+j), ((ColorArea *) ui->customGridLayout->itemAtPosition(i, j)->widget())->color().rgba());
        }
    }

    delete ui;
}

QColor ColorEditDialog::selectedColor() const
{
    return mMainColorArea->color();
}

#define BLOCK_SIGNALS(aLock) \
    mColorSpectrum->blockSignals(aLock); \
    mValueColorBar->blockSignals(aLock); \
    mTransparencyColorBar->blockSignals(aLock); \
    ui->hueSpinBox->blockSignals(aLock); \
    ui->satSpinBox->blockSignals(aLock); \
    ui->valSpinBox->blockSignals(aLock); \
    ui->redSpinBox->blockSignals(aLock); \
    ui->greenSpinBox->blockSignals(aLock); \
    ui->blueSpinBox->blockSignals(aLock); \
    ui->alphaSpinBox->blockSignals(aLock);

void ColorEditDialog::setColor(const QColor &aColor)
{
    BLOCK_SIGNALS(true);

    mColorSpectrum->setColor(aColor);
    mValueColorBar->setColor(aColor);
    mValueColorBar->setValue(aColor.value());
    mTransparencyColorBar->setValue(aColor.alpha());

    mMainColorArea->setColor(aColor);

    ui->hueSpinBox->setValue(aColor.hue());
    ui->satSpinBox->setValue(aColor.saturation());
    ui->valSpinBox->setValue(aColor.value());

    ui->redSpinBox->setValue(aColor.red());
    ui->greenSpinBox->setValue(aColor.green());
    ui->blueSpinBox->setValue(aColor.blue());
    ui->alphaSpinBox->setValue(aColor.alpha());

    BLOCK_SIGNALS(false);
}

void ColorEditDialog::basicColorClicked()
{
    ColorArea* aArea=(ColorArea *)sender();

    setColor(aArea->color());



    mSelectedCustomColorArea->setSelected(false);

    if (mSelectedBasicColorArea)
    {
        mSelectedBasicColorArea->setSelected(false);
    }

    mSelectedBasicColorArea=aArea;
    mSelectedBasicColorArea->setSelected(true);
}

void ColorEditDialog::customColorClicked()
{
    ColorArea* aArea=(ColorArea *)sender();

    setColor(aArea->color());



    mSelectedCustomColorArea->setSelected(false);

    if (mSelectedBasicColorArea)
    {
        mSelectedBasicColorArea->setSelected(false);
        mSelectedBasicColorArea=0;
    }

    mSelectedCustomColorArea=aArea;
    mSelectedCustomColorArea->setSelected(true);
}

void ColorEditDialog::spectrumColorChanged(QColor aColor)
{
    setColor(QColor::fromHsv(aColor.hue(),            aColor.saturation(),     ui->valSpinBox->value(), ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_hueSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(aValue,                  ui->satSpinBox->value(), ui->valSpinBox->value(), ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_satSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(ui->hueSpinBox->value(), aValue,                  ui->valSpinBox->value(), ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_valSpinBox_valueChanged(int aValue)
{
    setColor(QColor::fromHsv(ui->hueSpinBox->value(), ui->satSpinBox->value(), aValue,                  ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_redSpinBox_valueChanged(int aValue)
{
    setColor(QColor(aValue,                  ui->greenSpinBox->value(), ui->blueSpinBox->value(), ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_greenSpinBox_valueChanged(int aValue)
{
    setColor(QColor(ui->redSpinBox->value(), aValue,                    ui->blueSpinBox->value(), ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_blueSpinBox_valueChanged(int aValue)
{
    setColor(QColor(ui->redSpinBox->value(), ui->greenSpinBox->value(), aValue,                   ui->alphaSpinBox->value()));
}

void ColorEditDialog::on_alphaSpinBox_valueChanged(int aValue)
{
    setColor(QColor(ui->redSpinBox->value(), ui->greenSpinBox->value(), ui->blueSpinBox->value(), aValue));
}

void ColorEditDialog::on_addToCustomButton_clicked()
{
    mSelectedCustomColorArea->setColor(mMainColorArea->color());
}

void ColorEditDialog::on_okButton_clicked()
{
    accept();
}

void ColorEditDialog::on_cancelButton_clicked()
{
    reject();
}
