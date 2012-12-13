#include "polygoneditor.h"
#include "ui_polygoneditor.h"

#include "../dialogs/polygoneditdialog.h"

PolygonEditor::PolygonEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PolygonEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

PolygonEditor::~PolygonEditor()
{
    delete ui;
}

void PolygonEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PolygonEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PolygonEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PolygonEditor::setValue(const QPolygon &aValue)
{
    mValue=aValue;



    QString res="[";

    for (int i=0; i<mValue.count(); ++i)
    {
        int x;
        int y;

        mValue.point(i, &x, &y);

        res.append("(");
        res.append(QString::number(x));
        res.append(", ");
        res.append(QString::number(y));
        res.append(")");

        if (i<mValue.count()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    ui->valueEdit->setText(res);
}

void PolygonEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void PolygonEditor::on_editButton_clicked()
{
    PolygonEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
