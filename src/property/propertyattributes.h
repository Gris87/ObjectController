#ifndef PROPERTYATTRIBUTES_H
#define PROPERTYATTRIBUTES_H

#include <QMap>
#include <QString>
#include <QDate>
#include <QTime>
#include <QColor>
#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>

class PropertyAttributes: public QMap<QString, QString>
{
public:
    explicit PropertyAttributes();

    void fromString(const QString &aString);

    bool boolValue(const QString &aKey, const bool aDefaultValue=false) const;
    int intValue(const QString &aKey, const int aDefaultValue=0) const;
    double doubleValue(const QString &aKey, const double aDefaultValue=0) const;
    QString stringValue(const QString &aKey, const QString aDefaultValue=QString()) const;
    QDate dateValue(const QString &aKey, const QDate aDefaultValue=QDate()) const;
    QTime timeValue(const QString &aKey, const QTime aDefaultValue=QTime()) const;
    QColor colorValue(const QString &aKey, const QColor aDefaultValue=QColor()) const;

    QList<bool> boolValues(const QString &aKey, const QList<bool> aDefaultValues=QList<bool>()) const;
    QList<int> intValues(const QString &aKey, const QList<int> aDefaultValues=QList<int>()) const;
    QList<double> doubleValues(const QString &aKey, const QList<double> aDefaultValues=QList<double>()) const;
    QStringList stringValues(const QString &aKey, const QStringList aDefaultValues=QStringList()) const;
    QList<QDate> dateValues(const QString &aKey, const QList<QDate> aDefaultValues=QList<QDate>()) const;
    QList<QTime> timeValues(const QString &aKey, const QList<QTime> aDefaultValues=QList<QTime>()) const;
    QList<QColor> colorValues(const QString &aKey, const QList<QColor> aDefaultValues=QList<QColor>()) const;

    void applyToPalette(QWidget *aWidget) const;
    void applyToWidget(QWidget *aWidget) const;
    void applyToCheckBox(QCheckBox *aWidget) const;
    void applyToSpinBox(QSpinBox *aWidget) const;
    void applyToDoubleSpinBox(QDoubleSpinBox *aWidget) const;
    void applyToLineEdit1Char(QLineEdit *aWidget) const;
    void applyToLineEdit(QLineEdit *aWidget) const;
    void applyToCombobox(QComboBox *aWidget) const;
    void applyToDateEdit(QDateEdit *aWidget) const;
    void applyToTimeEdit(QTimeEdit *aWidget) const;
    void applyToDateTimeEdit(QDateTimeEdit *aWidget) const;

protected:
    bool valueToBool(const QString &aValue, bool &aResultValue) const;
    bool valueToInt(const QString &aValue, int &aResultValue) const;
    bool valueToDouble(const QString &aValue, double &aResultValue) const;
    bool valueToString(const QString &aValue, QString &aResultValue) const;
    bool valueToDate(const QString &aValue, QDate &aResultValue) const;
    bool valueToTime(const QString &aValue, QTime &aResultValue) const;
    bool valueToColor(const QString &aValue, QColor &aResultValue) const;
};

#endif // PROPERTYATTRIBUTES_H
