#include "cursoreditor.h"
#include "ui_cursoreditor.h"

#include <QBitmap>
#include <QMetaEnum>

#include "../dialogs/paintdialog.h"
#include "../propertyutils.h"

CursorEditor::CursorEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::CursorEditor)
{
    ui->setupUi(this);

    mAttributes=0;

    QMetaEnum aShapeEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("CursorShape"));
    QStringList aShapeItems;

    for (int i=0; i<aShapeEnum.keyCount(); ++i)
    {
        aShapeItems.append(QString::fromLatin1(aShapeEnum.key(i)));
    }

    aShapeItems.removeOne("LastCursor");
    aShapeItems.removeOne("CustomCursor");

    ui->valueComboBox->blockSignals(true);
    ui->valueComboBox->addItems(aShapeItems);
    ui->valueComboBox->blockSignals(false);

    connect(&mHotSpotTimer, SIGNAL(timeout()), this, SLOT(hotSpotChanged()));
}

CursorEditor::~CursorEditor()
{
    if (mHotSpotTimer.isActive())
    {
        hotSpotChanged();
    }

    delete ui;
}

void CursorEditor::putFocus()
{
    ui->valueComboBox->setFocus();
}

void CursorEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void CursorEditor::setValue(const QCursor &aValue)
{
    mCursor=aValue;

    if (mCursor.shape()==Qt::BitmapCursor)
    {
        mBitmapCursor=mCursor;
    }



    QString res=cursorToString(mCursor);

    ui->valueComboBox->setCurrentIndex(ui->valueComboBox->findText(res));



    QIcon aIcon;

    QPixmap aPixmap=mCursor.pixmap();

    if (!aPixmap.isNull())
    {
        aIcon=QIcon(aPixmap);
    }
    else
    {
        const QBitmap *aBitmap=mCursor.bitmap();

        if (aBitmap)
        {
            aPixmap=QPixmap::fromImage(aBitmap->toImage());
            aPixmap.setMask(*mCursor.mask());

            aIcon=QIcon(aPixmap);
        }
        else
        {
            aIcon=QIcon(":/objectcontroller/images/Cursor-"+res+".png");
        }
    }

    setIcon(aIcon);



    ui->xSpinBox->blockSignals(true);
    ui->ySpinBox->blockSignals(true);

    ui->bitmapWidget->setVisible(false);
    ui->bitmapButton->setVisible(false);
    ui->maskButton->setVisible(false);
    ui->pixmapButton->setVisible(false);

    aPixmap=mCursor.pixmap();

    if (!aPixmap.isNull())
    {
        ui->xSpinBox->setValue(mCursor.hotSpot().x());
        ui->ySpinBox->setValue(mCursor.hotSpot().y());

        ui->pixmapButton->setVisible(true);
        ui->bitmapWidget->setVisible(true);
    }
    else
    {
        const QBitmap *aBitmap=mCursor.bitmap();

        if (aBitmap)
        {
            ui->xSpinBox->setValue(mCursor.hotSpot().x());
            ui->ySpinBox->setValue(mCursor.hotSpot().y());

            ui->bitmapButton->setVisible(true);
            ui->maskButton->setVisible(true);
            ui->bitmapWidget->setVisible(true);
        }
    }

    ui->xSpinBox->blockSignals(false);
    ui->ySpinBox->blockSignals(false);
}

void CursorEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;

    aAttributes->applyToCombobox(ui->valueComboBox);
    aAttributes->applyToSpinBox(ui->xSpinBox);
    aAttributes->applyToSpinBox(ui->ySpinBox);

    if (!aAttributes->boolValue("allowBitmap", true))
    {
        ui->valueComboBox->blockSignals(true);

        if (ui->valueComboBox->currentText()=="BitmapCursor")
        {
            ui->valueComboBox->setCurrentIndex(0);
        }

        QString aValue=ui->valueComboBox->currentText();
        QStringList aValues;

        for (int i=0; i<ui->valueComboBox->count(); ++i)
        {
            QString aItem=ui->valueComboBox->itemText(i);

            if (aItem!="BitmapCursor")
            {
                aValues.append(aItem);
            }
        }

        ui->valueComboBox->clear();
        ui->valueComboBox->addItems(aValues);
        ui->valueComboBox->setCurrentIndex(ui->valueComboBox->findText(aValue));

        ui->valueComboBox->blockSignals(false);
    }
}

void CursorEditor::on_valueComboBox_currentIndexChanged(const QString &aValue)
{
    QMetaEnum aShapeEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("CursorShape"));
    Qt::CursorShape aCursorShape=(Qt::CursorShape)aShapeEnum.keyToValue(aValue.toLatin1());

    if (aCursorShape==Qt::BitmapCursor)
    {
        if (mBitmapCursor.shape()==Qt::BitmapCursor)
        {
            mCursor=mBitmapCursor;
        }
        else
        {
            QPixmap aPixmap(32, 32);
            aPixmap.fill(QColor(0, 0, 0));

            mCursor=QCursor(aPixmap);
        }
    }
    else
    {
        mCursor.setShape(aCursorShape);
    }

    setValue(mCursor);
    emit valueChanged(mCursor);
}

void CursorEditor::hotSpotChanged()
{
    QPixmap aPixmap=mCursor.pixmap();

    if (!aPixmap.isNull())
    {
        mCursor=QCursor(aPixmap, ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
    else
    {
        mCursor=QCursor(*mCursor.bitmap(), *mCursor.mask(), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}

void CursorEditor::on_xSpinBox_valueChanged(int /*aValue*/)
{
    mHotSpotTimer.stop();
    mHotSpotTimer.start(2000);
}

void CursorEditor::on_ySpinBox_valueChanged(int /*aValue*/)
{
    mHotSpotTimer.stop();
    mHotSpotTimer.start(2000);
}

void CursorEditor::on_bitmapButton_clicked()
{
    PaintDialog dialog(QPixmap::fromImage(mCursor.bitmap()->toImage()), true, mAttributes, this);

    if (dialog.exec())
    {
        mCursor=QCursor(QBitmap::fromImage(dialog.resultValue().toImage()), *mCursor.mask(), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}

void CursorEditor::on_maskButton_clicked()
{
    PaintDialog dialog(QPixmap::fromImage(mCursor.mask()->toImage()), true, mAttributes, this);

    if (dialog.exec())
    {
        mCursor=QCursor(*mCursor.bitmap(), QBitmap::fromImage(dialog.resultValue().toImage()), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}

void CursorEditor::on_pixmapButton_clicked()
{
    PaintDialog dialog(mCursor.pixmap(), false, mAttributes, this);

    if (dialog.exec())
    {
        mCursor=QCursor(dialog.resultValue(), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}
