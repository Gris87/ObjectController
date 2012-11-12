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

    updateProperties();

    drawTexture();
    drawTextureImage();
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

}

void BrushEditDialog::drawTextureImage()
{

}

void BrushEditDialog::drawBrush()
{
    int aWidth=ui->resultLabel->width();
    int aHeight=ui->resultLabel->height();

    if (aWidth<1)
    {
        aWidth=166;
    }

    if (aHeight<1)
    {
        aHeight=166;
    }

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
        mBrush.setStyle(Qt::LinearGradientPattern);
    }
    else
    if (aValue=="RadialGradientPattern")
    {
        mBrush.setStyle(Qt::RadialGradientPattern);
    }
    else
    if (aValue=="ConicalGradientPattern")
    {
        mBrush.setStyle(Qt::ConicalGradientPattern);
    }
    else
    if (aValue=="TexturePattern")
    {
        mBrush.setStyle(Qt::TexturePattern);
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
        mBrush.setTexture(dialog.resultValue());

        drawTexture();
        drawTextureImage();
        drawBrush();
    }
}

void BrushEditDialog::on_textureImageButton_clicked()
{
    PaintDialog dialog(QPixmap::fromImage(mBrush.textureImage()), false, this);

    if (dialog.exec())
    {
        mBrush.setTextureImage(dialog.resultValue().toImage());

        drawTexture();
        drawTextureImage();
        drawBrush();
    }
}

void BrushEditDialog::on_matrixButton_clicked()
{
    MatrixEditDialog dialog(mBrush.matrix(), this);

    if (dialog.exec())
    {
        mBrush.setMatrix(dialog.resultValue());

        updateProperties();

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

void BrushEditDialog::updateProperties()
{
    ui->styleComboBox->blockSignals(true);
    mColorArea->blockSignals(true);



    QString aStyle="[Unknown brush style]";

    switch (mBrush.style())
    {
        case Qt::NoBrush:                aStyle="NoBrush";                break;
        case Qt::SolidPattern:           aStyle="SolidPattern";           break;
        case Qt::Dense1Pattern:          aStyle="Dense1Pattern";          break;
        case Qt::Dense2Pattern:          aStyle="Dense2Pattern";          break;
        case Qt::Dense3Pattern:          aStyle="Dense3Pattern";          break;
        case Qt::Dense4Pattern:          aStyle="Dense4Pattern";          break;
        case Qt::Dense5Pattern:          aStyle="Dense5Pattern";          break;
        case Qt::Dense6Pattern:          aStyle="Dense6Pattern";          break;
        case Qt::Dense7Pattern:          aStyle="Dense7Pattern";          break;
        case Qt::HorPattern:             aStyle="HorPattern";             break;
        case Qt::VerPattern:             aStyle="VerPattern";             break;
        case Qt::CrossPattern:           aStyle="CrossPattern";           break;
        case Qt::BDiagPattern:           aStyle="BDiagPattern";           break;
        case Qt::FDiagPattern:           aStyle="FDiagPattern";           break;
        case Qt::DiagCrossPattern:       aStyle="DiagCrossPattern";       break;
        case Qt::LinearGradientPattern:  aStyle="LinearGradientPattern";  break;
        case Qt::RadialGradientPattern:  aStyle="RadialGradientPattern";  break;
        case Qt::ConicalGradientPattern: aStyle="ConicalGradientPattern"; break;
        case Qt::TexturePattern:         aStyle="TexturePattern";         break;
    }

    QMatrix aMatrix=mBrush.matrix();
    QTransform aTransform=mBrush.transform();

    ui->styleComboBox->setCurrentIndex(ui->styleComboBox->findText(aStyle));
    mColorArea->setColor(mBrush.color());

    ui->matrixEdit->setText(
                            "[("+
                            QString::number(aMatrix.m11())+
                            ", "+
                            QString::number(aMatrix.m12())+
                            "), ("+
                            QString::number(aMatrix.m21())+
                            ", "+
                            QString::number(aMatrix.m22())+
                            "); ("+
                            QString::number(aMatrix.dx())+
                            ", "+
                            QString::number(aMatrix.dy())+
                            ")]"
                           );

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



    ui->styleComboBox->blockSignals(false);
    mColorArea->blockSignals(false);
}
