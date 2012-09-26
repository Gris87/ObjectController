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
    explicit TestObject(QObject *parent = 0);

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
};

#endif // TESTOBJECT_H
