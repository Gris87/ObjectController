#ifndef PROPERTYATTRIBUTES_H
#define PROPERTYATTRIBUTES_H

#include <QMap>
#include <QString>
#include <QDate>
#include <QTime>
#include <QColor>
#include <QWidget>
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

    void applyToPalette(QWidget *aWidget) const;
    void applyToWidget(QWidget *aWidget) const;
    void applyToSpinBox(QSpinBox *aWidget) const;
    void applyToDoubleSpinBox(QDoubleSpinBox *aWidget) const;
    void applyToLineEdit1Char(QLineEdit *aWidget) const;
    void applyToLineEdit(QLineEdit *aWidget) const;
    void applyToCombobox(QComboBox *aWidget) const;
    void applyToDateEdit(QDateEdit *aWidget) const;
    void applyToTimeEdit(QTimeEdit *aWidget) const;
    void applyToDateTimeEdit(QDateTimeEdit *aWidget) const;
};

#endif // PROPERTYATTRIBUTES_H
