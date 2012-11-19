#ifndef TABFRAME_H
#define TABFRAME_H

#include <QWidget>

#include <QTextOption>

namespace Ui {
    class TabFrame;
}

class TabFrame : public QWidget
{
    Q_OBJECT

public:
    explicit TabFrame(QWidget *parent = 0);
    ~TabFrame();

    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    qreal position() const;
    void setPosition(const qreal &aPosition);

    QTextOption::TabType type() const;
    void setType(const QTextOption::TabType &aType);

    QChar delimiter() const;
    void setDelimiter(const QChar &aDelimiter);

    QTextOption::Tab tab() const;
    void setTab(const QTextOption::Tab &aTab);

private:
    Ui::TabFrame *ui;

signals:
    void deletePressed();
    void upPressed();
    void downPressed();
    void tabChanged();

private slots:
    void on_downToolButton_clicked();
    void on_upToolButton_clicked();
    void on_delToolButton_clicked();
    void on_positionSpinBox_valueChanged(double aValue);
    void on_typeComboBox_currentIndexChanged(const QString &aValue);
    void on_delimiterEdit_textEdited(const QString &aValue);
};

#endif // TABFRAME_H
