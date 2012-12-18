#include "fonteditdialog.h"
#include "ui_fonteditdialog.h"

#include <QFontDatabase>
#include <QKeyEvent>

FontEditDialog::FontEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontEditDialog)
{
    init(QFont(), 0);
}

FontEditDialog::FontEditDialog(QFont aFont, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontEditDialog)
{
    init(aFont, 0);
}

FontEditDialog::FontEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontEditDialog)
{
    init(QFont(), aAttributes);
}

FontEditDialog::FontEditDialog(QFont aFont, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontEditDialog)
{
    init(aFont, aAttributes);
}

void FontEditDialog::init(QFont aFont, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    ui->familyEdit->setFocusProxy(ui->familyList);
    ui->styleEdit->setFocusProxy(ui->styleList);

    mMinSize=1;
    mMaxSize=512;

    if (aAttributes)
    {
        mMinSize=qBound<int>(1, aAttributes->intValue("minValue", mMinSize), 512);
        mMaxSize=qBound<int>(1, aAttributes->intValue("maxValue", mMaxSize), 512);

        if (mMinSize>mMaxSize)
        {
            mMaxSize=mMinSize;
        }
    }

    QIntValidator *validator = new QIntValidator(mMinSize, mMaxSize, this);
    ui->sizeEdit->setValidator(validator);

    for (int i=0; i<QFontDatabase::WritingSystemsCount; ++i)
    {
        QFontDatabase::WritingSystem ws=QFontDatabase::WritingSystem(i);
        QString writingSystemName = QFontDatabase::writingSystemName(ws);

        if (writingSystemName.isEmpty())
            break;

        ui->writingSystemComboBox->addItem(writingSystemName);
    }

    on_writingSystemComboBox_activated(0);

    setCurrentFont(aFont);

    ui->sizeEdit->installEventFilter(this);
    ui->familyList->installEventFilter(this);
    ui->styleList->installEventFilter(this);
    ui->sizeList->installEventFilter(this);

    ui->familyList->setFocus();

    if (aAttributes)
    {
        aAttributes->applyToWidget(ui->familyEdit);
        aAttributes->applyToWidget(ui->familyList);
        aAttributes->applyToWidget(ui->styleEdit);
        aAttributes->applyToWidget(ui->styleList);
        aAttributes->applyToWidget(ui->sizeEdit);
        aAttributes->applyToWidget(ui->sizeList);
        aAttributes->applyToCheckBox(ui->strikeoutCheckBox);
        aAttributes->applyToCheckBox(ui->underlineCheckBox);
        aAttributes->applyToCombobox(ui->writingSystemComboBox);
        aAttributes->applyToWidget(ui->sampleEdit);

        ui->sampleEdit->setReadOnly(!aAttributes->boolValue("allowModifySample", !ui->sampleEdit->isReadOnly()));
    }
}

FontEditDialog::~FontEditDialog()
{
    delete ui;
}

bool FontEditDialog::eventFilter(QObject *object, QEvent *event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent *keyEvent=(QKeyEvent *) event;

        if (
            object==ui->sizeEdit
            &&
            (
             keyEvent->key()==Qt::Key_Up
             ||
             keyEvent->key()==Qt::Key_Down
             ||
             keyEvent->key()==Qt::Key_PageUp
             ||
             keyEvent->key()==Qt::Key_PageDown
            )
           )
        {
            int previousIndex=ui->sizeList->currentRow();
            QApplication::sendEvent(ui->sizeList, keyEvent);

            if (
                previousIndex!=ui->sizeList->currentRow()
                &&
                style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
               )
            {
                ui->sizeEdit->selectAll();
            }

            return true;
        }
        else
        if (
            (
             object==ui->familyList
             ||
             object==ui->styleList
            )
            &&
            (
             keyEvent->key()==Qt::Key_Return
             ||
             keyEvent->key()==Qt::Key_Enter
            )
           )
        {
            keyEvent->accept();
            accept();

            return true;
        }
    }
    else
    if (
        event->type() == QEvent::FocusIn
        &&
        style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
       )
    {
        if (object==ui->familyList)
        {
            ui->familyEdit->selectAll();
        }
        else
        if (object==ui->styleList)
        {
            ui->styleEdit->selectAll();
        }
        else
        if (object==ui->sizeList)
        {
            ui->sizeEdit->selectAll();
        }
    }
    else
    if (
        event->type()==QEvent::MouseButtonPress
        &&
        object==ui->sizeList
       )
    {
        ui->sizeEdit->setFocus();
    }

    return QDialog::eventFilter(object, event);
}

