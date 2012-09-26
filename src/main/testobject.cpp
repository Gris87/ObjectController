#include "testobject.h"

TestObject::TestObject(QObject *parent) :
    QObject(parent)
{
}

// ----------------------------------------------------------------------------------------------------

bool                   TestObject::getBool()
{
    return mBool;
}

qint8                  TestObject::getInt8()
{
    return mInt8;
}

quint8                 TestObject::getUInt8()
{
    return mUInt8;
}

qint16                 TestObject::getInt16()
{
    return mInt16;
}

quint16                TestObject::getUInt16()
{
    return mUInt16;
}

qint32                 TestObject::getInt32()
{
    return mInt32;
}

quint32                TestObject::getUInt32()
{
    return mUInt32;
}

qint64                 TestObject::getInt64()
{
    return mInt64;
}

quint64                TestObject::getUInt64()
{
    return mUInt64;
}

float                  TestObject::getFloat()
{
    return mFloat;
}

double                 TestObject::getDouble()
{
    return mDouble;
}

QChar                  TestObject::getChar()
{
    return mChar;
}

QVariantMap            TestObject::getMap()
{
    return QVariantMap();// mMap;
}

QVariantList           TestObject::getList()
{
    return QVariantList();//mList;
}

QStringList            TestObject::getStringList()
{
    return mStringList;
}

QByteArray             TestObject::getByteArray()
{
    return mByteArray;
}

QBitArray              TestObject::getBitArray()
{
    return mBitArray;
}

QDate                  TestObject::getDate()
{
    return mDate;
}

QTime                  TestObject::getTime()
{
    return mTime;
}

QDateTime              TestObject::getDateTime()
{
    return mDateTime;
}

QUrl                   TestObject::getUrl()
{
    return mUrl;
}

QLocale                TestObject::getLocale()
{
    return mLocale;
}

QRect                  TestObject::getRect()
{
    return mRect;
}

QRectF                 TestObject::getRectF()
{
    return mRectF;
}

QSize                  TestObject::getSize()
{
    return mSize;
}

QSizeF                 TestObject::getSizeF()
{
    return mSizeF;
}

QLineF                 TestObject::getLineF()
{
    return mLineF;
}

QPoint                 TestObject::getPoint()
{
    return mPoint;
}

QPointF                TestObject::getPointF()
{
    return mPointF;
}

QRegExp                TestObject::getRegExp()
{
    return mRegExp;
}

QVariantHash           TestObject::getHash()
{
    return QVariantHash(); //mHash;
}

QEasingCurve           TestObject::getEasingCurve()
{
    return mEasingCurve;
}

QFont                  TestObject::getFont()
{
    return mFont;
}

QPixmap                TestObject::getPixmap()
{
    return mPixmap;
}

QBrush                 TestObject::getBrush()
{
    return mBrush;
}

QColor                 TestObject::getColor()
{
    return mColor;
}

QPalette               TestObject::getPalette()
{
    return mPalette;
}

QIcon                  TestObject::getIcon()
{
    return mIcon;
}

QImage                 TestObject::getImage()
{
    return mImage;
}

QPolygon               TestObject::getPolygon()
{
    return mPolygon;
}

QRegion                TestObject::getRegion()
{
    return mRegion;
}

QBitmap                TestObject::getBitmap()
{
    return mBitmap;
}

QCursor                TestObject::getCursor()
{
    return mCursor;
}

QSizePolicy            TestObject::getSizePolicy()
{
    return mSizePolicy;
}

QKeySequence           TestObject::getKeySequence()
{
    return mKeySequence;
}

QPen                   TestObject::getPen()
{
    return mPen;
}

QTextLength            TestObject::getTextLength()
{
    return mTextLength;
}

QTextFormat            TestObject::getTextFormat()
{
    return mTextFormat;
}

QMatrix                TestObject::getMatrix()
{
    return mMatrix;
}

QTransform             TestObject::getTransform()
{
    return mTransform;
}

QMatrix4x4             TestObject::getMatrix4x4()
{
    return mMatrix4x4;
}

QVector2D              TestObject::getVector2D()
{
    return mVector2D;
}

QVector3D              TestObject::getVector3D()
{
    return mVector3D;
}

QVector4D              TestObject::getVector4D()
{
    return mVector4D;
}

QQuaternion            TestObject::getQuaternion()
{
    return mQuaternion;
}

void*                  TestObject::getVoid()
{
    return mVoid;
}

QObject*               TestObject::getObject()
{
    return mObject;
}
