#include "property.h"

#include <QBitArray>
#include <QDate>
#include <QUrl>
#include <QEasingCurve>
#include <QBitmap>
#include <QPen>
#include <QTextLength>
#include <QMatrix4x4>
#include <QVector2D>

#include "propertytreewidgetitem.h"

Property::Property(const QMetaProperty &aMetaProperty)
{
    mMetaProperty=aMetaProperty;

    mName=mMetaProperty.name();
    mModified=false;
}

bool Property::equals(const Property *aProperty)
{
    return mName==aProperty->mName;
}

QVariant Property::read(const QObjectList &aObjects)
{
    if (aObjects.length()==0)
    {
        return QVariant();
    }

    QVariant res=mMetaProperty.read(aObjects.at(0));

    for (int i=1; i<aObjects.length(); ++i)
    {
        QVariant aOneValue=mMetaProperty.read(aObjects.at(i));

        if (res!=aOneValue)
        {
            return QVariant();
        }
    }

    return res;
}

void Property::write(const QObjectList &aObjects, const QVariant &aValue)
{
    for (int i=0; i<aObjects.length(); ++i)
    {
        mMetaProperty.write(aObjects[i], aValue);
    }
}

void Property::update(PropertyTreeWidgetItem *aItem, const QObjectList &aObjects)
{
    QVariant aValue=read(aObjects);

    aItem->setText(1, valueText(aValue));
    aItem->setIcon(1, valueIcon(aValue));
}

#define FUNCTION_FOR_VARIANT(aValue, aFunction, aDefaultResult) \
    switch (aValue.type()) \
    { \
        case QVariant::Bool:         return aFunction(aValue.value<bool>()); \
        case QVariant::Int:          return aFunction(aValue.value<qint32>()); \
        case QVariant::UInt:         return aFunction(aValue.value<quint32>()); \
        case QVariant::LongLong:     return aFunction(aValue.value<qint64>()); \
        case QVariant::ULongLong:    return aFunction(aValue.value<quint64>()); \
        case QVariant::Double:       return aFunction(aValue.value<double>()); \
        case QVariant::Char:         return aFunction(aValue.value<QChar>()); \
        case QVariant::Map:          return aFunction(aValue.value<QVariantMap>()); \
        case QVariant::List:         return aFunction(aValue.value<QVariantList>()); \
        case QVariant::StringList:   return aFunction(aValue.value<QStringList>()); \
        case QVariant::ByteArray:    return aFunction(aValue.value<QByteArray>()); \
        case QVariant::BitArray:     return aFunction(aValue.value<QBitArray>()); \
        case QVariant::Date:         return aFunction(aValue.value<QDate>()); \
        case QVariant::Time:         return aFunction(aValue.value<QTime>()); \
        case QVariant::DateTime:     return aFunction(aValue.value<QDateTime>()); \
        case QVariant::Url:          return aFunction(aValue.value<QUrl>()); \
        case QVariant::Locale:       return aFunction(aValue.value<QLocale>()); \
        case QVariant::Rect:         return aFunction(aValue.value<QRect>()); \
        case QVariant::RectF:        return aFunction(aValue.value<QRectF>()); \
        case QVariant::Size:         return aFunction(aValue.value<QSize>()); \
        case QVariant::SizeF:        return aFunction(aValue.value<QSizeF>()); \
        case QVariant::Line:         return aFunction(aValue.value<QLine>()); \
        case QVariant::LineF:        return aFunction(aValue.value<QLineF>()); \
        case QVariant::Point:        return aFunction(aValue.value<QPoint>()); \
        case QVariant::PointF:       return aFunction(aValue.value<QPointF>()); \
        case QVariant::RegExp:       return aFunction(aValue.value<QRegExp>()); \
        case QVariant::Hash:         return aFunction(aValue.value<QVariantHash>()); \
        case QVariant::EasingCurve:  return aFunction(aValue.value<QEasingCurve>()); \
        case QVariant::Font:         return aFunction(aValue.value<QFont>()); \
        case QVariant::Pixmap:       return aFunction(aValue.value<QPixmap>()); \
        case QVariant::Brush:        return aFunction(aValue.value<QBrush>()); \
        case QVariant::Color:        return aFunction(aValue.value<QColor>()); \
        case QVariant::Palette:      return aFunction(aValue.value<QPalette>()); \
        case QVariant::Icon:         return aFunction(aValue.value<QIcon>()); \
        case QVariant::Image:        return aFunction(aValue.value<QImage>()); \
        case QVariant::Polygon:      return aFunction(aValue.value<QPolygon>()); \
        case QVariant::Region:       return aFunction(aValue.value<QRegion>()); \
        case QVariant::Bitmap:       return aFunction(aValue.value<QBitmap>()); \
        case QVariant::Cursor:       return aFunction(aValue.value<QCursor>()); \
        case QVariant::SizePolicy:   return aFunction(aValue.value<QSizePolicy>()); \
        case QVariant::KeySequence:  return aFunction(aValue.value<QKeySequence>()); \
        case QVariant::Pen:          return aFunction(aValue.value<QPen>()); \
        case QVariant::TextLength:   return aFunction(aValue.value<QTextLength>()); \
        case QVariant::TextFormat:   return aFunction(aValue.value<QTextFormat>()); \
        case QVariant::Matrix:       return aFunction(aValue.value<QMatrix>()); \
        case QVariant::Transform:    return aFunction(aValue.value<QTransform>()); \
        case QVariant::Matrix4x4:    return aFunction(aValue.value<QMatrix4x4>()); \
        case QVariant::Vector2D:     return aFunction(aValue.value<QVector2D>()); \
        case QVariant::Vector3D:     return aFunction(aValue.value<QVector3D>()); \
        case QVariant::Vector4D:     return aFunction(aValue.value<QVector4D>()); \
        case QVariant::Quaternion:   return aFunction(aValue.value<QQuaternion>()); \
        case QMetaType::Long:        return aFunction(aValue.value<qint32>()); \
        case QMetaType::Short:       return aFunction(aValue.value<qint16>()); \
        case QMetaType::Char:        return aFunction(aValue.value<qint8>()); \
        case QMetaType::ULong:       return aFunction(aValue.value<quint32>()); \
        case QMetaType::UShort:      return aFunction(aValue.value<quint16>()); \
        case QMetaType::UChar:       return aFunction(aValue.value<quint8>()); \
        case QMetaType::Float:       return aFunction(aValue.value<float>()); \
        case QMetaType::VoidStar:    return aFunction(aValue.value<void *>()); \
        case QMetaType::QObjectStar: return aFunction(aValue.value<QObject *>()); \
        case QMetaType::QWidgetStar: return aFunction(aValue.value<QWidget *>()); \
        default: return aDefaultResult; \
    } \

