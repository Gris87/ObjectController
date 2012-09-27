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

    mMap["13.04.95"]=2;
    mMap["03.12.87"]=5;
    mMap["27.09.12"]=4;

    mList.append(8);
    mList.append(2);
    mList.append(6);

    mStringList << "Ann" << "John" << "Mary";

    mString="It is a string";

    mByteArray=QString("Maxim").toUtf8();

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

    mHash["Hello"]=6;
    mHash["World!"]=9;
    mHash["From"]=7;
    mHash["Russia"]=2;

    mEasingCurve.setType(QEasingCurve::InOutCubic);
    mFont=QFont("Times New Roman", 12);

    mPixmap=QPixmap(64, 64);
    mPixmap.fill(QColor(255, 255, 255, 0));
    QPainter aPainter(&mPixmap);
    aPainter.setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
    aPainter.drawEllipse(1, 1, 61, 61);
    aPainter.setPen(QPen(QBrush(QColor(255, 255, 255)), 3));
    aPainter.drawEllipse(4, 4, 55, 55);
    aPainter.end();

    QRadialGradient aGradient(16, 16, 16);
    aGradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    aGradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 1));
    mBrush=QBrush(aGradient);

    mColor.setRgb(128, 0, 255, 128);
    mPalette.setColor(QPalette::Base, QColor(1, 2, 3));
    mIcon=QIcon(mPixmap);
    mImage=mPixmap.toImage();
    mPolygon.setPoints(3, 10, 40, 30, 97, 43, 16);
    mRegion=QRegion(10, 30, 40, 90);
    mBitmap=QBitmap::fromImage(mImage);
    mCursor.setShape(Qt::PointingHandCursor);
    mSizePolicy=QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    mKeySequence=QKeySequence("Ctrl+O");

    mPen.setStyle(Qt::DotLine);
    mPen.setWidth(2);

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

bool                   TestObject::getBool() const
{
    return mBool;
}

qint8                  TestObject::getInt8() const
{
    return mInt8;
}

quint8                 TestObject::getUInt8() const
{
    return mUInt8;
}

qint16                 TestObject::getInt16() const
{
    return mInt16;
}

quint16                TestObject::getUInt16() const
{
    return mUInt16;
}

qint32                 TestObject::getInt32() const
{
    return mInt32;
}

quint32                TestObject::getUInt32() const
{
    return mUInt32;
}

qint64                 TestObject::getInt64() const
{
    return mInt64;
}

quint64                TestObject::getUInt64() const
{
    return mUInt64;
}

float                  TestObject::getFloat() const
{
    return mFloat;
}

double                 TestObject::getDouble() const
{
    return mDouble;
}

QChar                  TestObject::getChar() const
{
    return mChar;
}

QVariantMap            TestObject::getMap() const
{
    QVariantMap res;

    for (QMap<QString, quint32>::iterator i=mMap.begin(); i!=mMap.end(); ++i)
    {
        res[i.key()]=i.value();
    }

    return res;
}

QVariantList           TestObject::getList() const
{
    QVariantList res;

    for (int i=0; i<mList.length(); ++i)
    {
        res.append(mList.at(i));
    }

    return res;
}

QStringList            TestObject::getStringList() const
{
    return mStringList;
}

QString                TestObject::getString() const
{
    return mString;
}

QByteArray             TestObject::getByteArray() const
{
    return mByteArray;
}

QBitArray              TestObject::getBitArray() const
{
    return mBitArray;
}

QDate                  TestObject::getDate() const
{
    return mDate;
}

QTime                  TestObject::getTime() const
{
    return mTime;
}

QDateTime              TestObject::getDateTime() const
{
    return mDateTime;
}

QUrl                   TestObject::getUrl() const
{
    return mUrl;
}

QLocale                TestObject::getLocale() const
{
    return mLocale;
}

QRect                  TestObject::getRect() const
{
    return mRect;
}

QRectF                 TestObject::getRectF() const
{
    return mRectF;
}

QSize                  TestObject::getSize() const
{
    return mSize;
}

QSizeF                 TestObject::getSizeF() const
{
    return mSizeF;
}

QLine                  TestObject::getLine() const
{
    return mLine;
}

QLineF                 TestObject::getLineF() const
{
    return mLineF;
}

QPoint                 TestObject::getPoint() const
{
    return mPoint;
}

QPointF                TestObject::getPointF() const
{
    return mPointF;
}

QRegExp                TestObject::getRegExp() const
{
    return mRegExp;
}

QVariantHash           TestObject::getHash() const
{
    QVariantHash res;

    for (QHash<QString, qint16>::const_iterator i=mHash.constBegin(); i!=mHash.constEnd(); ++i)
    {
        res[i.key()]=i.value();
    }

    return res;
}

QEasingCurve           TestObject::getEasingCurve() const
{
    return mEasingCurve;
}

QFont                  TestObject::getFont() const
{
    return mFont;
}

QPixmap                TestObject::getPixmap() const
{
    return mPixmap;
}

QBrush                 TestObject::getBrush() const
{
    return mBrush;
}

QColor                 TestObject::getColor() const
{
    return mColor;
}

QPalette               TestObject::getPalette() const
{
    return mPalette;
}

QIcon                  TestObject::getIcon() const
{
    return mIcon;
}

QImage                 TestObject::getImage() const
{
    return mImage;
}

QPolygon               TestObject::getPolygon() const
{
    return mPolygon;
}

QRegion                TestObject::getRegion() const
{
    return mRegion;
}

QBitmap                TestObject::getBitmap() const
{
    return mBitmap;
}

QCursor                TestObject::getCursor() const
{
    return mCursor;
}

QSizePolicy            TestObject::getSizePolicy() const
{
    return mSizePolicy;
}

QKeySequence           TestObject::getKeySequence() const
{
    return mKeySequence;
}

QPen                   TestObject::getPen() const
{
    return mPen;
}

QTextLength            TestObject::getTextLength() const
{
    return mTextLength;
}

QTextFormat            TestObject::getTextFormat() const
{
    return mTextFormat;
}

QMatrix                TestObject::getMatrix() const
{
    return mMatrix;
}

QTransform             TestObject::getTransform() const
{
    return mTransform;
}

QMatrix4x4             TestObject::getMatrix4x4() const
{
    return mMatrix4x4;
}

QVector2D              TestObject::getVector2D() const
{
    return mVector2D;
}

QVector3D              TestObject::getVector3D() const
{
    return mVector3D;
}

QVector4D              TestObject::getVector4D() const
{
    return mVector4D;
}

QQuaternion            TestObject::getQuaternion() const
{
    return mQuaternion;
}

void*                  TestObject::getVoid() const
{
    return mVoid;
}

QObject*               TestObject::getObject() const
{
    return mObject;
}
