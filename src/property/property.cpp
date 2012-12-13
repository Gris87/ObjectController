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
#include "propertyutils.h"

Property::Property(const QMetaObject *aPropertyObject, const QMetaProperty &aMetaProperty, QObject *parent) :
    QObject(parent)
{
    mPropertyObject=aPropertyObject;
    mMetaProperty=aMetaProperty;

    mName=mMetaProperty.name();
    mIsWritable=mMetaProperty.isWritable();



    int index=mPropertyObject->indexOfClassInfo(QString(mName+" attributes").toLatin1());

    if (index>=0)
    {
        mAttributes.fromString(mPropertyObject->classInfo(index).value());
    }
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

const PropertyAttributes* Property::attributes() const
{
    return &mAttributes;
}

void Property::setPropertiesForItem(const QVariant &aValue, const QVariant &aFirstValue, PropertyTreeWidgetItem *aParentItem)
{
    aParentItem->setText(1, valueText(aValue, aParentItem));
    aParentItem->setIcon(1, valueIcon(aFirstValue, aParentItem));

    aParentItem->setFirstValue(aFirstValue);
    aParentItem->setDelegate(valueDelegate(aFirstValue, aParentItem));

    int aChildCount=valueSubProperies(aValue, aParentItem);

    while (aParentItem->childCount()>aChildCount)
    {
        delete aParentItem->takeChild(aParentItem->childCount()-1);
    }
}

void Property::setPropertiesForItem(const QVariant &aValue, PropertyTreeWidgetItem *aParentItem)
{
    setPropertiesForItem(aValue, aValue, aParentItem);
}

#define FUNCTION_FOR_VARIANT(aValue, aParentItem, aFunction, aDefaultResult) \
    if (aParentItem->property() && mMetaProperty.isEnumType()) \
    { \
        if (mMetaProperty.isFlagType()) \
        { \
             return aFunction##Flag(mMetaProperty.enumerator(), aValue.value<int>(), aParentItem); \
        } \
        else \
        { \
             return aFunction##Enum(mMetaProperty.enumerator(), aValue.value<int>(), aParentItem); \
        } \
    } \
    else \
    { \
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
    }

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

// -------------------------------------------------------------------------------------

const QMetaObject* Property::propertyObject() const
{
    return mPropertyObject;
}

QString Property::name() const
{
    return mName;
}

QColor Property::backgroundColor() const
{
    return mBackgroundColor;
}

void Property::setBackgroundColor(const QColor &aBackgroundColor)
{
    mBackgroundColor=aBackgroundColor;
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

QString Property::valueToStringEnum(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
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

QString Property::valueToStringFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QStringList resList;

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
                resList.append(QString::fromLatin1(aMetaEnum.key(i)));
            }
        }
    }

    return "["+resList.join(", ")+"]";
}

QString Property::valueToString(const bool &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue ? qApp->translate("Property", "true") : qApp->translate("Property", "false");
}

QString Property::valueToString(const qint8 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const quint8 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const qint16 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const quint16 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const qint32 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const quint32 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const qint64 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const quint64 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           QString::number(aValue)+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const float &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           doubleToString(aValue, mAttributes.intValue("decimals", 6))+
           mAttributes.stringValue("suffix");
}

QString Property::valueToString(const double &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return mAttributes.stringValue("prefix")+
           doubleToString(aValue, mAttributes.intValue("decimals", 6))+
           mAttributes.stringValue("suffix");
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
    return aValue.toString(mAttributes.stringValue("displayFormat", "dd.MM.yyyy"));
}

QString Property::valueToString(const QTime &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString(mAttributes.stringValue("displayFormat", "HH:mm:ss"));
}

QString Property::valueToString(const QDateTime &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return aValue.toString(mAttributes.stringValue("displayFormat", "dd.MM.yyyy HH:mm:ss"));
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
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "[("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           "), "+
           doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals)+
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
    int aDecimals=mAttributes.intValue("decimals", 6);

    return doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals);
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
    int aDecimals=mAttributes.intValue("decimals", 6);

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
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
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
    QMetaEnum aEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("BrushStyle"));
    return aEnum.valueToKey(aValue.style());
}

