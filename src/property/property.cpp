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

bool Property::isNumber(const QVariant &aValue)
{
    QVariant::Type aType=aValue.type();

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
            res.append(valueText(i.value()));
        }
        else
        {
            res.append("\"");
            res.append(valueText(i.value()));
            res.append("\"");
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QVariantList &aValue)
{
    QString res="[";

    for (int i=0; i<aValue.length(); ++i)
    {
        if (isNumber(aValue.at(i)))
        {
            res.append(valueText(aValue.at(i)));
        }
        else
        {
            res.append("\"");
            res.append(valueText(aValue.at(i)));
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

QString Property::valueToString(const QStringList &aValue)
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
    return aValue.languageToString(aValue.language())+
           ", "+
           aValue.countryToString(aValue.country());
}

QString Property::valueToString(const QRect &aValue)
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

QString Property::valueToString(const QRectF &aValue)
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

QString Property::valueToString(const QSize &aValue)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString Property::valueToString(const QSizeF &aValue)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString Property::valueToString(const QLine &aValue)
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

QString Property::valueToString(const QLineF &aValue)
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

QString Property::valueToString(const QPoint &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString Property::valueToString(const QPointF &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString Property::valueToString(const QRegExp &aValue)
{
    return aValue.pattern();
}

QString Property::valueToString(const QVariantHash &aValue)
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
            res.append(valueText(i.value()));
        }
        else
        {
            res.append("\"");
            res.append(valueText(i.value()));
            res.append("\"");
        }

        res.append(")");
    }

    res.append("]");

    return res;
}

QString Property::valueToString(const QEasingCurve &aValue)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("Type"));
    return aEnum.valueToKey(aValue.type());
}

QString Property::valueToString(const QFont &aValue)
{
    return "["+
           aValue.family()+
           ", "+
           QString::number(aValue.pointSize())+
           "]";
}

QString Property::valueToString(const QPixmap &aValue)
{
    return valueToString(aValue.size());
}

QString Property::valueToString(const QBrush &aValue)
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

QString Property::valueToString(const QColor &aValue)
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

QString Property::valueToString(const QPalette &/*aValue*/)
{
    return "Palette";
}

QString Property::valueToString(const QIcon &aValue)
{
    QString res=aValue.name();

    if (res!="")
    {
        return res;
    }

    return "Icon";
}

QString Property::valueToString(const QImage &aValue)
{
    return valueToString(aValue.size());
}

QString Property::valueToString(const QPolygon &aValue)
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

QString Property::valueToString(const QRegion &aValue)
{
    QVector<QRect> aRects=aValue.rects();

    QString res="[";

    for (int i=0; i<aRects.count(); ++i)
    {
        res.append(valueToString(aRects.at(i)));

        if (i<aRects.count()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    return res;
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

QString Property::valueToString(const QKeySequence &aValue)
{
    return aValue.toString();
}

QString Property::valueToString(const QPen &/*aValue*/)
{
    return "Pen";
}

QString Property::valueToString(const QTextLength &aValue)
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

QString Property::valueToString(const QTextFormat &aValue)
{
    QMetaEnum aEnum=aValue.staticMetaObject.enumerator(aValue.staticMetaObject.indexOfEnumerator("FormatType"));
    return aEnum.valueToKey(aValue.type());
}

QString Property::valueToString(const QMatrix &aValue)
{
    return "[("+
           QString::number(aValue.m11())+
           ", "+
           QString::number(aValue.m12())+
           "), ("+
           QString::number(aValue.m21())+
           ", "+
           QString::number(aValue.m22())+
           "), ("+
           QString::number(aValue.dx())+
           ", "+
           QString::number(aValue.dy())+
           ")]";
}

QString Property::valueToString(const QTransform &aValue)
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

QString Property::valueToString(const QMatrix4x4 &aValue)
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

QString Property::valueToString(const QVector2D &aValue)
{
    return "["+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           "]";
}

QString Property::valueToString(const QVector3D &aValue)
{
    return "["+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.z())+
           "]";
}

QString Property::valueToString(const QVector4D &aValue)
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

QString Property::valueToString(const QQuaternion &aValue)
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

QString Property::valueToString(void *aValue)
{
    return "0x"+QString::number((qint64)aValue, 16).toUpper();
}

QString Property::valueToString(QObject *aValue)
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
