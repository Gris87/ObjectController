#include "brusheditdialog.h"
#include "ui_brusheditdialog.h"

#include <QPainter>
#include <QMetaEnum>
#include <QTimer>

#include "paintdialog.h"
#include "matrixeditdialog.h"
#include "transformeditdialog.h"
#include "../propertyutils.h"

BrushEditDialog::BrushEditDialog(QBrush aBrush, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mBrush=aBrush;
    mDecimals=6;
    mAttributes=aAttributes;



    mColorArea=new ColorArea(mAttributes, this);
    mColorArea->setMinimumSize(20, 20);
    mColorArea->setMaximumSize(20, 20);
    mColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mColorArea->setTransparentBlockSize(5);
    ui->colorLayout->insertWidget(0, mColorArea);

    connect(mColorArea, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));



    mGradientWidget=new GradientWidget(this);
    ui->gradientLayout->insertWidget(1, mGradientWidget);

    connect(mGradientWidget, SIGNAL(gradientChanged(QGradientStops)), this, SLOT(gradientChanged(QGradientStops)));



    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("BrushStyle"));
    QMetaEnum aCoordinateModeEnum=QGradient::staticMetaObject.enumerator(QGradient::staticMetaObject.indexOfEnumerator("CoordinateMode"));
    QMetaEnum aSpreadEnum=QGradient::staticMetaObject.enumerator(QGradient::staticMetaObject.indexOfEnumerator("Spread"));
    QStringList aStyleItems;
    QStringList aCoordinateModeItems;
    QStringList aSpreadItems;

    for (int i=0; i<aStyleEnum.keyCount(); ++i)
    {
        aStyleItems.append(QString::fromLatin1(aStyleEnum.key(i)));
    }

    for (int i=0; i<aCoordinateModeEnum.keyCount(); ++i)
    {
        aCoordinateModeItems.append(QString::fromLatin1(aCoordinateModeEnum.key(i)));
    }

    for (int i=0; i<aSpreadEnum.keyCount(); ++i)
    {
        aSpreadItems.append(QString::fromLatin1(aSpreadEnum.key(i)));
    }

    ui->styleComboBox->blockSignals(true);
    ui->coordinateModeComboBox->blockSignals(true);
    ui->spreadComboBox->blockSignals(true);

    ui->styleComboBox->addItems(aStyleItems);
    ui->coordinateModeComboBox->addItems(aCoordinateModeItems);
    ui->spreadComboBox->addItems(aSpreadItems);

    ui->styleComboBox->blockSignals(false);
    ui->coordinateModeComboBox->blockSignals(false);
    ui->spreadComboBox->blockSignals(false);



    Qt::BrushStyle aStyle=mBrush.style();

    if (aStyle==Qt::LinearGradientPattern)
    {
        mLinearGradient=*(QLinearGradient *)mBrush.gradient();
        mRadialGradient.setStops(mLinearGradient.stops());
        mConicalGradient.setStops(mLinearGradient.stops());
    }
    else
    if (aStyle==Qt::RadialGradientPattern)
    {
        mRadialGradient=*(QRadialGradient *)mBrush.gradient();
        mLinearGradient.setStops(mRadialGradient.stops());
        mConicalGradient.setStops(mRadialGradient.stops());
    }
    else
    if (aStyle==Qt::ConicalGradientPattern)
    {
        mConicalGradient=*(QConicalGradient *)mBrush.gradient();
        mLinearGradient.setStops(mConicalGradient.stops());
        mRadialGradient.setStops(mConicalGradient.stops());
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



    if (aAttributes)
    {
        aAttributes->applyToCombobox(ui->styleComboBox);

        mDecimals=aAttributes->intValue("decimals", mDecimals);

        ui->styleComboBox->setEnabled(  aAttributes->boolValue("allowChangeType", ui->styleComboBox->isEnabled()));
        ui->transformButton->setVisible(aAttributes->boolValue("allowTransform",  true));

        if (aAttributes->boolValue("allowGradient", true))
        {
            aAttributes->applyToCombobox(ui->coordinateModeComboBox);
            aAttributes->applyToCombobox(ui->spreadComboBox);

            aAttributes->applyToDoubleSpinBox(ui->linearX1SpinBox);
            aAttributes->applyToDoubleSpinBox(ui->linearY1SpinBox);
            aAttributes->applyToDoubleSpinBox(ui->linearX2SpinBox);
            aAttributes->applyToDoubleSpinBox(ui->linearY2SpinBox);

            aAttributes->applyToDoubleSpinBox(ui->radialCenterXSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->radialCenterYSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->radialRadiusSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->radialFocalXSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->radialFocalYSpinBox);

            aAttributes->applyToDoubleSpinBox(ui->conicalCenterXSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->conicalCenterYSpinBox);
            aAttributes->applyToDoubleSpinBox(ui->conicalAngleSpinBox);
        }
        else
        {
            aStyleItems.removeOne("LinearGradientPattern");
            aStyleItems.removeOne("RadialGradientPattern");
            aStyleItems.removeOne("ConicalGradientPattern");

            ui->styleComboBox->blockSignals(true);

            ui->styleComboBox->clear();
            ui->styleComboBox->addItems(aStyleItems);

            ui->styleComboBox->blockSignals(false);

            if (
                aStyle==Qt::LinearGradientPattern
                ||
                aStyle==Qt::RadialGradientPattern
                ||
                aStyle==Qt::ConicalGradientPattern
               )
            {
                mBrush.setStyle(Qt::NoBrush);
            }
        }
    }



    updateProperties();

    drawTexture();
    QTimer::singleShot(0, this, SLOT(updateTransparentArea()));
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
    updateTransparentArea();
}

