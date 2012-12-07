#include "testobject.h"

#include <QPainter>

TestObject::TestObject(QObject *parent) :
    QObject(parent)
{
    mEnumeration=ENUM_TWO;
    mFlags=FLAG_1_3;
    mStringCombo="Option 1";

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

    mByteArray=QString("It is a test object. Try to edit it...").toUtf8();

    mBitArray.resize(mByteArray.length()*8);

    for (int i=0; i<mByteArray.length(); ++i)
    {
        char aChar=mByteArray.at(i);

        for (int j=0; j<8; ++j)
        {
            mBitArray.setBit(i*8+7-j, (aChar & 1)==1);
            aChar>>=1;
        }
    }

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
    mPalette.setColor(QPalette::Light, QColor(1, 2, 3));
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
    mTextFormat=QTextTableFormat();
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

bool TestObject::valuesForProperty(QString aPropertyName, QStringList &aValues)
{
    if (aPropertyName=="StringCombo")
    {
        aValues.append("Option 1");
        aValues.append("Option 2");
        aValues.append("Option 3");
        aValues.append("Option 4");
        aValues.append("Option 5");
        aValues.append("Option 6");

        return true;
    }

    return false;
}

// ----------------------------------------------------------------------------------------------------

TestObject::TestEnumeration TestObject::getEnumeration() const
{
    return mEnumeration;
}

TestObject::TestFlags TestObject::getFlags() const
{
    return mFlags;
}

QString TestObject::getStringCombo() const
{
    return mStringCombo;
}

bool TestObject::getBool() const
{
    return mBool;
}

qint8 TestObject::getInt8() const
{
    return mInt8;
}

quint8 TestObject::getUInt8() const
{
    return mUInt8;
}

qint16 TestObject::getInt16() const
{
    return mInt16;
}

quint16 TestObject::getUInt16() const
{
    return mUInt16;
}

qint32 TestObject::getInt32() const
{
    return mInt32;
}

quint32 TestObject::getUInt32() const
{
    return mUInt32;
}

qint64 TestObject::getInt64() const
{
    return mInt64;
}

quint64 TestObject::getUInt64() const
{
    return mUInt64;
}

float TestObject::getFloat() const
{
    return mFloat;
}

double TestObject::getDouble() const
{
    return mDouble;
}

QChar TestObject::getChar() const
{
    return mChar;
}

QVariantMap TestObject::getMap() const
{
    QVariantMap res;

    for (QMap<QString, quint32>::const_iterator i=mMap.constBegin(); i!=mMap.constEnd(); ++i)
    {
        res[i.key()]=i.value();
    }

    return res;
}

QVariantList TestObject::getList() const
{
    QVariantList res;

    for (int i=0; i<mList.length(); ++i)
    {
        res.append(mList.at(i));
    }

    return res;
}

QStringList TestObject::getStringList() const
{
    return mStringList;
}

QString TestObject::getString() const
{
    return mString;
}

QByteArray TestObject::getByteArray() const
{
    return mByteArray;
}

QBitArray TestObject::getBitArray() const
{
    return mBitArray;
}

QDate TestObject::getDate() const
{
    return mDate;
}

QTime TestObject::getTime() const
{
    return mTime;
}

QDateTime TestObject::getDateTime() const
{
    return mDateTime;
}

QUrl TestObject::getUrl() const
{
    return mUrl;
}

QLocale TestObject::getLocale() const
{
    return mLocale;
}

QRect TestObject::getRect() const
{
    return mRect;
}

QRectF TestObject::getRectF() const
{
    return mRectF;
}

QSize TestObject::getSize() const
{
    return mSize;
}

QSizeF TestObject::getSizeF() const
{
    return mSizeF;
}

QLine TestObject::getLine() const
{
    return mLine;
}

QLineF TestObject::getLineF() const
{
    return mLineF;
}

QPoint TestObject::getPoint() const
{
    return mPoint;
}

QPointF TestObject::getPointF() const
{
    return mPointF;
}

QRegExp TestObject::getRegExp() const
{
    return mRegExp;
}

QVariantHash TestObject::getHash() const
{
    QVariantHash res;

    for (QHash<QString, qint16>::const_iterator i=mHash.constBegin(); i!=mHash.constEnd(); ++i)
    {
        res[i.key()]=i.value();
    }

    return res;
}

QEasingCurve TestObject::getEasingCurve() const
{
    return mEasingCurve;
}

QFont TestObject::getFont() const
{
    return mFont;
}

QPixmap TestObject::getPixmap() const
{
    return mPixmap;
}

QBrush TestObject::getBrush() const
{
    return mBrush;
}

QColor TestObject::getColor() const
{
    return mColor;
}

QPalette TestObject::getPalette() const
{
    return mPalette;
}

QIcon TestObject::getIcon() const
{
    return mIcon;
}

QImage TestObject::getImage() const
{
    return mImage;
}

QPolygon TestObject::getPolygon() const
{
    return mPolygon;
}

QRegion TestObject::getRegion() const
{
    return mRegion;
}

QBitmap TestObject::getBitmap() const
{
    return mBitmap;
}

QCursor TestObject::getCursor() const
{
    return mCursor;
}

QSizePolicy TestObject::getSizePolicy() const
{
    return mSizePolicy;
}

QKeySequence TestObject::getKeySequence() const
{
    return mKeySequence;
}

QPen TestObject::getPen() const
{
    return mPen;
}

QTextLength TestObject::getTextLength() const
{
    return mTextLength;
}

QTextFormat TestObject::getTextFormat() const
{
    return mTextFormat;
}

QMatrix TestObject::getMatrix() const
{
    return mMatrix;
}

QTransform TestObject::getTransform() const
{
    return mTransform;
}

QMatrix4x4 TestObject::getMatrix4x4() const
{
    return mMatrix4x4;
}

QVector2D TestObject::getVector2D() const
{
    return mVector2D;
}

QVector3D TestObject::getVector3D() const
{
    return mVector3D;
}

QVector4D TestObject::getVector4D() const
{
    return mVector4D;
}

QQuaternion TestObject::getQuaternion() const
{
    return mQuaternion;
}

void* TestObject::getVoid() const
{
    return mVoid;
}

QObject* TestObject::getObject() const
{
    return mObject;
}

// ----------------------------------------------------------------------------------------------------

void TestObject::setEnumeration(const TestEnumeration &aEnumeration)
{
    mEnumeration=aEnumeration;
}

void TestObject::setFlags(const TestFlags &aFlags)
{
    mFlags=aFlags;
}

void TestObject::setStringCombo(const QString &aStringCombo)
{
    mStringCombo=aStringCombo;
}

void TestObject::setBool(const bool &aBool)
{
    mBool=aBool;
}

void TestObject::setInt8(const qint8 &aInt8)
{
    mInt8=aInt8;
}

void TestObject::setUInt8(const quint8 &aUInt8)
{
    mUInt8=aUInt8;
}

void TestObject::setInt16(const qint16 &aInt16)
{
    mInt16=aInt16;
}

void TestObject::setUInt16(const quint16 &aUInt16)
{
    mUInt16=aUInt16;
}

void TestObject::setInt32(const qint32 &aInt32)
{
    mInt32=aInt32;
}

void TestObject::setUInt32(const quint32 &aUInt32)
{
    mUInt32=aUInt32;
}

void TestObject::setInt64(const qint64 &aInt64)
{
    mInt64=aInt64;
}

void TestObject::setUInt64(const quint64 &aUInt64)
{
    mUInt64=aUInt64;
}

void TestObject::setFloat(const float &aFloat)
{
    mFloat=aFloat;
}

void TestObject::setDouble(const double &aDouble)
{
    mDouble=aDouble;
}

void TestObject::setChar(const QChar &aChar)
{
    mChar=aChar;
}

void TestObject::setMap(const QVariantMap &aMap)
{
    mMap.clear();

    for (QVariantMap::const_iterator i=aMap.constBegin(); i!=aMap.constEnd(); ++i)
    {
        bool ok;

        quint32 aValue=i.value().toUInt(&ok);

        if (ok)
        {
            mMap[i.key()]=aValue;
        }
    }
}

void TestObject::setList(const QVariantList &aList)
{
    mList.clear();

    for (int i=0; i<aList.length(); ++i)
    {
        bool ok;

        quint8 aValue=aList.at(i).toUInt(&ok);

        if (ok)
        {
            mList.append(aValue);
        }
    }
}

void TestObject::setStringList(const QStringList &aStringList)
{
    mStringList=aStringList;
}

void TestObject::setString(const QString &aString)
{
    mString=aString;
}

void TestObject::setByteArray(const QByteArray &aByteArray)
{
    mByteArray=aByteArray;
}

void TestObject::setBitArray(const QBitArray &aBitArray)
{
    mBitArray=aBitArray;
}

void TestObject::setDate(const QDate &aDate)
{
    mDate=aDate;
}

void TestObject::setTime(const QTime &aTime)
{
    mTime=aTime;
}

void TestObject::setDateTime(const QDateTime &aDateTime)
{
    mDateTime=aDateTime;
}

void TestObject::setUrl(const QUrl &aUrl)
{
    mUrl=aUrl;
}

void TestObject::setLocale(const QLocale &aLocale)
{
    mLocale=aLocale;
}

void TestObject::setRect(const QRect &aRect)
{
    mRect=aRect;
}

void TestObject::setRectF(const QRectF &aRectF)
{
    mRectF=aRectF;
}

void TestObject::setSize(const QSize &aSize)
{
    mSize=aSize;
}

void TestObject::setSizeF(const QSizeF &aSizeF)
{
    mSizeF=aSizeF;
}

void TestObject::setLine(const QLine &aLine)
{
    mLine=aLine;
}

void TestObject::setLineF(const QLineF &aLineF)
{
    mLineF=aLineF;
}

void TestObject::setPoint(const QPoint &aPoint)
{
    mPoint=aPoint;
}

void TestObject::setPointF(const QPointF &aPointF)
{
    mPointF=aPointF;
}

void TestObject::setRegExp(const QRegExp &aRegExp)
{
    mRegExp=aRegExp;
}

void TestObject::setHash(const QVariantHash &aHash)
{
    mHash.clear();

    for (QVariantHash::const_iterator i=aHash.constBegin(); i!=aHash.constEnd(); ++i)
    {
        bool ok;

        qint16 aValue=i.value().toInt(&ok);

        if (ok)
        {
            mHash[i.key()]=aValue;
        }
    }
}

void TestObject::setEasingCurve(const QEasingCurve &aEasingCurve)
{
    mEasingCurve=aEasingCurve;
}

void TestObject::setFont(const QFont &aFont)
{
    mFont=aFont;
}

void TestObject::setPixmap(const QPixmap &aPixmap)
{
    mPixmap=aPixmap;
}

void TestObject::setBrush(const QBrush &aBrush)
{
    mBrush=aBrush;
}

void TestObject::setColor(const QColor &aColor)
{
    mColor=aColor;
}

void TestObject::setPalette(const QPalette &aPalette)
{
    mPalette=aPalette;
}

void TestObject::setIcon(const QIcon &aIcon)
{
    mIcon=aIcon;
}

void TestObject::setImage(const QImage &aImage)
{
    mImage=aImage;
}

void TestObject::setPolygon(const QPolygon &aPolygon)
{
    mPolygon=aPolygon;
}

void TestObject::setRegion(const QRegion &aRegion)
{
    mRegion=aRegion;
}

void TestObject::setBitmap(const QBitmap &aBitmap)
{
    mBitmap=aBitmap;
}

void TestObject::setCursor(const QCursor &aCursor)
{
    mCursor=aCursor;
}

void TestObject::setSizePolicy(const QSizePolicy &aSizePolicy)
{
    mSizePolicy=aSizePolicy;
}

void TestObject::setKeySequence(const QKeySequence &aKeySequence)
{
    mKeySequence=aKeySequence;
}

void TestObject::setPen(const QPen &aPen)
{
    mPen=aPen;
}

void TestObject::setTextLength(const QTextLength &aTextLength)
{
    mTextLength=aTextLength;
}

void TestObject::setTextFormat(const QTextFormat &aTextFormat)
{
    mTextFormat=aTextFormat;
}

void TestObject::setMatrix(const QMatrix &aMatrix)
{
    mMatrix=aMatrix;
}

void TestObject::setTransform(const QTransform &aTransform)
{
    mTransform=aTransform;
}

void TestObject::setMatrix4x4(const QMatrix4x4 &aMatrix4x4)
{
    mMatrix4x4=aMatrix4x4;
}

void TestObject::setVector2D(const QVector2D &aVector2D)
{
    mVector2D=aVector2D;
}

void TestObject::setVector3D(const QVector3D &aVector3D)
{
    mVector3D=aVector3D;
}

void TestObject::setVector4D(const QVector4D &aVector4D)
{
    mVector4D=aVector4D;
}

void TestObject::setQuaternion(const QQuaternion &aQuaternion)
{
    mQuaternion=aQuaternion;
}
