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
    QMap<quint32, QString> mMap;
    QList<quint8>          mList;
    QStringList            mStringList;
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

    bool                   getBool();
    qint8                  getInt8();
    quint8                 getUInt8();
    qint16                 getInt16();
    quint16                getUInt16();
    qint32                 getInt32();
    quint32                getUInt32();
    qint64                 getInt64();
    quint64                getUInt64();
    float                  getFloat();
    double                 getDouble();
    QChar                  getChar();
    QVariantMap            getMap();
    QVariantList           getList();
    QStringList            getStringList();
    QByteArray             getByteArray();
    QBitArray              getBitArray();
    QDate                  getDate();
    QTime                  getTime();
    QDateTime              getDateTime();
    QUrl                   getUrl();
    QLocale                getLocale();
    QRect                  getRect();
    QRectF                 getRectF();
    QSize                  getSize();
    QSizeF                 getSizeF();
    QLineF                 getLineF();
    QPoint                 getPoint();
    QPointF                getPointF();
    QRegExp                getRegExp();
    QVariantHash           getHash();
    QEasingCurve           getEasingCurve();
    QFont                  getFont();
    QPixmap                getPixmap();
    QBrush                 getBrush();
    QColor                 getColor();
    QPalette               getPalette();
    QIcon                  getIcon();
    QImage                 getImage();
    QPolygon               getPolygon();
    QRegion                getRegion();
    QBitmap                getBitmap();
    QCursor                getCursor();
    QSizePolicy            getSizePolicy();
    QKeySequence           getKeySequence();
    QPen                   getPen();
    QTextLength            getTextLength();
    QTextFormat            getTextFormat();
    QMatrix                getMatrix();
    QTransform             getTransform();
    QMatrix4x4             getMatrix4x4();
    QVector2D              getVector2D();
    QVector3D              getVector3D();
    QVector4D              getVector4D();
    QQuaternion            getQuaternion();
    void*                  getVoid();
    QObject*               getObject();
};

#endif // TESTOBJECT_H
