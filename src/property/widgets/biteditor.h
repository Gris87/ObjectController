#ifndef BITEDITOR_H
#define BITEDITOR_H

#include <QAbstractScrollArea>

#include <QUndoCommand>
#include <QTimer>
#include <QBitArray>

class BitEditor : public QAbstractScrollArea
{
    Q_OBJECT

public:
    Q_PROPERTY(QBitArray    Data                     READ data                     WRITE setData)
    Q_PROPERTY(Mode         Mode                     READ mode                     WRITE setMode)
    Q_PROPERTY(bool         ReadOnly                 READ isReadOnly               WRITE setReadOnly)
    Q_PROPERTY(qint64       Position                 READ position                 WRITE setPosition)
    Q_PROPERTY(int          CursorPosition           READ cursorPosition           WRITE setCursorPosition)
    Q_PROPERTY(QFont        Font                     READ font                     WRITE setFont)

    Q_PROPERTY(int      charWidth      READ charWidth)
    Q_PROPERTY(int      charHeight     READ charHeight)
    Q_PROPERTY(quint8   addressWidth   READ addressWidth)
    Q_PROPERTY(int      linesCount     READ linesCount)

    Q_PROPERTY(int    SelectionStart    READ selectionStart)
    Q_PROPERTY(int    SelectionEnd      READ selectionEnd)
    Q_PROPERTY(bool   CursorAtTheLeft   READ isCursorAtTheLeft)

    Q_ENUMS(Mode)

    enum Mode
    {
        INSERT,
        OVERWRITE
    };



    BitEditor(QWidget *parent = 0);



    void scrollToCursor();

    // ------------------------------------------------------------------

    QBitArray data() const;
    void setData(QBitArray const &aData);

    Mode mode() const;
    void setMode(const Mode &aMode);

    bool isReadOnly() const;
    void setReadOnly(const bool &aReadOnly);

    int position() const;
    void setPosition(int aPosition);

    qint64 cursorPosition() const;
    void setCursorPosition(qint64 aCursorPos);

    QFont font() const;
    void setFont(const QFont &aFont);

    int    charWidth();
    int    charHeight();
    quint8 addressWidth();
    int    linesCount();

    int  selectionStart();
    int  selectionEnd();
    bool isCursorAtTheLeft();

protected:
    QBitArray  mData;
    Mode       mMode;
    bool       mReadOnly;
    qint64     mCursorPosition;
    QFont      mFont;

    QString    mAsciiChars;
    int        mCharWidth;
    int        mCharHeight;
    quint8     mAddressWidth;
    int        mLinesCount;

    int        mSelectionStart;
    int        mSelectionEnd;
    int        mSelectionInit;
    bool       mCursorVisible;
    bool       mCursorAtTheLeft;
    QTimer     mCursorTimer;

    bool       mLeftButtonPressed;
    bool       mOneMoreSelection;

    QUndoStack mUndoStack;

    void updateScrollBars();
    void resetCursorTimer();
    void resetSelection();
    void updateSelection();
    void cursorMoved(bool aKeepSelection);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void undo();
    void redo();

protected slots:
    void cursorBlicking();

signals:
    void dataChanged();
    void selectionChanged(int aStart, int aEnd);
    void modeChanged(Mode aMode);
    void positionChanged(int aPosition);
};

#endif // BITEDITOR_H