QString Property::valueToString(const QColor &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    if (mAttributes.boolValue("alphaEnabled", true))
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
    else
    {
        return "("+
               QString::number(aValue.red())+
               ", "+
               QString::number(aValue.green())+
               ", "+
               QString::number(aValue.blue())+
               ")";
    }
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

QString Property::valueToString(const QRegion &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QVector<QRect> aRects=aValue.rects();

    QString res="[";

    for (int i=0; i<aRects.count(); ++i)
    {
        res.append(
                   "[("+
                   QString::number(aRects.at(i).x())+
                   ", "+
                   QString::number(aRects.at(i).y())+
                   "), "+
                   QString::number(aRects.at(i).width())+
                   " x "+
                   QString::number(aRects.at(i).height())+
                   "]"
                  );

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
    QMetaEnum aEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("CursorShape"));
    return QString::fromLatin1(aEnum.valueToKey(aValue.shape()));
}

QString Property::valueToString(const QSizePolicy &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Policy"));

    return "["+
           QString::fromLatin1(aEnum.valueToKey(aValue.horizontalPolicy()))+
           ", "+
           QString::fromLatin1(aEnum.valueToKey(aValue.verticalPolicy()))+
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
    res.append(doubleToString(aValue.rawValue(), mAttributes.intValue("decimals", 6)));
    res.append("]");

    return res;
}

QString Property::valueToString(const QTextFormat &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    QString res="[Unknown type]";

    if (aValue.isImageFormat())
    {
        res="ImageFormat";
    }
    else
    if (aValue.isTableCellFormat())
    {
        res="TableCellFormat";
    }
    else
    if (aValue.isTableFormat())
    {
        res="TableFormat";
    }
    else
    if (aValue.isBlockFormat())
    {
        res="BlockFormat";
    }
    else
    if (aValue.isCharFormat())
    {
        res="CharFormat";
    }
    else
    if (aValue.isFrameFormat())
    {
        res="FrameFormat";
    }
    else
    if (aValue.isListFormat())
    {
        res="ListFormat";
    }

    return res;
}

QString Property::valueToString(const QMatrix &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "[("+
           doubleToString(aValue.m11(), aDecimals)+
           ", "+
           doubleToString(aValue.m12(), aDecimals)+
           "), ("+
           doubleToString(aValue.m21(), aDecimals)+
           ", "+
           doubleToString(aValue.m22(), aDecimals)+
           "); ("+
           doubleToString(aValue.dx(), aDecimals)+
           ", "+
           doubleToString(aValue.dy(), aDecimals)+
           ")]";
}

QString Property::valueToString(const QTransform &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "[("+
           doubleToString(aValue.m11(), aDecimals)+
           ", "+
           doubleToString(aValue.m12(), aDecimals)+
           ", "+
           doubleToString(aValue.m13(), aDecimals)+
           "), ("+
           doubleToString(aValue.m21(), aDecimals)+
           ", "+
           doubleToString(aValue.m22(), aDecimals)+
           ", "+
           doubleToString(aValue.m23(), aDecimals)+
           "), ("+
           doubleToString(aValue.m31(), aDecimals)+
           ", "+
           doubleToString(aValue.m32(), aDecimals)+
           ", "+
           doubleToString(aValue.m33(), aDecimals)+
           ")]";
}

QString Property::valueToString(const QMatrix4x4 &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    qreal aMatrix[16];

    aValue.copyDataTo(aMatrix);

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

            res.append(doubleToString(aMatrix[i*4+j], aDecimals));
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QVector2D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "["+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           "]";
}

QString Property::valueToString(const QVector3D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "["+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
           "]";
}

QString Property::valueToString(const QVector4D &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "["+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
           ", "+
           doubleToString(aValue.w(), aDecimals)+
           "]";
}

QString Property::valueToString(const QQuaternion &aValue, PropertyTreeWidgetItem * /*aParentItem*/)
{
    int aDecimals=mAttributes.intValue("decimals", 6);

    return "["+
           doubleToString(aValue.scalar(), aDecimals)+
           "; "+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
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

QIcon Property::iconForValueEnum(const QMetaEnum &/*aMetaEnum*/, const int &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

QIcon Property::iconForValueFlag(const QMetaEnum &/*aMetaEnum*/, const int &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon();
}

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
    return QIcon(":/objectcontroller/images/Size.png");
}

QIcon Property::iconForValue(const QSizeF &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return QIcon(":/objectcontroller/images/Size.png");
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
    QIcon aIcon;

    QPixmap aPixmap=aValue.pixmap();

    if (!aPixmap.isNull())
    {
        aIcon=QIcon(aPixmap);
    }
    else
    {
        const QBitmap *aBitmap=aValue.bitmap();

        if (aBitmap)
        {
            aPixmap=QPixmap::fromImage(aBitmap->toImage());
            aPixmap.setMask(*aValue.mask());

            aIcon=QIcon(aPixmap);
        }
        else
        {
            aIcon=QIcon(":/objectcontroller/images/Cursor-"+valueToString(aValue, aParentItem)+".png");
        }
    }

    return aIcon;
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

CustomDelegate* Property::delegateForValueEnum(const QMetaEnum &aMetaEnum, const int &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        aParentItem->setMetaEnum(aMetaEnum);
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->enumDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValueFlag(const QMetaEnum &/*aMetaEnum*/, const int &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

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

CustomDelegate* Property::delegateForValue(const QStringList &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->stringListDelegate();
    }

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

CustomDelegate* Property::delegateForValue(const QLocale &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->localeDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QRect &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->rectDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QRectF &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->rectFDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QSize &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->sizeDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QSizeF &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->sizeFDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QLine &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->lineDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QLineF &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->lineFDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPoint &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->pointDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPointF &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->pointFDelegate();
    }

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
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->colorDelegate();
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
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->iconDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QImage &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->pixmapDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPolygon &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->polygonDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QRegion &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->regionDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QBitmap &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->pixmapDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QCursor &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->cursorDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QSizePolicy &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->sizePolicyDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QKeySequence &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->keySequenceDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QPen &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->penDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTextLength &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->textLengthDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTextFormat &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->textFormatDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QMatrix &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->matrixDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QTransform &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->transformDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QMatrix4x4 &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->matrix4x4Delegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector2D &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->vector2DDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector3D &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->vector3DDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QVector4D &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->vector4DDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(const QQuaternion &/*aValue*/, PropertyTreeWidgetItem *aParentItem)
{
    if (mIsWritable)
    {
        return ((PropertyTreeWidget*)aParentItem->treeWidget())->quaternionDelegate();
    }

    return 0;
}

CustomDelegate* Property::delegateForValue(void * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

CustomDelegate* Property::delegateForValue(QObject * /*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

// -------------------------------------------------------------------------------------

PropertyTreeWidgetItem* Property::senderItem()
{
    return ((ItemConnector *)sender())->item();
}

void Property::removeAllChildren(PropertyTreeWidgetItem *aParentItem)
{
    while (aParentItem->childCount()>0)
    {
        delete aParentItem->takeChild(0);
    }
}

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

#define GET_OR_CREATE_ITEM_NEW(aParentItem, aNewItem, aID, aName) \
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
    aNewItem->setText(0, aName);

#define GET_OR_CREATE_ITEM_SETUP(aParentItem, aNewItem, aID, aName, aValue) \
    GET_OR_CREATE_ITEM_NEW(aParentItem, aNewItem, aID, aName); \
    setPropertiesForItem(aValue, aNewItem);

#define GET_OR_CREATE_ITEM_SETUP_ENUM(aParentItem, aNewItem, aID, aName, aEnum, aValue) \
    GET_OR_CREATE_ITEM_NEW(aParentItem, aNewItem, aID, aName); \
    aNewItem->setText(1, valueToStringEnum(aEnum, (int)aValue, aNewItem)); \
    aNewItem->setIcon(1, iconForValueEnum(aEnum, (int)aValue, aNewItem)); \
    aNewItem->setFirstValue((int)aValue); \
    aNewItem->setDelegate(delegateForValueEnum(aEnum, (int)aValue, aNewItem)); \
    removeAllChildren(aNewItem);

#define GET_OR_CREATE_ITEM_CONNECT(aNewItem, aSlot) \
    aNewItem->itemConnector()->disconnect(); \
    connect(aNewItem->itemConnector(), SIGNAL(valueChanged(QVariant)), this, SLOT(aSlot(QVariant)));

#define GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aNewItem, aID, aName, aValue, aSlot) \
    GET_OR_CREATE_ITEM_SETUP(aParentItem, aNewItem, aID, aName, aValue); \
    GET_OR_CREATE_ITEM_CONNECT(aNewItem, aSlot);

#define GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aNewItem, aID, aName, aEnum, aValue, aSlot) \
    GET_OR_CREATE_ITEM_SETUP_ENUM(aParentItem, aNewItem, aID, aName, aEnum, aValue); \
    GET_OR_CREATE_ITEM_CONNECT(aNewItem, aSlot);

int Property::subPropertiesForValueEnum(const QMetaEnum &/*aMetaEnum*/, const int &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

void Property::flagChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QString aFlagName=aItem->text(0);

    QMetaEnum aMetaEnum=mMetaProperty.enumerator();
    int aFlag=aMetaEnum.keyToValue(aFlagName.toLatin1());

    if (aFlag==0)
    {
        aParentItem->setFirstValue(0);
    }
    else
    {
        if (aNewValue.value<bool>())
        {
            aParentItem->setFirstValue(aParentItem->firstValue().value<int>() | aFlag);
        }
        else
        {
            aParentItem->setFirstValue(aParentItem->firstValue().value<int>() & ~aFlag);
        }
    }

    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValueFlag(const QMetaEnum &aMetaEnum, const int &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aMetaEnum.keyCount(); ++i)
    {
        int aFlag=aMetaEnum.value(i);
        bool aChecked=(((aValue & aFlag)==aFlag) && (aFlag!=0 || aValue==0));

        PropertyTreeWidgetItem *aFlagItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aFlagItem, aCount, QString::fromLatin1(aMetaEnum.key(i)), aChecked, flagChanged);
    }

    return aCount;
}

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

void Property::mapItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVariantMap aMap=aParentItem->firstValue().value<QVariantMap>();
    QString aKey=aItem->text(0);

    aMap[aKey]=aNewValue;

    aParentItem->setFirstValue(aMap);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVariantMap &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (QVariantMap::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, i.key(), i.value(), mapItemChanged);
    }

    return aCount;
}

void Property::listItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVariantList aList=aParentItem->firstValue().value<QVariantList>();
    int aIndex=aItem->text(0).toInt()-1;

    aList[aIndex]=aNewValue;

    aParentItem->setFirstValue(aList);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVariantList &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aValue.length(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, QString::number(i+1), aValue.at(i), listItemChanged);
    }

    return aCount;
}

void Property::stringListItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QStringList aList=aParentItem->firstValue().value<QStringList>();
    int aIndex=aItem->text(0).toInt()-1;

    aList[aIndex]=aNewValue.value<QString>();

    aParentItem->setFirstValue(aList);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QStringList &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aValue.length(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, QString::number(i+1), aValue.at(i), stringListItemChanged);
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

void Property::localeLanguageChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLocale aLocale=aParentItem->firstValue().value<QLocale>();
    aLocale=QLocale((QLocale::Language)aNewValue.value<int>(), aLocale.country());

    aParentItem->setFirstValue(aLocale);
    aParentItem->itemConnector()->sendSignal();
}

