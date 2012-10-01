#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include <QWidget>

#define SET_ICON(aIcon) \
    if (aIcon.isNull()) \
    { \
        ui->iconLabel->setVisible(false); \
        ui->dataLayout->setContentsMargins(0, 0, 0, 0); \
    } \
    else \
    { \
        ui->iconLabel->setPixmap(aIcon.pixmap(18)); \
    }

class CustomEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CustomEditor(QWidget *parent = 0);

    virtual void setIcon(const QIcon &aIcon);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

    virtual void putFocus();
    virtual void selectText();

private slots:
    void selectSlot();
};

#endif // CUSTOMEDITOR_H
