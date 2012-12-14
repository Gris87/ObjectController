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

#define RETURN_ONE(aType, aConvertFunc, aKey, aDefValueForKey, aDefaultValue) \
    aType res; \
\
    if (aConvertFunc(value(aKey, aDefValueForKey), res)) \
    { \
        return res; \
    } \
\
    return aDefaultValue;

bool PropertyAttributes::boolValue(const QString &aKey, const bool aDefaultValue) const
{
    RETURN_ONE(bool, valueToBool, aKey, "", aDefaultValue);
}

int PropertyAttributes::intValue(const QString &aKey, const int aDefaultValue) const
{
    RETURN_ONE(int, valueToInt, aKey, "", aDefaultValue);
}

double PropertyAttributes::doubleValue(const QString &aKey, const double aDefaultValue) const
{
    RETURN_ONE(double, valueToDouble, aKey, "", aDefaultValue);
}

QString PropertyAttributes::stringValue(const QString &aKey, const QString aDefaultValue) const
{
    RETURN_ONE(QString, valueToString, aKey, aDefaultValue, aDefaultValue);
}

QDate PropertyAttributes::dateValue(const QString &aKey, const QDate aDefaultValue) const
{
    RETURN_ONE(QDate, valueToDate, aKey, "", aDefaultValue);
}

QTime PropertyAttributes::timeValue(const QString &aKey, const QTime aDefaultValue) const
{
    RETURN_ONE(QTime, valueToTime, aKey, "", aDefaultValue);
}

QColor PropertyAttributes::colorValue(const QString &aKey, const QColor aDefaultValue) const
{
    RETURN_ONE(QColor, valueToColor, aKey, aDefaultValue.name(), aDefaultValue);
}

#define RETURN_LIST(aListType, aType, aConvertFunc, aKey, aDefaultValues) \
    QString aValue=value(aKey); \
\
    if (aValue=="") \
    { \
        return aDefaultValues; \
    } \
\
    QStringList aParts=aValue.split("|"); \
    aListType aResultList; \
\
    for (int i=0; i<aParts.length(); ++i) \
    { \
        aType aItem; \
\
        if (aConvertFunc(aParts.at(i).trimmed(), aItem)) \
        { \
            aResultList.append(aItem); \
        } \
    } \
\
    if (aResultList.length()==0) \
    { \
        return aDefaultValues; \
    } \
\
    return aResultList;

QList<bool> PropertyAttributes::boolValues(const QString &aKey, const QList<bool> aDefaultValues) const
{
    RETURN_LIST(QList<bool>, bool, valueToBool, aKey, aDefaultValues);
}

QList<int> PropertyAttributes::intValues(const QString &aKey, const QList<int> aDefaultValues) const
{
    RETURN_LIST(QList<int>, int, valueToInt, aKey, aDefaultValues);
}

QList<double> PropertyAttributes::doubleValues(const QString &aKey, const QList<double> aDefaultValues) const
{
    RETURN_LIST(QList<double>, double, valueToDouble, aKey, aDefaultValues);
}

QStringList PropertyAttributes::stringValues(const QString &aKey, const QStringList aDefaultValues) const
{
    RETURN_LIST(QStringList, QString, valueToString, aKey, aDefaultValues);
}

QList<QDate> PropertyAttributes::dateValues(const QString &aKey, const QList<QDate> aDefaultValues) const
{
    RETURN_LIST(QList<QDate>, QDate, valueToDate, aKey, aDefaultValues);
}

QList<QTime> PropertyAttributes::timeValues(const QString &aKey, const QList<QTime> aDefaultValues) const
{
    RETURN_LIST(QList<QTime>, QTime, valueToTime, aKey, aDefaultValues);
}

QList<QColor> PropertyAttributes::colorValues(const QString &aKey, const QList<QColor> aDefaultValues) const
{
    RETURN_LIST(QList<QColor>, QColor, valueToColor, aKey, aDefaultValues);
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

void PropertyAttributes::applyToCheckBox(QCheckBox *aWidget) const
{
    applyToWidget(aWidget);
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

    QStringList aItems=stringValues("values");

    if (aItems.length()>0)
    {
        QString aValue=aWidget->currentText();

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

bool PropertyAttributes::valueToBool(const QString &aValue, bool &aResultValue) const
{
    if (aValue=="1" || aValue.compare("true", Qt::CaseInsensitive)==0)
    {
        aResultValue=true;
        return true;
    }

    if (aValue=="0" || aValue.compare("false", Qt::CaseInsensitive)==0)
    {
        aResultValue=false;
        return true;
    }

    return false;
}

bool PropertyAttributes::valueToInt(const QString &aValue, int &aResultValue) const
{
    bool ok;
    aResultValue=aValue.toInt(&ok);
    return ok;
}

bool PropertyAttributes::valueToDouble(const QString &aValue, double &aResultValue) const
{
    bool ok;
    aResultValue=aValue.toDouble(&ok);
    return ok;
}

bool PropertyAttributes::valueToString(const QString &aValue, QString &aResultValue) const
{
    aResultValue=aValue;

    if (aResultValue.endsWith("\""))
    {
        aResultValue.remove(aResultValue.length()-1, 1);
    }

    if (aResultValue.startsWith("\""))
    {
        aResultValue.remove(0, 1);
    }

    return true;
}

bool PropertyAttributes::valueToDate(const QString &aValue, QDate &aResultValue) const
{
    aResultValue=QDate::fromString(aValue, "dd.MM.yyyy");
    return aResultValue.isValid();
}

bool PropertyAttributes::valueToTime(const QString &aValue, QTime &aResultValue) const
{
    aResultValue=QTime::fromString(aValue, "HH:mm:ss");
    return aResultValue.isValid();
}

bool PropertyAttributes::valueToColor(const QString &aValue, QColor &aResultValue) const
{
    aResultValue.setNamedColor(aValue);
    return aResultValue.isValid();
}