void Property::localeCountryChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLocale aLocale=aParentItem->firstValue().value<QLocale>();
    aLocale=QLocale(aLocale.language(), (QLocale::Country)aNewValue.value<int>());

    aParentItem->setFirstValue(aLocale);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QLocale &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aLanguageEnum=QLocale::staticMetaObject.enumerator(QLocale::staticMetaObject.indexOfEnumerator("Language"));
    QMetaEnum aCountryEnum=QLocale::staticMetaObject.enumerator(QLocale::staticMetaObject.indexOfEnumerator("Country"));
    QLocale::Language aLanguage=aValue.language();
    QLocale::Country aCountry=aValue.country();

    PropertyTreeWidgetItem *aLanguageItem;
    PropertyTreeWidgetItem *aCountryItem;

    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aLanguageItem, aCount, qApp->translate("Property", "Language"), aLanguageEnum, aLanguage, localeLanguageChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aCountryItem,  aCount, qApp->translate("Property", "Country"), aCountryEnum, aCountry, localeCountryChanged);

    return aCount;
}

void Property::rectXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRect aRect=aParentItem->firstValue().value<QRect>();
    aRect.moveLeft(aNewValue.value<int>());

    aParentItem->setFirstValue(aRect);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRect aRect=aParentItem->firstValue().value<QRect>();
    aRect.moveTop(aNewValue.value<int>());

    aParentItem->setFirstValue(aRect);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectWidthChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRect aRect=aParentItem->firstValue().value<QRect>();
    aRect.setWidth(aNewValue.value<int>());

    aParentItem->setFirstValue(aRect);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectHeightChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRect aRect=aParentItem->firstValue().value<QRect>();
    aRect.setHeight(aNewValue.value<int>());

    aParentItem->setFirstValue(aRect);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QRect &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      aValue.x(),      rectXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      aValue.y(),      rectYChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  aValue.width(),  rectWidthChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), aValue.height(), rectHeightChanged);

    return aCount;
}