void FontEditDialog::updateFamilies()
{
    QFontDatabase::WritingSystem aWritingSystem=(QFontDatabase::WritingSystem)ui->writingSystemComboBox->currentIndex();
    QFontDatabase aFontDB;

    QStringList familyNames = aFontDB.families(aWritingSystem);

    ui->familyList->blockSignals(true);
    ui->familyList->clear();
    ui->familyList->addItems(familyNames);

    int index=familyNames.indexOf(mFont.family());

    if (index>=0)
    {
        ui->familyList->setCurrentRow(index);
        ui->familyEdit->setText(mFont.family());
    }
    else
    {
        if (familyNames.length()>0)
        {
            ui->familyList->setCurrentRow(0);
            ui->familyEdit->setText(ui->familyList->currentItem()->text());
        }
        else
        {
            ui->familyEdit->setText("");
        }
    }

    if (
        style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
        &&
        ui->familyList->hasFocus()
       )
    {
        ui->familyEdit->selectAll();
    }

    ui->familyList->blockSignals(false);

    updateStyles();
}

void FontEditDialog::updateStyles()
{
    QFontDatabase aFontDB;

    QStringList styles=aFontDB.styles(ui->familyEdit->text());

    ui->styleList->blockSignals(true);
    ui->styleList->clear();
    ui->styleList->addItems(styles);

    if (styles.length()>0)
    {
        QString aStyle=aFontDB.styleString(mFont);

        if (!aStyle.isEmpty())
        {
            bool found = false;
            bool first = true;

redo:
            for (int i=0; i<styles.length(); ++i)
            {
                if (aStyle==styles.at(i))
                {
                    ui->styleList->setCurrentRow(i);
                    found=true;
                    break;
                }
            }

            if (!found && first)
            {
                if (aStyle.contains(QLatin1String("Italic")))
                {
                    aStyle.replace(QLatin1String("Italic"), QLatin1String("Oblique"));
                    first = false;
                    goto redo;
                }
                else
                if (aStyle.contains(QLatin1String("Oblique")))
                {
                    aStyle.replace(QLatin1String("Oblique"), QLatin1String("Italic"));
                    first = false;
                    goto redo;
                }
            }

            if (!found)
            {
                ui->styleList->setCurrentRow(0);
            }
        }
        else
        {
            ui->styleList->setCurrentRow(0);
        }

        ui->styleEdit->setText(ui->styleList->currentItem()->text());

        if (
            style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
            &&
            ui->styleList->hasFocus()
           )
        {
            ui->styleEdit->selectAll();
        }
    }
    else
    {
        ui->styleEdit->setText("");
    }

    ui->styleList->blockSignals(false);

    updateSizes();
}

void FontEditDialog::updateSizes()
{
    QFontDatabase aFontDB;

    QList<int> sizes=aFontDB.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());

    int i=0;
    int current=-1;
    QStringList str_sizes;

    int size=mFont.pointSize();

    if (size<0)
    {
        QFontInfo aFontInfo(mFont);
        size=aFontInfo.pointSize();
    }

    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it)
    {
        if (*it<mMinSize)
        {
            continue;
        }

        if (*it>mMaxSize)
        {
            break;
        }

        str_sizes.append(QString::number(*it));

        if (current==-1 && *it>=size)
        {
            current=i;
        }

        ++i;
    }

    ui->sizeList->blockSignals(true);
    ui->sizeEdit->blockSignals(true);

    ui->sizeList->clear();
    ui->sizeList->addItems(str_sizes);

    if (current<0)
    {
        // we request a size bigger than the ones in the list, select the biggest one
        current=str_sizes.length()-1;
    }

    if (current>=0)
    {
        ui->sizeList->setCurrentRow(current);

        bool smoothScalable = aFontDB.isSmoothlyScalable(ui->familyEdit->text(), ui->styleEdit->text());
        ui->sizeEdit->setText(smoothScalable ? QString::number(size) : ui->sizeList->currentItem()->text());

        if (
            style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
            &&
            ui->sizeList->hasFocus()
           )
        {
            ui->sizeEdit->selectAll();
        }
    }
    else
    {
        ui->sizeEdit->clear();
    }

    ui->sizeEdit->blockSignals(false);
    ui->sizeList->blockSignals(false);

    updateSample();
}

