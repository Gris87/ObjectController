#include "pixmapeditor.h"
#include "ui_dialogeditor.h"

#include <QImage>
#include <QBitmap>

#include "../dialogs/paintdialog.h"
#include "../propertyutils.h"

PixmapEditor::PixmapEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;

    mDataType=PIXMAP;
}

PixmapEditor::~PixmapEditor()
{
    delete ui;
}

void PixmapEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PixmapEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PixmapEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PixmapEditor::setValue(const QPixmap &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(pixmapToString(mValue));
    setIcon(iconForPixmap(mValue));

    mDataType=PIXMAP;
}

void PixmapEditor::setValue(const QImage &aValue)
{
    mValue=QPixmap::fromImage(aValue);

    ui->valueEdit->setText(imageToString(aValue));
    setIcon(iconForPixmap(mValue));

    mDataType=IMAGE;
}

void PixmapEditor::setValue(const QBitmap &aValue)
{
    mValue=QPixmap::fromImage(aValue.toImage());

    ui->valueEdit->setText(bitmapToString(aValue));
    setIcon(iconForPixmap(mValue));

    mDataType=BITMAP;
}

void PixmapEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void PixmapEditor::on_editButton_clicked()
{
    PaintDialog *dialog=0;

    switch (mDataType)
    {
        case PIXMAP:
            dialog=new PaintDialog(mValue, false, mAttributes, this);
        break;
        case IMAGE:
            dialog=new PaintDialog(mValue, false, mAttributes, this);
        break;
        case BITMAP:
            dialog=new PaintDialog(mValue, true, mAttributes, this);
        break;
    }

    if (dialog->exec())
    {
        switch (mDataType)
        {
            case PIXMAP:
            {
                setValue(dialog->resultValue());
                emit valueChanged(mValue);
            }
            break;
            case IMAGE:
            {
                QImage aImage=dialog->resultValue().toImage();

                setValue(aImage);
                emit valueChanged(aImage);
            }
            break;
            case BITMAP:
            {
                QBitmap aBitmap=QBitmap::fromImage(dialog->resultValue().toImage());

                setValue(aBitmap);
                emit valueChanged(aBitmap);
            }
            break;
        }
    }

    delete dialog;
}
