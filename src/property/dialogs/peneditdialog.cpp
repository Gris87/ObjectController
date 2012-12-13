#include "peneditdialog.h"
#include "ui_peneditdialog.h"

#include <QPainter>
#include <QScrollBar>
#include <QTimer>
#include <QMetaEnum>

#include "brusheditdialog.h"
#include "../widgets/doubleframe.h"

PenEditDialog::PenEditDialog(QPen aPen, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PenEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mPen=aPen;

    // TODO: Add attributes here
    mColorArea=new ColorArea(0, this);
    mColorArea->setMinimumSize(20, 20);
    mColorArea->setMaximumSize(20, 20);
    mColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mColorArea->setTransparentBlockSize(5);
    ui->colorLayout->insertWidget(0, mColorArea);

    connect(mColorArea, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));



    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenStyle"));
    QMetaEnum aCapStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenCapStyle"));
    QMetaEnum aJoinStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenJoinStyle"));
    QStringList aStyleItems;
    QStringList aCapStyleItems;
    QStringList aJoinStyleItems;

    for (int i=0; i<aStyleEnum.keyCount(); ++i)
    {
        aStyleItems.append(QString::fromLatin1(aStyleEnum.key(i)));
    }

    for (int i=0; i<aCapStyleEnum.keyCount(); ++i)
    {
        aCapStyleItems.append(QString::fromLatin1(aCapStyleEnum.key(i)));
    }

    for (int i=0; i<aJoinStyleEnum.keyCount(); ++i)
    {
        aJoinStyleItems.append(QString::fromLatin1(aJoinStyleEnum.key(i)));
    }

    ui->styleComboBox->blockSignals(true);
    ui->capStyleComboBox->blockSignals(true);
    ui->joinStyleComboBox->blockSignals(true);

    ui->styleComboBox->addItems(aStyleItems);
    ui->capStyleComboBox->addItems(aCapStyleItems);
    ui->joinStyleComboBox->addItems(aJoinStyleItems);

    ui->styleComboBox->blockSignals(false);
    ui->capStyleComboBox->blockSignals(false);
    ui->joinStyleComboBox->blockSignals(false);



    updateProperties(true);

    drawBrush();
    QTimer::singleShot(0, this, SLOT(drawPen()));
}

PenEditDialog::~PenEditDialog()
{
    delete ui;
}

QPen PenEditDialog::resultValue() const
{
    return mPen;
}

void PenEditDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    drawPen();
}

void PenEditDialog::drawBrush()
{
    int aWidth=32;
    int aHeight=32;

    QPixmap aPixmap(aWidth, aHeight);
    aPixmap.fill(QColor(255, 255, 255));

    QPainter aPainter(&aPixmap);
    aPainter.fillRect(0, 0, aWidth, aHeight, mPen.brush());
    aPainter.end();

    ui->brushIconLabel->setPixmap(QIcon(aPixmap).pixmap(18, 18));
}

void PenEditDialog::drawPen()
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

    QPolygon aPolygon;

    aPolygon.append(QPoint(aWidth>>3,   aHeight>>3));
    aPolygon.append(QPoint(3*aWidth>>2, aHeight>>2));
    aPolygon.append(QPoint(aWidth>>1, 3*aHeight>>2));
    aPolygon.append(QPoint(aWidth>>3, 5*aHeight>>3));
    aPolygon.append(QPoint(aWidth>>1,   aHeight>>1));

    QPainter aPainter(&aPixmap);
    aPainter.setPen(mPen);
    aPainter.drawPolygon(aPolygon);
    aPainter.end();

    ui->resultLabel->setPixmap(aPixmap);
}

void PenEditDialog::on_okButton_clicked()
{
    accept();
}

void PenEditDialog::on_cancelButton_clicked()
{
    reject();
}

void PenEditDialog::on_brushButton_clicked()
{
    // TODO: Add attributes here
    BrushEditDialog dialog(mPen.brush(), 0, this);

    if (dialog.exec())
    {
        mPen.setBrush(dialog.resultValue());

        mColorArea->blockSignals(true);
        mColorArea->setColor(mPen.color());
        mColorArea->blockSignals(false);

        drawBrush();
        drawPen();
    }
}

void PenEditDialog::on_widthSpinBox_valueChanged(double aValue)
{
    mPen.setWidthF(aValue);
    drawPen();
}

void PenEditDialog::on_styleComboBox_currentIndexChanged(const QString &aValue)
{
    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenStyle"));
    mPen.setStyle((Qt::PenStyle)aStyleEnum.keyToValue(aValue.toLatin1()));

    updateProperties(true);

    drawPen();
}

void PenEditDialog::on_capStyleComboBox_currentIndexChanged(const QString &aValue)
{
    QMetaEnum aCapStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenCapStyle"));
    mPen.setCapStyle((Qt::PenCapStyle)aCapStyleEnum.keyToValue(aValue.toLatin1()));

    updateProperties(true);

    drawPen();
}

void PenEditDialog::on_joinStyleComboBox_currentIndexChanged(const QString &aValue)
{
    QMetaEnum aJoinStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenJoinStyle"));
    mPen.setJoinStyle((Qt::PenJoinStyle)aJoinStyleEnum.keyToValue(aValue.toLatin1()));

    updateProperties(true);

    drawPen();
}

void PenEditDialog::colorChanged(QColor aColor)
{
    mPen.setColor(aColor);

    drawBrush();
    drawPen();
}

void PenEditDialog::on_cosmeticCheckBox_toggled(bool aChecked)
{
    mPen.setCosmetic(aChecked);
    drawPen();
}