void Property::rectFXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRectF aRectF=aParentItem->firstValue().value<QRectF>();
    aRectF.moveLeft(aNewValue.value<double>());

    aParentItem->setFirstValue(aRectF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectFYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRectF aRectF=aParentItem->firstValue().value<QRectF>();
    aRectF.moveTop(aNewValue.value<double>());

    aParentItem->setFirstValue(aRectF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectFWidthChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRectF aRectF=aParentItem->firstValue().value<QRectF>();
    aRectF.setWidth(aNewValue.value<double>());

    aParentItem->setFirstValue(aRectF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::rectFHeightChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRectF aRectF=aParentItem->firstValue().value<QRectF>();
    aRectF.setHeight(aNewValue.value<double>());

    aParentItem->setFirstValue(aRectF);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QRectF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      aValue.x(),      rectFXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      aValue.y(),      rectFYChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  aValue.width(),  rectFWidthChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), aValue.height(), rectFHeightChanged);

    return aCount;
}

void Property::sizeWidthChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSize aSize=aParentItem->firstValue().value<QSize>();
    aSize.setWidth(aNewValue.value<int>());

    aParentItem->setFirstValue(aSize);
    aParentItem->itemConnector()->sendSignal();
}

void Property::sizeHeightChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSize aSize=aParentItem->firstValue().value<QSize>();
    aSize.setHeight(aNewValue.value<int>());

    aParentItem->setFirstValue(aSize);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QSize &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  aValue.width(),  sizeWidthChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), aValue.height(), sizeHeightChanged);

    return aCount;
}

void Property::sizeFWidthChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizeF aSizeF=aParentItem->firstValue().value<QSizeF>();
    aSizeF.setWidth(aNewValue.value<double>());

    aParentItem->setFirstValue(aSizeF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::sizeFHeightChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizeF aSizeF=aParentItem->firstValue().value<QSizeF>();
    aSizeF.setHeight(aNewValue.value<double>());

    aParentItem->setFirstValue(aSizeF);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QSizeF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aWidthItem;
    PropertyTreeWidgetItem *aHeightItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aWidthItem,  aCount, qApp->translate("Property", "Width"),  aValue.width(),  sizeFWidthChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aHeightItem, aCount, qApp->translate("Property", "Height"), aValue.height(), sizeFHeightChanged);

    return aCount;
}

void Property::lineX1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLine aLine=aParentItem->firstValue().value<QLine>();
    aLine.setP1(QPoint(aNewValue.value<int>(), aLine.y1()));

    aParentItem->setFirstValue(aLine);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineY1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLine aLine=aParentItem->firstValue().value<QLine>();
    aLine.setP1(QPoint(aLine.x1(), aNewValue.value<int>()));

    aParentItem->setFirstValue(aLine);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineX2Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLine aLine=aParentItem->firstValue().value<QLine>();
    aLine.setP2(QPoint(aNewValue.value<int>(), aLine.y2()));

    aParentItem->setFirstValue(aLine);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineY2Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLine aLine=aParentItem->firstValue().value<QLine>();
    aLine.setP2(QPoint(aLine.x2(), aNewValue.value<int>()));

    aParentItem->setFirstValue(aLine);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QLine &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aX1Item;
    PropertyTreeWidgetItem *aY1Item;
    PropertyTreeWidgetItem *aX2Item;
    PropertyTreeWidgetItem *aY2Item;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aX1Item, aCount, qApp->translate("Property", "X1"), aValue.x1(), lineX1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aY1Item, aCount, qApp->translate("Property", "Y1"), aValue.y1(), lineY1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aX2Item, aCount, qApp->translate("Property", "X2"), aValue.x2(), lineX2Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aY2Item, aCount, qApp->translate("Property", "Y2"), aValue.y2(), lineY2Changed);

    return aCount;
}

void Property::lineFX1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLineF aLineF=aParentItem->firstValue().value<QLineF>();
    aLineF.setP1(QPointF(aNewValue.value<double>(), aLineF.y1()));

    aParentItem->setFirstValue(aLineF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineFY1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLineF aLineF=aParentItem->firstValue().value<QLineF>();
    aLineF.setP1(QPointF(aLineF.x1(), aNewValue.value<double>()));

    aParentItem->setFirstValue(aLineF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineFX2Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLineF aLineF=aParentItem->firstValue().value<QLineF>();
    aLineF.setP2(QPointF(aNewValue.value<double>(), aLineF.y2()));

    aParentItem->setFirstValue(aLineF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::lineFY2Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QLineF aLineF=aParentItem->firstValue().value<QLineF>();
    aLineF.setP2(QPointF(aLineF.x2(), aNewValue.value<double>()));

    aParentItem->setFirstValue(aLineF);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QLineF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aX1Item;
    PropertyTreeWidgetItem *aY1Item;
    PropertyTreeWidgetItem *aX2Item;
    PropertyTreeWidgetItem *aY2Item;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aX1Item, aCount, qApp->translate("Property", "X1"), aValue.x1(), lineFX1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aY1Item, aCount, qApp->translate("Property", "Y1"), aValue.y1(), lineFY1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aX2Item, aCount, qApp->translate("Property", "X2"), aValue.x2(), lineFX2Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aY2Item, aCount, qApp->translate("Property", "Y2"), aValue.y2(), lineFY2Changed);

    return aCount;
}

void Property::pointX1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPoint aPoint=aParentItem->firstValue().value<QPoint>();
    aPoint.setX(aNewValue.value<int>());

    aParentItem->setFirstValue(aPoint);
    aParentItem->itemConnector()->sendSignal();
}

