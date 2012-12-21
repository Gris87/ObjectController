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
QString easingCurveToString(const QEasingCurve &aValue, int aDecimals=6);
QString fontToString(const QFont &aValue);
QString pixmapToString(const QPixmap &aValue);
QString brushToString(const QBrush &aValue, bool alphaEnabled=true, int aDecimals=6);
QString colorToString(const QColor &aValue, bool alphaEnabled=true);
QString imageToString(const QImage &aValue);
QString polygonToString(const QPolygon &aValue);
QString regionToString(const QRegion &aValue);
QString bitmapToString(const QBitmap &aValue);
QString cursorToString(const QCursor &aValue);
QString sizePolicyToString(const QSizePolicy &aValue);
QString keySequenceToString(const QKeySequence &aValue);
QString textLengthToString(const QTextLength &aValue, int aDecimals=6);
QString textFormatToString(const QTextFormat &aValue);
QString matrixToString(const QMatrix &aValue, int aDecimals=6);
QString transformToString(const QTransform &aValue, int aDecimals=6);
QString matrix4x4ToString(const QMatrix4x4 &aValue, int aDecimals=6);
QString vector2DToString(const QVector2D &aValue, int aDecimals=6);
QString vector3DToString(const QVector3D &aValue, int aDecimals=6);
QString vector4DToString(const QVector4D &aValue, int aDecimals=6);
QString quaternionToString(const QQuaternion &aValue, int aDecimals=6);
QString voidToString(void *aValue);
QString objectToString(QObject *aValue);

// -------------------------------------------------------------------------------------

QIcon iconForBool(const bool &aValue, QStyle *aStyle);
QIcon iconForDate();
QIcon iconForTime();
QIcon iconForDateTime();
QIcon iconForRect();
QIcon iconForRectF();
QIcon iconForSize();
QIcon iconForSizeF();
QIcon iconForLine();
QIcon iconForLineF();
QIcon iconForPoint();
QIcon iconForPointF();
QIcon iconForEasingCurve();
QIcon iconForFont(QFont aValue);
QIcon iconForPixmap(const QPixmap &aValue);
QIcon iconForBrush(const QBrush &aValue);
QIcon iconForColor(const QColor &aValue);
QIcon iconForPalette();
QIcon iconForImage(const QImage &aValue);
QIcon iconForPolygon();
QIcon iconForRegion();
QIcon iconForBitmap(const QBitmap &aValue);
QIcon iconForCursor(const QCursor &aValue);
QIcon iconForPen(const QPen &aValue);
QIcon iconForMatrix();
QIcon iconForTransform();
QIcon iconForMatrix4x4();
QIcon iconForVector2D();
QIcon iconForVector3D();
QIcon iconForVector4D();

#endif // PROPERTYUTILS_H
