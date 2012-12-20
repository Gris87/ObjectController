#include "regioneditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/regioneditdialog.h"

RegionEditor::RegionEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

RegionEditor::~RegionEditor()
{
    delete ui;
}

void RegionEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RegionEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RegionEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RegionEditor::setValue(const QRegion &aValue)
{
    mValue=aValue;



    QVector<QRect> aRects=mValue.rects();

    QString res="[";

    for (int i=0; i<aRects.count(); ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }

        res.append(
                   "[("+
                   QString::number(aRects.at(i).x())+
                   ", "+
                   QString::number(aRects.at(i).y())+
                   "), "+
                   QString::number(aRects.at(i).width())+
                   " x "+
                   QString::number(aRects.at(i).height())+
                   "]"
                  );
    }

    res.append("]");

    ui->valueEdit->setText(res);
}

void RegionEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void RegionEditor::on_editButton_clicked()
{
    RegionEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
