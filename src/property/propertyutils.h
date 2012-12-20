#ifndef PROPERTYUTILS_H
#define PROPERTYUTILS_H

#include <QWidget>
#include <QString>
#include <QMetaEnum>

#include "propertyattributes.h"

QString enumToString(const QMetaEnum &aMetaEnum, const int &aValue);
QString flagsToString(const QMetaEnum &aMetaEnum, const int &aValue);
QString boolToString(const bool &aValue);
QString intToString(const qint8 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const quint8 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const qint16 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const quint16 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const qint32 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const quint32 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const qint64 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString intToString(const quint64 &aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString());
QString doubleToString(double aValue, int aDecimals=6);
QString doubleToString(double aValue, const QString &aPrefix=QString(), const QString &aSuffix=QString(), int aDecimals=6);
QString charToString(const QChar &aValue, const QString &aEchoMode=QString());
QString stringListToString(const QStringList &aValue, const QString &aEchoMode=QString());
QString stringToString(const QString &aValue, const QString &aEchoMode=QString());
QString byteArrayToString(const QByteArray &aValue);
QString bitArrayToString(const QBitArray &aValue);
QString dateToString(const QDate &aValue, const QString &aFormat=QString("dd.MM.yyyy"));
QString timeToString(const QTime &aValue, const QString &aFormat=QString("HH:mm:ss"));
QString dateTimeToString(const QDateTime &aValue, const QString &aFormat=QString("dd.MM.yyyy HH:mm:ss"));

#endif // PROPERTYUTILS_H
