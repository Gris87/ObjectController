#include "paletteeditdialog.h"
#include "ui_paletteeditdialog.h"

#include <QMetaEnum>

#include "../widgets/colorarea.h"

PaletteEditDialog::PaletteEditDialog(QPalette aPalette, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaletteEditDialog)
{
    ui->setupUi(this);

    QMetaEnum aGroupEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorGroup"));
    QMetaEnum aRoleEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorRole"));

    ui->colorsTableWidget->setRowCount(20);
    ui->colorsTableWidget->setColumnCount(3);

    for (int i=0; i<ui->colorsTableWidget->columnCount(); ++i)
    {
        ui->colorsTableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromLatin1(aGroupEnum.key(i))));
    }

    for (int i=0; i<20; ++i)
    {
        ui->colorsTableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromLatin1(aRoleEnum.key(i))));

        for (int j=0; j<3; ++j)
        {
            QPalette::ColorGroup aGroup=(QPalette::ColorGroup)aGroupEnum.value(j);
            QPalette::ColorRole aRole=(QPalette::ColorRole)aRoleEnum.value(i);

            ColorArea *aArea=new ColorArea(this);
            aArea->setColor(aPalette.color(aGroup, aRole));

            ui->colorsTableWidget->setCellWidget(i, j, aArea);
        }
    }
}

PaletteEditDialog::~PaletteEditDialog()
{
    delete ui;
}

QPalette PaletteEditDialog::resultValue() const
{
    QPalette aPalette;

    QMetaEnum aGroupEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorGroup"));
    QMetaEnum aRoleEnum=aPalette.staticMetaObject.enumerator(aPalette.staticMetaObject.indexOfEnumerator("ColorRole"));

    for (int i=0; i<20; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            QPalette::ColorGroup aGroup=(QPalette::ColorGroup)aGroupEnum.value(j);
            QPalette::ColorRole aRole=(QPalette::ColorRole)aRoleEnum.value(i);

            aPalette.setColor(aGroup, aRole, ((ColorArea *)ui->colorsTableWidget->cellWidget(i, j))->color());
        }
    }

    return aPalette;
}

void PaletteEditDialog::on_okButton_clicked()
{
    accept();
}

void PaletteEditDialog::on_cancelButton_clicked()
{
    reject();
}
