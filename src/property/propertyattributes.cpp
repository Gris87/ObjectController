#include "propertyattributes.h"

#include <QStringList>
#include <QMetaEnum>

PropertyAttributes::PropertyAttributes() :
    QMap<QString, QString>()
{
}

void PropertyAttributes::fromString(const QString &aString)
{
    clear();

    QStringList aAttributes=aString.split(";");

    for (int i=0; i<aAttributes.length(); ++i)
    {
        QStringList aOnePair=aAttributes.at(i).split(":");

        if (aOnePair.length()>=2)
        {
            QString aValue=aAttributes.at(i).mid(aOnePair.at(0).length()+1);
            insert(aOnePair.at(0).trimmed(), aValue.trimmed());
        }
    }
}

bool PropertyAttributes::boolValue(const QString &aKey, const bool aDefaultValue) const
{
    QString aValue=value(aKey);

    if (aValue=="1" || aValue.compare("true", Qt::CaseInsensitive)==0)
    {
        return true;
    }

    if (aValue=="0" || aValue.compare("false", Qt::CaseInsensitive)==0)
    {
        return false;
    }

    return aDefaultValue;
}

int PropertyAttributes::intValue(const QString &aKey, const int aDefaultValue) const
{
    QString aValue=value(aKey);

    bool ok;

    int res=aValue.toInt(&ok);

    if (ok)
    {
        return res;
    }

    return aDefaultValue;
}

double PropertyAttributes::doubleValue(const QString &aKey, const double aDefaultValue) const
{
    QString aValue=value(aKey);

    bool ok;

    double res=aValue.toDouble(&ok);

    if (ok)
    {
        return res;
    }

    return aDefaultValue;
}

QString PropertyAttributes::stringValue(const QString &aKey, const QString aDefaultValue) const
{
    QString aValue=value(aKey, aDefaultValue);

    if (aValue.endsWith("\""))
    {
        aValue.remove(aValue.length()-1, 1);
    }

    if (aValue.startsWith("\""))
    {
        aValue.remove(0, 1);
    }

    return aValue;
}

QDate PropertyAttributes::dateValue(const QString &aKey, const QDate aDefaultValue) const
{
    QString aValue=value(aKey);
    QDate res=QDate::fromString(aValue, "dd.MM.yyyy");

    if (res.isValid())
    {
        return res;
    }

    return aDefaultValue;
}

QTime PropertyAttributes::timeValue(const QString &aKey, const QTime aDefaultValue) const
{
    QString aValue=value(aKey);
    QTime res=QTime::fromString(aValue, "HH:mm:ss");

    if (res.isValid())
    {
        return res;
    }

    return aDefaultValue;
}

QColor PropertyAttributes::colorValue(const QString &aKey, const QColor aDefaultValue) const
{
    QString aValue=value(aKey, aDefaultValue.name());
    QColor res(aValue);

    if (res.isValid())
    {
        return res;
    }

    return aDefaultValue;
}

void PropertyAttributes::applyToPalette(QWidget *aWidget) const
{
    QMetaEnum aMetaEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorRole"));

    QPalette aPalette=aWidget->palette();

    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        QString aColorName=aMetaEnum.valueToKey(i);
        aColorName[0]=aColorName.at(0).toLower();
        aColorName.append("Color");

        aPalette.setColor((QPalette::ColorRole)i, colorValue(aColorName, aPalette.color((QPalette::ColorRole)i)));
    }

    aWidget->setPalette(aPalette);
}

void PropertyAttributes::applyToWidget(QWidget *aWidget) const
{
    aWidget->setToolTip(stringValue("toolTip", aWidget->toolTip()));

    applyToPalette(aWidget);
}

void PropertyAttributes::applyToSpinBox(QSpinBox *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setWrapping(   boolValue(  "wrapping",    aWidget->wrapping()));
    aWidget->setAccelerated(boolValue(  "accelerated", aWidget->isAccelerated()));
    aWidget->setPrefix(     stringValue("prefix",      aWidget->prefix()));
    aWidget->setSuffix(     stringValue("suffix",      aWidget->suffix()));
    aWidget->setMinimum(    intValue(   "minValue",    aWidget->minimum()));
    aWidget->setMaximum(    intValue(   "maxValue",    aWidget->maximum()));
    aWidget->setSingleStep( intValue(   "step",        aWidget->singleStep()));
}

