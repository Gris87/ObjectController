#include "easingcurveeditdialog.h"
#include "ui_easingcurveeditdialog.h"

#include <QPainter>
#include <QMetaEnum>
#include <QTimer>

EasingCurveEditDialog::EasingCurveEditDialog(QEasingCurve aEasingCurve, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EasingCurveEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mOriginalEasingCurve=aEasingCurve;
    mEasingCurve=aEasingCurve;



    ui->typeComboBox->blockSignals(true);
    ui->amplitudeSpinBox->blockSignals(true);
    ui->overshootSpinBox->blockSignals(true);
    ui->periodSpinBox->blockSignals(true);



    QMetaEnum aEnum=mEasingCurve.staticMetaObject.enumerator(mEasingCurve.staticMetaObject.indexOfEnumerator("Type"));
    QStringList aItems;

    for (int i=0; i<(mEasingCurve.type()==QEasingCurve::Custom? QEasingCurve::NCurveTypes : QEasingCurve::Custom); ++i)
    {
        aItems.append(QString::fromLatin1(aEnum.key(i)));
    }

    ui->typeComboBox->addItems(aItems);
    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aEnum.valueToKey(mEasingCurve.type())));

    ui->amplitudeSpinBox->setValue(mEasingCurve.amplitude());
    ui->overshootSpinBox->setValue(mEasingCurve.overshoot());
    ui->periodSpinBox->setValue(mEasingCurve.period());



    ui->typeComboBox->blockSignals(false);
    ui->amplitudeSpinBox->blockSignals(false);
    ui->overshootSpinBox->blockSignals(false);
    ui->periodSpinBox->blockSignals(false);



    QTimer::singleShot(0, this, SLOT(drawCurve()));
}

EasingCurveEditDialog::~EasingCurveEditDialog()
{
    delete ui;
}

QEasingCurve EasingCurveEditDialog::resultValue() const
{
    return mEasingCurve;
}

void EasingCurveEditDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    drawCurve();
}

void EasingCurveEditDialog::drawCurve()
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
    aPainter.setPen(QColor(0, 0, 255));

    for (int i=0; i<aWidth; ++i)
    {
        aPainter.drawLine(i, aHeight-mEasingCurve.valueForProgress(i/((double)aWidth))*aHeight, i+1, aHeight-mEasingCurve.valueForProgress((i+1)/((double)aWidth))*aHeight);
    }

    aPainter.end();

    ui->resultLabel->setPixmap(aPixmap);
}

void EasingCurveEditDialog::on_typeComboBox_currentIndexChanged(QString aValue)
{
    QMetaEnum aEnum=mEasingCurve.staticMetaObject.enumerator(mEasingCurve.staticMetaObject.indexOfEnumerator("Type"));
    QEasingCurve::Type aType=(QEasingCurve::Type)aEnum.keyToValue(aValue.toLatin1());

    if (mOriginalEasingCurve.type()==aType)
    {
        mEasingCurve=mOriginalEasingCurve;
    }
    else
    {
        mEasingCurve=QEasingCurve(aType);
    }

    mEasingCurve.setAmplitude(ui->amplitudeSpinBox->value());
    mEasingCurve.setOvershoot(ui->overshootSpinBox->value());
    mEasingCurve.setPeriod(ui->periodSpinBox->value());

    drawCurve();
}

void EasingCurveEditDialog::on_amplitudeSpinBox_valueChanged(double aValue)
{
    mEasingCurve.setAmplitude(aValue);
    drawCurve();
}

void EasingCurveEditDialog::on_overshootSpinBox_valueChanged(double aValue)
{
    mEasingCurve.setOvershoot(aValue);
    drawCurve();
}

void EasingCurveEditDialog::on_periodSpinBox_valueChanged(double aValue)
{
    mEasingCurve.setPeriod(aValue);
    drawCurve();
}

void EasingCurveEditDialog::on_okButton_clicked()
{
    accept();
}

void EasingCurveEditDialog::on_cancelButton_clicked()
{
    reject();
}
