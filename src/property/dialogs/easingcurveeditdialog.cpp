#include "easingcurveeditdialog.h"
#include "ui_easingcurveeditdialog.h"

#include <QPainter>
#include <QMetaEnum>

EasingCurveEditDialog::EasingCurveEditDialog(QEasingCurve aEasingCurve, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EasingCurveEditDialog)
{
    ui->setupUi(this);

    mEasingCurve=aEasingCurve;

    QMetaEnum aEnum=mEasingCurve.staticMetaObject.enumerator(mEasingCurve.staticMetaObject.indexOfEnumerator("Type"));
    int index=ui->typeComboBox->findText(aEnum.valueToKey(mEasingCurve.type()));

    if (index<0)
    {
        index=0;
    }

    ui->typeComboBox->setCurrentIndex(index);
    ui->amplitudeSpinBox->setValue(mEasingCurve.amplitude());
    ui->overshootSpinBox->setValue(mEasingCurve.overshoot());
    ui->periodSpinBox->setValue(mEasingCurve.period());

    drawCurve();
}

EasingCurveEditDialog::~EasingCurveEditDialog()
{
    delete ui;
}

QEasingCurve EasingCurveEditDialog::resultValue() const
{
    return mEasingCurve;
}

void EasingCurveEditDialog::drawCurve()
{
    QPixmap aPixmap(100, 100);
    aPixmap.fill(QColor(255, 255, 255));

    QPainter aPainter(&aPixmap);
    aPainter.setPen(QColor(0, 0, 255));

    for (int i=0; i<100; ++i)
    {
        aPainter.drawLine(i, 100-mEasingCurve.valueForProgress(i*0.01f)*100, i+1, 100-mEasingCurve.valueForProgress((i+1)*0.01f)*100);
    }

    aPainter.end();

    ui->resultLabel->setPixmap(aPixmap);
}

void EasingCurveEditDialog::on_typeComboBox_currentIndexChanged(QString aValue)
{
    QMetaEnum aEnum=mEasingCurve.staticMetaObject.enumerator(mEasingCurve.staticMetaObject.indexOfEnumerator("Type"));
    mEasingCurve.setType((QEasingCurve::Type)aEnum.keyToValue(aValue.toLatin1()));

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
