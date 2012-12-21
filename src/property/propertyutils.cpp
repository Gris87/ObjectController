#include "propertyutils.h"

#include <QApplication>
#include <QMetaEnum>
#include <QByteArray>
#include <QBitArray>
#include <QEasingCurve>
#include <QBitmap>
#include <QMatrix4x4>
#include <QVector2D>
#include <QPainter>

class QT_Object : public QObject
{
public:
    static const QMetaObject qtMetaObject()
    {
        return staticQtMetaObject;
    }
};

QString enumToString(const QMetaEnum &aMetaEnum, const int &aValue)
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

QString flagsToString(const QMetaEnum &aMetaEnum, const int &aValue)
{
    QString res="[";

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
                if (res.length()>1)
                {
                    res.append(", ");
                }

                res.append(QString::fromLatin1(aMetaEnum.key(i)));
            }
        }
    }

    res.append("]");

    return res;
}

QString boolToString(const bool &aValue)
{
    return aValue ? "true" : "false";
}

QString intToString(const qint8 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint8 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint16 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint16 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint32 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint32 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const qint64 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QString intToString(const quint64 &aValue, const QString &aPrefix, const QString &aSuffix)
{
    return aPrefix+
           QString::number(aValue)+
           aSuffix;
}

QList<double> *decimals=0;

QString doubleToString(double aValue, int aDecimals)
{
    if (aDecimals<0 || aDecimals>6)
    {
        return QString::number(aValue);
    }

    if (decimals==0)
    {
        decimals=new QList<double>();

        decimals->append(1);
        decimals->append(10);
        decimals->append(100);
        decimals->append(1000);
        decimals->append(10000);
        decimals->append(100000);
        decimals->append(1000000);
    }

    double aMultiplier=decimals->at(aDecimals);

    return QString::number(qRound(aValue*aMultiplier)/aMultiplier);
}

QString doubleToString(double aValue, const QString &aPrefix, const QString &aSuffix, int aDecimals)
{
    return aPrefix+
           doubleToString(aValue, aDecimals)+
           aSuffix;
}

QString charToString(const QChar &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    switch (aMode)
    {
        case QLineEdit::Normal:             return QString(aValue);
        case QLineEdit::NoEcho:             return "";
        case QLineEdit::Password:
        case QLineEdit::PasswordEchoOnEdit: return qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter);
        default:
            Q_ASSERT(false);
        break;
    }

    return QString(aValue);
}

QString stringListToString(const QStringList &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    QString res="[";

    for (int i=0; i<aValue.length(); ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }



        res.append("\"");

        switch (aMode)
        {
            case QLineEdit::Normal:
                res.append(aValue.at(i));
            break;
            case QLineEdit::NoEcho:
                // Nothing
            break;
            case QLineEdit::Password:
            case QLineEdit::PasswordEchoOnEdit:
                res.append(QString(aValue.at(i).length(), qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter)));
            break;
            default:
                Q_ASSERT(false);
            break;
        }

        res.append("\"");
    }

    res.append("]");

    return res;
}

QString stringToString(const QString &aValue, const QString &aEchoMode)
{
    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));
    QLineEdit::EchoMode aMode=QLineEdit::Normal;

    for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
    {
        if (QString::fromLatin1(aEchoModeEnum.key(i))==aEchoMode)
        {
            aMode=(QLineEdit::EchoMode)aEchoModeEnum.value(i);
            break;
        }
    }

    switch (aMode)
    {
        case QLineEdit::Normal:             return aValue;
        case QLineEdit::NoEcho:             return "";
        case QLineEdit::Password:
        case QLineEdit::PasswordEchoOnEdit: return QString(aValue.length(), qApp->style()->styleHint(QStyle::SH_LineEdit_PasswordCharacter));
        default:
            Q_ASSERT(false);
        break;
    }

    return aValue;
}

QString byteArrayToString(const QByteArray &aValue)
{
    return aValue.toHex().toUpper();
}

QString bitArrayToString(const QBitArray &aValue)
{
    QString res;

    for (int i=0; i<aValue.count(); ++i)
    {
        res.append(aValue.at(i) ? "1" : "0");
    }

    return res;
}

QString dateToString(const QDate &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString timeToString(const QTime &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString dateTimeToString(const QDateTime &aValue, const QString &aFormat)
{
    return aValue.toString(aFormat);
}

QString localeToString(const QLocale &aValue)
{
    return aValue.languageToString(aValue.language())+
           ", "+
           aValue.countryToString(aValue.country());
}

QString rectToString(const QRect &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ", "+
           QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height())+
           ")";
}

QString rectFToString(const QRectF &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals)+
           ")";
}

QString sizeToString(const QSize &aValue)
{
    return QString::number(aValue.width())+
           " x "+
           QString::number(aValue.height());
}

QString sizeFToString(const QSizeF &aValue, int aDecimals)
{
    return doubleToString(aValue.width(), aDecimals)+
           " x "+
           doubleToString(aValue.height(), aDecimals);
}