void Property::pointY1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPoint aPoint=aParentItem->firstValue().value<QPoint>();
    aPoint.setY(aNewValue.value<int>());

    aParentItem->setFirstValue(aPoint);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QPoint &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), aValue.x(), pointX1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), aValue.y(), pointY1Changed);

    return aCount;
}

void Property::pointFX1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPointF aPointF=aParentItem->firstValue().value<QPointF>();
    aPointF.setX(aNewValue.value<double>());

    aParentItem->setFirstValue(aPointF);
    aParentItem->itemConnector()->sendSignal();
}

void Property::pointFY1Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPointF aPointF=aParentItem->firstValue().value<QPointF>();
    aPointF.setY(aNewValue.value<double>());

    aParentItem->setFirstValue(aPointF);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QPointF &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), aValue.x(), pointFX1Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), aValue.y(), pointFY1Changed);

    return aCount;
}

int Property::subPropertiesForValue(const QRegExp &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

void Property::hashItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVariantHash aHash=aParentItem->firstValue().value<QVariantHash>();
    QString aKey=aItem->text(0);

    aHash[aKey]=aNewValue;

    aParentItem->setFirstValue(aHash);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVariantHash &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (QVariantHash::const_iterator i=aValue.constBegin(); i!=aValue.constEnd(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, i.key(), i.value(), hashItemChanged);
    }

    return aCount;
}

int Property::subPropertiesForValue(const QEasingCurve &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

void Property::fontFamilyChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setFamily(aNewValue.value<QString>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontSizeChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setPointSize(aNewValue.value<int>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontBoldChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setBold(aNewValue.value<bool>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontItalicChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setItalic(aNewValue.value<bool>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontUnderlineChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setUnderline(aNewValue.value<bool>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontStrikeOutChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setStrikeOut(aNewValue.value<bool>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontKerningChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setKerning(aNewValue.value<bool>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

void Property::fontAntiAliasingChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QFont aFont=aParentItem->firstValue().value<QFont>();
    aFont.setStyleStrategy((QFont::StyleStrategy)aNewValue.value<int>());

    aParentItem->setFirstValue(aFont);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QFont &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("StyleStrategy"));
    QFont::StyleStrategy aStrategy=aValue.styleStrategy();

    PropertyTreeWidgetItem *aFamilyItem;
    PropertyTreeWidgetItem *aSizeItem;
    PropertyTreeWidgetItem *aBoldItem;
    PropertyTreeWidgetItem *aItalicItem;
    PropertyTreeWidgetItem *aUnderlineItem;
    PropertyTreeWidgetItem *aStrikeOutItem;
    PropertyTreeWidgetItem *aKerningItem;
    PropertyTreeWidgetItem *aAntiAliasingItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aFamilyItem,       aCount, qApp->translate("Property", "Family", "Font"),       aValue.family(),    fontFamilyChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aSizeItem,         aCount, qApp->translate("Property", "Size", "Font"),         aValue.pointSize(), fontSizeChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aBoldItem,         aCount, qApp->translate("Property", "Bold", "Font"),         aValue.bold(),      fontBoldChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aItalicItem,       aCount, qApp->translate("Property", "Italic", "Font"),       aValue.italic(),    fontItalicChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aUnderlineItem,    aCount, qApp->translate("Property", "Underline", "Font"),    aValue.underline(), fontUnderlineChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aStrikeOutItem,    aCount, qApp->translate("Property", "Strike out", "Font"),   aValue.strikeOut(), fontStrikeOutChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aKerningItem,      aCount, qApp->translate("Property", "Kerning", "Font"),      aValue.kerning(),   fontKerningChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aAntiAliasingItem, aCount, qApp->translate("Property", "AntiAliasing", "Font"), aEnum, aStrategy,   fontAntiAliasingChanged);

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


void Property::colorRedChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QColor aColor=aParentItem->firstValue().value<QColor>();
    aColor.setRed(aNewValue.value<int>());

    aParentItem->setFirstValue(aColor);
    aParentItem->itemConnector()->sendSignal();
}

void Property::colorGreenChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QColor aColor=aParentItem->firstValue().value<QColor>();
    aColor.setGreen(aNewValue.value<int>());

    aParentItem->setFirstValue(aColor);
    aParentItem->itemConnector()->sendSignal();
}

void Property::colorBlueChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QColor aColor=aParentItem->firstValue().value<QColor>();
    aColor.setBlue(aNewValue.value<int>());

    aParentItem->setFirstValue(aColor);
    aParentItem->itemConnector()->sendSignal();
}

void Property::colorAlphaChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QColor aColor=aParentItem->firstValue().value<QColor>();
    aColor.setAlpha(aNewValue.value<int>());

    aParentItem->setFirstValue(aColor);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QColor &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aRedItem;
    PropertyTreeWidgetItem *aGreenItem;
    PropertyTreeWidgetItem *aBlueItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aRedItem,   aCount, qApp->translate("Property", "Red"),   aValue.red(),   colorRedChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aGreenItem, aCount, qApp->translate("Property", "Green"), aValue.green(), colorGreenChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aBlueItem,  aCount, qApp->translate("Property", "Blue"),  aValue.blue(),  colorBlueChanged);

    if (mAttributes.boolValue("alphaEnabled", true))
    {
        PropertyTreeWidgetItem *aAlphaItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aAlphaItem, aCount, qApp->translate("Property", "Alpha"), aValue.alpha(), colorAlphaChanged);
    }

    return aCount;
}

