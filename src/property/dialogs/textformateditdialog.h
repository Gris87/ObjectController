#ifndef TEXTFORMATEDITDIALOG_H
#define TEXTFORMATEDITDIALOG_H

#include <QDialog>

#include <QTextFormat>
#include <QLabel>
#include <QSplitter>
#include <QToolButton>

#include "../widgets/colorarea.h"

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

    ColorArea                *mCharUnderlineColorArea;

    void copyFromTextFormat(QTextFormat aTextFormat);
    void blockUpdateProperties();
    void charUpdateProperties();
    void updateProperties();

    void drawBrush(const QBrush &aBrush, QLabel *aIconLabel);
    void drawBackgroundBrush();
    void drawForegroundBrush();
    void charDrawTextOutlinePen();

    inline void showOrHideCategory(QWidget *aCategory, QToolButton *aButton);

    void blockSetLineHeight(const double &aHeight, const QString &aType);
    void blockSetAlignment(const QString &aHorizontal, const QString &aVertical);
    void blockUpdateTabPositions();
    void blockAddTabPosition();

private slots:
    void hideCategories();

    void blockTabPositionUp();
    void blockTabPositionDown();
    void blockTabPositionDelete();
    void blockTabPositionChanged();

    void on_okButton_clicked();
    void on_cancelButton_clicked();

    // GENERAL
    void on_typeComboBox_currentIndexChanged(const QString &aValue);
    void on_backgroundButton_clicked();
    void on_foregroundButton_clicked();
    void on_layoutDirectionComboBox_currentIndexChanged(const QString &aValue);
    void on_objectIndexSpinBox_valueChanged(int aValue);

    // BLOCK
    void on_blockAlignmentButton_clicked();
    void on_blockMarginsButton_clicked();
    void on_blockIndentationButton_clicked();
    void on_blockLineHeightButton_clicked();
    void on_blockPageBreakButton_clicked();
    void on_blockTabPositionsButton_clicked();

    void on_blockHorizontalAlignmentComboBox_currentIndexChanged(const QString &aValue);
    void on_blockVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue);
    void on_blockTopMarginSpinBox_valueChanged(double aValue);
    void on_blockBottomMarginSpinBox_valueChanged(double aValue);
    void on_blockLeftMarginSpinBox_valueChanged(double aValue);
    void on_blockRightMarginSpinBox_valueChanged(double aValue);
    void on_blockTextIndentSpinBox_valueChanged(double aValue);
    void on_blockIndentSpinBox_valueChanged(int aValue);
    void on_blockLineHeightSpinBox_valueChanged(double aValue);
    void on_blockLineHeightTypeComboBox_currentIndexChanged(const QString &aValue);
    void on_blockNonBreakableLinesCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyAutoCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyBeforeCheckBox_toggled(bool checked);
    void on_blockPageBreakPolicyAfterCheckBox_toggled(bool checked);
    void on_blockTabPositionsAddButton_clicked();

    // CHAR
    void on_charFontCategoryButton_clicked();
    void on_charSpacingButton_clicked();
    void on_charStyleButton_clicked();
    void on_charAnchorButton_clicked();
    void on_charOthersButton_clicked();
    void on_charFontButton_clicked();
    void on_charFontFamilyEdit_textEdited(const QString &aValue);
    void on_charFontPointSizeSpinBox_valueChanged(double aValue);
    void on_charFontWeightSpinBox_valueChanged(int aValue);
    void on_charFontItalicCheckBox_toggled(bool checked);
    void on_charFontFixedPitchCheckBox_toggled(bool checked);
    void on_charFontStrikeOutCheckBox_toggled(bool checked);
    void on_charFontKerningCheckBox_toggled(bool checked);
    void on_charFontOverlineCheckBox_toggled(bool checked);
    void on_charFontUnderlineCheckBox_toggled(bool checked);
    void on_charUnderlineStyleComboBox_currentIndexChanged(const QString &aValue);
    void charUnderlineColorChanged(QColor aValue);
    void on_charFontLetterSpacingSpinBox_valueChanged(double aValue);
    void on_charFontWordSpacingSpinBox_valueChanged(double aValue);
    void on_charFontStyleHintComboBox_currentIndexChanged(const QString &aValue);
    void on_charFontStyleStrategyComboBox_currentIndexChanged(const QString &aValue);
    void on_charFontStyleStrategyFlagComboBox_currentIndexChanged(const QString &aValue);
    void on_charAnchorCheckBox_toggled(bool checked);
    void on_charAnchorHrefLineEdit_textEdited(const QString &aValue);
    void on_charAnchorNamesButton_clicked();
    void on_charFontCapitalizationComboBox_currentIndexChanged(const QString &aValue);
    void on_charFontHintingPreferenceComboBox_currentIndexChanged(const QString &aValue);
    void on_charVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue);
    void on_charTextOutlineButton_clicked();
    void on_charTooltipEdit_textEdited(const QString &aValue);
};

#endif // TEXTFORMATEDITDIALOG_H
