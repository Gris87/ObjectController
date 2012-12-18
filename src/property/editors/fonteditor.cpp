#include "fonteditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>

#include "../dialogs/fonteditdialog.h"

FontEditor::FontEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

FontEditor::~FontEditor()
{
    delete ui;
}

void FontEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void FontEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void FontEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void FontEditor::setValue(const QFont &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "["+
                           mValue.family()+
                           ", "+
                           QString::number(mValue.pointSize())+
                           "]"
                          );



    QFont aFont=mValue;
    aFont.setPixelSize(32);

    QFontMetrics aMetrics(aFont);

    int aSize=qMax(aMetrics.width('A'), aMetrics.height())-6;

    if (aSize<1)
    {
        aSize=1;
    }

    QRect aBoundingRect(0, 0, aSize, aSize);

    QPixmap aPenPixmap=QPixmap(aSize, aSize);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setFont(aFont);
    aPainter.drawText(aBoundingRect, Qt::AlignCenter, "A", &aBoundingRect);
    aPainter.end();

    if (aSize<32)
    {
        setIcon(QIcon(aPenPixmap.scaled(32, 32)));
    }
    else
    {
        setIcon(QIcon(aPenPixmap));
    }
}

void FontEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void FontEditor::on_editButton_clicked()
{
    FontEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.selectedFont());
        emit valueChanged(mValue);
    }
}