void BrushEditDialog::drawTexture()
{
    ui->textureIconLabel->setPixmap(QIcon(mTexture).pixmap(18));
}

void BrushEditDialog::updateTransparentArea()
{
    int aWidth=ui->resultLabel->width();
    int aHeight=ui->resultLabel->height();

    mTransparentArea=QPixmap(aWidth, aHeight);

    QPainter aPainter(&mTransparentArea);
    drawTransparentArea(&aPainter, QRect(0, 0, aWidth, aHeight));
    aPainter.end();

    drawBrush();
}

void BrushEditDialog::drawBrush()
{
    Qt::BrushStyle aStyle=mBrush.style();

    int aWidth=ui->resultLabel->width();
    int aHeight=ui->resultLabel->height();

    QPixmap aPixmap(aWidth, aHeight);
    aPixmap.fill(QColor(255, 255, 255));



    QPainter aPainter(&aPixmap);

    if (
        aStyle==Qt::NoBrush
        ||
        aStyle==Qt::SolidPattern
        ||
        aStyle==Qt::LinearGradientPattern
        ||
        aStyle==Qt::RadialGradientPattern
        ||
        aStyle==Qt::ConicalGradientPattern
        ||
        aStyle==Qt::TexturePattern
       )
    {
        aPainter.drawPixmap(0, 0, mTransparentArea);
    }

    aPainter.fillRect(0, 0, aWidth, aHeight, mBrush);
    aPainter.end();

    ui->resultLabel->setPixmap(aPixmap);
}

