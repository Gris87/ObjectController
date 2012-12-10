#include "brusheditor.h"
#include "ui_brusheditor.h"

#include <QPainter>
#include <QMetaEnum>

#include "../dialogs/brusheditdialog.h"

BrushEditor::BrushEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::BrushEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

BrushEditor::~BrushEditor()
{
    delete ui;
}

void BrushEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void BrushEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void BrushEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void BrushEditor::setValue(const QBrush &aValue)
{
    mValue=aValue;



    QMetaEnum aEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("BrushStyle"));
    ui->valueEdit->setText(aEnum.valueToKey(aValue.style()));



    QPixmap aBrushPixmap=QPixmap(32, 32);
    aBrushPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aBrushPixmap);
    aPainter.fillRect(0, 0, aBrushPixmap.width(), aBrushPixmap.height(), mValue);
    aPainter.end();

    setIcon(QIcon(aBrushPixmap));
}

void BrushEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);
}

void BrushEditor::on_editButton_clicked()
{
    BrushEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
