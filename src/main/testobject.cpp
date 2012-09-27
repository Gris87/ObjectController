#include "testobject.h"

#include <QPainter>

TestObject::TestObject(QObject *parent) :
    QObject(parent)
{
    mBool=true;
    mInt8=1;
    mUInt8=2;
    mInt16=3;
    mUInt16=4;
    mInt32=5;
    mUInt32=6;
    mInt64=7;
    mUInt64=8;
    mFloat=9.87654321f;
    mDouble=1.23456789;
    mChar='T';

    mMap[5]="World!";
    mMap[2]="Hello";
    mMap[4]=", ";

    mList.append(8);
    mList.append(2);
    mList.append(6);

    mStringList << "Ann" << "Jhon" << "Mary";

    mByteArray=QString("ByteArray").toUtf8();

    mBitArray.resize(8);
    mBitArray.setBit(0, true);
    mBitArray.setBit(1, false);
    mBitArray.setBit(2, true);
    mBitArray.setBit(3, false);
    mBitArray.setBit(4, false);
    mBitArray.setBit(5, true);
    mBitArray.setBit(6, true);
    mBitArray.setBit(7, false);

    mDate=QDate::currentDate();
    mTime=QTime::currentTime();
    mDateTime=QDateTime::currentDateTime();
    mUrl.setUrl("http:/google.com");
    mLocale=QLocale::system();
    mRect.setRect(10, 20, 800, 600);
    mRectF.setRect(20, 10, 640, 480);
    mSize=QSize(32, 32);
    mSizeF=QSize(48, 48);
    mLine.setLine(10, 10, 600, 10);
    mLineF.setLine(4, 4, 4, 300);
    mPoint=QPoint(320, 240);
    mPointF=QPoint(240, 320);
    mRegExp.setPattern("^[a-z]");

    mHash["03.12.87"]=5;
    mHash["13.04.95"]=2;
    mHash["27.09.12"]=4;

    mEasingCurve.setType(QEasingCurve::InOutCubic);
    mFont=QFont("Times New Roman", 12);

    mPixmap=QPixmap(64, 64);
    QPainter aPainter(&mPixmap);
    aPainter.drawEllipse(0, 0, 63, 63);
    aPainter.end();

    QRadialGradient aGradient(50, 50, 50, 50, 50);
    aGradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    aGradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    mBrush=QBrush(aGradient);

    mColor.setRgb(240, 200, 240);
    mPalette.setColor(QPalette::Base, QColor(1, 2, 3));
    mIcon=QIcon::fromTheme("edit-undo");
    mImage=mPixmap.toImage();
    mPolygon.setPoints(3, 10, 40, 30, 97, 43, 16);
    mRegion=QRegion(10, 30, 40, 90);
    mBitmap=QBitmap::fromImage(mImage);
    mCursor.setShape(Qt::PointingHandCursor);
    mSizePolicy=QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    mKeySequence=QKeySequence("Ctrl+O");
    mPen.setStyle(Qt::DashDotLine);
    mTextLength=QTextLength(QTextLength::PercentageLength, 90);
    mTextFormat=QTextFormat(QTextFormat::TableFormat);
    mMatrix.setMatrix(6, 9, 12, 5, 7, 6);
    mTransform.setMatrix(1, 2, 3, 4, 5, 6, 7, 8, 9);
    mMatrix4x4=QMatrix4x4(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    mVector2D=QVector2D(6, 7);
    mVector3D=QVector3D(1, 5, 8);
    mVector4D=QVector4D(4, 3, 9, 6);
    mQuaternion=QQuaternion(1, 7, 6, 5);
    mVoid=&mQuaternion;
    mObject=this;
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

QLine                  TestObject::getLine()
{
    return mLine;
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
