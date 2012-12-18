#ifndef RECTFRAME_H
#define RECTFRAME_H

#include <QWidget>

#include "../propertyattributes.h"

namespace Ui {
    class RectFrame;
}

class RectFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RectFrame(QWidget *parent = 0);
    explicit RectFrame(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~RectFrame();

    void setDelEnabled(bool aEnabled);
    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    QRect value() const;
    void setValue(const QRect &aValue);

private:
    Ui::RectFrame *ui;
    QRect          mRect;
    const PropertyAttributes *mAttributes;

    void init(const PropertyAttributes *aAttributes);

signals:
    void deletePressed();
    void upPressed();
    void downPressed();

private slots:
    void on_downToolButton_clicked();
    void on_upToolButton_clicked();
    void on_delToolButton_clicked();
    void on_editButton_clicked();
};

#endif // RECTFRAME_H
