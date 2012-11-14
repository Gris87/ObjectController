#include "brusheditdialog.h"
#include "ui_brusheditdialog.h"

#include <QPainter>

#include "paintdialog.h"
#include "matrixeditdialog.h"
#include "transformeditdialog.h"

BrushEditDialog::BrushEditDialog(QBrush aBrush, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mBrush=aBrush;

    mColorArea=new ColorArea(this);
    mColorArea->setMinimumSize(20, 20);
    mColorArea->setMaximumSize(20, 20);
    mColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->colorLayout->insertWidget(0, mColorArea);

    connect(mColorArea, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));



    Qt::BrushStyle aStyle=mBrush.style();

    if (aStyle==Qt::LinearGradientPattern)
    {
        mLinearGradient=*(QLinearGradient *)mBrush.gradient();
    }
    else
    if (aStyle==Qt::RadialGradientPattern)
    {
        mRadialGradient=*(QRadialGradient *)mBrush.gradient();
    }
    else
    if (aStyle==Qt::ConicalGradientPattern)
    {
        mConicalGradient=*(QConicalGradient *)mBrush.gradient();
    }

    if (aStyle==Qt::TexturePattern)
    {
        mTexture=mBrush.texture();
    }
    else
    {
        mTexture=QPixmap(32, 32);
        mTexture.fill(QColor(255, 255, 255));
    }



    updateProperties();

    drawTexture();
    drawBrush();
}

BrushEditDialog::~BrushEditDialog()
{
    delete ui;
}

QBrush BrushEditDialog::resultValue() const
{
    return mBrush;
}

void BrushEditDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    drawBrush();
}

void BrushEditDialog::drawTexture()
{
    ui->textureIconLabel->setPixmap(QIcon(mTexture).pixmap(18));
}

void BrushEditDialog::drawBrush()
{
    int aWidth=ui->resultLabel->width();
    int aHeight=ui->resultLabel->height();

    QPixmap aPixmap(aWidth, aHeight);
    aPixmap.fill(QColor(255, 255, 255));

    QPainter aPainter(&aPixmap);
    aPainter.fillRect(0, 0, aWidth, aHeight, mBrush);
    aPainter.end();

    ui->resultLabel->setPixmap(aPixmap);
}

void BrushEditDialog::on_okButton_clicked()
{
    accept();
}

void BrushEditDialog::on_cancelButton_clicked()
{
    reject();
}

void BrushEditDialog::on_styleComboBox_currentIndexChanged(const QString &aValue)
{
    if (aValue=="NoBrush")
    {
        mBrush.setStyle(Qt::NoBrush);
    }
    else
    if (aValue=="SolidPattern")
    {
        mBrush.setStyle(Qt::SolidPattern);
    }
    else
    if (aValue=="Dense1Pattern")
    {
        mBrush.setStyle(Qt::Dense1Pattern);
    }
    else
    if (aValue=="Dense2Pattern")
    {
        mBrush.setStyle(Qt::Dense2Pattern);
    }
    else
    if (aValue=="Dense3Pattern")
    {
        mBrush.setStyle(Qt::Dense3Pattern);
    }
    else
    if (aValue=="Dense4Pattern")
    {
        mBrush.setStyle(Qt::Dense4Pattern);
    }
    else
    if (aValue=="Dense5Pattern")
    {
        mBrush.setStyle(Qt::Dense5Pattern);
    }
    else
    if (aValue=="Dense6Pattern")
    {
        mBrush.setStyle(Qt::Dense6Pattern);
    }
    else
    if (aValue=="Dense7Pattern")
    {
        mBrush.setStyle(Qt::Dense7Pattern);
    }
    else
    if (aValue=="HorPattern")
    {
        mBrush.setStyle(Qt::HorPattern);
    }
    else
    if (aValue=="VerPattern")
    {
        mBrush.setStyle(Qt::VerPattern);
    }
    else
    if (aValue=="CrossPattern")
    {
        mBrush.setStyle(Qt::CrossPattern);
    }
    else
    if (aValue=="BDiagPattern")
    {
        mBrush.setStyle(Qt::BDiagPattern);
    }
    else
    if (aValue=="FDiagPattern")
    {
        mBrush.setStyle(Qt::FDiagPattern);
    }
    else
    if (aValue=="DiagCrossPattern")
    {
        mBrush.setStyle(Qt::DiagCrossPattern);
    }
    else
    if (aValue=="LinearGradientPattern")
    {
        copyFromBrush(QBrush(mLinearGradient));
    }
    else
    if (aValue=="RadialGradientPattern")
    {
        copyFromBrush(QBrush(mRadialGradient));
    }
    else
    if (aValue=="ConicalGradientPattern")
    {
        copyFromBrush(QBrush(mConicalGradient));
    }
    else
    if (aValue=="TexturePattern")
    {
        copyFromBrush(QBrush(mTexture));
    }
    else
    {
        Q_ASSERT(false);
    }

    updateProperties();

    drawBrush();
}

