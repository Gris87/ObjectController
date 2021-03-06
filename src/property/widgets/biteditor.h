#ifndef BITEDITOR_H
#define BITEDITOR_H

#include <QAbstractScrollArea>

#include <QUndoCommand>
#include <QTimer>
#include <QBitArray>

class BitEditor : public QAbstractScrollArea
{
    Q_OBJECT

    friend class MultipleBitUndoCommand;

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
    int charAt(QPoint aPos, bool *aAtLeftPart=0);
    int indexOf(const QBitArray &aArray, int aFrom=0) const;
    int indexOf(const bool &aBool, int aFrom=0) const;
    int lastIndexOf(const QBitArray &aArray, int aFrom=0) const;
    int lastIndexOf(const bool &aBool, int aFrom=0) const;
    void insert(int aIndex, bool aBool);
    void insert(int aIndex, const QBitArray &aArray);
    void remove(int aPos, int aLength=1);
    void replace(int aPos, bool aBool);
    void replace(int aPos, const QBitArray &aArray);
    void replace(int aPos, int aLength, const QBitArray &aArray);
    void setSelection(int aPos, int aCount);
    void cut();
    void copy();
    void paste();
    QString toString();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

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

// *********************************************************************************

class MultipleBitUndoCommand : public QUndoCommand
{
public:
    enum Type
    {
        Insert,
        Remove,
        Replace
    };

    MultipleBitUndoCommand(BitEditor *aEditor, Type aType, int aPos, int aLength, QBitArray aNewArray=QBitArray(), QUndoCommand *parent=0);

    void insert(int aIndex, const QBitArray &aArray);
    void replace(int aPos, int aLength, const QBitArray &aArray);
    void remove(int aPos, int aLength=1);
    QBitArray mid(int aPos, int aLength=-1);

    void undo();
    void redo();

private:
    BitEditor *mEditor;
    Type       mType;
    int        mPos;
    int        mLength;
    QBitArray  mNewArray;
    QBitArray  mOldArray;
    qint64     mPrevPosition;
};

#endif // BITEDITOR_H