void BrushEditDialog::drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize)
{
    int aCurRow=0;

    while ((aCurRow*aBoxSize)<aRect.height())
    {
        int aCurCol=0;

        while ((aCurCol*aBoxSize)<aRect.width())
        {
            int aRectWidth=aRect.width()-(aCurCol*aBoxSize);
            int aRectHeight=aRect.height()-(aCurRow*aBoxSize);

            if (aRectWidth>aBoxSize)
            {
                aRectWidth=aBoxSize;
            }

            if (aRectHeight>aBoxSize)
            {
                aRectHeight=aBoxSize;
            }



            if ((aCurRow + aCurCol) & 1)
            {
                aPainter->fillRect(aRect.left()+(aCurCol*aBoxSize), aRect.top()+(aCurRow*aBoxSize), aRectWidth, aRectHeight, QBrush(QColor(255, 255, 255)));
            }
            else
            {
                aPainter->fillRect(aRect.left()+(aCurCol*aBoxSize), aRect.top()+(aCurRow*aBoxSize), aRectWidth, aRectHeight, QBrush(QColor(0, 0, 0)));
            }



            ++aCurCol;
        }

        ++aCurRow;
    }
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
    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("BrushStyle"));
    Qt::BrushStyle aStyle=(Qt::BrushStyle)aStyleEnum.keyToValue(aValue.toLatin1());

    if (aStyle==Qt::LinearGradientPattern)
    {
        copyFromBrush(QBrush(mLinearGradient));
    }
    else
    if (aStyle==Qt::RadialGradientPattern)
    {
        copyFromBrush(QBrush(mRadialGradient));
    }
    else
    if (aStyle==Qt::ConicalGradientPattern)
    {
        copyFromBrush(QBrush(mConicalGradient));
    }
    else
    if (aStyle==Qt::TexturePattern)
    {
        copyFromBrush(QBrush(mTexture));
    }
    else
    {
        mBrush.setStyle(aStyle);
    }

    updateProperties();

    drawBrush();
}

void BrushEditDialog::colorChanged(QColor aColor)
{
    mBrush.setColor(aColor);
    drawBrush();
}

void BrushEditDialog::gradientChanged(const QGradientStops &aGradientStops)
{
    mLinearGradient.setStops(aGradientStops);
    mRadialGradient.setStops(aGradientStops);
    mConicalGradient.setStops(aGradientStops);

    updateGradient();
}

void BrushEditDialog::on_coordinateModeComboBox_currentIndexChanged(const QString &aValue)
{
    QGradient::CoordinateMode aMode=QGradient::LogicalMode;

    if (aValue=="LogicalMode")
    {
        aMode=QGradient::LogicalMode;
    }
    else
    if (aValue=="StretchToDeviceMode")
    {
        aMode=QGradient::StretchToDeviceMode;
    }
    else
    if (aValue=="ObjectBoundingMode")
    {
        aMode=QGradient::ObjectBoundingMode;
    }
    else
    {
        Q_ASSERT(false);
    }

    mLinearGradient.setCoordinateMode(aMode);
    mRadialGradient.setCoordinateMode(aMode);
    mConicalGradient.setCoordinateMode(aMode);

    updateGradient();
}

void BrushEditDialog::on_spreadComboBox_currentIndexChanged(const QString &aValue)
{
    QGradient::Spread aSpread=QGradient::PadSpread;

    if (aValue=="PadSpread")
    {
        aSpread=QGradient::PadSpread;
    }
    else
    if (aValue=="ReflectSpread")
    {
        aSpread=QGradient::ReflectSpread;
    }
    else
    if (aValue=="RepeatSpread")
    {
        aSpread=QGradient::RepeatSpread;
    }
    else
    {
        Q_ASSERT(false);
    }

    mLinearGradient.setSpread(aSpread);
    mRadialGradient.setSpread(aSpread);
    mConicalGradient.setSpread(aSpread);

    updateGradient();
}

void BrushEditDialog::on_linearX1SpinBox_valueChanged(double aValue)
{
    mLinearGradient.setStart(aValue, ui->linearY1SpinBox->value());
    copyFromBrush(QBrush(mLinearGradient));
    drawBrush();
}

void BrushEditDialog::on_linearY1SpinBox_valueChanged(double aValue)
{
    mLinearGradient.setStart(ui->linearX1SpinBox->value(), aValue);
    copyFromBrush(QBrush(mLinearGradient));
    drawBrush();
}

void BrushEditDialog::on_linearX2SpinBox_valueChanged(double aValue)
{
    mLinearGradient.setFinalStop(aValue, ui->linearY2SpinBox->value());
    copyFromBrush(QBrush(mLinearGradient));
    drawBrush();
}

