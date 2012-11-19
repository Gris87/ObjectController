#ifndef TEXTFORMATEDITDIALOG_H
#define TEXTFORMATEDITDIALOG_H

#include <QDialog>

#include <QTextFormat>
#include <QLabel>
#include <QSplitter>

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
    QSplitter                *mDividerSplitter;
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

    void blockSetLineHeight(const double &aHeight, const QString &aType);
    void blockSetAlignment(const QString &aHorizontal, const QString &aVertical);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_typeComboBox_currentIndexChanged(const QString &aValue);
    void on_backgroundButton_clicked();
    void on_foregroundButton_clicked();
    void on_layoutDirectionComboBox_currentIndexChanged(const QString &aValue);
    void on_objectIndexSpinBox_valueChanged(int aValue);
    void on_blockNonBreakableLinesCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyAutoCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyBeforeCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyAfterCheckBox_toggled(bool checked);
    void on_blockLineHeightSpinBox_valueChanged(double aValue);
    void on_blockLineHeightTypeComboBox_currentIndexChanged(const QString &aValue);
    void on_blockHorizontalAlignmentComboBox_currentIndexChanged(const QString &aValue);
    void on_blockVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue);
    void on_blockIndentSpinBox_valueChanged(int aValue);
    void on_blockTextIndentSpinBox_valueChanged(double aValue);
    void on_blockLeftMarginSpinBox_valueChanged(double aValue);
    void on_blockTopMarginSpinBox_valueChanged(double aValue);
    void on_blockRightMarginSpinBox_valueChanged(double aValue);
    void on_blockBottomMarginSpinBox_valueChanged(double aValue);
};

#endif // TEXTFORMATEDITDIALOG_H