void PenEditDialog::on_milerLimitSpinBox_valueChanged(double aValue)
{
    mPen.setMiterLimit(aValue);
    drawPen();
}

void PenEditDialog::on_dashOffsetSpinBox_valueChanged(double aValue)
{
    mPen.setDashOffset(aValue);
    drawPen();
}

void PenEditDialog::on_addButton_clicked()
{
    addPattern();
    updatePattern();
}

void PenEditDialog::updatePattern()
{
    QVector<qreal> aPattern;

    for (int i=0; i<ui->patternLayout->count(); ++i)
    {
        aPattern.append(((DoubleFrame *)ui->patternLayout->itemAt(i)->widget())->value());
    }

    if (aPattern.count() & 1)
    {
        aPattern.append(0);
    }

    mPen.setDashPattern(aPattern);

    updateProperties(false);

    drawPen();
}

void PenEditDialog::addPattern()
{
    DoubleFrame *aFrame=new DoubleFrame(this);

    if (ui->patternLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((DoubleFrame *)ui->patternLayout->itemAt(ui->patternLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),          this, SLOT(patternUp()));
    connect(aFrame, SIGNAL(downPressed()),        this, SLOT(patternDown()));
    connect(aFrame, SIGNAL(deletePressed()),      this, SLOT(patternDelete()));
    connect(aFrame, SIGNAL(valueChanged(double)), this, SLOT(patternValueChanged(double)));

    ui->patternLayout->addWidget(aFrame);
    ui->patternScrollArea->verticalScrollBar()->setValue(ui->patternScrollArea->verticalScrollBar()->maximum());
}

void PenEditDialog::patternUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->patternLayout->indexOf(aWidget);

    if (index==1)
    {
        ((DoubleFrame *)ui->patternLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((DoubleFrame *)ui->patternLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->patternLayout->count()-1)
    {
        ((DoubleFrame *)ui->patternLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((DoubleFrame *)ui->patternLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->patternLayout->removeWidget(aWidget);
    ui->patternLayout->insertWidget(index-1, aWidget);

    updatePattern();
}

void PenEditDialog::patternDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->patternLayout->indexOf(aWidget);

    if (index==0)
    {
        ((DoubleFrame *)ui->patternLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((DoubleFrame *)ui->patternLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->patternLayout->count()-2)
    {
        ((DoubleFrame *)ui->patternLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((DoubleFrame *)ui->patternLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->patternLayout->removeWidget(aWidget);
    ui->patternLayout->insertWidget(index+1, aWidget);

    updatePattern();
}

void PenEditDialog::patternDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->patternLayout->count()>1)
    {
        int index=ui->patternLayout->indexOf(aWidget);

        if (index==0)
        {
            ((DoubleFrame *)ui->patternLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->patternLayout->count()-1)
        {
            ((DoubleFrame *)ui->patternLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;

    updatePattern();
}

void PenEditDialog::patternValueChanged(double /*aValue*/)
{
    updatePattern();
}

#define BLOCK_SIGNALS(aLock) \
    mColorArea->blockSignals(aLock); \
    ui->widthSpinBox->blockSignals(aLock); \
    ui->styleComboBox->blockSignals(aLock); \
    ui->capStyleComboBox->blockSignals(aLock); \
    ui->joinStyleComboBox->blockSignals(aLock); \
    ui->cosmeticCheckBox->blockSignals(aLock); \
    ui->milerLimitSpinBox->blockSignals(aLock); \
    ui->dashOffsetSpinBox->blockSignals(aLock);

void PenEditDialog::updateProperties(const bool &aNeedToUpdatePattern)
{
    BLOCK_SIGNALS(true);

    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenStyle"));
    QString aStyle=QString::fromLatin1(aStyleEnum.valueToKey(mPen.style()));

    QMetaEnum aCapStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenCapStyle"));
    QString aCapStyle=QString::fromLatin1(aCapStyleEnum.valueToKey(mPen.capStyle()));

    QMetaEnum aJoinStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenJoinStyle"));
    QString aJoinStyle=QString::fromLatin1(aJoinStyleEnum.valueToKey(mPen.joinStyle()));

    mColorArea->setColor(mPen.color());
    ui->widthSpinBox->setValue(mPen.widthF());
    ui->styleComboBox->setCurrentIndex(ui->styleComboBox->findText(aStyle));
    ui->capStyleComboBox->setCurrentIndex(ui->capStyleComboBox->findText(aCapStyle));
    ui->joinStyleComboBox->setCurrentIndex(ui->joinStyleComboBox->findText(aJoinStyle));
    ui->cosmeticCheckBox->setChecked(mPen.isCosmetic());
    ui->milerLimitSpinBox->setValue(mPen.miterLimit());
    ui->dashOffsetSpinBox->setValue(mPen.dashOffset());

    if (aNeedToUpdatePattern)
    {
        while (ui->patternLayout->count()>0)
        {
            delete ui->patternLayout->takeAt(0)->widget();
        }

        QVector<qreal> aPattern=mPen.dashPattern();

        for (int i=0; i<aPattern.count(); ++i)
        {
            addPattern();

            ((DoubleFrame *)ui->patternLayout->itemAt(i)->widget())->blockSignals(true);
            ((DoubleFrame *)ui->patternLayout->itemAt(i)->widget())->setValue(aPattern.at(i));
            ((DoubleFrame *)ui->patternLayout->itemAt(i)->widget())->blockSignals(false);
        }
    }

    BLOCK_SIGNALS(false);
}
