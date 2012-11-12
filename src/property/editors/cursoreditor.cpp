#include "cursoreditor.h"
#include "ui_cursoreditor.h"

#include <QBitmap>

#include "../dialogs/paintdialog.h"

CursorEditor::CursorEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::CursorEditor)
{
    ui->setupUi(this);

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



    QString res="[Unknown cursor]";

    switch (mCursor.shape())
    {
        case Qt::ArrowCursor:        res="ArrowCursor";        break;
        case Qt::UpArrowCursor:      res="UpArrowCursor";      break;
        case Qt::CrossCursor:        res="CrossCursor";        break;
        case Qt::WaitCursor:         res="WaitCursor";         break;
        case Qt::IBeamCursor:        res="IBeamCursor";        break;
        case Qt::SizeVerCursor:      res="SizeVerCursor";      break;
        case Qt::SizeHorCursor:      res="SizeHorCursor";      break;
        case Qt::SizeBDiagCursor:    res="SizeBDiagCursor";    break;
        case Qt::SizeFDiagCursor:    res="SizeFDiagCursor";    break;
        case Qt::SizeAllCursor:      res="SizeAllCursor";      break;
        case Qt::BlankCursor:        res="BlankCursor";        break;
        case Qt::SplitVCursor:       res="SplitVCursor";       break;
        case Qt::SplitHCursor:       res="SplitHCursor";       break;
        case Qt::PointingHandCursor: res="PointingHandCursor"; break;
        case Qt::ForbiddenCursor:    res="ForbiddenCursor";    break;
        case Qt::WhatsThisCursor:    res="WhatsThisCursor";    break;
        case Qt::BusyCursor:         res="BusyCursor";         break;
        case Qt::OpenHandCursor:     res="OpenHandCursor";     break;
        case Qt::ClosedHandCursor:   res="ClosedHandCursor";   break;
        case Qt::DragCopyCursor:     res="DragCopyCursor";     break;
        case Qt::DragMoveCursor:     res="DragMoveCursor";     break;
        case Qt::DragLinkCursor:     res="DragLinkCursor";     break;
        case Qt::BitmapCursor:       res="BitmapCursor";       break;
        case Qt::CustomCursor:       res="CustomCursor";       break;
    }

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

void CursorEditor::on_valueComboBox_currentIndexChanged(const QString &aValue)
{
    if (aValue=="ArrowCursor")
    {
        mCursor.setShape(Qt::ArrowCursor);
    }
    else
    if (aValue=="UpArrowCursor")
    {
        mCursor.setShape(Qt::UpArrowCursor);
    }
    else
    if (aValue=="CrossCursor")
    {
        mCursor.setShape(Qt::CrossCursor);
    }
    else
    if (aValue=="WaitCursor")
    {
        mCursor.setShape(Qt::WaitCursor);
    }
    else
    if (aValue=="IBeamCursor")
    {
        mCursor.setShape(Qt::IBeamCursor);
    }
    else
    if (aValue=="SizeVerCursor")
    {
        mCursor.setShape(Qt::SizeVerCursor);
    }
    else
    if (aValue=="SizeHorCursor")
    {
        mCursor.setShape(Qt::SizeHorCursor);
    }
    else
    if (aValue=="SizeBDiagCursor")
    {
        mCursor.setShape(Qt::SizeBDiagCursor);
    }
    else
    if (aValue=="SizeFDiagCursor")
    {
        mCursor.setShape(Qt::SizeFDiagCursor);
    }
    else
    if (aValue=="SizeAllCursor")
    {
        mCursor.setShape(Qt::SizeAllCursor);
    }
    else
    if (aValue=="BlankCursor")
    {
        mCursor.setShape(Qt::BlankCursor);
    }
    else
    if (aValue=="SplitVCursor")
    {
        mCursor.setShape(Qt::SplitVCursor);
    }
    else
    if (aValue=="SplitHCursor")
    {
        mCursor.setShape(Qt::SplitHCursor);
    }
    else
    if (aValue=="PointingHandCursor")
    {
        mCursor.setShape(Qt::PointingHandCursor);
    }
    else
    if (aValue=="ForbiddenCursor")
    {
        mCursor.setShape(Qt::ForbiddenCursor);
    }
    else
    if (aValue=="WhatsThisCursor")
    {
        mCursor.setShape(Qt::WhatsThisCursor);
    }
    else
    if (aValue=="BusyCursor")
    {
        mCursor.setShape(Qt::BusyCursor);
    }
    else
    if (aValue=="OpenHandCursor")
    {
        mCursor.setShape(Qt::OpenHandCursor);
    }
    else
    if (aValue=="ClosedHandCursor")
    {
        mCursor.setShape(Qt::ClosedHandCursor);
    }
    else
    if (aValue=="DragCopyCursor")
    {
        mCursor.setShape(Qt::DragCopyCursor);
    }
    else
    if (aValue=="DragMoveCursor")
    {
        mCursor.setShape(Qt::DragMoveCursor);
    }
    else
    if (aValue=="DragLinkCursor")
    {
        mCursor.setShape(Qt::DragLinkCursor);
    }
    else
    if (aValue=="BitmapCursor")
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
        Q_ASSERT(false);
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
    PaintDialog dialog(QPixmap::fromImage(mCursor.bitmap()->toImage()), true, this);

    if (dialog.exec())
    {
        mCursor=QCursor(QBitmap::fromImage(dialog.resultValue().toImage()), *mCursor.mask(), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}

void CursorEditor::on_maskButton_clicked()
{
    PaintDialog dialog(QPixmap::fromImage(mCursor.mask()->toImage()), true, this);

    if (dialog.exec())
    {
        mCursor=QCursor(*mCursor.bitmap(), QBitmap::fromImage(dialog.resultValue().toImage()), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}

void CursorEditor::on_pixmapButton_clicked()
{
    PaintDialog dialog(mCursor.pixmap(), false, this);

    if (dialog.exec())
    {
        mCursor=QCursor(dialog.resultValue(), ui->xSpinBox->value(), ui->ySpinBox->value());

        setValue(mCursor);
        emit valueChanged(mCursor);
    }
}