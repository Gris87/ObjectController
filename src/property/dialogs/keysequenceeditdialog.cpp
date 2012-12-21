#include "keysequenceeditdialog.h"
#include "ui_keysequenceeditdialog.h"

#include "../propertyutils.h"

KeySequenceEditDialog::KeySequenceEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySequenceEditDialog)
{
    init(QKeySequence(), 0);
}

KeySequenceEditDialog::KeySequenceEditDialog(QKeySequence aKeySequence, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySequenceEditDialog)
{
    init(aKeySequence, 0);
}

KeySequenceEditDialog::KeySequenceEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySequenceEditDialog)
{
    init(QKeySequence(), aAttributes);
}

KeySequenceEditDialog::KeySequenceEditDialog(QKeySequence aKeySequence, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySequenceEditDialog)
{
    init(aKeySequence, aAttributes);
}

void KeySequenceEditDialog::init(QKeySequence aKeySequence, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    mShortCutEdit=new ShortCutEdit(aAttributes, this);
    mShortCutEdit->setText(keySequenceToString(aKeySequence));
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