void FontEditDialog::updateSample()
{
    if (ui->familyList->currentRow()<0)
    {
        ui->sampleEdit->setText("");
        return;
    }

    ui->sampleEdit->setFont(mFont);
}

void FontEditDialog::on_writingSystemComboBox_activated(int index)
{
    QFontDatabase::WritingSystem aWritingSystem=QFontDatabase::WritingSystem(index);
    ui->sampleEdit->setText(QFontDatabase::writingSystemSample(aWritingSystem));
    updateFamilies();
}

void FontEditDialog::on_strikeoutCheckBox_toggled(bool checked)
{
    mFont.setStrikeOut(checked);
    updateSample();
}

void FontEditDialog::on_underlineCheckBox_toggled(bool checked)
{
    mFont.setUnderline(checked);
    updateSample();
}

void FontEditDialog::on_familyList_currentTextChanged(const QString &currentText)
{
    ui->familyEdit->setText(currentText);

    if (
        style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
        &&
        ui->familyList->hasFocus()
       )
    {
        ui->familyEdit->selectAll();
    }

    mFont.setFamily(currentText);

    updateStyles();
}

void FontEditDialog::on_styleList_currentTextChanged(const QString &currentText)
{
    ui->styleEdit->setText(currentText);

    if (
        style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
        &&
        ui->styleList->hasFocus()
       )
    {
        ui->styleEdit->selectAll();
    }

    int size=mFont.pointSize();

    if (size<0)
    {
        QFontInfo aFontInfo(mFont);
        size=aFontInfo.pointSize();
    }

    QFontDatabase aFontDB;
    mFont=aFontDB.font(ui->familyEdit->text(), currentText, size);

    mFont.setStrikeOut(ui->strikeoutCheckBox->isChecked());
    mFont.setUnderline(ui->underlineCheckBox->isChecked());

    updateSizes();
}

void FontEditDialog::on_sizeList_currentTextChanged(const QString &currentText)
{
    ui->sizeEdit->setText(currentText);

    if (
        style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)
        &&
        ui->sizeEdit->hasFocus()
       )
    {
        ui->sizeEdit->selectAll();
    }
}

void FontEditDialog::on_sizeEdit_textChanged(const QString &aValue)
{
    int size=qBound<int>(mMinSize, aValue.toInt(), mMaxSize);

    for (int i=0; i<ui->sizeList->count(); i++)
    {
        if (i==ui->sizeList->count()-1 || ui->sizeList->item(i)->text().toInt()>=size)
        {
            ui->sizeList->blockSignals(true);
            ui->sizeList->setCurrentRow(i);
            ui->sizeList->blockSignals(false);

            break;
        }
    }

    mFont.setPointSize(size);

    updateSample();
}

void FontEditDialog::setCurrentFont(const QFont &font)
{
    mFont=font;

    ui->strikeoutCheckBox->blockSignals(true);
    ui->underlineCheckBox->blockSignals(true);

    ui->strikeoutCheckBox->setChecked(mFont.strikeOut());
    ui->underlineCheckBox->setChecked(mFont.underline());

    ui->strikeoutCheckBox->blockSignals(false);
    ui->underlineCheckBox->blockSignals(false);

    updateFamilies();
}

QFont FontEditDialog::currentFont() const
{
    return mFont;
}

QFont FontEditDialog::selectedFont() const
{
    return mFont;
}

void FontEditDialog::on_okButton_clicked()
{
    accept();
}

void FontEditDialog::on_cancelButton_clicked()
{
    reject();
}
