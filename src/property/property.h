#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

#include <QMetaProperty>
#include <QColor>

#include "delegates/customdelegate.h"
#include "propertyattributes.h"

class PropertyTreeWidgetItem;

class Property : public QObject
{
    Q_OBJECT
public:
    // It is a hack to provide Type from QTextLength
    Q_ENUMS(LengthType)
    enum LengthType { VariableLength = 0, FixedLength, PercentageLength };

    explicit Property(const QMetaObject *aPropertyObject, const QMetaProperty &aMetaProperty, QObject *parent = 0);

    bool equals(const Property *aProperty);

    QVariant read(const QObjectList &aObjects, QVariant *aFirstValue=0);
    void write(const QObjectList &aObjects, const QVariant &aValue);

    void update(PropertyTreeWidgetItem *aItem, const QObjectList &aObjects);

    const PropertyAttributes *attributes() const;
    QString valueText(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    const QMetaObject *propertyObject() const;

    QString            name() const;

    QColor             backgroundColor() const;
    void               setBackgroundColor(const QColor &aBackgroundColor);

    bool               isWriteable() const;

protected:
    const QMetaObject *mPropertyObject;
    QMetaProperty      mMetaProperty;
    PropertyAttributes mAttributes;
    QString            mName;
    QColor             mBackgroundColor;
    bool               mIsWritable;

    void setPropertiesForItem(const QVariant &aValue, const QVariant &aFirstValue, PropertyTreeWidgetItem *aParentItem);
    void setPropertiesForItem(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon valueIcon(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* valueDelegate(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);
    int valueSubProperies(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    QString variantToStringEnum(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToStringFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const bool &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const qint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const quint8 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const qint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const quint16 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const qint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const quint32 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const qint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const quint64 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const float &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const double &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QChar &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QString &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QByteArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QBitArray &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QDate &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QDateTime &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QUrl &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QRect &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QSize &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QLine &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QRegExp &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QEasingCurve &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QFont &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QBrush &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QColor &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QIcon &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QImage &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QKeySequence &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QPen &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QTextLength &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QTextFormat &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(void *aValue, PropertyTreeWidgetItem *aParentItem);
    QString variantToString(QObject *aValue, PropertyTreeWidgetItem *aParentItem);

    // -------------------------------------------------------------------------------------

    QIcon iconForValueEnum(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
    QIcon iconForValueFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
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

    CustomDelegate* delegateForValueEnum(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
    CustomDelegate* delegateForValueFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
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

    PropertyTreeWidgetItem *senderItem();
    void removeAllChildren(PropertyTreeWidgetItem *aParentItem);

    int subPropertiesForValueEnum(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
    int subPropertiesForValueFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem);
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
    void flagChanged(const QVariant &aNewValue);

    void mapItemChanged(const QVariant &aNewValue);

    void listItemChanged(const QVariant &aNewValue);

    void stringListItemChanged(const QVariant &aNewValue);

    void localeLanguageChanged(const QVariant &aNewValue);
    void localeCountryChanged(const QVariant &aNewValue);

    void rectXChanged(const QVariant &aNewValue);
    void rectYChanged(const QVariant &aNewValue);
    void rectWidthChanged(const QVariant &aNewValue);
    void rectHeightChanged(const QVariant &aNewValue);

    void rectFXChanged(const QVariant &aNewValue);
    void rectFYChanged(const QVariant &aNewValue);
    void rectFWidthChanged(const QVariant &aNewValue);
    void rectFHeightChanged(const QVariant &aNewValue);

    void sizeWidthChanged(const QVariant &aNewValue);
    void sizeHeightChanged(const QVariant &aNewValue);

    void sizeFWidthChanged(const QVariant &aNewValue);
    void sizeFHeightChanged(const QVariant &aNewValue);

    void lineX1Changed(const QVariant &aNewValue);
    void lineY1Changed(const QVariant &aNewValue);
    void lineX2Changed(const QVariant &aNewValue);
    void lineY2Changed(const QVariant &aNewValue);

    void lineFX1Changed(const QVariant &aNewValue);
    void lineFY1Changed(const QVariant &aNewValue);
    void lineFX2Changed(const QVariant &aNewValue);
    void lineFY2Changed(const QVariant &aNewValue);

    void pointX1Changed(const QVariant &aNewValue);
    void pointY1Changed(const QVariant &aNewValue);

    void pointFX1Changed(const QVariant &aNewValue);
    void pointFY1Changed(const QVariant &aNewValue);

    void hashItemChanged(const QVariant &aNewValue);

    void easingCurveTypeChanged(const QVariant &aNewValue);
    void easingCurveAmplitudeChanged(const QVariant &aNewValue);
    void easingCurveOvershootChanged(const QVariant &aNewValue);
    void easingCurvePeriodChanged(const QVariant &aNewValue);

    void fontFamilyChanged(const QVariant &aNewValue);
    void fontSizeChanged(const QVariant &aNewValue);
    void fontBoldChanged(const QVariant &aNewValue);
    void fontItalicChanged(const QVariant &aNewValue);
    void fontUnderlineChanged(const QVariant &aNewValue);
    void fontStrikeOutChanged(const QVariant &aNewValue);
    void fontKerningChanged(const QVariant &aNewValue);
    void fontAntiAliasingChanged(const QVariant &aNewValue);

    void colorRedChanged(const QVariant &aNewValue);
    void colorGreenChanged(const QVariant &aNewValue);
    void colorBlueChanged(const QVariant &aNewValue);
    void colorAlphaChanged(const QVariant &aNewValue);

    void paletteColorChanged(const QVariant &aNewValue);

    void polygonItemChanged(const QVariant &aNewValue);

    void regionItemChanged(const QVariant &aNewValue);

    void sizePolicyHorizontalPolicyChanged(const QVariant &aNewValue);
    void sizePolicyVerticalPolicyChanged(const QVariant &aNewValue);
    void sizePolicyHorizontalStretchChanged(const QVariant &aNewValue);
    void sizePolicyVerticalStretchChanged(const QVariant &aNewValue);

    void penBrushChanged(const QVariant &aNewValue);
    void penWidthChanged(const QVariant &aNewValue);
    void penStyleChanged(const QVariant &aNewValue);
    void penCapStyleChanged(const QVariant &aNewValue);
    void penJoinStyleChanged(const QVariant &aNewValue);
    void penColorChanged(const QVariant &aNewValue);

    void textLengthTypeChanged(const QVariant &aNewValue);
    void textLengthValueChanged(const QVariant &aNewValue);

    void matrixM11Changed(const QVariant &aNewValue);
    void matrixM12Changed(const QVariant &aNewValue);
    void matrixM21Changed(const QVariant &aNewValue);
    void matrixM22Changed(const QVariant &aNewValue);
    void matrixDxChanged(const QVariant &aNewValue);
    void matrixDyChanged(const QVariant &aNewValue);

    void transformM11Changed(const QVariant &aNewValue);
    void transformM12Changed(const QVariant &aNewValue);
    void transformM13Changed(const QVariant &aNewValue);
    void transformM21Changed(const QVariant &aNewValue);
    void transformM22Changed(const QVariant &aNewValue);
    void transformM23Changed(const QVariant &aNewValue);
    void transformM31Changed(const QVariant &aNewValue);
    void transformM32Changed(const QVariant &aNewValue);
    void transformM33Changed(const QVariant &aNewValue);

    void matrix4x4ItemChanged(const QVariant &aNewValue);

    void vector2DXChanged(const QVariant &aNewValue);
    void vector2DYChanged(const QVariant &aNewValue);

    void vector3DXChanged(const QVariant &aNewValue);
    void vector3DYChanged(const QVariant &aNewValue);
    void vector3DZChanged(const QVariant &aNewValue);

    void vector4DXChanged(const QVariant &aNewValue);
    void vector4DYChanged(const QVariant &aNewValue);
    void vector4DZChanged(const QVariant &aNewValue);
    void vector4DWChanged(const QVariant &aNewValue);

    void quaternionScalarChanged(const QVariant &aNewValue);
    void quaternionXChanged(const QVariant &aNewValue);
    void quaternionYChanged(const QVariant &aNewValue);
    void quaternionZChanged(const QVariant &aNewValue);

signals:
    void valueChanged(const QVariant &aNewValue);
};

#endif // PROPERTY_H
