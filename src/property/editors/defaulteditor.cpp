#include "defaulteditor.h"
#include "ui_defaulteditor.h"

#include <QTimer>

DefaultEditor::DefaultEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultEditor)
{
    ui->setupUi(this);
    ui->valueEdit->setReadOnly(true);

    QTimer::singleShot(0, this, SLOT(select()));
}

DefaultEditor::~DefaultEditor()
{
    delete ui;
}

void DefaultEditor::keyPressEvent(QKeyEvent * /*event*/)
{
    // Nothing
}

void DefaultEditor::mousePressEvent(QMouseEvent * /*event*/)
{
    ui->valueEdit->setFocus();
}

void DefaultEditor::setIcon(const QIcon &aIcon)
{
    if (aIcon.isNull())
    {
        ui->iconLabel->setVisible(false);
        ui->dataLayout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        ui->iconLabel->setPixmap(aIcon.pixmap(18));
    }
}

void DefaultEditor::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
}

void DefaultEditor::select()
{
    ui->valueEdit->setFocus();
    ui->valueEdit->selectAll();
}