QString lineToString(const QLine &aValue)
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

QString lineFToString(const QLineF &aValue, int aDecimals)
{
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

QString pointToString(const QPoint &aValue)
{
    return "("+
           QString::number(aValue.x())+
           ", "+
           QString::number(aValue.y())+
           ")";
}

QString pointFToString(const QPointF &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ")";
}

QString easingCurveToString(const QEasingCurve &aValue, int aDecimals)
{
    QMetaEnum aEnum=QEasingCurve::staticMetaObject.enumerator(QEasingCurve::staticMetaObject.indexOfEnumerator("Type"));
    return "("+
           QString::fromLatin1(aEnum.valueToKey(aValue.type()))+
           ", "+
           doubleToString(aValue.amplitude(), aDecimals)+
           ", "+
           doubleToString(aValue.overshoot(), aDecimals)+
           ", "+
           doubleToString(aValue.period(), aDecimals)+
           ")";
}

QString fontToString(const QFont &aValue)
{
    return "["+
           aValue.family()+
           ", "+
           QString::number(aValue.pointSize())+
           "]";
}

QString pixmapToString(const QPixmap &aValue)
{
    return sizeToString(aValue.size());
}

QString brushToString(const QBrush &aValue)
{
    QMetaEnum aEnum=QT_Object::qtMetaObject().enumerator(QT_Object::qtMetaObject().indexOfEnumerator("BrushStyle"));
    return aEnum.valueToKey(aValue.style());
}

QString colorToString(const QColor &aValue, bool alphaEnabled)
{
    if (alphaEnabled)
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

QString imageToString(const QImage &aValue)
{
    return sizeToString(aValue.size());
}

QString polygonToString(const QPolygon &aValue)
{
    QString res="[";

    for (int i=0; i<aValue.count(); ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }

        res.append(pointToString(aValue.at(i)));
    }

    res.append("]");

    return res;
}

QString regionToString(const QRegion &aValue)
{
    QVector<QRect> aRects=aValue.rects();

    QString res="[";

    for (int i=0; i<aRects.count(); ++i)
    {
        if (i>0)
        {
            res.append(", ");
        }

        res.append(rectToString(aRects.at(i)));
    }

    res.append("]");

    return res;
}

QString bitmapToString(const QBitmap &aValue)
{
    return sizeToString(aValue.size());
}

QString cursorToString(const QCursor &aValue)
{
    QMetaEnum aEnum=QT_Object::qtMetaObject().enumerator(QT_Object::qtMetaObject().indexOfEnumerator("CursorShape"));
    return QString::fromLatin1(aEnum.valueToKey(aValue.shape()));
}

QString sizePolicyToString(const QSizePolicy &aValue)
{
    QMetaEnum aEnum=QSizePolicy::staticMetaObject.enumerator(QSizePolicy::staticMetaObject.indexOfEnumerator("Policy"));

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

QString keySequenceToString(const QKeySequence &aValue)
{
    return aValue.toString();
}

QString textLengthToString(const QTextLength &aValue, int aDecimals)
{
    QString res="[";

    switch (aValue.type())
    {
        case QTextLength::VariableLength:   res.append("VariableLength");   break;
        case QTextLength::FixedLength:      res.append("FixedLength");      break;
        case QTextLength::PercentageLength: res.append("PercentageLength"); break;
    }

    res.append(", ");
    res.append(doubleToString(aValue.rawValue(), aDecimals));
    res.append("]");

    return res;
}

QString textFormatToString(const QTextFormat &aValue)
{
    QString res=qApp->translate("Property", "[Unknown type]");

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
    else
    {
        Q_ASSERT(false);
    }

    return res;
}

QString matrixToString(const QMatrix &aValue, int aDecimals)
{
    return "[("+
           doubleToString(aValue.m11(), aDecimals)+
           ", "+
           doubleToString(aValue.m12(), aDecimals)+
           "), ("+
           doubleToString(aValue.m21(), aDecimals)+
           ", "+
           doubleToString(aValue.m22(), aDecimals)+
           "), ("+
           doubleToString(aValue.dx(), aDecimals)+
           ", "+
           doubleToString(aValue.dy(), aDecimals)+
           ")]";
}

QString transformToString(const QTransform &aValue, int aDecimals)
{
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

QString matrix4x4ToString(const QMatrix4x4 &aValue, int aDecimals)
{
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

QString vector2DToString(const QVector2D &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ")";
}

QString vector3DToString(const QVector3D &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
           ")";
}

QString vector4DToString(const QVector4D &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
           ", "+
           doubleToString(aValue.w(), aDecimals)+
           ")";
}

QString quaternionToString(const QQuaternion &aValue, int aDecimals)
{
    return "("+
           doubleToString(aValue.scalar(), aDecimals)+
           ", "+
           doubleToString(aValue.x(), aDecimals)+
           ", "+
           doubleToString(aValue.y(), aDecimals)+
           ", "+
           doubleToString(aValue.z(), aDecimals)+
           ")";
}

QString voidToString(void *aValue)
{
    return "0x"+QString::number((qint64)aValue, 16).toUpper();
}

QString objectToString(QObject *aValue)
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

QIcon iconForBool(const bool &aValue, QStyle *aStyle)
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

    aStyle->drawControl(QStyle::CE_CheckBox, &checkboxstyle, &aPainter);

    aPainter.end();

    return QIcon(aBoolPixmap);
}

QIcon iconForDate()
{
    return QIcon(":/objectcontroller/images/Date.png");
}

QIcon iconForTime()
{
    return QIcon(":/objectcontroller/images/Time.png");
}

QIcon iconForDateTime()
{
    return QIcon(":/objectcontroller/images/DateTime.png");
}

QIcon iconForRect()
{
    return QIcon(":/objectcontroller/images/Rect.png");
}

QIcon iconForRectF()
{
    return QIcon(":/objectcontroller/images/Rect.png");
}

QIcon iconForSize()
{
    return QIcon(":/objectcontroller/images/Size.png");
}

QIcon iconForSizeF()
{
    return QIcon(":/objectcontroller/images/Size.png");
}

QIcon iconForLine()
{
    return QIcon(":/objectcontroller/images/Line.png");
}

QIcon iconForLineF()
{
    return QIcon(":/objectcontroller/images/Line.png");
}

QIcon iconForPoint()
{
    return QIcon(":/objectcontroller/images/Point.png");
}

QIcon iconForPointF()
{
    return QIcon(":/objectcontroller/images/Point.png");
}

QIcon iconForEasingCurve()
{
    return QIcon(":/objectcontroller/images/EasingCurve.png");
}

QIcon iconForFont(QFont aValue)
{
    aValue.setPixelSize(32);

    QFontMetrics aMetrics(aValue);

    int aSize=qMax(aMetrics.width('A'), aMetrics.height())-6;

    if (aSize<1)
    {
        aSize=1;
    }

    QRect aBoundingRect(0, 0, aSize, aSize);

    QPixmap aPenPixmap=QPixmap(aSize, aSize);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setFont(aValue);
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

QIcon iconForPixmap(const QPixmap &aValue)
{
    return QIcon(aValue);
}

QIcon iconForBrush(const QBrush &aValue)
{
    QPixmap aBrushPixmap=QPixmap(32, 32);
    aBrushPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aBrushPixmap);
    aPainter.fillRect(0, 0, aBrushPixmap.width(), aBrushPixmap.height(), aValue);
    aPainter.end();

    return QIcon(aBrushPixmap);
}

QIcon iconForColor(const QColor &aValue)
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

QIcon iconForPalette()
{
    return QIcon(":/objectcontroller/images/Palette.png");
}

QIcon iconForImage(const QImage &aValue)
{
    return QIcon(QPixmap::fromImage(aValue));
}

QIcon iconForPolygon()
{
    return QIcon(":/objectcontroller/images/Polygon.png");
}

QIcon iconForRegion()
{
    return QIcon(":/objectcontroller/images/Region.png");
}

QIcon iconForBitmap(const QBitmap &aValue)
{
    return QIcon(QPixmap::fromImage(aValue.toImage()));
}

QIcon iconForCursor(const QCursor &aValue)
{
    QPixmap aPixmap=aValue.pixmap();

    if (!aPixmap.isNull())
    {
        return QIcon(aPixmap);
    }
    else
    {
        const QBitmap *aBitmap=aValue.bitmap();

        if (aBitmap)
        {
            aPixmap=QPixmap::fromImage(aBitmap->toImage());
            aPixmap.setMask(*aValue.mask());

            return QIcon(aPixmap);
        }
        else
        {
            return QIcon(":/objectcontroller/images/Cursor-"+cursorToString(aValue)+".png");
        }
    }
}

QIcon iconForPen(const QPen &aValue)
{
    QPixmap aPenPixmap=QPixmap(16, 16);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setPen(aValue);
    aPainter.drawLine(aPenPixmap.width(), 0, 0, aPenPixmap.height());
    aPainter.end();

    return QIcon(aPenPixmap);
}

QIcon iconForMatrix()
{
    return QIcon(":/objectcontroller/images/Matrix.png");
}

QIcon iconForTransform()
{
    return QIcon(":/objectcontroller/images/Transform.png");
}

QIcon iconForMatrix4x4()
{
    return QIcon(":/objectcontroller/images/Matrix4x4.png");
}

QIcon iconForVector2D()
{
    return QIcon(":/objectcontroller/images/Vector2D.png");
}

QIcon iconForVector3D()
{
    return QIcon(":/objectcontroller/images/Vector3D.png");
}

QIcon iconForVector4D()
{
    return QIcon(":/objectcontroller/images/Vector4D.png");
}
