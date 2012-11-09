#ifndef POINTFRAME_H
#define POINTFRAME_H

#include <QWidget>

namespace Ui {
    class PointFrame;
}

class PointFrame : public QWidget
{
    Q_OBJECT

public:
    explicit PointFrame(QWidget *parent = 0);
    ~PointFrame();

    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    QPoint value() const;
    void setValue(const QPoint &aValue);

private:
    Ui::PointFrame *ui;
    QPoint          mPoint;

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

#endif // POINTFRAME_H
