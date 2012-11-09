#include "keysequenceeditdialog.h"
#include "ui_keysequenceeditdialog.h"

KeySequenceEditDialog::KeySequenceEditDialog(QKeySequence aKeySequence, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySequenceEditDialog)
{
    ui->setupUi(this);

    mShortCutEdit=new ShortCutEdit(this);
    mShortCutEdit->setText(aKeySequence.toString());
    ui->mainLayout->insertWidget(0, mShortCutEdit);

    mShortCutEdit->grabKeyboard();
}

KeySequenceEditDialog::~KeySequenceEditDialog()
{
    delete ui;
}

QKeySequence KeySequenceEditDialog::resultValue() const
{
    return QKeySequence::fromString(mShortCutEdit->text());
}

void KeySequenceEditDialog::on_okButton_clicked()
{
    accept();
}

void KeySequenceEditDialog::on_cancelButton_clicked()
{
    reject();
}