QString Property::valueText(const QVariant &aValue)
{
    FUNCTION_FOR_VARIANT(aValue, valueToString, aValue.toString());
}

QIcon Property::valueIcon(const QVariant &aValue)
{
    return QIcon();
}

// -------------------------------------------------------------------------------------

QString Property::name() const
{
    return mName;
}

QColor Property::backgroundColor() const
{
    return mBackgroundColor;
}

bool Property::isModified() const
{
    return mModified;
}

void Property::setModified(const bool aModified)
{
    mModified=aModified;
}

// -------------------------------------------------------------------------------------

QString Property::valueToString(const bool &aValue)
{
    return aValue ? "true" : "false";
}

QString Property::valueToString(const qint8 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint8 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint16 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint16 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint32 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint32 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint64 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint64 &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const float &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const double &aValue)
{
    return QString::number(aValue);
}

QString Property::valueToString(const QChar &aValue)
{
    return QString(aValue);
}

QString Property::valueToString(const QVariantMap &aValue)
{
    return "";
}

QString Property::valueToString(const QVariantList &aValue)
{
    return "";
}

QString Property::valueToString(const QStringList &aValue)
{
    QString res="(";

    for (int i=0; i<aValue.length(); ++i)
    {
        res.append("\"");
        res.append(aValue.at(i));
        res.append("\"");

        if (i<aValue.length()-1)
        {
            res.append(";");
        }
    }

    res.append(")");

    return res;
}

QString Property::valueToString(const QByteArray &aValue)
{
    return aValue.toHex().toUpper();
}

QString Property::valueToString(const QBitArray &aValue)
{
    QString res;

    for (int i=0; i<aValue.count(); ++i)
    {
        res.append(aValue.at(i) ? "1" : "0");
    }

    return res;
}

QString Property::valueToString(const QDate &aValue)
{
    return aValue.toString("dd.MM.yyyy");
}

QString Property::valueToString(const QTime &aValue)
{
    return aValue.toString("HH:mm:ss");
}

QString Property::valueToString(const QDateTime &aValue)
{
    return aValue.toString("dd.MM.yyyy HH:mm:ss");
}

QString Property::valueToString(const QUrl &aValue)
{
    return aValue.toString();
}

QString Property::valueToString(const QLocale &aValue)
{
    return aValue.languageToString(aValue.language())+", "+aValue.countryToString(aValue.country());
}

QString Property::valueToString(const QRect &aValue)
{
    return "[("+QString::number(aValue.x())+", "+QString::number(aValue.y())+"), "+QString::number(aValue.width())+" x "+QString::number(aValue.height())+"]";
}

QString Property::valueToString(const QRectF &aValue)
{
    return "[("+QString::number(aValue.x())+", "+QString::number(aValue.y())+"), "+QString::number(aValue.width())+" x "+QString::number(aValue.height())+"]";
}

QString Property::valueToString(const QSize &aValue)
{
    return QString::number(aValue.width())+" x "+QString::number(aValue.height());
}

QString Property::valueToString(const QSizeF &aValue)
{
    return QString::number(aValue.width())+" x "+QString::number(aValue.height());
}

