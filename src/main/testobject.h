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
    Q_PROPERTY(bool           Bool          READ getBool)
    Q_PROPERTY(qint8          Int8          READ getInt8)
    Q_PROPERTY(quint8         UInt8         READ getUInt8)
    Q_PROPERTY(qint16         Int16         READ getInt16)
    Q_PROPERTY(quint16        UInt16        READ getUInt16)
    Q_PROPERTY(qint32         Int32         READ getInt32)
    Q_PROPERTY(quint32        UInt32        READ getUInt32)
    Q_PROPERTY(qint64         Int64         READ getInt64)
    Q_PROPERTY(quint64        UInt64        READ getUInt64)
    Q_PROPERTY(float          Float         READ getFloat)
    Q_PROPERTY(double         Double        READ getDouble)
    Q_PROPERTY(QChar          Char          READ getChar)
    Q_PROPERTY(QVariantMap    Map           READ getMap)
    Q_PROPERTY(QVariantList   List          READ getList)
    Q_PROPERTY(QStringList    StringList    READ getStringList)
    Q_PROPERTY(QString        String        READ getString)
    Q_PROPERTY(QByteArray     ByteArray     READ getByteArray)
    Q_PROPERTY(QBitArray      BitArray      READ getBitArray)
    Q_PROPERTY(QDate          Date          READ getDate)
    Q_PROPERTY(QTime          Time          READ getTime)
    Q_PROPERTY(QDateTime      DateTime      READ getDateTime)
    Q_PROPERTY(QUrl           Url           READ getUrl)
    Q_PROPERTY(QLocale        Locale        READ getLocale)
    Q_PROPERTY(QRect          RectF         READ getRect)
    Q_PROPERTY(QRectF         RectF         READ getRectF)
    Q_PROPERTY(QSize          Size          READ getSize)
    Q_PROPERTY(QSizeF         SizeF         READ getSizeF)
    Q_PROPERTY(QLine          Line          READ getLine)
    Q_PROPERTY(QLineF         LineF         READ getLineF)
    Q_PROPERTY(QPoint         Point         READ getPoint)
    Q_PROPERTY(QPointF        PointF        READ getPointF)
    Q_PROPERTY(QRegExp        RegExp        READ getRegExp)
    Q_PROPERTY(QVariantHash   Hash          READ getHash)
    Q_PROPERTY(QEasingCurve   EasingCurve   READ getEasingCurve)
    Q_PROPERTY(QFont          Font          READ getFont)
    Q_PROPERTY(QPixmap        Pixmap        READ getPixmap)
    Q_PROPERTY(QBrush         Brush         READ getBrush)
    Q_PROPERTY(QColor         Color         READ getColor)
    Q_PROPERTY(QPalette       Palette       READ getPalette)
    Q_PROPERTY(QIcon          Icon          READ getIcon)
    Q_PROPERTY(QImage         Image         READ getImage)
    Q_PROPERTY(QPolygon       Polygon       READ getPolygon)
    Q_PROPERTY(QRegion        Region        READ getRegion)
    Q_PROPERTY(QBitmap        Bitmap        READ getBitmap)
    Q_PROPERTY(QCursor        Cursor        READ getCursor)
    Q_PROPERTY(QSizePolicy    SizePolicy    READ getSizePolicy)
    Q_PROPERTY(QKeySequence   KeySequence   READ getKeySequence)
    Q_PROPERTY(QPen           Pen           READ getPen)
    Q_PROPERTY(QTextLength    TextLength    READ getTextLength)
    Q_PROPERTY(QTextFormat    TextFormat    READ getTextFormat)
    Q_PROPERTY(QMatrix        Matrix        READ getMatrix)
    Q_PROPERTY(QTransform     Transform     READ getTransform)
    Q_PROPERTY(QMatrix4x4     Matrix4x4     READ getMatrix4x4)
    Q_PROPERTY(QVector2D      Vector2D      READ getVector2D)
    Q_PROPERTY(QVector3D      Vector3D      READ getVector3D)
    Q_PROPERTY(QVector4D      Vector4D      READ getVector4D)
    Q_PROPERTY(QQuaternion    Quaternion    READ getQuaternion)
    Q_PROPERTY(void*          Void          READ getVoid)
    Q_PROPERTY(QObject*       Object        READ getObject)

    // ----------------------------------------------------------------------------------------------------

    explicit TestObject(QObject *parent = 0);

    // ----------------------------------------------------------------------------------------------------

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
};

#endif // TESTOBJECT_H
