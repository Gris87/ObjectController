#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>

#include <QBitArray>
#include <QDate>
#include <QUrl>
#include <QEasingCurve>
#include <QFont>
#include <QBrush>
#include <QPalette>
#include <QIcon>
#include <QBitmap>
#include <QCursor>
#include <QSizePolicy>
#include <QKeySequence>
#include <QPen>
#include <QTextLength>
#include <QMatrix4x4>
#include <QVector2D>

class TestObject : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(TestEnumeration   Enumeration   READ getEnumeration   WRITE setEnumeration)
    Q_PROPERTY(TestFlags         Flags         READ getFlags         WRITE setFlags)
    Q_PROPERTY(QString           StringCombo   READ getStringCombo   WRITE setStringCombo)
    Q_PROPERTY(bool              Bool          READ getBool          WRITE setBool)
    Q_PROPERTY(qint8             Int8          READ getInt8          WRITE setInt8)
    Q_PROPERTY(quint8            UInt8         READ getUInt8         WRITE setUInt8)
    Q_PROPERTY(qint16            Int16         READ getInt16         WRITE setInt16)
    Q_PROPERTY(quint16           UInt16        READ getUInt16        WRITE setUInt16)
    Q_PROPERTY(qint32            Int32         READ getInt32         WRITE setInt32)
    Q_PROPERTY(quint32           UInt32        READ getUInt32        WRITE setUInt32)
    Q_PROPERTY(qint64            Int64         READ getInt64         WRITE setInt64)
    Q_PROPERTY(quint64           UInt64        READ getUInt64        WRITE setUInt64)
    Q_PROPERTY(float             Float         READ getFloat         WRITE setFloat)
    Q_PROPERTY(double            Double        READ getDouble        WRITE setDouble)
    Q_PROPERTY(QChar             Char          READ getChar          WRITE setChar)
    Q_PROPERTY(QVariantMap       Map           READ getMap           WRITE setMap)
    Q_PROPERTY(QVariantList      List          READ getList          WRITE setList)
    Q_PROPERTY(QStringList       StringList    READ getStringList    WRITE setStringList)
    Q_PROPERTY(QString           String        READ getString        WRITE setString)
    Q_PROPERTY(QByteArray        ByteArray     READ getByteArray     WRITE setByteArray)
    Q_PROPERTY(QBitArray         BitArray      READ getBitArray      WRITE setBitArray)
    Q_PROPERTY(QDate             Date          READ getDate          WRITE setDate)
    Q_PROPERTY(QTime             Time          READ getTime          WRITE setTime)
    Q_PROPERTY(QDateTime         DateTime      READ getDateTime      WRITE setDateTime)
    Q_PROPERTY(QUrl              Url           READ getUrl           WRITE setUrl)
    Q_PROPERTY(QLocale           Locale        READ getLocale        WRITE setLocale)
    Q_PROPERTY(QRect             Rect          READ getRect          WRITE setRect)
    Q_PROPERTY(QRectF            RectF         READ getRectF         WRITE setRectF)
    Q_PROPERTY(QSize             Size          READ getSize          WRITE setSize)
    Q_PROPERTY(QSizeF            SizeF         READ getSizeF         WRITE setSizeF)
    Q_PROPERTY(QLine             Line          READ getLine          WRITE setLine)
    Q_PROPERTY(QLineF            LineF         READ getLineF         WRITE setLineF)
    Q_PROPERTY(QPoint            Point         READ getPoint         WRITE setPoint)
    Q_PROPERTY(QPointF           PointF        READ getPointF        WRITE setPointF)
    Q_PROPERTY(QRegExp           RegExp        READ getRegExp        WRITE setRegExp)
    Q_PROPERTY(QVariantHash      Hash          READ getHash          WRITE setHash)
    Q_PROPERTY(QEasingCurve      EasingCurve   READ getEasingCurve   WRITE setEasingCurve)
    Q_PROPERTY(QFont             Font          READ getFont          WRITE setFont)
    Q_PROPERTY(QPixmap           Pixmap        READ getPixmap        WRITE setPixmap)
    Q_PROPERTY(QBrush            Brush         READ getBrush         WRITE setBrush)
    Q_PROPERTY(QColor            Color         READ getColor         WRITE setColor)
    Q_PROPERTY(QPalette          Palette       READ getPalette       WRITE setPalette)
    Q_PROPERTY(QIcon             Icon          READ getIcon          WRITE setIcon)
    Q_PROPERTY(QImage            Image         READ getImage         WRITE setImage)
    Q_PROPERTY(QPolygon          Polygon       READ getPolygon       WRITE setPolygon)
    Q_PROPERTY(QRegion           Region        READ getRegion        WRITE setRegion)
    Q_PROPERTY(QBitmap           Bitmap        READ getBitmap        WRITE setBitmap)
    Q_PROPERTY(QCursor           Cursor        READ getCursor        WRITE setCursor)
    Q_PROPERTY(QSizePolicy       SizePolicy    READ getSizePolicy    WRITE setSizePolicy)
    Q_PROPERTY(QKeySequence      KeySequence   READ getKeySequence   WRITE setKeySequence)
    Q_PROPERTY(QPen              Pen           READ getPen           WRITE setPen)
    Q_PROPERTY(QTextLength       TextLength    READ getTextLength    WRITE setTextLength)
    Q_PROPERTY(QTextFormat       TextFormat    READ getTextFormat    WRITE setTextFormat)
    Q_PROPERTY(QMatrix           Matrix        READ getMatrix        WRITE setMatrix)
    Q_PROPERTY(QTransform        Transform     READ getTransform     WRITE setTransform)
    Q_PROPERTY(QMatrix4x4        Matrix4x4     READ getMatrix4x4     WRITE setMatrix4x4)
    Q_PROPERTY(QVector2D         Vector2D      READ getVector2D      WRITE setVector2D)
    Q_PROPERTY(QVector3D         Vector3D      READ getVector3D      WRITE setVector3D)
    Q_PROPERTY(QVector4D         Vector4D      READ getVector4D      WRITE setVector4D)
    Q_PROPERTY(QQuaternion       Quaternion    READ getQuaternion    WRITE setQuaternion)
    Q_PROPERTY(void*             Void          READ getVoid)
    Q_PROPERTY(QObject*          Object        READ getObject)

    // ----------------------------------------------------------------------------------------------------

    Q_CLASSINFO("Enumeration attributes", "toolTip         : \"It is a Enumeration\" ;"
                                          "delay           : 100                     ;"
                                          "maxVisibleItems : 5                       ;")

    Q_CLASSINFO("Flags attributes",       "toolTip         : \"It is a Flags\"       ;"
                                          "delay           : 100                     ;")

    Q_CLASSINFO("StringCombo attributes", "toolTip         : \"It is a StringCombo\" ;"
                                          "delay           : 100                     ;"
                                          "maxVisibleItems : 5                       ;")

    Q_CLASSINFO("Bool attributes",        "toolTip         : \"It is a Bool\"        ;"
                                          "delay           : 100                     ;")

    Q_CLASSINFO("Int8 attributes",        "toolTip         : \"It is a Int8\"        ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("UInt8 attributes",       "toolTip         : \"It is a UInt8\"       ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("Int16 attributes",       "toolTip         : \"It is a Int16\"       ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("UInt16 attributes",      "toolTip         : \"It is a UInt16\"      ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("Int32 attributes",       "toolTip         : \"It is a Int32\"       ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("UInt32 attributes",      "toolTip         : \"It is a UInt32\"      ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("Int64 attributes",       "toolTip         : \"It is a Int64\"       ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("UInt64 attributes",      "toolTip         : \"It is a UInt64\"      ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"per \"                ;"
                                          "suffix          : \" item(s)\"            ;"
                                        //"minValue        : 0                       ;"
                                        //"maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("Float attributes",       "toolTip         : \"It is a Float\"       ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : true                    ;"
                                          "accelerated     : false                   ;"
                                          "prefix          : \"I have \"             ;"
                                          "suffix          : \" apple(s)\"           ;"
                                          "minValue        : 0                       ;"
                                          "maxValue        : 30.73                   ;"
                                          "decimals        : 3                       ;"
                                          "step            : 0.1                     ;")

    Q_CLASSINFO("Double attributes",      "toolTip         : \"It is a Double\"      ;"
                                          "delay           : 100                     ;"
                                          "wrapping        : false                   ;"
                                          "accelerated     : true                    ;"
                                          "prefix          : \"There is no \"        ;"
                                          "suffix          : \" human(s)\"           ;"
                                          "minValue        : 0.05                    ;"
                                          "maxValue        : 54.34                   ;"
                                          "decimals        : 5                       ;"
                                          "step            : 0.03                    ;")

    Q_CLASSINFO("Char attributes",        "toolTip         : \"It is a Char\"        ;"
                                          "delay           : 100                     ;"
                                          "inputMask       : >A!                     ;"
                                          "echoMode        : Password                ;"
                                          "placeholderText : \"Insert capital\"      ;")

    Q_CLASSINFO("Map attributes",         "toolTip         : \"It is a Map\"         ;"
                                          "delay           : 100                     ;"
                                        //"wrapping        : false                   ;"
                                        //"accelerated     : false                   ;"
                                        //"prefix          : \"\"                    ;"
                                          "suffix          : \" book(s)\"            ;"
                                          "minValue        : 0                       ;"
                                          "maxValue        : 100                     ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("List attributes",        "toolTip         : \"It is a List\"        ;"
                                          "delay           : 100                     ;"
                                        //"wrapping        : false                   ;"
                                        //"accelerated     : false                   ;"
                                        //"prefix          : \"\"                    ;"
                                          "suffix          : \" PC(s)\"              ;"
                                          "minValue        : 0                       ;"
                                          "maxValue        : 10                      ;"
                                          "step            : 1                       ;")

    Q_CLASSINFO("StringList attributes",  "toolTip         : \"It is a StringList\"  ;"
                                          "delay           : 100                     ;"
                                          "minCount        : 1                       ;"
                                          "maxCount        : 5                       ;"
                                       // "inputMask       : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                       // "echoMode        : Password                ;"
                                          "placeholderText : \"Insert name\"         ;")

    Q_CLASSINFO("String attributes",      "toolTip         : \"It is a String\"      ;"
                                          "delay           : 100                     ;"
                                          "inputMask       : >A!AAAAAAAAAAAAAAAAAAAA ;"
                                          "echoMode        : Password                ;"
                                          "placeholderText : \"Insert sentence\"     ;")

    Q_CLASSINFO("Rect attributes",        "toolTip         : \"It is a Rect\"        ;"
                                          "delay           : 100                     ;"
                                        //"wrapping        : false                   ;"
                                        //"accelerated     : false                   ;"
                                        //"prefix          : \"\"                    ;"
                                          "suffix          : \" px\"                 ;"
                                          "minValue        : 0                       ;"
                                          "maxValue        : 2000                    ;"
                                          "step            : 10                      ;")

    Q_CLASSINFO("RectF attributes",       "toolTip         : \"It is a RectF\"       ;"
                                          "delay           : 100                     ;"
                                        //"wrapping        : false                   ;"
                                        //"accelerated     : false                   ;"
                                        //"prefix          : \"\"                    ;"
                                          "suffix          : \" px\"                 ;"
                                          "minValue        : 0                       ;"
                                          "maxValue        : 2000                    ;"
                                          "decimals        : 3                       ;"
                                          "step            : 0.1                     ;")

    // ----------------------------------------------------------------------------------------------------

    explicit TestObject(QObject *parent = 0);

    Q_ENUMS(TestEnumeration)
    enum TestEnumeration
    {
        ENUM_ONE,
        ENUM_TWO,
        ENUM_THREE,
        ENUM_FOUR,
        ENUM_FIVE,
        ENUM_SIX
    };

    Q_FLAGS(TestFlags)
    enum TestFlag
    {
        NO_FLAGS   = 0,
        FLAG_1     = 0x1,
        FLAG_2     = 0x2,
        FLAG_3     = 0x4,
        FLAG_4     = 0x8,
        FLAG_5     = 0x10,
        FLAG_1_3   = FLAG_1 | FLAG_3,
        FLAG_1_3_5 = FLAG_1 | FLAG_3 | FLAG_5,
        FLAG_2_4   = FLAG_2 | FLAG_4,
        FLAG_3_5   = FLAG_3 | FLAG_5,
        ALL_FLAGS  = FLAG_1_3_5 | FLAG_2_4
    };

    Q_DECLARE_FLAGS(TestFlags, TestFlag)

    // ----------------------------------------------------------------------------------------------------

    TestEnumeration        mEnumeration;
    TestFlags              mFlags;
    QString                mStringCombo;
    bool                   mBool;
    qint8                  mInt8;
    quint8                 mUInt8;
    qint16                 mInt16;
    quint16                mUInt16;
    qint32                 mInt32;
    quint32                mUInt32;
    qint64                 mInt64;
    quint64                mUInt64;
    float                  mFloat;
    double                 mDouble;
    QChar                  mChar;
    QMap<QString, quint32> mMap;
    QList<quint8>          mList;
    QStringList            mStringList;
    QString                mString;
    QByteArray             mByteArray;
    QBitArray              mBitArray;
    QDate                  mDate;
    QTime                  mTime;
    QDateTime              mDateTime;
    QUrl                   mUrl;
    QLocale                mLocale;
    QRect                  mRect;
    QRectF                 mRectF;
    QSize                  mSize;
    QSizeF                 mSizeF;
    QLine                  mLine;
    QLineF                 mLineF;
    QPoint                 mPoint;
    QPointF                mPointF;
    QRegExp                mRegExp;
    QHash<QString, qint16> mHash;
    QEasingCurve           mEasingCurve;
    QFont                  mFont;
    QPixmap                mPixmap;
    QBrush                 mBrush;
    QColor                 mColor;
    QPalette               mPalette;
    QIcon                  mIcon;
    QImage                 mImage;
    QPolygon               mPolygon;
    QRegion                mRegion;
    QBitmap                mBitmap;
    QCursor                mCursor;
    QSizePolicy            mSizePolicy;
    QKeySequence           mKeySequence;
    QPen                   mPen;
    QTextLength            mTextLength;
    QTextFormat            mTextFormat;
    QMatrix                mMatrix;
    QTransform             mTransform;
    QMatrix4x4             mMatrix4x4;
    QVector2D              mVector2D;
    QVector3D              mVector3D;
    QVector4D              mVector4D;
    QQuaternion            mQuaternion;
    void*                  mVoid;
    QObject*               mObject;

    // ----------------------------------------------------------------------------------------------------

    TestEnumeration        getEnumeration() const;
    TestFlags              getFlags() const;
    QString                getStringCombo() const;
    bool                   getBool() const;
    qint8                  getInt8() const;
    quint8                 getUInt8() const;
    qint16                 getInt16() const;
    quint16                getUInt16() const;
    qint32                 getInt32() const;
    quint32                getUInt32() const;
    qint64                 getInt64() const;
    quint64                getUInt64() const;
    float                  getFloat() const;
    double                 getDouble() const;
    QChar                  getChar() const;
    QVariantMap            getMap() const;
    QVariantList           getList() const;
    QStringList            getStringList() const;
    QString                getString() const;
    QByteArray             getByteArray() const;
    QBitArray              getBitArray() const;
    QDate                  getDate() const;
    QTime                  getTime() const;
    QDateTime              getDateTime() const;
    QUrl                   getUrl() const;
    QLocale                getLocale() const;
    QRect                  getRect() const;
    QRectF                 getRectF() const;
    QSize                  getSize() const;
    QSizeF                 getSizeF() const;
    QLine                  getLine() const;
    QLineF                 getLineF() const;
    QPoint                 getPoint() const;
    QPointF                getPointF() const;
    QRegExp                getRegExp() const;
    QVariantHash           getHash() const;
    QEasingCurve           getEasingCurve() const;
    QFont                  getFont() const;
    QPixmap                getPixmap() const;
    QBrush                 getBrush() const;
    QColor                 getColor() const;
    QPalette               getPalette() const;
    QIcon                  getIcon() const;
    QImage                 getImage() const;
    QPolygon               getPolygon() const;
    QRegion                getRegion() const;
    QBitmap                getBitmap() const;
    QCursor                getCursor() const;
    QSizePolicy            getSizePolicy() const;
    QKeySequence           getKeySequence() const;
    QPen                   getPen() const;
    QTextLength            getTextLength() const;
    QTextFormat            getTextFormat() const;
    QMatrix                getMatrix() const;
    QTransform             getTransform() const;
    QMatrix4x4             getMatrix4x4() const;
    QVector2D              getVector2D() const;
    QVector3D              getVector3D() const;
    QVector4D              getVector4D() const;
    QQuaternion            getQuaternion() const;
    void*                  getVoid() const;
    QObject*               getObject() const;

    // ----------------------------------------------------------------------------------------------------

    void setEnumeration(const TestEnumeration &aEnumeration);
    void setFlags(const TestFlags &aFlags);
    void setStringCombo(const QString &aStringCombo);
    void setBool(const bool &aBool);
    void setInt8(const qint8 &aInt8);
    void setUInt8(const quint8 &aUInt8);
    void setInt16(const qint16 &aInt16);
    void setUInt16(const quint16 &aUInt16);
    void setInt32(const qint32 &aInt32);
    void setUInt32(const quint32 &aUInt32);
    void setInt64(const qint64 &aInt64);
    void setUInt64(const quint64 &aUInt64);
    void setFloat(const float &aFloat);
    void setDouble(const double &aDouble);
    void setChar(const QChar &aChar);
    void setMap(const QVariantMap &aMap);
    void setList(const QVariantList &aList);
    void setStringList(const QStringList &aStringList);
    void setString(const QString &aString);
    void setByteArray(const QByteArray &aByteArray);
    void setBitArray(const QBitArray &aBitArray);
    void setDate(const QDate &aDate);
    void setTime(const QTime &aTime);
    void setDateTime(const QDateTime &aDateTime);
    void setUrl(const QUrl &aUrl);
    void setLocale(const QLocale &aLocale);
    void setRect(const QRect &aRect);
    void setRectF(const QRectF &aRectF);
    void setSize(const QSize &aSize);
    void setSizeF(const QSizeF &aSizeF);
    void setLine(const QLine &aLine);
    void setLineF(const QLineF &aLineF);
    void setPoint(const QPoint &aPoint);
    void setPointF(const QPointF &aPointF);
    void setRegExp(const QRegExp &aRegExp);
    void setHash(const QVariantHash &aHash);
    void setEasingCurve(const QEasingCurve &aEasingCurve);
    void setFont(const QFont &aFont);
    void setPixmap(const QPixmap &aPixmap);
    void setBrush(const QBrush &aBrush);
    void setColor(const QColor &aColor);
    void setPalette(const QPalette &aPalette);
    void setIcon(const QIcon &aIcon);
    void setImage(const QImage &aImage);
    void setPolygon(const QPolygon &aPolygon);
    void setRegion(const QRegion &aRegion);
    void setBitmap(const QBitmap &aBitmap);
    void setCursor(const QCursor &aCursor);
    void setSizePolicy(const QSizePolicy &aSizePolicy);
    void setKeySequence(const QKeySequence &aKeySequence);
    void setPen(const QPen &aPen);
    void setTextLength(const QTextLength &aTextLength);
    void setTextFormat(const QTextFormat &aTextFormat);
    void setMatrix(const QMatrix &aMatrix);
    void setTransform(const QTransform &aTransform);
    void setMatrix4x4(const QMatrix4x4 &aMatrix4x4);
    void setVector2D(const QVector2D &aVector2D);
    void setVector3D(const QVector3D &aVector3D);
    void setVector4D(const QVector4D &aVector4D);
    void setQuaternion(const QQuaternion &aQuaternion);

public slots:
    bool valuesForProperty(QString aPropertyName, QStringList &aValues);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TestObject::TestFlags)

#endif // TESTOBJECT_H