QString Property::valueToString(const QLine &aValue)
{
    return "[("+QString::number(aValue.x1())+", "+QString::number(aValue.y1())+"), ("+QString::number(aValue.x2())+", "+QString::number(aValue.y2())+")]";
}

QString Property::valueToString(const QLineF &aValue)
{
    return "[("+QString::number(aValue.x1())+", "+QString::number(aValue.y1())+"), ("+QString::number(aValue.x2())+", "+QString::number(aValue.y2())+")]";
}

QString Property::valueToString(const QPoint &aValue)
{
    return QString::number(aValue.x())+", "+QString::number(aValue.y());
}

QString Property::valueToString(const QPointF &aValue)
{
    return QString::number(aValue.x())+", "+QString::number(aValue.y());
}

QString Property::valueToString(const QRegExp &aValue)
{
    return aValue.pattern();
}

QString Property::valueToString(const QVariantHash &aValue)
{
    return "";
}

QString Property::valueToString(const QEasingCurve &aValue)
{
    return "";
}

QString Property::valueToString(const QFont &aValue)
{
    return "["+aValue.family()+", "+QString::number(aValue.pointSize())+"]";
}

QString Property::valueToString(const QPixmap &aValue)
{
    return valueToString(aValue.size());
}

QString Property::valueToString(const QBrush &aValue)
{
    return "";
}

QString Property::valueToString(const QColor &aValue)
{
    return "("+QString::number(aValue.red())+", "+QString::number(aValue.green())+", "+QString::number(aValue.blue())+")"+"["+QString::number(aValue.alpha())+"]";
}

QString Property::valueToString(const QPalette &aValue)
{
    return "";
}

QString Property::valueToString(const QIcon &aValue)
{
    return aValue.name();
}

QString Property::valueToString(const QImage &aValue)
{
    return valueToString(aValue.size());
}

QString Property::valueToString(const QPolygon &aValue)
{
    return "";
}

QString Property::valueToString(const QRegion &aValue)
{
    return "";
}

QString Property::valueToString(const QBitmap &aValue)
{
    return valueToString(aValue.size());
}

QString Property::valueToString(const QCursor &aValue)
{
    switch (aValue.shape())
    {
        case Qt::ArrowCursor:        return "ArrowCursor";
        case Qt::UpArrowCursor:      return "UpArrowCursor";
        case Qt::CrossCursor:        return "CrossCursor";
        case Qt::WaitCursor:         return "WaitCursor";
        case Qt::IBeamCursor:        return "IBeamCursor";
        case Qt::SizeVerCursor:      return "SizeVerCursor";
        case Qt::SizeHorCursor:      return "SizeHorCursor";
        case Qt::SizeBDiagCursor:    return "SizeBDiagCursor";
        case Qt::SizeFDiagCursor:    return "SizeFDiagCursor";
        case Qt::SizeAllCursor:      return "SizeAllCursor";
        case Qt::BlankCursor:        return "BlankCursor";
        case Qt::SplitVCursor:       return "SplitVCursor";
        case Qt::SplitHCursor:       return "SplitHCursor";
        case Qt::PointingHandCursor: return "PointingHandCursor";
        case Qt::ForbiddenCursor:    return "ForbiddenCursor";
        case Qt::WhatsThisCursor:    return "WhatsThisCursor";
        case Qt::BusyCursor:         return "BusyCursor";
        case Qt::OpenHandCursor:     return "OpenHandCursor";
        case Qt::ClosedHandCursor:   return "ClosedHandCursor";
        case Qt::DragCopyCursor:     return "DragCopyCursor";
        case Qt::DragMoveCursor:     return "DragMoveCursor";
        case Qt::DragLinkCursor:     return "DragLinkCursor";
        case Qt::BitmapCursor:       return "BitmapCursor";
        case Qt::CustomCursor:       return "CustomCursor";
    }

    return "[Unknown cursor]";
}

QString Property::valueToString(const QSizePolicy &aValue)
{
    return "";
}

QString Property::valueToString(const QKeySequence &aValue)
{
    return "";
}

QString Property::valueToString(const QPen &aValue)
{
    return "";
}

QString Property::valueToString(const QTextLength &aValue)
{
    return "";
}

QString Property::valueToString(const QTextFormat &aValue)
{
    return "";
}

QString Property::valueToString(const QMatrix &aValue)
{
    return "";
}

QString Property::valueToString(const QTransform &aValue)
{
    return "";
}

QString Property::valueToString(const QMatrix4x4 &aValue)
{
    return "";
}

QString Property::valueToString(const QVector2D &aValue)
{
    return "";
}

QString Property::valueToString(const QVector3D &aValue)
{
    return "";
}

QString Property::valueToString(const QVector4D &aValue)
{
    return "";
}

QString Property::valueToString(const QQuaternion &aValue)
{
    return "";
}

QString Property::valueToString(void *aValue)
{
    return "";
}

QString Property::valueToString(QObject *aValue)
{
    return "";
}
