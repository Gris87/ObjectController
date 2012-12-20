#include "propertyutils.h"

#include <QApplication>
#include <QList>
#include <QByteArray>
#include <QBitArray>

QString enumToString(const QMetaEnum &aMetaEnum, const int &aValue)
{
    QString res=qApp->translate("Property", "[No enumeration value]");

    for (int i=0; i<aMetaEnum.keyCount(); ++i)
    {
        if (aMetaEnum.value(i)==aValue)
        {
            res=QString::fromLatin1(aMetaEnum.key(i));
            break;
        }
    }

    return res;
}

QString flagsToString(const QMetaEnum &aMetaEnum, const int &aValue)
{
    QString res="[";

    for (int i=0; i<aMetaEnum.keyCount(); ++i)
    {
        int aFlag=aMetaEnum.value(i);

        if (((aValue & aFlag)==aFlag) && (aFlag!=0 || aValue==0))
        {
            bool good=true;

            while (aFlag)
            {
                if (aFlag & 1)
                {
                    good=(aFlag==1);
                    break;
                }

                aFlag>>=1;
            }

            if (good)
            {
                if (res.length()>1)
                {
                    res.append(", ");
                }

                res.append(QString::fromLatin1(aMetaEnum.key(i)));
            }
        }
    }

    res.append("]");

    return res;
}

QString boolToString(const bool &aValue)
{
    return aValue ? "true" : "false";
}

QString intToString(const qint8 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint8 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint16 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint16 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint32 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint32 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint64 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint64 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QList<double> *decimals=0;

QString doubleToString(double aValue, int aDecimals)
{
    if (aDecimals<0 || aDecimals>6)
    {
        return QString::number(aValue);
    }

    if (decimals==0)
    {
        decimals=new QList<double>();

        decimals->append(1);
        decimals->append(10);
        decimals->append(100);
        decimals->append(1000);
        decimals->append(10000);
        decimals->append(100000);
        decimals->append(1000000);
    }

    double aMultiplier=decimals->at(aDecimals);

    return QString::number(qRound(aValue*aMultiplier)/aMultiplier);
}

QString doubleToString(double aValue, const QString &aPrefix, const QString &aSuffix, int aDecimals)
{
    return aPrefix+
           doubleToString(aValue, aDecimals)+
           aSuffix;
}

QString charToString(const QChar &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    switch (aMode)
    {
        case QLineEdit::Normal:             return QString(aValue);
        case QLineEdit::NoEcho:             return "";
        case QLineEdit::Password:
        case QLineEdit::PasswordEchoOnEdit: return qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter);
        default:
            Q_ASSERT(false);
        break;
    }

    return QString(aValue);
}

QString stringListToString(const QStringList &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    QString res="[";

    for (int i=0; i<aValue.length(); ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }



        res.append("\"");

        switch (aMode)
        {
            case QLineEdit::Normal:
                res.append(aValue.at(i));
            break;
            case QLineEdit::NoEcho:
                // Nothing
            break;
            case QLineEdit::Password:
            case QLineEdit::PasswordEchoOnEdit:
                res.append(QString(aValue.at(i).length(), qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter)));
            break;
            default:
                Q_ASSERT(false);
            break;
        }

        res.append("\"");
    }

    res.append("]");

    return res;
}

QString stringToString(const QString &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    switch (aMode)
    {
        case QLineEdit::Normal:             return aValue;
        case QLineEdit::NoEcho:             return "";
        case QLineEdit::Password:
        case QLineEdit::PasswordEchoOnEdit: return QString(aValue.length(), qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter));
        default:
            Q_ASSERT(false);
        break;
    }

    return aValue;
}

QString byteArrayToString(const QByteArray &aValue)
{
    return aValue.toHex().toUpper();
}

QString bitArrayToString(const QBitArray &aValue)
{
    QString res;

    for (int i=0; i<aValue.count(); ++i)
    {
        res.append(aValue.at(i) ? "1" : "0");
    }

    return res;
}

QString dateToString(const QDate &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString timeToString(const QTime &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString dateTimeToString(const QDateTime &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString localeToString(const QLocale &aValue)
{
    return aValue.languageToString(aValue.language())+
           ", "+
           aValue.countryToString(aValue.country());
}

QString rectToString(const QRect &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height())+
           ")";
}

QString rectFToString(const QRectF &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals)+
           ")";
}

QString sizeToString(const QSize &aValue)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString sizeFToString(const QSizeF &aValue, int aDecimals)
{
    return doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals);
}

QString lineToString(const QLine &aValue)
{
    return "[("+
           QString::number(aValue.x1())+
           ", "+
           QString::number(aValue.y1())+
           "), ("+
           QString::number(aValue.x2())+
           ", "+
           QString::number(aValue.y2())+
           ")]";
}

QString lineFToString(const QLineF &aValue, int aDecimals)
{
    return "[("+
           doubleToString(aValue.x1(), aDecimals)+
           ", "+
           doubleToString(aValue.y1(), aDecimals)+
           "), ("+
           doubleToString(aValue.x2(), aDecimals)+
           ", "+
           doubleToString(aValue.y2(), aDecimals)+
           ")]";
}

QString pointToString(const QPoint &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString pointFToString(const QPointF &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ")";
}
