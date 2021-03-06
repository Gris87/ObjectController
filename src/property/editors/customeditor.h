#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include <QWidget>

#include <QVariant>
#include <QTimer>

#include "../propertyattributes.h"

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
    ~CustomEditor();

    virtual void setIcon(const QIcon &aIcon);
    virtual void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    bool mCanEmitValueChangedSignal;
    int mDelay;
    QTimer mModificationTimer;
    QVariant mNewValue;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

    virtual void putFocus();
    virtual void selectText();
    void modificationDone(const QVariant &aNewValue);

private slots:
    void modificationSlot();
    void afterCreatingSlot();

signals:
    void valueChanged(const QVariant &aNewValue);
};

#endif // CUSTOMEDITOR_H
