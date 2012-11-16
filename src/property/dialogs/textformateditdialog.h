#ifndef TEXTFORMATEDITDIALOG_H
#define TEXTFORMATEDITDIALOG_H

#include <QDialog>

#include <QTextFormat>
#include <QLabel>

namespace Ui {
class TextFormatEditDialog;
}

class TextFormatEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent = 0);
    ~TextFormatEditDialog();

    QTextFormat resultValue() const;

private:
    Ui::TextFormatEditDialog *ui;
    QTextFormat               mTextFormat;
    QTextBlockFormat          mTextBlockFormat;
    QTextCharFormat           mTextCharFormat;
    QTextFrameFormat          mTextFrameFormat;
    QTextImageFormat          mTextImageFormat;
    QTextListFormat           mTextListFormat;
    QTextTableCellFormat      mTextTableCellFormat;
    QTextTableFormat          mTextTableFormat;

    void copyFromTextFormat(QTextFormat aTextFormat);
    void updateProperties();
    void drawBackgroundBrush();
    void drawForegroundBrush();
    void drawBrush(const QBrush &aBrush, QLabel *aIconLabel);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_typeComboBox_currentIndexChanged(const QString &aValue);
    void on_backgroundButton_clicked();
    void on_foregroundButton_clicked();
    void on_layoutDirectionComboBox_currentIndexChanged(const QString &aValue);
    void on_objectIndexSpinBox_valueChanged(int aValue);
};

#endif // TEXTFORMATEDITDIALOG_H