void Property::paletteColorChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPalette aPalette=aParentItem->firstValue().value<QPalette>();
    QString aColorName=aItem->text(0);
    int index=aColorName.indexOf("(");

    QString aColorGroup=aColorName.mid(index+1, aColorName.length()-index-2);
    QString aColorRole=aColorName.left(index-1);

    QMetaEnum aGroupEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorGroup"));
    QMetaEnum aRoleEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorRole"));

    QPalette::ColorGroup aGroup=(QPalette::ColorGroup)aGroupEnum.keyToValue(aColorGroup.toLatin1());
    QPalette::ColorRole aRole=(QPalette::ColorRole)aRoleEnum.keyToValue(aColorRole.toLatin1());

    aPalette.setColor(aGroup, aRole, aNewValue.value<QColor>());

    aParentItem->setFirstValue(aPalette);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QPalette &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aGroupEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorGroup"));
    QMetaEnum aRoleEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorRole"));

    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        for (int j=0; j<QPalette::NColorGroups; ++j)
        {
            PropertyTreeWidgetItem *aColorItem;
            QColor                  aColor=aValue.color((QPalette::ColorGroup)j, (QPalette::ColorRole)i);

            GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aColorItem, aCount, QString::fromLatin1(aRoleEnum.valueToKey(i))+" ("+QString::fromLatin1(aGroupEnum.valueToKey(j))+")", aColor, paletteColorChanged);
        }
    }

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

void Property::polygonItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPolygon aPolygon=aParentItem->firstValue().value<QPolygon>();
    int aIndex=aItem->text(0).toInt()-1;

    aPolygon[aIndex]=aNewValue.value<QPoint>();

    aParentItem->setFirstValue(aPolygon);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QPolygon &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    for (int i=0; i<aValue.count(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, QString::number(i+1), aValue.at(i), polygonItemChanged);
    }

    return aCount;
}

void Property::regionItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QRegion aRegion=aParentItem->firstValue().value<QRegion>();
    int aIndex=aItem->text(0).toInt()-1;

    QVector<QRect> aRects=aRegion.rects();
    aRects[aIndex]=aNewValue.value<QRect>();
    aRegion.setRects(aRects.data(), aRects.count());

    aParentItem->setFirstValue(aRegion);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QRegion &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QVector<QRect> aRects=aValue.rects();

    for (int i=0; i<aRects.count(); ++i)
    {
        PropertyTreeWidgetItem *aEntryItem;
        GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aEntryItem, aCount, QString::number(i+1), aRects.at(i), regionItemChanged);
    }

    return aCount;
}

int Property::subPropertiesForValue(const QBitmap &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

int Property::subPropertiesForValue(const QCursor &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

void Property::sizePolicyHorizontalPolicyChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizePolicy aSizePolicy=aParentItem->firstValue().value<QSizePolicy>();
    aSizePolicy.setHorizontalPolicy((QSizePolicy::Policy)aNewValue.value<int>());

    aParentItem->setFirstValue(aSizePolicy);
    aParentItem->itemConnector()->sendSignal();
}

void Property::sizePolicyVerticalPolicyChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizePolicy aSizePolicy=aParentItem->firstValue().value<QSizePolicy>();
    aSizePolicy.setVerticalPolicy((QSizePolicy::Policy)aNewValue.value<int>());

    aParentItem->setFirstValue(aSizePolicy);
    aParentItem->itemConnector()->sendSignal();
}

void Property::sizePolicyHorizontalStretchChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizePolicy aSizePolicy=aParentItem->firstValue().value<QSizePolicy>();
    aSizePolicy.setHorizontalStretch(aNewValue.value<int>());

    aParentItem->setFirstValue(aSizePolicy);
    aParentItem->itemConnector()->sendSignal();
}

void Property::sizePolicyVerticalStretchChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QSizePolicy aSizePolicy=aParentItem->firstValue().value<QSizePolicy>();
    aSizePolicy.setVerticalStretch(aNewValue.value<int>());

    aParentItem->setFirstValue(aSizePolicy);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QSizePolicy &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Policy"));
    QSizePolicy::Policy aHorizontalPolicy=aValue.horizontalPolicy();
    QSizePolicy::Policy aVerticalPolicy=aValue.verticalPolicy();

    PropertyTreeWidgetItem *aHorizontalPolicyItem;
    PropertyTreeWidgetItem *aVerticalPolicyItem;
    PropertyTreeWidgetItem *aHorizontalStretchItem;
    PropertyTreeWidgetItem *aVerticalStretchItem;

    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aHorizontalPolicyItem,  aCount, qApp->translate("Property", "Horizontal policy"),  aEnum, aHorizontalPolicy,   sizePolicyHorizontalPolicyChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aVerticalPolicyItem,    aCount, qApp->translate("Property", "Vertical policy"),    aEnum, aVerticalPolicy,     sizePolicyVerticalPolicyChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aHorizontalStretchItem, aCount, qApp->translate("Property", "Horizontal stretch"), aValue.horizontalStretch(), sizePolicyHorizontalStretchChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aVerticalStretchItem,   aCount, qApp->translate("Property", "Vertical stretch"),   aValue.verticalStretch(),   sizePolicyVerticalStretchChanged);

    return aCount;
}

int Property::subPropertiesForValue(const QKeySequence &/*aValue*/, PropertyTreeWidgetItem * /*aParentItem*/)
{
    return 0;
}

void Property::penBrushChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setBrush(aNewValue.value<QBrush>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();
}

void Property::penWidthChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setWidthF(aNewValue.value<double>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();
}

void Property::penStyleChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setStyle((Qt::PenStyle)aNewValue.value<int>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();

    ((CustomEditor *)aItem->itemConnector()->sender())->setIcon(aItem->icon(1));
}

void Property::penCapStyleChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setCapStyle((Qt::PenCapStyle)aNewValue.value<int>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();

    ((CustomEditor *)aItem->itemConnector()->sender())->setIcon(aItem->icon(1));
}

void Property::penJoinStyleChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setJoinStyle((Qt::PenJoinStyle)aNewValue.value<int>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();

    ((CustomEditor *)aItem->itemConnector()->sender())->setIcon(aItem->icon(1));
}

