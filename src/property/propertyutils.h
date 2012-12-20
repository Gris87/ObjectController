#ifndef PROPERTYUTILS_H
#define PROPERTYUTILS_H

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
QString localeToString(const QLocale &aValue);
QString rectToString(const QRect &aValue);
QString rectFToString(const QRectF &aValue, int aDecimals=6);
QString sizeToString(const QSize &aValue);
QString sizeFToString(const QSizeF &aValue, int aDecimals=6);
QString lineToString(const QLine &aValue);
QString lineFToString(const QLineF &aValue, int aDecimals=6);
QString pointToString(const QPoint &aValue);
QString pointFToString(const QPointF &aValue, int aDecimals=6);
QString easingCurveToString(const QEasingCurve &aValue);
QString fontToString(const QFont &aValue);
QString pixmapToString(const QPixmap &aValue);
QString brushToString(const QBrush &aValue);
QString colorToString(const QColor &aValue, bool alphaEnabled=true);

#endif // PROPERTYUTILS_H
