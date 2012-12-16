#ifndef TEXTLENGTHFRAME_H
#define TEXTLENGTHFRAME_H

#include <QWidget>

#include <QTextLength>

#include "../propertyattributes.h"

namespace Ui {
    class TextLengthFrame;
}

class TextLengthFrame : public QWidget
{
    Q_OBJECT

public:
    explicit TextLengthFrame(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~TextLengthFrame();

    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    QTextLength value() const;
    void setValue(const QTextLength &aValue);

private:
    Ui::TextLengthFrame *ui;
    QTextLength          mTextLength;
    const PropertyAttributes *mAttributes;
    int mDecimals;

signals:
    void deletePressed();
    void upPressed();
    void downPressed();
    void textLengthChanged();

private slots:
    void on_downToolButton_clicked();
    void on_upToolButton_clicked();
    void on_delToolButton_clicked();
    void on_editButton_clicked();
};

#endif // TEXTLENGTHFRAME_H