void Property::penColorChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QPen aPen=aParentItem->firstValue().value<QPen>();
    aPen.setColor(aNewValue.value<QColor>());

    aParentItem->setFirstValue(aPen);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QPen &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    QMetaEnum aStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenStyle"));
    QMetaEnum aCapStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenCapStyle"));
    QMetaEnum aJoinStyleEnum=staticQtMetaObject.enumerator(staticQtMetaObject.indexOfEnumerator("PenJoinStyle"));

    Qt::PenStyle aStyle=aValue.style();
    Qt::PenCapStyle aCapStyle=aValue.capStyle();
    Qt::PenJoinStyle aJoinStyle=aValue.joinStyle();

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

    aStylePen.setStyle(aStyle);
    aCapStylePen.setCapStyle(aCapStyle);
    aJoinStylePen.setJoinStyle(aJoinStyle);

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

    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aBrushItem,     aCount, qApp->translate("Property", "Brush"),      aValue.brush(),             penBrushChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aWidthItem,     aCount, qApp->translate("Property", "Width"),      aValue.widthF(),            penWidthChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aStyleItem,     aCount, qApp->translate("Property", "Style"),      aStyleEnum, aStyle,         penStyleChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aCapStyleItem,  aCount, qApp->translate("Property", "Cap style"),  aCapStyleEnum, aCapStyle,   penCapStyleChanged);
    GET_OR_CREATE_ITEM_SETUP_ENUM_CONNECT(aParentItem, aJoinStyleItem, aCount, qApp->translate("Property", "Join style"), aJoinStyleEnum, aJoinStyle, penJoinStyleChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(     aParentItem, aColorItem,     aCount, qApp->translate("Property", "Color"),      aValue.color(),             penColorChanged);

    aStyleItem->setIcon(1, QIcon(aStylePixmap));
    aCapStyleItem->setIcon(1, QIcon(aCapStylePixmap));
    aJoinStyleItem->setIcon(1, QIcon(aJoinStylePixmap));

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

void Property::matrixM11Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aNewValue.value<double>(),
                      aMatrix.m12(),
                      aMatrix.m21(),
                      aMatrix.m22(),
                      aMatrix.dx(),
                      aMatrix.dy()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
}

void Property::matrixM12Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aMatrix.m11(),
                      aNewValue.value<double>(),
                      aMatrix.m21(),
                      aMatrix.m22(),
                      aMatrix.dx(),
                      aMatrix.dy()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
}

void Property::matrixM21Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aMatrix.m11(),
                      aMatrix.m12(),
                      aNewValue.value<double>(),
                      aMatrix.m22(),
                      aMatrix.dx(),
                      aMatrix.dy()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
}

void Property::matrixM22Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aMatrix.m11(),
                      aMatrix.m12(),
                      aMatrix.m21(),
                      aNewValue.value<double>(),
                      aMatrix.dx(),
                      aMatrix.dy()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
}

void Property::matrixDxChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aMatrix.m11(),
                      aMatrix.m12(),
                      aMatrix.m21(),
                      aMatrix.m22(),
                      aNewValue.value<double>(),
                      aMatrix.dy()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
}

void Property::matrixDyChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix aMatrix=aParentItem->firstValue().value<QMatrix>();
    aMatrix.setMatrix(
                      aMatrix.m11(),
                      aMatrix.m12(),
                      aMatrix.m21(),
                      aMatrix.m22(),
                      aMatrix.dx(),
                      aNewValue.value<double>()
                     );

    aParentItem->setFirstValue(aMatrix);
    aParentItem->itemConnector()->sendSignal();
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

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), aValue.m11(), matrixM11Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), aValue.m12(), matrixM12Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), aValue.m21(), matrixM21Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), aValue.m22(), matrixM22Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aDXItem,  aCount, qApp->translate("Property", "dx"),  aValue.dx(),  matrixDxChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aDYItem,  aCount, qApp->translate("Property", "dy"),  aValue.dy(),  matrixDyChanged);

    return aCount;
}

void Property::transformM11Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aNewValue.value<double>(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM12Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aNewValue.value<double>(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM13Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aNewValue.value<double>(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM21Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aNewValue.value<double>(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM22Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aNewValue.value<double>(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM23Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aNewValue.value<double>(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM31Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aNewValue.value<double>(),
                         aTransform.m32(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM32Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aNewValue.value<double>(),
                         aTransform.m33()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
}

void Property::transformM33Changed(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QTransform aTransform=aParentItem->firstValue().value<QTransform>();
    aTransform.setMatrix(
                         aTransform.m11(),
                         aTransform.m12(),
                         aTransform.m13(),
                         aTransform.m21(),
                         aTransform.m22(),
                         aTransform.m23(),
                         aTransform.m31(),
                         aTransform.m32(),
                         aNewValue.value<double>()
                        );

    aParentItem->setFirstValue(aTransform);
    aParentItem->itemConnector()->sendSignal();
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

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), aValue.m11(), transformM11Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), aValue.m12(), transformM12Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM13Item, aCount, qApp->translate("Property", "M13"), aValue.m13(), transformM13Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), aValue.m21(), transformM21Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), aValue.m22(), transformM22Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM23Item, aCount, qApp->translate("Property", "M23"), aValue.m23(), transformM23Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM31Item, aCount, qApp->translate("Property", "M31"), aValue.m31(), transformM31Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM32Item, aCount, qApp->translate("Property", "M32"), aValue.m32(), transformM32Changed);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM33Item, aCount, qApp->translate("Property", "M33"), aValue.m33(), transformM33Changed);

    return aCount;
}

