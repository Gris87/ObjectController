#include "brusheditor.h"
#include "ui_brusheditor.h"

#include <QPainter>

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



    QString res="[Unknown brush style]";

    // TODO: Use QMetaEnum
    switch (mValue.style())
    {
        case Qt::NoBrush:                res="NoBrush";                break;
        case Qt::SolidPattern:           res="SolidPattern";           break;
        case Qt::Dense1Pattern:          res="Dense1Pattern";          break;
        case Qt::Dense2Pattern:          res="Dense2Pattern";          break;
        case Qt::Dense3Pattern:          res="Dense3Pattern";          break;
        case Qt::Dense4Pattern:          res="Dense4Pattern";          break;
        case Qt::Dense5Pattern:          res="Dense5Pattern";          break;
        case Qt::Dense6Pattern:          res="Dense6Pattern";          break;
        case Qt::Dense7Pattern:          res="Dense7Pattern";          break;
        case Qt::HorPattern:             res="HorPattern";             break;
        case Qt::VerPattern:             res="VerPattern";             break;
        case Qt::CrossPattern:           res="CrossPattern";           break;
        case Qt::BDiagPattern:           res="BDiagPattern";           break;
        case Qt::FDiagPattern:           res="FDiagPattern";           break;
        case Qt::DiagCrossPattern:       res="DiagCrossPattern";       break;
        case Qt::LinearGradientPattern:  res="LinearGradientPattern";  break;
        case Qt::RadialGradientPattern:  res="RadialGradientPattern";  break;
        case Qt::ConicalGradientPattern: res="ConicalGradientPattern"; break;
        case Qt::TexturePattern:         res="TexturePattern";         break;
    }

    ui->valueEdit->setText(res);



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
