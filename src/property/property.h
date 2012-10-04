#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

#include <QMetaProperty>
#include <QColor>

#include "delegates/customdelegate.h"

class PropertyTreeWidgetItem;

class Property : public QObject
{
    Q_OBJECT
public:
    explicit Property(const QMetaProperty &aMetaProperty, QObject *parent = 0);

    bool equals(const Property *aProperty);

    QVariant read(const QObjectList &aObjects, QVariant *aFirstValue=0);
    void write(const QObjectList &aObjects, const QVariant &aValue);

    void update(PropertyTreeWidgetItem *aItem, const QObjectList &aObjects);

    // -------------------------------------------------------------------------------------

    QString name() const;
    QColor  backgroundColor() const;
    bool    isWriteable() const;

protected:
    QMetaProperty mMetaProperty;
    QString       mName;
    QColor        mBackgroundColor;
    bool          mIsWritable;

    void setPropertiesForItem(const QVariant &aValue, const QVariant &aFirstValue, PropertyTreeWidgetItem *aParentItem);
    QIcon valueIcon(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueText(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* valueDelegate(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    int valueSubProperies(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    bool isNumber(const QVariant &aValue);

    QString valueToString(const bool &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const qint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const quint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const qint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const quint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const qint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const quint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const qint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const quint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const float &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const double &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QChar &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QString &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QByteArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QBitArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QDate &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QDateTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QUrl &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QRect &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QSize &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QLine &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QRegExp &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QEasingCurve &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QFont &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QBrush &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QColor &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QIcon &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QImage &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QKeySequence &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QPen &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QTextLength &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QTextFormat &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(void *aValue, PropertyTreeWidgetItem *aParentItem);
    QString valueToString(QObject *aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    QIcon iconForValue(const bool &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const qint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const quint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const qint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const quint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const qint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const quint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const qint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const quint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const float &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const double &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QChar &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QString &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QByteArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QBitArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QDate &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QDateTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QUrl &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QRect &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QSize &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QLine &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QRegExp &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QEasingCurve &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QFont &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QBrush &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QColor &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QIcon &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QImage &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QKeySequence &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QPen &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QTextLength &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QTextFormat &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(void *aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValue(QObject *aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    CustomDelegate* delegateForValue(const bool &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const qint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const quint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const qint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const quint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const qint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const quint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const qint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const quint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const float &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const double &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QChar &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QString &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QByteArray &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QBitArray &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QDate &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QTime &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QDateTime &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QUrl &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QRect &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QSize &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QLine &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QRegExp &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QEasingCurve &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QFont &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QBrush &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QColor &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QIcon &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QImage &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QKeySequence &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QPen &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QTextLength &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QTextFormat &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(void *aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValue(QObject *aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    int subPropertiesForValue(const bool &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const qint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const quint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const qint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const quint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const qint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const quint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const qint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const quint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const float &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const double &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QChar &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QString &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QByteArray &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QBitArray &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QDate &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QTime &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QDateTime &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QUrl &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QRect &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QSize &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QLine &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QRegExp &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QEasingCurve &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QFont &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QBrush &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QColor &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QIcon &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QImage &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QKeySequence &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QPen &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QTextLength &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QTextFormat &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(void *aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValue(QObject *aValue, PropertyTreeWidgetItem *aParentItem);

private slots:
    void valueChangedSlot(const QVariant &aNewValue);

signals:
    void valueChanged(const QVariant &aNewValue);
};

#endif // PROPERTY_H
