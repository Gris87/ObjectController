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
#include <QPainter>
#include <QApplication>

#include "propertytreewidget.h"
#include "propertytreewidgetitem.h"

Property::Property(const QMetaProperty &aMetaProperty, QObject *parent) :
    QObject(parent)
{
    mMetaProperty=aMetaProperty;

    mName=mMetaProperty.name();
    mIsWritable=mMetaProperty.isWritable();
}

bool Property::equals(const Property *aProperty)
{
    return mName==aProperty->mName;
}

QVariant Property::read(const QObjectList &aObjects, QVariant *aFirstValue)
{
    if (aObjects.length()==0)
    {
        if (aFirstValue)
        {
            *aFirstValue=QVariant();
        }

        return QVariant();
    }

    QVariant res=mMetaProperty.read(aObjects.at(0));

    if (aFirstValue)
    {
        *aFirstValue=res;
    }

    for (int i=1; i<aObjects.length(); ++i)
    {
        QVariant aOneValue=mMetaProperty.read(aObjects.at(i));

        if (aFirstValue && !aFirstValue->isValid())
        {
            *aFirstValue=aOneValue;
        }

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
    QVariant aFirstValue;
    QVariant aValue=read(aObjects, &aFirstValue);

    setPropertiesForItem(aValue, aFirstValue, aItem);
}

void Property::setPropertiesForItem(const QVariant &aValue, const QVariant &aFirstValue, PropertyTreeWidgetItem *aParentItem)
{
    aParentItem->setText(1, valueText(aValue, aParentItem));
    aParentItem->setIcon(1, valueIcon(aValue, aParentItem));

    aParentItem->setFirstValue(aFirstValue);
    aParentItem->setDelegate(valueDelegate(aValue, aParentItem));

    int aChildCount=valueSubProperies(aValue, aParentItem);

    while (aParentItem->childCount()>aChildCount)
    {
        delete aParentItem->takeChild(aParentItem->childCount()-1);
    }
}

#define FUNCTION_FOR_VARIANT(aValue, aParentItem, aFunction, aDefaultResult) \
    switch (aValue.type()) \
    { \
        case QVariant::Bool:         return aFunction(aValue.value<bool>(), aParentItem); \
        case QVariant::Int:          return aFunction(aValue.value<qint32>(), aParentItem); \
        case QVariant::UInt:         return aFunction(aValue.value<quint32>(), aParentItem); \
        case QVariant::LongLong:     return aFunction(aValue.value<qint64>(), aParentItem); \
        case QVariant::ULongLong:    return aFunction(aValue.value<quint64>(), aParentItem); \
        case QVariant::Double:       return aFunction(aValue.value<double>(), aParentItem); \
        case QVariant::Char:         return aFunction(aValue.value<QChar>(), aParentItem); \
        case QVariant::Map:          return aFunction(aValue.value<QVariantMap>(), aParentItem); \
        case QVariant::List:         return aFunction(aValue.value<QVariantList>(), aParentItem); \
        case QVariant::StringList:   return aFunction(aValue.value<QStringList>(), aParentItem); \
        case QVariant::String:       return aFunction(aValue.value<QString>(), aParentItem); \
        case QVariant::ByteArray:    return aFunction(aValue.value<QByteArray>(), aParentItem); \
        case QVariant::BitArray:     return aFunction(aValue.value<QBitArray>(), aParentItem); \
        case QVariant::Date:         return aFunction(aValue.value<QDate>(), aParentItem); \
        case QVariant::Time:         return aFunction(aValue.value<QTime>(), aParentItem); \
        case QVariant::DateTime:     return aFunction(aValue.value<QDateTime>(), aParentItem); \
        case QVariant::Url:          return aFunction(aValue.value<QUrl>(), aParentItem); \
        case QVariant::Locale:       return aFunction(aValue.value<QLocale>(), aParentItem); \
        case QVariant::Rect:         return aFunction(aValue.value<QRect>(), aParentItem); \
        case QVariant::RectF:        return aFunction(aValue.value<QRectF>(), aParentItem); \
        case QVariant::Size:         return aFunction(aValue.value<QSize>(), aParentItem); \
        case QVariant::SizeF:        return aFunction(aValue.value<QSizeF>(), aParentItem); \
        case QVariant::Line:         return aFunction(aValue.value<QLine>(), aParentItem); \
        case QVariant::LineF:        return aFunction(aValue.value<QLineF>(), aParentItem); \
        case QVariant::Point:        return aFunction(aValue.value<QPoint>(), aParentItem); \
        case QVariant::PointF:       return aFunction(aValue.value<QPointF>(), aParentItem); \
        case QVariant::RegExp:       return aFunction(aValue.value<QRegExp>(), aParentItem); \
        case QVariant::Hash:         return aFunction(aValue.value<QVariantHash>(), aParentItem); \
        case QVariant::EasingCurve:  return aFunction(aValue.value<QEasingCurve>(), aParentItem); \
        case QVariant::Font:         return aFunction(aValue.value<QFont>(), aParentItem); \
        case QVariant::Pixmap:       return aFunction(aValue.value<QPixmap>(), aParentItem); \
        case QVariant::Brush:        return aFunction(aValue.value<QBrush>(), aParentItem); \
        case QVariant::Color:        return aFunction(aValue.value<QColor>(), aParentItem); \
        case QVariant::Palette:      return aFunction(aValue.value<QPalette>(), aParentItem); \
        case QVariant::Icon:         return aFunction(aValue.value<QIcon>(), aParentItem); \
        case QVariant::Image:        return aFunction(aValue.value<QImage>(), aParentItem); \
        case QVariant::Polygon:      return aFunction(aValue.value<QPolygon>(), aParentItem); \
        case QVariant::Region:       return aFunction(aValue.value<QRegion>(), aParentItem); \
        case QVariant::Bitmap:       return aFunction(aValue.value<QBitmap>(), aParentItem); \
        case QVariant::Cursor:       return aFunction(aValue.value<QCursor>(), aParentItem); \
        case QVariant::SizePolicy:   return aFunction(aValue.value<QSizePolicy>(), aParentItem); \
        case QVariant::KeySequence:  return aFunction(aValue.value<QKeySequence>(), aParentItem); \
        case QVariant::Pen:          return aFunction(aValue.value<QPen>(), aParentItem); \
        case QVariant::TextLength:   return aFunction(aValue.value<QTextLength>(), aParentItem); \
        case QVariant::TextFormat:   return aFunction(aValue.value<QTextFormat>(), aParentItem); \
        case QVariant::Matrix:       return aFunction(aValue.value<QMatrix>(), aParentItem); \
        case QVariant::Transform:    return aFunction(aValue.value<QTransform>(), aParentItem); \
        case QVariant::Matrix4x4:    return aFunction(aValue.value<QMatrix4x4>(), aParentItem); \
        case QVariant::Vector2D:     return aFunction(aValue.value<QVector2D>(), aParentItem); \
        case QVariant::Vector3D:     return aFunction(aValue.value<QVector3D>(), aParentItem); \
        case QVariant::Vector4D:     return aFunction(aValue.value<QVector4D>(), aParentItem); \
        case QVariant::Quaternion:   return aFunction(aValue.value<QQuaternion>(), aParentItem); \
        case QMetaType::Long:        return aFunction(aValue.value<qint32>(), aParentItem); \
        case QMetaType::Short:       return aFunction(aValue.value<qint16>(), aParentItem); \
        case QMetaType::Char:        return aFunction(aValue.value<qint8>(), aParentItem); \
        case QMetaType::ULong:       return aFunction(aValue.value<quint32>(), aParentItem); \
        case QMetaType::UShort:      return aFunction(aValue.value<quint16>(), aParentItem); \
        case QMetaType::UChar:       return aFunction(aValue.value<quint8>(), aParentItem); \
        case QMetaType::Float:       return aFunction(aValue.value<float>(), aParentItem); \
        case QMetaType::VoidStar:    return aFunction(aValue.value<void *>(), aParentItem); \
        case QMetaType::QObjectStar: return aFunction(aValue.value<QObject *>(), aParentItem); \
        case QMetaType::QWidgetStar: return aFunction(aValue.value<QWidget *>(), aParentItem); \
        default: return aDefaultResult; \
    } \

QString Property::valueText(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem)
{
    FUNCTION_FOR_VARIANT(aValue, aParentItem, valueToString, aValue.toString());
}

QIcon Property::valueIcon(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem)
{
    FUNCTION_FOR_VARIANT(aValue, aParentItem, iconForValue, QIcon());
}

CustomDelegate* Property::valueDelegate(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem)
{
    FUNCTION_FOR_VARIANT(aValue, aParentItem, delegateForValue, 0);
}

int Property::valueSubProperies(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem)
{
    FUNCTION_FOR_VARIANT(aValue, aParentItem, subPropertiesForValue, 0);
}

void Property::valueChangedSlot(const QVariant &aNewValue)
{
    emit valueChanged(aNewValue);
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

bool Property::isWriteable() const
{
    return mIsWritable;
}

// -------------------------------------------------------------------------------------

bool Property::isNumber(const QVariant &aValue)
{
    int aType=aValue.type();

    return (
            aType==QVariant::Int
            ||
            aType==QVariant::UInt
            ||
            aType==QVariant::LongLong
            ||
            aType==QVariant::ULongLong
            ||
            aType==QVariant::Double
            ||
            aType==QMetaType::Float
            ||
            aType==QMetaType::Long
            ||
            aType==QMetaType::Short
            ||
            aType==QMetaType::Char
            ||
            aType==QMetaType::ULong
            ||
            aType==QMetaType::UShort
            ||
            aType==QMetaType::UChar
           );
}

QString Property::valueToString(const bool &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue ? qApp->translate("Property", "true") : qApp->translate("Property", "false");
}

QString Property::valueToString(const qint8 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint8 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint16 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint16 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint32 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint32 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const qint64 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const quint64 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const float &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const double &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue);
}

QString Property::valueToString(const QChar &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString(aValue);
}

QString Property::valueToString(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem)
{
    QString res="[";

    for (QVariantMap::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        if (res.length()>1)
        {
            res.append("; ");
        }

        res.append("(");

        res.append("\"");
        res.append(i.key());
        res.append("\"");

        res.append(", ");

        if (isNumber(i.value()))
        {
            res.append(valueText(i.value(), aParentItem));
        }
        else
        {
            res.append("\"");
            res.append(valueText(i.value(), aParentItem));
            res.append("\"");
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem)
{
    QString res="[";

    for (int i=0; i<aValue.length(); ++i)
    {
        if (isNumber(aValue.at(i)))
        {
            res.append(valueText(aValue.at(i), aParentItem));
        }
        else
        {
            res.append("\"");
            res.append(valueText(aValue.at(i), aParentItem));
            res.append("\"");
        }

        if (i<aValue.length()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QStringList &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res="[";

    for (int i=0; i<aValue.length(); ++i)
    {
        res.append("\"");
        res.append(aValue.at(i));
        res.append("\"");

        if (i<aValue.length()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QString &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue;
}

QString Property::valueToString(const QByteArray &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toHex().toUpper();
}

QString Property::valueToString(const QBitArray &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res;

    for (int i=0; i<aValue.count(); ++i)
    {
        res.append(aValue.at(i) ? "1" : "0");
    }

    return res;
}

QString Property::valueToString(const QDate &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString("dd.MM.yyyy");
}

QString Property::valueToString(const QTime &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString("HH:mm:ss");
}

QString Property::valueToString(const QDateTime &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString("dd.MM.yyyy HH:mm:ss");
}

QString Property::valueToString(const QUrl &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString();
}

QString Property::valueToString(const QLocale &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.languageToString(aValue.language())+
           ", "+
           aValue.countryToString(aValue.country());
}

QString Property::valueToString(const QRect &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "[("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           "), "+
           QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height())+
           "]";
}

QString Property::valueToString(const QRectF &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "[("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           "), "+
           QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height())+
           "]";
}

QString Property::valueToString(const QSize &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString Property::valueToString(const QSizeF &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString Property::valueToString(const QLine &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
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

QString Property::valueToString(const QLineF &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
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

QString Property::valueToString(const QPoint &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString Property::valueToString(const QPointF &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString Property::valueToString(const QRegExp &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.pattern();
}

QString Property::valueToString(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem)
{
    QString res="[";

    for (QVariantHash::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        if (res.length()>1)
        {
            res.append("; ");
        }

        res.append("(");

        res.append("\"");
        res.append(i.key());
        res.append("\"");

        res.append(", ");

        if (isNumber(i.value()))
        {
            res.append(valueText(i.value(), aParentItem));
        }
        else
        {
            res.append("\"");
            res.append(valueText(i.value(), aParentItem));
            res.append("\"");
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QEasingCurve &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Type"));
    return aEnum.valueToKey(aValue.type());
}

QString Property::valueToString(const QFont &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "["+
           aValue.family()+
           ", "+
           QString::number(aValue.pointSize())+
           "]";
}

QString Property::valueToString(const QPixmap &aValue, PropertyTreeWidgetItem *aParentItem)
{
    return valueToString(aValue.size(), aParentItem);
}

QString Property::valueToString(const QBrush &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    switch (aValue.style())
    {
        case Qt::NoBrush:                return "NoBrush";
        case Qt::SolidPattern:           return "SolidPattern";
        case Qt::Dense1Pattern:          return "Dense1Pattern";
        case Qt::Dense2Pattern:          return "Dense2Pattern";
        case Qt::Dense3Pattern:          return "Dense3Pattern";
        case Qt::Dense4Pattern:          return "Dense4Pattern";
        case Qt::Dense5Pattern:          return "Dense5Pattern";
        case Qt::Dense6Pattern:          return "Dense6Pattern";
        case Qt::Dense7Pattern:          return "Dense7Pattern";
        case Qt::HorPattern:             return "HorPattern";
        case Qt::VerPattern:             return "VerPattern";
        case Qt::CrossPattern:           return "CrossPattern";
        case Qt::BDiagPattern:           return "BDiagPattern";
        case Qt::FDiagPattern:           return "FDiagPattern";
        case Qt::DiagCrossPattern:       return "DiagCrossPattern";
        case Qt::LinearGradientPattern:  return "LinearGradientPattern";
        case Qt::RadialGradientPattern:  return "RadialGradientPattern";
        case Qt::ConicalGradientPattern: return "ConicalGradientPattern";
        case Qt::TexturePattern:         return "TexturePattern";
    }

    return "[Unknown brush style]";
}

QString Property::valueToString(const QColor &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "("+
           QString::number(aValue.red())+
           ", "+
           QString::number(aValue.green())+
           ", "+
           QString::number(aValue.blue())+
           ") ["+
           QString::number(aValue.alpha())+
           "]";
}

QString Property::valueToString(const QPalette &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "Palette";
}

QString Property::valueToString(const QIcon &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res=aValue.name();

    if (res!="")
    {
        return res;
    }

    return "Icon";
}

QString Property::valueToString(const QImage &aValue, PropertyTreeWidgetItem *aParentItem)
{
    return valueToString(aValue.size(), aParentItem);
}

QString Property::valueToString(const QPolygon &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res="[";

    for (int i=0; i<aValue.count(); ++i)
    {
        int x;
        int y;

        aValue.point(i, &x, &y);

        res.append("(");
        res.append(QString::number(x));
        res.append(", ");
        res.append(QString::number(y));
        res.append(")");

        if (i<aValue.count()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem)
{
    QVector<QRect> aRects=aValue.rects();

    QString res="[";

    for (int i=0; i<aRects.count(); ++i)
    {
        res.append(valueToString(aRects.at(i), aParentItem));

        if (i<aRects.count()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QBitmap &aValue, PropertyTreeWidgetItem *aParentItem)
{
    return valueToString(aValue.size(), aParentItem);
}

QString Property::valueToString(const QCursor &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
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

QString Property::valueToString(const QSizePolicy &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Policy"));

    return "["+
           QString::fromUtf8(aEnum.valueToKey(aValue.horizontalPolicy()))+
           ", "+
           QString::fromUtf8(aEnum.valueToKey(aValue.verticalPolicy()))+
           ", "+
           QString::number(aValue.horizontalStretch())+
           ", "+
           QString::number(aValue.verticalStretch())+
           "]";
}

QString Property::valueToString(const QKeySequence &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString();
}

QString Property::valueToString(const QPen &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "Pen";
}

QString Property::valueToString(const QTextLength &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res="[";

    switch (aValue.type())
    {
        case QTextLength::VariableLength:   res.append("VariableLength");   break;
        case QTextLength::FixedLength:      res.append("FixedLength");      break;
        case QTextLength::PercentageLength: res.append("PercentageLength"); break;
    }

    res.append(", ");
    res.append(QString::number(aValue.rawValue()));
    res.append("]");

    return res;
}

QString Property::valueToString(const QTextFormat &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("FormatType"));
    return aEnum.valueToKey(aValue.type());
}

QString Property::valueToString(const QMatrix &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "[("+
           QString::number(aValue.m11())+
           ", "+
           QString::number(aValue.m12())+
           "), ("+
           QString::number(aValue.m21())+
           ", "+
           QString::number(aValue.m22())+
           "); ("+
           QString::number(aValue.dx())+
           ", "+
           QString::number(aValue.dy())+
           ")]";
}

QString Property::valueToString(const QTransform &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "[("+
           QString::number(aValue.m11())+
           ", "+
           QString::number(aValue.m12())+
           ", "+
           QString::number(aValue.m13())+
           "), ("+
           QString::number(aValue.m21())+
           ", "+
           QString::number(aValue.m22())+
           ", "+
           QString::number(aValue.m23())+
           "), ("+
           QString::number(aValue.m31())+
           ", "+
           QString::number(aValue.m32())+
           ", "+
           QString::number(aValue.m33())+
           ")]";
}

QString Property::valueToString(const QMatrix4x4 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    qreal matrix[16];

    aValue.copyDataTo(matrix);

    QString res="[";

    for (int i=0; i<4; ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }

        res.append("(");

        for (int j=0; j<4; ++j)
        {
            if (j>0)
            {
                res.append(", ");
            }

            res.append(QString::number(matrix[i*4+j]));
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QVector2D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "["+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           "]";
}

QString Property::valueToString(const QVector3D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "["+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.z())+
           "]";
}

QString Property::valueToString(const QVector4D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "["+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.z())+
           ", "+
           QString::number(aValue.w())+
           "]";
}

QString Property::valueToString(const QQuaternion &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "["+
           QString::number(aValue.scalar())+
           "; "+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.z())+
           "]";
}

QString Property::valueToString(void *aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return "0x"+QString::number((qint64)aValue, 16).toUpper();
}

QString Property::valueToString(QObject *aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    if (aValue==0)
    {
        return "0x0";
    }

    QString res=aValue->metaObject()->className();
    QString aObjectName=aValue->objectName();

    if (aObjectName!="")
    {
        res.append(" (");
        res.append(aObjectName);
        res.append(")");
    }

    res.append(" 0x");
    res.append(QString::number((qint64)aValue, 16).toUpper());

    return res;
}

// -------------------------------------------------------------------------------------

QIcon Property::iconForValue(const bool &aValue, PropertyTreeWidgetItem *aParentItem)
{
    QPixmap aBoolPixmap=QPixmap(13, 13);
    aBoolPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aBoolPixmap);

    QStyleOptionButton checkboxstyle;
    checkboxstyle.rect.setRect(0, 0, aBoolPixmap.width(), aBoolPixmap.height());

    if (aValue)
    {
        checkboxstyle.state = QStyle::State_On|QStyle::State_Enabled;
    }
    else
    {
        checkboxstyle.state = QStyle::State_Off|QStyle::State_Enabled;
    }

    aParentItem->treeWidget()->style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, &aPainter);

    aPainter.end();

    return QIcon(aBoolPixmap);
}

QIcon Property::iconForValue(const qint8 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const quint8 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const qint16 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const quint16 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const qint32 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const quint32 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const qint64 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const quint64 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const float &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const double &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QChar &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QVariantMap &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QVariantList &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QStringList &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QString &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QByteArray &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QBitArray &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QDate &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Date.png");
}

QIcon Property::iconForValue(const QTime &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Time.png");
}

QIcon Property::iconForValue(const QDateTime &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/DateTime.png");
}

QIcon Property::iconForValue(const QUrl &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QLocale &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QRect &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Rect.png");
}

QIcon Property::iconForValue(const QRectF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Rect.png");
}

QIcon Property::iconForValue(const QSize &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QSizeF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QLine &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Line.png");
}

QIcon Property::iconForValue(const QLineF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Line.png");
}

QIcon Property::iconForValue(const QPoint &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Point.png");
}

QIcon Property::iconForValue(const QPointF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Point.png");
}

QIcon Property::iconForValue(const QRegExp &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QVariantHash &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QEasingCurve &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/EasingCurve.png");
}

QIcon Property::iconForValue(const QFont &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QFont aFont=aValue;
    aFont.setPixelSize(32);

    QFontMetrics aMetrics(aFont);

    int aSize=qMax(aMetrics.width('A'), aMetrics.height())-6;

    if (aSize<1)
    {
        aSize=1;
    }

    QRect aBoundingRect(0, 0, aSize, aSize);

    QPixmap aPenPixmap=QPixmap(aSize, aSize);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setFont(aFont);
    aPainter.drawText(aBoundingRect, Qt::AlignCenter, "A", &aBoundingRect);
    aPainter.end();

    if (aSize<32)
    {
        return QIcon(aPenPixmap.scaled(32, 32));
    }
    else
    {
        return QIcon(aPenPixmap);
    }
}

QIcon Property::iconForValue(const QPixmap &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(aValue);
}

QIcon Property::iconForValue(const QBrush &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QPixmap aBrushPixmap=QPixmap(32, 32);
    aBrushPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aBrushPixmap);
    aPainter.fillRect(0, 0, aBrushPixmap.width(), aBrushPixmap.height(), aValue);
    aPainter.end();

    return QIcon(aBrushPixmap);
}

QIcon Property::iconForValue(const QColor &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QColor aSolidColor(aValue.red(), aValue.green(), aValue.blue());

    QPixmap aColorPixmap=QPixmap(16, 16);
    aColorPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aColorPixmap);

    aPainter.fillRect(0, 0, aColorPixmap.width(), aColorPixmap.height(), aValue);
    aPainter.fillRect(aColorPixmap.width()>>2, aColorPixmap.height()>>2, aColorPixmap.width()>>1, aColorPixmap.height()>>1, aSolidColor);

    aPainter.end();

    return QIcon(aColorPixmap);
}

QIcon Property::iconForValue(const QPalette &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Palette.png");
}

QIcon Property::iconForValue(const QIcon &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue;
}

QIcon Property::iconForValue(const QImage &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(QPixmap::fromImage(aValue));
}

QIcon Property::iconForValue(const QPolygon &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Polygon.png");
}

QIcon Property::iconForValue(const QRegion &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Region.png");
}

QIcon Property::iconForValue(const QBitmap &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(QPixmap::fromImage(aValue.toImage()));
}

QIcon Property::iconForValue(const QCursor &aValue, PropertyTreeWidgetItem *aParentItem)
{
    const QBitmap *aBitmap=aValue.bitmap();

    if (aBitmap)
    {
        return iconForValue(*aBitmap, aParentItem);
    }

    QPixmap aPixmap=aValue.pixmap();

    if (!aPixmap.isNull())
    {
        return iconForValue(aPixmap, aParentItem);
    }

    return QIcon(":/objectcontroller/images/Cursor-"+valueToString(aValue, aParentItem)+".png");
}

QIcon Property::iconForValue(const QSizePolicy &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QKeySequence &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QPen &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QPixmap aPenPixmap=QPixmap(16, 16);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setPen(aValue);
    aPainter.drawLine(aPenPixmap.width(), 0, 0, aPenPixmap.height());
    aPainter.end();

    return QIcon(aPenPixmap);
}

QIcon Property::iconForValue(const QTextLength &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QTextFormat &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(const QMatrix &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Matrix.png");
}

QIcon Property::iconForValue(const QTransform &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Transform.png");
}

QIcon Property::iconForValue(const QMatrix4x4 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Matrix4x4.png");
}

QIcon Property::iconForValue(const QVector2D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Vector2D.png");
}

QIcon Property::iconForValue(const QVector3D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Vector3D.png");
}

QIcon Property::iconForValue(const QVector4D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Vector4D.png");
}

QIcon Property::iconForValue(const QQuaternion &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(void * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValue(QObject * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

// -------------------------------------------------------------------------------------

CustomDelegate* Property::delegateForValue(const bool &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->boolDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const qint8 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const quint8 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const qint16 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const quint16 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const qint32 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const quint32 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const qint64 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const quint64 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->integerDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const float &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->doubleDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const double &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->doubleDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QChar &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->charDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QVariantMap &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QVariantList &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QStringList &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QString &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->stringDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QByteArray &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->byteArrayDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QBitArray &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->bitArrayDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QDate &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->dateDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTime &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->timeDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QDateTime &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->dateTimeDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QUrl &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->stringDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QLocale &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QRect &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QRectF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QSize &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QSizeF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QLine &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QLineF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QPoint &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QPointF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QRegExp &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->stringDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QVariantHash &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QEasingCurve &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->easingCurveDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QFont &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->fontDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPixmap &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->pixmapDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QBrush &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->brushDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QColor &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPalette &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->paletteDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QIcon &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QImage &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPolygon &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QRegion &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QBitmap &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QCursor &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QSizePolicy &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QKeySequence &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPen &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTextLength &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTextFormat &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QMatrix &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QTransform &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QMatrix4x4 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector2D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector3D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector4D &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(const QQuaternion &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(void * /*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

CustomDelegate* Property::delegateForValue(QObject * /*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {

    }

    return 0;
}

// -------------------------------------------------------------------------------------

#define GET_OR_CREATE_ITEM(aParentItem, aNewItem, aID, aName, aValue) \
    if (aParentItem->childCount()>aID) \
    { \
        aNewItem=(PropertyTreeWidgetItem *)aParentItem->child(aID); \
    } \
    else \
    { \
        aNewItem=new PropertyTreeWidgetItem(aParentItem); \
        aNewItem->setFlags(aNewItem->flags() | Qt::ItemIsEditable); \
    } \
\
    ++aID; \
\
    aNewItem->setText(0, aName); \
    aNewItem->setText(1, aValue);

#define GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aNewItem, aID, aName, aValue, aIcon) \
    GET_OR_CREATE_ITEM(aParentItem, aNewItem, aID, aName, aValue) \
    aNewItem->setIcon(1, aIcon);

int Property::subPropertiesForValue(const bool &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const qint8 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const quint8 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const qint16 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const quint16 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const qint32 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const quint32 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const qint64 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const quint64 &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const float &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const double &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QChar &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (QVariantMap::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;

        GET_OR_CREATE_ITEM(aParentItem, aEntryItem, aCount, i.key(), "");
        setPropertiesForItem(i.value(), i.value(), aEntryItem);

        // TODO: Editors
    }

    return aCount;
}

int Property::subPropertiesForValue(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aValue.length(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;

        GET_OR_CREATE_ITEM(aParentItem, aEntryItem, aCount, QString::number(i+1), "");
        setPropertiesForItem(aValue.at(i), aValue.at(i), aEntryItem);

        // TODO: Editors
    }

    return aCount;
}

int Property::subPropertiesForValue(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aValue.length(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;

        GET_OR_CREATE_ITEM(aParentItem, aEntryItem, aCount, QString::number(i+1), aValue.at(i));

        // TODO: Editors
    }

    return aCount;
}

int Property::subPropertiesForValue(const QString &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QByteArray &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QBitArray &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QDate &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QTime &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QDateTime &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QUrl &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aLanguageItem;
    PropertyTreeWidgetItem *aCountryItem;

    GET_OR_CREATE_ITEM(aParentItem, aLanguageItem, aCount, qApp->translate("Property", "Language"), aValue.languageToString(aValue.language()));
    GET_OR_CREATE_ITEM(aParentItem, aCountryItem,  aCount, qApp->translate("Property", "Country"),  aValue.countryToString(aValue.country()));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QRect &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      valueToString(aValue.x(),      aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      valueToString(aValue.y(),      aYItem));
    GET_OR_CREATE_ITEM(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  valueToString(aValue.width(),  aWidthItem));
    GET_OR_CREATE_ITEM(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), valueToString(aValue.height(), aHeightItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      valueToString(aValue.x(),      aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      valueToString(aValue.y(),      aYItem));
    GET_OR_CREATE_ITEM(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  valueToString(aValue.width(),  aWidthItem));
    GET_OR_CREATE_ITEM(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), valueToString(aValue.height(), aHeightItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QSize &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  valueToString(aValue.width(),  aWidthItem));
    GET_OR_CREATE_ITEM(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), valueToString(aValue.height(), aHeightItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  valueToString(aValue.width(),  aWidthItem));
    GET_OR_CREATE_ITEM(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), valueToString(aValue.height(), aHeightItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QLine &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aX1Item;
    PropertyTreeWidgetItem *aY1Item;
    PropertyTreeWidgetItem *aX2Item;
    PropertyTreeWidgetItem *aY2Item;

    GET_OR_CREATE_ITEM(aParentItem, aX1Item, aCount, qApp->translate("Property", "X1"), valueToString(aValue.x1(), aX1Item));
    GET_OR_CREATE_ITEM(aParentItem, aY1Item, aCount, qApp->translate("Property", "Y1"), valueToString(aValue.y1(), aY1Item));
    GET_OR_CREATE_ITEM(aParentItem, aX2Item, aCount, qApp->translate("Property", "X2"), valueToString(aValue.x2(), aX2Item));
    GET_OR_CREATE_ITEM(aParentItem, aY2Item, aCount, qApp->translate("Property", "Y2"), valueToString(aValue.y2(), aY2Item));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aX1Item;
    PropertyTreeWidgetItem *aY1Item;
    PropertyTreeWidgetItem *aX2Item;
    PropertyTreeWidgetItem *aY2Item;

    GET_OR_CREATE_ITEM(aParentItem, aX1Item, aCount, qApp->translate("Property", "X1"), valueToString(aValue.x1(), aX1Item));
    GET_OR_CREATE_ITEM(aParentItem, aY1Item, aCount, qApp->translate("Property", "Y1"), valueToString(aValue.y1(), aY1Item));
    GET_OR_CREATE_ITEM(aParentItem, aX2Item, aCount, qApp->translate("Property", "X2"), valueToString(aValue.x2(), aX2Item));
    GET_OR_CREATE_ITEM(aParentItem, aY2Item, aCount, qApp->translate("Property", "Y2"), valueToString(aValue.y2(), aY2Item));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), valueToString(aValue.x(), aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), valueToString(aValue.y(), aYItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), valueToString(aValue.x(), aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), valueToString(aValue.y(), aYItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QRegExp &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (QVariantHash::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;

        GET_OR_CREATE_ITEM(aParentItem, aEntryItem, aCount, i.key(), "");
        setPropertiesForItem(i.value(), i.value(), aEntryItem);

        // TODO: Editors
    }

    return aCount;
}

int Property::subPropertiesForValue(const QEasingCurve &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QFont &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("StyleStrategy"));

    PropertyTreeWidgetItem *aFamilyItem;
    PropertyTreeWidgetItem *aSizeItem;
    PropertyTreeWidgetItem *aBoldItem;
    PropertyTreeWidgetItem *aItalicItem;
    PropertyTreeWidgetItem *aUnderlineItem;
    PropertyTreeWidgetItem *aStrikeOutItem;
    PropertyTreeWidgetItem *aKerningItem;
    PropertyTreeWidgetItem *aAntiAliasingItem;

    GET_OR_CREATE_ITEM(          aParentItem, aFamilyItem,       aCount, qApp->translate("Property", "Family", "Font"),       aValue.family());
    GET_OR_CREATE_ITEM(          aParentItem, aSizeItem,         aCount, qApp->translate("Property", "Size", "Font"),         valueToString(aValue.pointSize(), aSizeItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aBoldItem,         aCount, qApp->translate("Property", "Bold", "Font"),         valueToString(aValue.bold(),      aBoldItem),      iconForValue(aValue.bold(),      aBoldItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aItalicItem,       aCount, qApp->translate("Property", "Italic", "Font"),       valueToString(aValue.italic(),    aItalicItem),    iconForValue(aValue.italic(),    aItalicItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aUnderlineItem,    aCount, qApp->translate("Property", "Underline", "Font"),    valueToString(aValue.underline(), aUnderlineItem), iconForValue(aValue.underline(), aUnderlineItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aStrikeOutItem,    aCount, qApp->translate("Property", "Strike out", "Font"),   valueToString(aValue.strikeOut(), aStrikeOutItem), iconForValue(aValue.strikeOut(), aStrikeOutItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aKerningItem,      aCount, qApp->translate("Property", "Kerning", "Font"),      valueToString(aValue.kerning(),   aKerningItem),   iconForValue(aValue.kerning(),   aKerningItem));
    GET_OR_CREATE_ITEM(          aParentItem, aAntiAliasingItem, aCount, qApp->translate("Property", "AntiAliasing", "Font"), aEnum.valueToKey(aValue.styleStrategy()));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QPixmap &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QBrush &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QColor &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aRedItem;
    PropertyTreeWidgetItem *aGreenItem;
    PropertyTreeWidgetItem *aBlueItem;
    PropertyTreeWidgetItem *aAlphaItem;

    GET_OR_CREATE_ITEM(aParentItem, aRedItem,   aCount, qApp->translate("Property", "Red"),   valueToString(aValue.red(),   aRedItem));
    GET_OR_CREATE_ITEM(aParentItem, aGreenItem, aCount, qApp->translate("Property", "Green"), valueToString(aValue.green(), aGreenItem));
    GET_OR_CREATE_ITEM(aParentItem, aBlueItem,  aCount, qApp->translate("Property", "Blue"),  valueToString(aValue.blue(),  aBlueItem));
    GET_OR_CREATE_ITEM(aParentItem, aAlphaItem, aCount, qApp->translate("Property", "Alpha"), valueToString(aValue.alpha(), aAlphaItem));

    // TODO: Editors

    return aCount;
}

#define INSERT_COLOR(aParentItem, aCount, aGroup, aRole, aValue) \
    PropertyTreeWidgetItem *aGroup##_##aRole##_Item; \
    QColor                  aGroup##_##aRole##_Color=aValue.color(QPalette::aGroup, QPalette::aRole); \
\
    GET_OR_CREATE_ITEM(aParentItem, aGroup##_##aRole##_Item, aCount, #aRole" ("#aGroup")", valueToString(aGroup##_##aRole##_Color, aGroup##_##aRole##_Item)); \
    setPropertiesForItem(aGroup##_##aRole##_Color, aGroup##_##aRole##_Color, aGroup##_##aRole##_Item);

#define INSERT_COLOR_ROLE(aParentItem, aCount, aRole, aValue) \
    INSERT_COLOR(aParentItem, aCount, Active,   aRole, aValue); \
    INSERT_COLOR(aParentItem, aCount, Inactive, aRole, aValue); \
    INSERT_COLOR(aParentItem, aCount, Disabled, aRole, aValue);

int Property::subPropertiesForValue(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    INSERT_COLOR_ROLE(aParentItem, aCount, WindowText, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Button, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Light, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Midlight, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Dark, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Mid, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Text, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, BrightText, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, ButtonText, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Base, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Window, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Shadow, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Highlight, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, HighlightedText, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, Link, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, LinkVisited, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, AlternateBase, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, NoRole, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, ToolTipBase, aValue);
    INSERT_COLOR_ROLE(aParentItem, aCount, ToolTipText, aValue);

    return aCount;
}

int Property::subPropertiesForValue(const QIcon &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QImage &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QPolygon &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QRegion &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QBitmap &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QCursor &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Policy"));

    PropertyTreeWidgetItem *aHorizontalPolicyItem;
    PropertyTreeWidgetItem *aVerticalPolicyItem;
    PropertyTreeWidgetItem *aHorizontalStretchItem;
    PropertyTreeWidgetItem *aVerticalStretchItem;

    GET_OR_CREATE_ITEM(aParentItem, aHorizontalPolicyItem,  aCount, qApp->translate("Property", "Horizontal policy"),  aEnum.valueToKey(aValue.horizontalPolicy()));
    GET_OR_CREATE_ITEM(aParentItem, aVerticalPolicyItem,    aCount, qApp->translate("Property", "Vertical policy"),    aEnum.valueToKey(aValue.verticalPolicy()));
    GET_OR_CREATE_ITEM(aParentItem, aHorizontalStretchItem, aCount, qApp->translate("Property", "Horizontal stretch"), valueToString(aValue.horizontalStretch(), aHorizontalStretchItem));
    GET_OR_CREATE_ITEM(aParentItem, aVerticalStretchItem,   aCount, qApp->translate("Property", "Vertical stretch"),   valueToString(aValue.verticalStretch(),   aVerticalStretchItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QKeySequence &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QPen &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QString aStyle;

    switch (aValue.style())
    {
        case Qt::NoPen:          aStyle="NoPen";           break;
        case Qt::SolidLine:      aStyle="SolidLine";       break;
        case Qt::DashLine:       aStyle="DashLine";        break;
        case Qt::DotLine:        aStyle="DotLine";         break;
        case Qt::DashDotLine:    aStyle="DashDotLine";     break;
        case Qt::DashDotDotLine: aStyle="DashDotDotLine";  break;
        case Qt::CustomDashLine: aStyle="CustomDashLine";  break;
        default:                 aStyle="[Unknown style]"; break;
    }

    QString aCapStyle;

    switch (aValue.capStyle())
    {
        case Qt::FlatCap:      aCapStyle="FlatCap";         break;
        case Qt::SquareCap:    aCapStyle="SquareCap";       break;
        case Qt::RoundCap:     aCapStyle="RoundCap";        break;
        case Qt::MPenCapStyle: aCapStyle="MPenCapStyle";    break;
        default:               aCapStyle="[Unknown style]"; break;
    }

    QString aJoinStyle;

    switch (aValue.joinStyle())
    {
        case Qt::MiterJoin:     aJoinStyle="MiterJoin";       break;
        case Qt::BevelJoin:     aJoinStyle="BevelJoin";       break;
        case Qt::RoundJoin:     aJoinStyle="RoundJoin";       break;
        case Qt::SvgMiterJoin:  aJoinStyle="SvgMiterJoin";    break;
        case Qt::MPenJoinStyle: aJoinStyle="MPenJoinStyle";   break;
        default:                aJoinStyle="[Unknown style]"; break;
    }

    // -----------------------------------------------------------------

    QPainter aPainter;

    QPixmap aStylePixmap(32, 32);
    QPixmap aCapStylePixmap(32, 32);
    QPixmap aJoinStylePixmap(32, 32);

    aStylePixmap.fill(QColor(255, 255, 255, 0));
    aCapStylePixmap.fill(QColor(255, 255, 255, 0));
    aJoinStylePixmap.fill(QColor(255, 255, 255, 0));

    QPen aStylePen;
    QPen aCapStylePen;
    QPen aJoinStylePen;

    aStylePen.setStyle(aValue.style());
    aCapStylePen.setCapStyle(aValue.capStyle());
    aJoinStylePen.setJoinStyle(aValue.joinStyle());

    aStylePen.setWidth(3);
    aCapStylePen.setWidth(24);
    aJoinStylePen.setWidth(16);



    aPainter.begin(&aStylePixmap);
    aPainter.setPen(aStylePen);
    aPainter.drawLine(0, aStylePixmap.height()>>1, aStylePixmap.width(), aStylePixmap.height()>>1);
    aPainter.end();



    aPainter.begin(&aCapStylePixmap);
    aPainter.setPen(aCapStylePen);
    aPainter.drawLine(aCapStylePen.width()>>1, aCapStylePixmap.height()>>1, aCapStylePixmap.width(), aCapStylePixmap.height()>>1);
    aPainter.end();



    aPainter.begin(&aJoinStylePixmap);
        aPainter.setPen(aJoinStylePen);

        QPainterPath aJoinStylePath;
        aJoinStylePath.moveTo(aJoinStylePixmap.width(), 0);
        aJoinStylePath.lineTo(aJoinStylePixmap.width()>>2, aJoinStylePixmap.height()>>1);
        aJoinStylePath.lineTo(aJoinStylePixmap.width(), aJoinStylePixmap.height());

        aPainter.drawPath(aJoinStylePath);
    aPainter.end();

    // -----------------------------------------------------------------

    PropertyTreeWidgetItem *aBrushItem;
    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aStyleItem;
    PropertyTreeWidgetItem *aCapStyleItem;
    PropertyTreeWidgetItem *aJoinStyleItem;
    PropertyTreeWidgetItem *aColorItem;

    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aBrushItem,     aCount, qApp->translate("Property", "Brush"),      valueToString(aValue.brush(),     aBrushItem), iconForValue(aValue.brush(), aBrushItem));
    GET_OR_CREATE_ITEM(          aParentItem, aWidthItem,     aCount, qApp->translate("Property", "Width"),      valueToString(aValue.width(),     aWidthItem));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aStyleItem,     aCount, qApp->translate("Property", "Style"),      aStyle,     QIcon(aStylePixmap));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aCapStyleItem,  aCount, qApp->translate("Property", "Cap style"),  aCapStyle,  QIcon(aCapStylePixmap));
    GET_OR_CREATE_ITEM_WITH_ICON(aParentItem, aJoinStyleItem, aCount, qApp->translate("Property", "Join style"), aJoinStyle, QIcon(aJoinStylePixmap));
    GET_OR_CREATE_ITEM(          aParentItem, aColorItem,     aCount, qApp->translate("Property", "Color"),      valueToString(aValue.color(),     aColorItem));

    setPropertiesForItem(aValue.color(), aValue.color(), aColorItem);

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QTextLength &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QTextFormat &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QMatrix &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aM11Item;
    PropertyTreeWidgetItem *aM12Item;
    PropertyTreeWidgetItem *aM21Item;
    PropertyTreeWidgetItem *aM22Item;
    PropertyTreeWidgetItem *aDXItem;
    PropertyTreeWidgetItem *aDYItem;

    GET_OR_CREATE_ITEM(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), valueToString(aValue.m11(), aM11Item));
    GET_OR_CREATE_ITEM(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), valueToString(aValue.m12(), aM12Item));
    GET_OR_CREATE_ITEM(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), valueToString(aValue.m21(), aM21Item));
    GET_OR_CREATE_ITEM(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), valueToString(aValue.m22(), aM22Item));
    GET_OR_CREATE_ITEM(aParentItem, aDXItem,  aCount, qApp->translate("Property", "dx"),  valueToString(aValue.dx(),  aDXItem));
    GET_OR_CREATE_ITEM(aParentItem, aDYItem,  aCount, qApp->translate("Property", "dy"),  valueToString(aValue.dy(),  aDYItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QTransform &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aM11Item;
    PropertyTreeWidgetItem *aM12Item;
    PropertyTreeWidgetItem *aM13Item;
    PropertyTreeWidgetItem *aM21Item;
    PropertyTreeWidgetItem *aM22Item;
    PropertyTreeWidgetItem *aM23Item;
    PropertyTreeWidgetItem *aM31Item;
    PropertyTreeWidgetItem *aM32Item;
    PropertyTreeWidgetItem *aM33Item;

    GET_OR_CREATE_ITEM(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), valueToString(aValue.m11(), aM11Item));
    GET_OR_CREATE_ITEM(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), valueToString(aValue.m12(), aM12Item));
    GET_OR_CREATE_ITEM(aParentItem, aM13Item, aCount, qApp->translate("Property", "M13"), valueToString(aValue.m13(), aM13Item));
    GET_OR_CREATE_ITEM(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), valueToString(aValue.m21(), aM21Item));
    GET_OR_CREATE_ITEM(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), valueToString(aValue.m22(), aM22Item));
    GET_OR_CREATE_ITEM(aParentItem, aM23Item, aCount, qApp->translate("Property", "M23"), valueToString(aValue.m23(), aM23Item));
    GET_OR_CREATE_ITEM(aParentItem, aM31Item, aCount, qApp->translate("Property", "M31"), valueToString(aValue.m31(), aM31Item));
    GET_OR_CREATE_ITEM(aParentItem, aM32Item, aCount, qApp->translate("Property", "M32"), valueToString(aValue.m32(), aM32Item));
    GET_OR_CREATE_ITEM(aParentItem, aM33Item, aCount, qApp->translate("Property", "M33"), valueToString(aValue.m33(), aM33Item));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QMatrix4x4 &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    qreal matrix[16];
    aValue.copyDataTo(matrix);

    PropertyTreeWidgetItem *aM11Item;
    PropertyTreeWidgetItem *aM12Item;
    PropertyTreeWidgetItem *aM13Item;
    PropertyTreeWidgetItem *aM14Item;
    PropertyTreeWidgetItem *aM21Item;
    PropertyTreeWidgetItem *aM22Item;
    PropertyTreeWidgetItem *aM23Item;
    PropertyTreeWidgetItem *aM24Item;
    PropertyTreeWidgetItem *aM31Item;
    PropertyTreeWidgetItem *aM32Item;
    PropertyTreeWidgetItem *aM33Item;
    PropertyTreeWidgetItem *aM34Item;
    PropertyTreeWidgetItem *aM41Item;
    PropertyTreeWidgetItem *aM42Item;
    PropertyTreeWidgetItem *aM43Item;
    PropertyTreeWidgetItem *aM44Item;

    GET_OR_CREATE_ITEM(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), valueToString(matrix[0],  aM11Item));
    GET_OR_CREATE_ITEM(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), valueToString(matrix[1],  aM12Item));
    GET_OR_CREATE_ITEM(aParentItem, aM13Item, aCount, qApp->translate("Property", "M13"), valueToString(matrix[2],  aM13Item));
    GET_OR_CREATE_ITEM(aParentItem, aM14Item, aCount, qApp->translate("Property", "M14"), valueToString(matrix[3],  aM14Item));
    GET_OR_CREATE_ITEM(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), valueToString(matrix[4],  aM21Item));
    GET_OR_CREATE_ITEM(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), valueToString(matrix[5],  aM22Item));
    GET_OR_CREATE_ITEM(aParentItem, aM23Item, aCount, qApp->translate("Property", "M23"), valueToString(matrix[6],  aM23Item));
    GET_OR_CREATE_ITEM(aParentItem, aM24Item, aCount, qApp->translate("Property", "M24"), valueToString(matrix[7],  aM24Item));
    GET_OR_CREATE_ITEM(aParentItem, aM31Item, aCount, qApp->translate("Property", "M31"), valueToString(matrix[8],  aM31Item));
    GET_OR_CREATE_ITEM(aParentItem, aM32Item, aCount, qApp->translate("Property", "M32"), valueToString(matrix[9],  aM32Item));
    GET_OR_CREATE_ITEM(aParentItem, aM33Item, aCount, qApp->translate("Property", "M33"), valueToString(matrix[10], aM33Item));
    GET_OR_CREATE_ITEM(aParentItem, aM34Item, aCount, qApp->translate("Property", "M34"), valueToString(matrix[11], aM34Item));
    GET_OR_CREATE_ITEM(aParentItem, aM41Item, aCount, qApp->translate("Property", "M41"), valueToString(matrix[12], aM41Item));
    GET_OR_CREATE_ITEM(aParentItem, aM42Item, aCount, qApp->translate("Property", "M42"), valueToString(matrix[13], aM42Item));
    GET_OR_CREATE_ITEM(aParentItem, aM43Item, aCount, qApp->translate("Property", "M43"), valueToString(matrix[14], aM43Item));
    GET_OR_CREATE_ITEM(aParentItem, aM44Item, aCount, qApp->translate("Property", "M44"), valueToString(matrix[15], aM44Item));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), valueToString(aValue.x(), aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), valueToString(aValue.y(), aYItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), valueToString(aValue.x(), aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), valueToString(aValue.y(), aYItem));
    GET_OR_CREATE_ITEM(aParentItem, aZItem, aCount, qApp->translate("Property", "Z"), valueToString(aValue.z(), aZItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;
    PropertyTreeWidgetItem *aWItem;

    GET_OR_CREATE_ITEM(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), valueToString(aValue.x(), aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), valueToString(aValue.y(), aYItem));
    GET_OR_CREATE_ITEM(aParentItem, aZItem, aCount, qApp->translate("Property", "Z"), valueToString(aValue.z(), aZItem));
    GET_OR_CREATE_ITEM(aParentItem, aWItem, aCount, qApp->translate("Property", "W"), valueToString(aValue.w(), aWItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aScalarItem;
    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;

    GET_OR_CREATE_ITEM(aParentItem, aScalarItem, aCount, qApp->translate("Property", "Scalar"), valueToString(aValue.scalar(), aScalarItem));
    GET_OR_CREATE_ITEM(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      valueToString(aValue.x(),      aXItem));
    GET_OR_CREATE_ITEM(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      valueToString(aValue.y(),      aYItem));
    GET_OR_CREATE_ITEM(aParentItem, aZItem,      aCount, qApp->translate("Property", "Z"),      valueToString(aValue.z(),      aZItem));

    // TODO: Editors

    return aCount;
}

int Property::subPropertiesForValue(void * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(QObject * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}