void BrushEditDialog::on_linearY2SpinBox_valueChanged(double aValue)
{
    mLinearGradient.setFinalStop(ui->linearX2SpinBox->value(), aValue);
    copyFromBrush(QBrush(mLinearGradient));
    drawBrush();
}

void BrushEditDialog::on_radialCenterXSpinBox_valueChanged(double aValue)
{
    mRadialGradient.setCenter(aValue, ui->radialCenterYSpinBox->value());
    copyFromBrush(QBrush(mRadialGradient));
    drawBrush();
}

void BrushEditDialog::on_radialCenterYSpinBox_valueChanged(double aValue)
{
    mRadialGradient.setCenter(ui->radialCenterXSpinBox->value(), aValue);
    copyFromBrush(QBrush(mRadialGradient));
    drawBrush();
}

void BrushEditDialog::on_radialRadiusSpinBox_valueChanged(double aValue)
{
    mRadialGradient.setRadius(aValue);
    copyFromBrush(QBrush(mRadialGradient));
    drawBrush();
}

void BrushEditDialog::on_radialFocalXSpinBox_valueChanged(double aValue)
{
    mRadialGradient.setFocalPoint(aValue, ui->radialFocalYSpinBox->value());
    copyFromBrush(QBrush(mRadialGradient));
    drawBrush();
}

void BrushEditDialog::on_radialFocalYSpinBox_valueChanged(double aValue)
{
    mRadialGradient.setFocalPoint(ui->radialFocalXSpinBox->value(), aValue);
    copyFromBrush(QBrush(mRadialGradient));
    drawBrush();
}

void BrushEditDialog::on_conicalCenterXSpinBox_valueChanged(double aValue)
{
    mConicalGradient.setCenter(aValue, ui->conicalCenterYSpinBox->value());
    copyFromBrush(QBrush(mConicalGradient));
    drawBrush();
}

void BrushEditDialog::on_conicalCenterYSpinBox_valueChanged(double aValue)
{
    mConicalGradient.setCenter(ui->conicalCenterXSpinBox->value(), aValue);
    copyFromBrush(QBrush(mConicalGradient));
    drawBrush();
}

void BrushEditDialog::on_conicalAngleSpinBox_valueChanged(double aValue)
{
    mConicalGradient.setAngle(aValue);
    copyFromBrush(QBrush(mConicalGradient));
    drawBrush();
}

