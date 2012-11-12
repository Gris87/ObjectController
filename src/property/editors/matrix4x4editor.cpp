#include "matrix4x4editor.h"
#include "ui_matrix4x4editor.h"

#include "../dialogs/matrix4x4editdialog.h"

Matrix4x4Editor::Matrix4x4Editor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Matrix4x4Editor)
{
    ui->setupUi(this);
}

Matrix4x4Editor::~Matrix4x4Editor()
{
    delete ui;
}

void Matrix4x4Editor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Matrix4x4Editor::selectText()
{
    ui->valueEdit->selectAll();
}

void Matrix4x4Editor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Matrix4x4Editor::setValue(const QMatrix4x4 &aValue)
{
    mValue=aValue;



    qreal aMatrix[16];

    mValue.copyDataTo(aMatrix);

    QString res="[";

    for (int i=0; i<4; ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }

        res.append("(");

        for (int j=0; j<4; ++j)
        {
            if (j>0)
            {
                res.append(", ");
            }

            res.append(QString::number(aMatrix[i*4+j]));
        }

        res.append(")");
    }

    res.append("]");

    ui->valueEdit->setText(res);
}

void Matrix4x4Editor::on_editButton_clicked()
{
    Matrix4x4EditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}