#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaProperty>

#include <QColor>

class PropertyTreeWidgetItem;

class Property
{
public:
    Property(const QMetaProperty &aMetaProperty);

    bool equals(const Property *aProperty);

    QVariant read(const QObjectList &aObjects);
    void write(const QObjectList &aObjects, const QVariant &aValue);

    void update(PropertyTreeWidgetItem *aItem, const QObjectList &aObjects);

    // -------------------------------------------------------------------------------------

    QString name() const;
    QColor  backgroundColor() const;

    bool    isModified() const;
    void    setModified(const bool aModified);

protected:
    QMetaProperty mMetaProperty;
    QString       mName;
    QColor        mBackgroundColor;
    bool          mModified;

    QIcon valueIcon(const QVariant &aValue);
    QString valueText(const QVariant &aValue);

    // -------------------------------------------------------------------------------------

    bool isNumber(const QVariant &aValue);

    QString valueToString(const bool &aValue);
    QString valueToString(const qint8 &aValue);
    QString valueToString(const quint8 &aValue);
    QString valueToString(const qint16 &aValue);
    QString valueToString(const quint16 &aValue);
    QString valueToString(const qint32 &aValue);
    QString valueToString(const quint32 &aValue);
    QString valueToString(const qint64 &aValue);
    QString valueToString(const quint64 &aValue);
    QString valueToString(const float &aValue);
    QString valueToString(const double &aValue);
    QString valueToString(const QChar &aValue);
    QString valueToString(const QVariantMap &aValue);
    QString valueToString(const QVariantList &aValue);
    QString valueToString(const QStringList &aValue);
    QString valueToString(const QByteArray &aValue);
    QString valueToString(const QBitArray &aValue);
    QString valueToString(const QDate &aValue);
    QString valueToString(const QTime &aValue);
    QString valueToString(const QDateTime &aValue);
    QString valueToString(const QUrl &aValue);
    QString valueToString(const QLocale &aValue);
    QString valueToString(const QRect &aValue);
    QString valueToString(const QRectF &aValue);
    QString valueToString(const QSize &aValue);
    QString valueToString(const QSizeF &aValue);
    QString valueToString(const QLine &aValue);
    QString valueToString(const QLineF &aValue);
    QString valueToString(const QPoint &aValue);
    QString valueToString(const QPointF &aValue);
    QString valueToString(const QRegExp &aValue);
    QString valueToString(const QVariantHash &aValue);
    QString valueToString(const QEasingCurve &aValue);
    QString valueToString(const QFont &aValue);
    QString valueToString(const QPixmap &aValue);
    QString valueToString(const QBrush &aValue);
    QString valueToString(const QColor &aValue);
    QString valueToString(const QPalette &aValue);
    QString valueToString(const QIcon &aValue);
    QString valueToString(const QImage &aValue);
    QString valueToString(const QPolygon &aValue);
    QString valueToString(const QRegion &aValue);
    QString valueToString(const QBitmap &aValue);
    QString valueToString(const QCursor &aValue);
    QString valueToString(const QSizePolicy &aValue);
    QString valueToString(const QKeySequence &aValue);
    QString valueToString(const QPen &aValue);
    QString valueToString(const QTextLength &aValue);
    QString valueToString(const QTextFormat &aValue);
    QString valueToString(const QMatrix &aValue);
    QString valueToString(const QTransform &aValue);
    QString valueToString(const QMatrix4x4 &aValue);
    QString valueToString(const QVector2D &aValue);
    QString valueToString(const QVector3D &aValue);
    QString valueToString(const QVector4D &aValue);
    QString valueToString(const QQuaternion &aValue);
    QString valueToString(void *aValue);
    QString valueToString(QObject *aValue);

    // -------------------------------------------------------------------------------------

    QIcon iconForValue(const bool &aValue);
    QIcon iconForValue(const qint8 &aValue);
    QIcon iconForValue(const quint8 &aValue);
    QIcon iconForValue(const qint16 &aValue);
    QIcon iconForValue(const quint16 &aValue);
    QIcon iconForValue(const qint32 &aValue);
    QIcon iconForValue(const quint32 &aValue);
    QIcon iconForValue(const qint64 &aValue);
    QIcon iconForValue(const quint64 &aValue);
    QIcon iconForValue(const float &aValue);
    QIcon iconForValue(const double &aValue);
    QIcon iconForValue(const QChar &aValue);
    QIcon iconForValue(const QVariantMap &aValue);
    QIcon iconForValue(const QVariantList &aValue);
    QIcon iconForValue(const QStringList &aValue);
    QIcon iconForValue(const QByteArray &aValue);
    QIcon iconForValue(const QBitArray &aValue);
    QIcon iconForValue(const QDate &aValue);
    QIcon iconForValue(const QTime &aValue);
    QIcon iconForValue(const QDateTime &aValue);
    QIcon iconForValue(const QUrl &aValue);
    QIcon iconForValue(const QLocale &aValue);
    QIcon iconForValue(const QRect &aValue);
    QIcon iconForValue(const QRectF &aValue);
    QIcon iconForValue(const QSize &aValue);
    QIcon iconForValue(const QSizeF &aValue);
    QIcon iconForValue(const QLine &aValue);
    QIcon iconForValue(const QLineF &aValue);
    QIcon iconForValue(const QPoint &aValue);
    QIcon iconForValue(const QPointF &aValue);
    QIcon iconForValue(const QRegExp &aValue);
    QIcon iconForValue(const QVariantHash &aValue);
    QIcon iconForValue(const QEasingCurve &aValue);
    QIcon iconForValue(const QFont &aValue);
    QIcon iconForValue(const QPixmap &aValue);
    QIcon iconForValue(const QBrush &aValue);
    QIcon iconForValue(const QColor &aValue);
    QIcon iconForValue(const QPalette &aValue);
    QIcon iconForValue(const QIcon &aValue);
    QIcon iconForValue(const QImage &aValue);
    QIcon iconForValue(const QPolygon &aValue);
    QIcon iconForValue(const QRegion &aValue);
    QIcon iconForValue(const QBitmap &aValue);
    QIcon iconForValue(const QCursor &aValue);
    QIcon iconForValue(const QSizePolicy &aValue);
    QIcon iconForValue(const QKeySequence &aValue);
    QIcon iconForValue(const QPen &aValue);
    QIcon iconForValue(const QTextLength &aValue);
    QIcon iconForValue(const QTextFormat &aValue);
    QIcon iconForValue(const QMatrix &aValue);
    QIcon iconForValue(const QTransform &aValue);
    QIcon iconForValue(const QMatrix4x4 &aValue);
    QIcon iconForValue(const QVector2D &aValue);
    QIcon iconForValue(const QVector3D &aValue);
    QIcon iconForValue(const QVector4D &aValue);
    QIcon iconForValue(const QQuaternion &aValue);
    QIcon iconForValue(void *aValue);
    QIcon iconForValue(QObject *aValue);
};

#endif // PROPERTY_H