void BrushEditDialog::on_textureButton_clicked()
{
    PaintDialog dialog(mBrush.texture(), false, mAttributes, this);

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
    TransformEditDialog dialog(mBrush.transform(), mAttributes, this);

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

void BrushEditDialog::updateGradient()
{
    Qt::BrushStyle aStyle=mBrush.style();

    if (aStyle==Qt::LinearGradientPattern)
    {
        copyFromBrush(QBrush(mLinearGradient));
    }
    else
    if (aStyle==Qt::RadialGradientPattern)
    {
        copyFromBrush(QBrush(mRadialGradient));
    }
    else
    if (aStyle==Qt::ConicalGradientPattern)
    {
        copyFromBrush(QBrush(mConicalGradient));
    }
    else
    {
        Q_ASSERT(false);
    }

    drawBrush();
}

#define BLOCK_SIGNALS(aLock) \
    ui->styleComboBox->blockSignals(aLock); \
    mColorArea->blockSignals(aLock); \
    mGradientWidget->blockSignals(aLock); \
    ui->coordinateModeComboBox->blockSignals(aLock); \
    ui->spreadComboBox->blockSignals(aLock); \
    ui->linearX1SpinBox->blockSignals(aLock); \
    ui->linearY1SpinBox->blockSignals(aLock); \
    ui->linearX2SpinBox->blockSignals(aLock); \
    ui->linearY2SpinBox->blockSignals(aLock); \
    ui->radialCenterXSpinBox->blockSignals(aLock); \
    ui->radialCenterYSpinBox->blockSignals(aLock); \
    ui->radialRadiusSpinBox->blockSignals(aLock); \
    ui->radialFocalXSpinBox->blockSignals(aLock); \
    ui->radialFocalYSpinBox->blockSignals(aLock); \
    ui->conicalCenterXSpinBox->blockSignals(aLock); \
    ui->conicalCenterYSpinBox->blockSignals(aLock); \
    ui->conicalAngleSpinBox->blockSignals(aLock);

void BrushEditDialog::updateProperties()
{
    BLOCK_SIGNALS(true);

    Qt::BrushStyle aStyle=mBrush.style();
    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("BrushStyle"));
    QString aStyleStr=aStyleEnum.valueToKey(aStyle);

    QTransform aTransform=mBrush.transform();

    ui->styleComboBox->setCurrentIndex(ui->styleComboBox->findText(aStyleStr));
    mColorArea->setColor(mBrush.color());

    const QGradient *aGradient=mBrush.gradient();

    if (aGradient)
    {
        mGradientWidget->setGradientStops(aGradient->stops());

        QMetaEnum aCoordinateModeEnum=QGradient::staticMetaObject.enumerator(QGradient::staticMetaObject.indexOfEnumerator("CoordinateMode"));
        QMetaEnum aSpreadEnum=QGradient::staticMetaObject.enumerator(QGradient::staticMetaObject.indexOfEnumerator("Spread"));

        ui->coordinateModeComboBox->setCurrentIndex(ui->coordinateModeComboBox->findText(aCoordinateModeEnum.valueToKey(aGradient->coordinateMode())));
        ui->spreadComboBox->setCurrentIndex(ui->spreadComboBox->findText(aSpreadEnum.valueToKey(aGradient->spread())));
    }

    ui->linearX1SpinBox->setValue(mLinearGradient.start().x());
    ui->linearY1SpinBox->setValue(mLinearGradient.start().y());
    ui->linearX2SpinBox->setValue(mLinearGradient.finalStop().x());
    ui->linearY2SpinBox->setValue(mLinearGradient.finalStop().y());

    ui->radialCenterXSpinBox->setValue(mRadialGradient.center().x());
    ui->radialCenterYSpinBox->setValue(mRadialGradient.center().y());
    ui->radialRadiusSpinBox->setValue(mRadialGradient.radius());
    ui->radialFocalXSpinBox->setValue(mRadialGradient.focalPoint().x());
    ui->radialFocalYSpinBox->setValue(mRadialGradient.focalPoint().y());

    ui->conicalCenterXSpinBox->setValue(mConicalGradient.center().x());
    ui->conicalCenterYSpinBox->setValue(mConicalGradient.center().y());
    ui->conicalAngleSpinBox->setValue(mConicalGradient.angle());



    ui->transformEdit->setText(
                               "[("+
                               doubleToString(aTransform.m11(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m12(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m13(), mDecimals)+
                               "), ("+
                               doubleToString(aTransform.m21(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m22(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m23(), mDecimals)+
                               "), ("+
                               doubleToString(aTransform.m31(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m32(), mDecimals)+
                               ", "+
                               doubleToString(aTransform.m33(), mDecimals)+
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

    ui->gradientWidget->setVisible(
                                   aStyle==Qt::LinearGradientPattern
                                   ||
                                   aStyle==Qt::RadialGradientPattern
                                   ||
                                   aStyle==Qt::ConicalGradientPattern
                                  );

    ui->linearGroupBox->setVisible(aStyle==Qt::LinearGradientPattern);
    ui->radialGroupBox->setVisible(aStyle==Qt::RadialGradientPattern);
    ui->conicalGroupBox->setVisible(aStyle==Qt::ConicalGradientPattern);

    ui->textureWidget->setVisible(aStyle==Qt::TexturePattern);
    ui->transformWidget->setVisible(aStyle!=Qt::NoBrush);

    BLOCK_SIGNALS(false);
}