void Property::matrix4x4ItemChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QMatrix4x4 aMatrix4x4=aParentItem->firstValue().value<QMatrix4x4>();

    qreal matrix[16];
    aMatrix4x4.copyDataTo(matrix);

    matrix[aParentItem->indexOfChild(aItem)]=aNewValue.value<double>();
    aMatrix4x4=QMatrix4x4(matrix);

    aParentItem->setFirstValue(aMatrix4x4);
    aParentItem->itemConnector()->sendSignal();
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

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM11Item, aCount, qApp->translate("Property", "M11"), matrix[0],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM12Item, aCount, qApp->translate("Property", "M12"), matrix[1],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM13Item, aCount, qApp->translate("Property", "M13"), matrix[2],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM14Item, aCount, qApp->translate("Property", "M14"), matrix[3],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM21Item, aCount, qApp->translate("Property", "M21"), matrix[4],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM22Item, aCount, qApp->translate("Property", "M22"), matrix[5],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM23Item, aCount, qApp->translate("Property", "M23"), matrix[6],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM24Item, aCount, qApp->translate("Property", "M24"), matrix[7],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM31Item, aCount, qApp->translate("Property", "M31"), matrix[8],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM32Item, aCount, qApp->translate("Property", "M32"), matrix[9],  matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM33Item, aCount, qApp->translate("Property", "M33"), matrix[10], matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM34Item, aCount, qApp->translate("Property", "M34"), matrix[11], matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM41Item, aCount, qApp->translate("Property", "M41"), matrix[12], matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM42Item, aCount, qApp->translate("Property", "M42"), matrix[13], matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM43Item, aCount, qApp->translate("Property", "M43"), matrix[14], matrix4x4ItemChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aM44Item, aCount, qApp->translate("Property", "M44"), matrix[15], matrix4x4ItemChanged);

    return aCount;
}

void Property::vector2DXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector2D aVector2D=aParentItem->firstValue().value<QVector2D>();
    aVector2D.setX(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector2D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector2DYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector2D aVector2D=aParentItem->firstValue().value<QVector2D>();
    aVector2D.setY(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector2D);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVector2D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), aValue.x(), vector2DXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), aValue.y(), vector2DYChanged);

    return aCount;
}

void Property::vector3DXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector3D aVector3D=aParentItem->firstValue().value<QVector3D>();
    aVector3D.setX(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector3D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector3DYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector3D aVector3D=aParentItem->firstValue().value<QVector3D>();
    aVector3D.setY(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector3D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector3DZChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector3D aVector3D=aParentItem->firstValue().value<QVector3D>();
    aVector3D.setZ(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector3D);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVector3D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), aValue.x(), vector3DXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), aValue.y(), vector3DYChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aZItem, aCount, qApp->translate("Property", "Z"), aValue.z(), vector3DZChanged);

    return aCount;
}

void Property::vector4DXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector4D aVector4D=aParentItem->firstValue().value<QVector4D>();
    aVector4D.setX(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector4D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector4DYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector4D aVector4D=aParentItem->firstValue().value<QVector4D>();
    aVector4D.setY(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector4D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector4DZChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector4D aVector4D=aParentItem->firstValue().value<QVector4D>();
    aVector4D.setZ(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector4D);
    aParentItem->itemConnector()->sendSignal();
}

void Property::vector4DWChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QVector4D aVector4D=aParentItem->firstValue().value<QVector4D>();
    aVector4D.setW(aNewValue.value<double>());

    aParentItem->setFirstValue(aVector4D);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QVector4D &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;
    PropertyTreeWidgetItem *aWItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem, aCount, qApp->translate("Property", "X"), aValue.x(), vector4DXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem, aCount, qApp->translate("Property", "Y"), aValue.y(), vector4DYChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aZItem, aCount, qApp->translate("Property", "Z"), aValue.z(), vector4DZChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aWItem, aCount, qApp->translate("Property", "W"), aValue.w(), vector4DWChanged);

    return aCount;
}

void Property::quaternionScalarChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QQuaternion aQuaternion=aParentItem->firstValue().value<QQuaternion>();
    aQuaternion.setScalar(aNewValue.value<double>());

    aParentItem->setFirstValue(aQuaternion);
    aParentItem->itemConnector()->sendSignal();
}

void Property::quaternionXChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QQuaternion aQuaternion=aParentItem->firstValue().value<QQuaternion>();
    aQuaternion.setX(aNewValue.value<double>());

    aParentItem->setFirstValue(aQuaternion);
    aParentItem->itemConnector()->sendSignal();
}

void Property::quaternionYChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QQuaternion aQuaternion=aParentItem->firstValue().value<QQuaternion>();
    aQuaternion.setY(aNewValue.value<double>());

    aParentItem->setFirstValue(aQuaternion);
    aParentItem->itemConnector()->sendSignal();
}

void Property::quaternionZChanged(const QVariant &aNewValue)
{
    PropertyTreeWidgetItem *aItem=senderItem();
    PropertyTreeWidgetItem *aParentItem=(PropertyTreeWidgetItem *)aItem->parent();

    QQuaternion aQuaternion=aParentItem->firstValue().value<QQuaternion>();
    aQuaternion.setZ(aNewValue.value<double>());

    aParentItem->setFirstValue(aQuaternion);
    aParentItem->itemConnector()->sendSignal();
}

int Property::subPropertiesForValue(const QQuaternion &aValue, PropertyTreeWidgetItem *aParentItem)
{
    int aCount=0;

    PropertyTreeWidgetItem *aScalarItem;
    PropertyTreeWidgetItem *aXItem;
    PropertyTreeWidgetItem *aYItem;
    PropertyTreeWidgetItem *aZItem;

    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aScalarItem, aCount, qApp->translate("Property", "Scalar"), aValue.scalar(), quaternionScalarChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aXItem,      aCount, qApp->translate("Property", "X"),      aValue.x(),      quaternionXChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aYItem,      aCount, qApp->translate("Property", "Y"),      aValue.y(),      quaternionYChanged);
    GET_OR_CREATE_ITEM_SETUP_CONNECT(aParentItem, aZItem,      aCount, qApp->translate("Property", "Z"),      aValue.z(),      quaternionZChanged);

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