void PropertyAttributes::applyToDoubleSpinBox(QDoubleSpinBox *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setWrapping(   boolValue(  "wrapping",    aWidget->wrapping()));
    aWidget->setAccelerated(boolValue(  "accelerated", aWidget->isAccelerated()));
    aWidget->setPrefix(     stringValue("prefix",      aWidget->prefix()));
    aWidget->setSuffix(     stringValue("suffix",      aWidget->suffix()));
    aWidget->setMinimum(    doubleValue("minValue",    aWidget->minimum()));
    aWidget->setMaximum(    doubleValue("maxValue",    aWidget->maximum()));
    aWidget->setDecimals(   intValue(   "decimals",    aWidget->decimals()));
    aWidget->setSingleStep( doubleValue("step",        aWidget->singleStep()));
}

void PropertyAttributes::applyToLineEdit1Char(QLineEdit *aWidget) const
{
    applyToWidget(aWidget);

    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));

    aWidget->setInputMask(      stringValue("inputMask",       aWidget->inputMask()));
    QString aMode =             stringValue("echoMode",        QString::fromLatin1(aEchoModeEnum.valueToKey(aWidget->echoMode())));
    aWidget->setPlaceholderText(stringValue("placeholderText", aWidget->placeholderText()));

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aMode)
        {
            aWidget->setEchoMode((QLineEdit::EchoMode)aEchoModeEnum.value(i));
            break;
        }
    }
}

void PropertyAttributes::applyToLineEdit(QLineEdit *aWidget) const
{
    applyToLineEdit1Char(aWidget);

    aWidget->setMaxLength(intValue("maxLength", aWidget->maxLength()));
}

void PropertyAttributes::applyToCombobox(QComboBox *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setMaxVisibleItems(intValue( "maxVisibleItems", aWidget->maxVisibleItems()));
    aWidget->setEditable(       boolValue("editable",        aWidget->isEditable()));

    QString aValues=stringValue("values");

    if (aValues!="")
    {
        QString aValue=aWidget->currentText();
        QStringList aItems=aValues.split("|");

        aWidget->clear();
        aWidget->addItems(aItems);

        int index=aItems.indexOf(aValue);
        aWidget->setCurrentIndex(index);

        if (index<0)
        {
            aWidget->setEditable(true);
            aWidget->setEditText(aValue);
        }
    }
}

void PropertyAttributes::applyToDateEdit(QDateEdit *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setMinimumDate(  dateValue(  "minDate",       aWidget->minimumDate()));
    aWidget->setMaximumDate(  dateValue(  "maxDate",       aWidget->maximumDate()));
    aWidget->setDisplayFormat(stringValue("displayFormat", aWidget->displayFormat()));
    aWidget->setCalendarPopup(boolValue(  "calendarPopup", aWidget->calendarPopup()));
}

void PropertyAttributes::applyToTimeEdit(QTimeEdit *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setMinimumTime(  timeValue(  "minTime",       aWidget->minimumTime()));
    aWidget->setMaximumTime(  timeValue(  "maxTime",       aWidget->maximumTime()));
    aWidget->setDisplayFormat(stringValue("displayFormat", aWidget->displayFormat()));
}

void PropertyAttributes::applyToDateTimeEdit(QDateTimeEdit *aWidget) const
{
    applyToWidget(aWidget);

    aWidget->setMinimumDate(  dateValue(  "minDate",       aWidget->minimumDate()));
    aWidget->setMaximumDate(  dateValue(  "maxDate",       aWidget->maximumDate()));
    aWidget->setMinimumTime(  timeValue(  "minTime",       aWidget->minimumTime()));
    aWidget->setMaximumTime(  timeValue(  "maxTime",       aWidget->maximumTime()));
    aWidget->setDisplayFormat(stringValue("displayFormat", aWidget->displayFormat()));
    aWidget->setCalendarPopup(boolValue(  "calendarPopup", aWidget->calendarPopup()));
}
