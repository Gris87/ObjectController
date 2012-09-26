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
};

#endif // PROPERTY_H