void BrushEditDialog::colorChanged(QColor aColor)
{
    mBrush.setColor(aColor);
    drawBrush();
}

void BrushEditDialog::on_textureButton_clicked()
{
    PaintDialog dialog(mBrush.texture(), false, this);

    if (dialog.exec())
    {
        mTexture=dialog.resultValue();
        mBrush.setTexture(mTexture);

        drawTexture();
        drawBrush();
    }
}

void BrushEditDialog::on_transformButton_clicked()
{
    TransformEditDialog dialog(mBrush.transform(), this);

    if (dialog.exec())
    {
        mBrush.setTransform(dialog.resultValue());

        updateProperties();

        drawBrush();
    }
}

void BrushEditDialog::copyFromBrush(QBrush aBrush)
{
    aBrush.setColor(mBrush.color());
    aBrush.setTransform(mBrush.transform());

    mBrush=aBrush;
}

void BrushEditDialog::updateProperties()
{
    ui->styleComboBox->blockSignals(true);
    mColorArea->blockSignals(true);



    Qt::BrushStyle aStyle=mBrush.style();
    QString aStyleStr="[Unknown brush style]";

    switch (aStyle)
    {
        case Qt::NoBrush:                aStyleStr="NoBrush";                break;
        case Qt::SolidPattern:           aStyleStr="SolidPattern";           break;
        case Qt::Dense1Pattern:          aStyleStr="Dense1Pattern";          break;
        case Qt::Dense2Pattern:          aStyleStr="Dense2Pattern";          break;
        case Qt::Dense3Pattern:          aStyleStr="Dense3Pattern";          break;
        case Qt::Dense4Pattern:          aStyleStr="Dense4Pattern";          break;
        case Qt::Dense5Pattern:          aStyleStr="Dense5Pattern";          break;
        case Qt::Dense6Pattern:          aStyleStr="Dense6Pattern";          break;
        case Qt::Dense7Pattern:          aStyleStr="Dense7Pattern";          break;
        case Qt::HorPattern:             aStyleStr="HorPattern";             break;
        case Qt::VerPattern:             aStyleStr="VerPattern";             break;
        case Qt::CrossPattern:           aStyleStr="CrossPattern";           break;
        case Qt::BDiagPattern:           aStyleStr="BDiagPattern";           break;
        case Qt::FDiagPattern:           aStyleStr="FDiagPattern";           break;
        case Qt::DiagCrossPattern:       aStyleStr="DiagCrossPattern";       break;
        case Qt::LinearGradientPattern:  aStyleStr="LinearGradientPattern";  break;
        case Qt::RadialGradientPattern:  aStyleStr="RadialGradientPattern";  break;
        case Qt::ConicalGradientPattern: aStyleStr="ConicalGradientPattern"; break;
        case Qt::TexturePattern:         aStyleStr="TexturePattern";         break;
    }

    QMatrix aMatrix=mBrush.matrix();
    QTransform aTransform=mBrush.transform();

    ui->styleComboBox->setCurrentIndex(ui->styleComboBox->findText(aStyleStr));
    mColorArea->setColor(mBrush.color());

    ui->transformEdit->setText(
                               "[("+
                               QString::number(aTransform.m11())+
                               ", "+
                               QString::number(aTransform.m12())+
                               ", "+
                               QString::number(aTransform.m13())+
                               "), ("+
                               QString::number(aTransform.m21())+
                               ", "+
                               QString::number(aTransform.m22())+
                               ", "+
                               QString::number(aTransform.m23())+
                               "), ("+
                               QString::number(aTransform.m31())+
                               ", "+
                               QString::number(aTransform.m32())+
                               ", "+
                               QString::number(aTransform.m33())+
                               ")]"
                              );

    ui->colorWidget->setVisible(
                                aStyle==Qt::SolidPattern
                                ||
                                aStyle==Qt::Dense1Pattern
                                ||
                                aStyle==Qt::Dense2Pattern
                                ||
                                aStyle==Qt::Dense3Pattern
                                ||
                                aStyle==Qt::Dense4Pattern
                                ||
                                aStyle==Qt::Dense5Pattern
                                ||
                                aStyle==Qt::Dense6Pattern
                                ||
                                aStyle==Qt::Dense7Pattern
                                ||
                                aStyle==Qt::HorPattern
                                ||
                                aStyle==Qt::VerPattern
                                ||
                                aStyle==Qt::CrossPattern
                                ||
                                aStyle==Qt::BDiagPattern
                                ||
                                aStyle==Qt::FDiagPattern
                                ||
                                aStyle==Qt::DiagCrossPattern
                               );

    ui->textureWidget->setVisible(aStyle==Qt::TexturePattern);
    ui->transformWidget->setVisible(aStyle!=Qt::NoBrush);

    ui->styleComboBox->blockSignals(false);
    mColorArea->blockSignals(false);
}
