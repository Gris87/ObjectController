#ifndef STRINGFRAME_H
#define STRINGFRAME_H

#include <QWidget>

#include "../propertyattributes.h"

namespace Ui {
    class StringFrame;
}

class StringFrame : public QWidget
{
    Q_OBJECT

public:
    explicit StringFrame(QWidget *parent = 0);
    explicit StringFrame(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~StringFrame();

    void setDelEnabled(bool aEnabled);
    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    QString value() const;
    void setValue(const QString &aValue);

private:
    Ui::StringFrame *ui;

    void init(const PropertyAttributes *aAttributes);

signals:
    void deletePressed();
    void upPressed();
    void downPressed();

private slots:
    void on_downToolButton_clicked();
    void on_upToolButton_clicked();
    void on_delToolButton_clicked();
};

#endif // STRINGFRAME_H
