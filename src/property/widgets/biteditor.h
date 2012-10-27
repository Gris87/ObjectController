#ifndef BITEDITOR_H
#define BITEDITOR_H

#include <QAbstractScrollArea>

class BitEditor : public QAbstractScrollArea
{
    Q_OBJECT

public:
    Q_ENUMS(Mode)

    enum Mode
    {
        INSERT,
        OVERWRITE
    };



    BitEditor(QWidget *parent = 0);
};

#endif // BITEDITOR_H
