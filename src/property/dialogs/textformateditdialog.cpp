#include "textformateditdialog.h"
#include "ui_textformateditdialog.h"

#include "brusheditdialog.h"

TextFormatEditDialog::TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextFormatEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mDividerSplitter = new QSplitter(Qt::Horizontal, this);
    ui->dividerLayout->removeWidget(ui->generalWidget);
    ui->dividerLayout->removeWidget(ui->typeStackedWidget);

    mDividerSplitter->addWidget(ui->generalWidget);
    mDividerSplitter->addWidget(ui->typeStackedWidget);
    mDividerSplitter->setChildrenCollapsible(false);

    ui->dividerLayout->addWidget(mDividerSplitter);

    mTextFormat=aTextFormat;

    if (mTextFormat.isImageFormat())
    {
        mTextImageFormat=mTextFormat.toImageFormat();
    }
    else
    if (mTextFormat.isTableCellFormat())
    {
        mTextTableCellFormat=mTextFormat.toTableCellFormat();
    }
    else
    if (mTextFormat.isTableFormat())
    {
        mTextTableFormat=mTextFormat.toTableFormat();
    }
    else
    if (mTextFormat.isBlockFormat())
    {
        mTextBlockFormat=mTextFormat.toBlockFormat();
    }
    else
    if (mTextFormat.isCharFormat())
    {
        mTextCharFormat=mTextFormat.toCharFormat();
    }
    else
    if (mTextFormat.isFrameFormat())
    {
        mTextFrameFormat=mTextFormat.toFrameFormat();
    }
    else
    if (mTextFormat.isListFormat())
    {
        mTextListFormat=mTextFormat.toListFormat();
    }
    else
    {
        Q_ASSERT(false);
    }

    // TODO: Create ideal editor that allow to modify any property according to it's type

    updateProperties();

    drawBackgroundBrush();
    drawForegroundBrush();
}

TextFormatEditDialog::~TextFormatEditDialog()
{
    delete ui;
}

QTextFormat TextFormatEditDialog::resultValue() const
{
    return mTextFormat;
}

void TextFormatEditDialog::drawBackgroundBrush()
{
    drawBrush(mTextFormat.background(), ui->backgroundIconLabel);
}

void TextFormatEditDialog::drawForegroundBrush()
{
    drawBrush(mTextFormat.foreground(), ui->foregroundIconLabel);
}

void TextFormatEditDialog::drawBrush(const QBrush &aBrush, QLabel *aIconLabel)
{
    int aWidth=32;
    int aHeight=32;

    QPixmap aPixmap(aWidth, aHeight);
    aPixmap.fill(QColor(255, 255, 255));

    QPainter aPainter(&aPixmap);
    aPainter.fillRect(0, 0, aWidth, aHeight, aBrush);
    aPainter.end();

    aIconLabel->setPixmap(QIcon(aPixmap).pixmap(18, 18));
}

void TextFormatEditDialog::on_okButton_clicked()
{
    accept();
}

void TextFormatEditDialog::on_cancelButton_clicked()
{
    reject();
}

void TextFormatEditDialog::on_typeComboBox_currentIndexChanged(const QString &aValue)
{
    if (aValue=="BlockFormat")
    {
        copyFromTextFormat(mTextBlockFormat);
    }
    else
    if (aValue=="CharFormat")
    {
        copyFromTextFormat(mTextCharFormat);
    }
    else
    if (aValue=="FrameFormat")
    {
        copyFromTextFormat(mTextFrameFormat);
    }
    else
    if (aValue=="ImageFormat")
    {
        copyFromTextFormat(mTextImageFormat);
    }
    else
    if (aValue=="ListFormat")
    {
        copyFromTextFormat(mTextListFormat);
    }
    else
    if (aValue=="TableCellFormat")
    {
        copyFromTextFormat(mTextTableCellFormat);
    }
    else
    if (aValue=="TableFormat")
    {
        copyFromTextFormat(mTextTableFormat);
    }
    else
    {
        Q_ASSERT(false);
    }

    updateProperties();
}

void TextFormatEditDialog::on_backgroundButton_clicked()
{
    BrushEditDialog dialog(mTextFormat.background(), this);

    if (dialog.exec())
    {
        mTextFormat.setBackground(dialog.resultValue());
        drawBackgroundBrush();
    }
}

void TextFormatEditDialog::on_foregroundButton_clicked()
{
    BrushEditDialog dialog(mTextFormat.foreground(), this);

    if (dialog.exec())
    {
        mTextFormat.setForeground(dialog.resultValue());
        drawForegroundBrush();
    }
}

void TextFormatEditDialog::on_layoutDirectionComboBox_currentIndexChanged(const QString &aValue)
{
    if (aValue=="LeftToRight")
    {
        mTextFormat.setLayoutDirection(Qt::LeftToRight);
    }
    else
    if (aValue=="RightToLeft")
    {
        mTextFormat.setLayoutDirection(Qt::RightToLeft);
    }
    else
    if (aValue=="LayoutDirectionAuto")
    {
        mTextFormat.setLayoutDirection(Qt::LayoutDirectionAuto);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void TextFormatEditDialog::on_objectIndexSpinBox_valueChanged(int aValue)
{
    mTextFormat.setObjectIndex(aValue);
}

void TextFormatEditDialog::on_blockNonBreakableLinesCheckBox_toggled(bool checked)
{
    mTextBlockFormat.setNonBreakableLines(checked);
    ((QTextBlockFormat *)&mTextFormat)->setNonBreakableLines(checked);
}

void TextFormatEditDialog::on_blockPageBreakPolicyAutoCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->blockPageBreakPolicyBeforeCheckBox->blockSignals(true);
        ui->blockPageBreakPolicyAfterCheckBox->blockSignals(true);

        ui->blockPageBreakPolicyBeforeCheckBox->setChecked(false);
        ui->blockPageBreakPolicyAfterCheckBox->setChecked(false);

        ui->blockPageBreakPolicyBeforeCheckBox->blockSignals(false);
        ui->blockPageBreakPolicyAfterCheckBox->blockSignals(false);

        mTextBlockFormat.setPageBreakPolicy(QTextFormat::PageBreak_Auto);
        ((QTextBlockFormat *)&mTextFormat)->setPageBreakPolicy(QTextFormat::PageBreak_Auto);
    }
    else
    {
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->blockPageBreakPolicyAutoCheckBox->setChecked(true);
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);
    }
}

void TextFormatEditDialog::on_blockPageBreakPolicyBeforeCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->blockPageBreakPolicyAutoCheckBox->setChecked(false);
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);

        mTextBlockFormat.setPageBreakPolicy(mTextBlockFormat.pageBreakPolicy() | QTextFormat::PageBreak_AlwaysBefore);
        ((QTextBlockFormat *)&mTextFormat)->setPageBreakPolicy(((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysBefore);
    }
    else
    {
        if (!ui->blockPageBreakPolicyAfterCheckBox->isChecked())
        {
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->blockPageBreakPolicyAutoCheckBox->setChecked(true);
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        mTextBlockFormat.setPageBreakPolicy(mTextBlockFormat.pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysBefore);
        ((QTextBlockFormat *)&mTextFormat)->setPageBreakPolicy(((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysBefore);
    }
}

void TextFormatEditDialog::on_blockPageBreakPolicyAfterCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->blockPageBreakPolicyAutoCheckBox->setChecked(false);
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);

        mTextBlockFormat.setPageBreakPolicy(mTextBlockFormat.pageBreakPolicy() | QTextFormat::PageBreak_AlwaysAfter);
        ((QTextBlockFormat *)&mTextFormat)->setPageBreakPolicy(((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysAfter);
    }
    else
    {
        if (!ui->blockPageBreakPolicyBeforeCheckBox->isChecked())
        {
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->blockPageBreakPolicyAutoCheckBox->setChecked(true);
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        mTextBlockFormat.setPageBreakPolicy(mTextBlockFormat.pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysAfter);
        ((QTextBlockFormat *)&mTextFormat)->setPageBreakPolicy(((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysAfter);
    }
}

void TextFormatEditDialog::blockSetLineHeight(const double &aHeight, const QString &aType)
{
    QTextBlockFormat::LineHeightTypes aHeightType=QTextBlockFormat::SingleHeight;

    if (aType=="SingleHeight")
    {
        aHeightType=QTextBlockFormat::SingleHeight;
    }
    else
    if (aType=="ProportionalHeight")
    {
        aHeightType=QTextBlockFormat::ProportionalHeight;
    }
    else
    if (aType=="FixedHeight")
    {
        aHeightType=QTextBlockFormat::FixedHeight;
    }
    else
    if (aType=="MinimumHeight")
    {
        aHeightType=QTextBlockFormat::MinimumHeight;
    }
    else
    if (aType=="LineDistanceHeight")
    {
        aHeightType=QTextBlockFormat::LineDistanceHeight;
    }
    else
    {
        Q_ASSERT(false);
    }

    mTextBlockFormat.setLineHeight(aHeight, aHeightType);
    ((QTextBlockFormat *)&mTextFormat)->setLineHeight(aHeight, aHeightType);
}

void TextFormatEditDialog::on_blockLineHeightSpinBox_valueChanged(double aValue)
{
    blockSetLineHeight(aValue, ui->blockLineHeightTypeComboBox->currentText());
}

void TextFormatEditDialog::on_blockLineHeightTypeComboBox_currentIndexChanged(const QString &aValue)
{
    blockSetLineHeight(ui->blockLineHeightSpinBox->value(), aValue);
}

void TextFormatEditDialog::blockSetAlignment(const QString &aHorizontal, const QString &aVertical)
{
    Qt::Alignment aHorizontalAlignment=Qt::AlignLeft;
    Qt::Alignment aVerticalAlignment=Qt::AlignTop;

    if (aHorizontal=="AlignHCenter")
    {
        aHorizontalAlignment=Qt::AlignHCenter;
    }
    else
    if (aHorizontal=="AlignRight")
    {
        aHorizontalAlignment=Qt::AlignRight;
    }
    else
    if (aHorizontal=="AlignJustify")
    {
        aHorizontalAlignment=Qt::AlignJustify;
    }
    else
    if (aHorizontal=="AlignAbsolute")
    {
        aHorizontalAlignment=Qt::AlignAbsolute;
    }

    if (aVertical=="AlignVCenter")
    {
        aVerticalAlignment=Qt::AlignVCenter;
    }
    else
    if (aVertical=="AlignBottom")
    {
        aVerticalAlignment=Qt::AlignBottom;
    }

    mTextBlockFormat.setAlignment(aHorizontalAlignment | aVerticalAlignment);
    ((QTextBlockFormat *)&mTextFormat)->setAlignment(aHorizontalAlignment | aVerticalAlignment);
}

void TextFormatEditDialog::on_blockHorizontalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{
    blockSetAlignment(aValue, ui->blockVerticalAlignmentComboBox->currentText());
}

void TextFormatEditDialog::on_blockVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{
    blockSetAlignment(ui->blockHorizontalAlignmentComboBox->currentText(), aValue);
}

void TextFormatEditDialog::on_blockIndentSpinBox_valueChanged(int aValue)
{
    mTextBlockFormat.setIndent(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setIndent(aValue);
}

void TextFormatEditDialog::on_blockTextIndentSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setTextIndent(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setTextIndent(aValue);
}

void TextFormatEditDialog::on_blockLeftMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setLeftMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setLeftMargin(aValue);
}

void TextFormatEditDialog::on_blockTopMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setTopMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setTopMargin(aValue);
}

void TextFormatEditDialog::on_blockRightMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setRightMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setRightMargin(aValue);
}

void TextFormatEditDialog::on_blockBottomMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setBottomMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setBottomMargin(aValue);
}

void TextFormatEditDialog::copyFromTextFormat(QTextFormat aTextFormat)
{
    aTextFormat.setBackground(mTextFormat.background());
    aTextFormat.setForeground(mTextFormat.foreground());
    aTextFormat.setLayoutDirection(mTextFormat.layoutDirection());
    aTextFormat.setObjectIndex(mTextFormat.objectIndex());

    mTextFormat=aTextFormat;
}

#define BLOCK_SIGNALS(aLock) \
    ui->typeComboBox->blockSignals(aLock); \
    ui->layoutDirectionComboBox->blockSignals(aLock); \
    ui->objectIndexSpinBox->blockSignals(aLock); \
    ui->blockNonBreakableLinesCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyAutoCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyBeforeCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyAfterCheckBox->blockSignals(aLock); \
    ui->blockLineHeightSpinBox->blockSignals(aLock); \
    ui->blockLineHeightTypeComboBox->blockSignals(aLock); \
    ui->blockHorizontalAlignmentComboBox->blockSignals(aLock); \
    ui->blockVerticalAlignmentComboBox->blockSignals(aLock); \
    ui->blockIndentSpinBox->blockSignals(aLock); \
    ui->blockTextIndentSpinBox->blockSignals(aLock); \
    ui->blockLeftMarginSpinBox->blockSignals(aLock); \
    ui->blockTopMarginSpinBox->blockSignals(aLock); \
    ui->blockRightMarginSpinBox->blockSignals(aLock); \
    ui->blockBottomMarginSpinBox->blockSignals(aLock);

void TextFormatEditDialog::updateProperties()
{
    BLOCK_SIGNALS(true);

    QString aTypeStr;

    if (mTextFormat.isImageFormat())
    {
        aTypeStr="ImageFormat";
    }
    else
    if (mTextFormat.isTableCellFormat())
    {
        aTypeStr="TableCellFormat";
    }
    else
    if (mTextFormat.isTableFormat())
    {
        aTypeStr="TableFormat";
    }
    else
    if (mTextFormat.isBlockFormat())
    {
        aTypeStr="BlockFormat";
    }
    else
    if (mTextFormat.isCharFormat())
    {
        aTypeStr="CharFormat";
    }
    else
    if (mTextFormat.isFrameFormat())
    {
        aTypeStr="FrameFormat";
    }
    else
    if (mTextFormat.isListFormat())
    {
        aTypeStr="ListFormat";
    }
    else
    {
        Q_ASSERT(false);
    }

    Qt::LayoutDirection aDirection=mTextFormat.layoutDirection();
    QString aLayoutDirectionStr;

    if (aDirection==Qt::LeftToRight)
    {
        aLayoutDirectionStr="LeftToRight";
    }
    else
    if (aDirection==Qt::RightToLeft)
    {
        aLayoutDirectionStr="RightToLeft";
    }
    else
    if (aDirection==Qt::LayoutDirectionAuto)
    {
        aLayoutDirectionStr="LayoutDirectionAuto";
    }
    else
    {
        Q_ASSERT(false);
    }

    QTextFormat::PageBreakFlags aBlockPageBreaks=mTextBlockFormat.pageBreakPolicy();

    Qt::Alignment aBlockAlignment=mTextBlockFormat.alignment();
    QString aBlockHorizontalAlignment="AlignLeft";
    QString aBlockVerticalAlignment="AlignTop";

    if (aBlockAlignment & Qt::AlignHCenter)
    {
        aBlockHorizontalAlignment="AlignHCenter";
    }
    else
    if (aBlockAlignment & Qt::AlignRight)
    {
        aBlockHorizontalAlignment="AlignRight";
    }
    else
    if (aBlockAlignment & Qt::AlignJustify)
    {
        aBlockHorizontalAlignment="AlignJustify";
    }
    else
    if (aBlockAlignment & Qt::AlignAbsolute)
    {
        aBlockHorizontalAlignment="AlignAbsolute";
    }

    if (aBlockAlignment & Qt::AlignVCenter)
    {
        aBlockVerticalAlignment="AlignVCenter";
    }
    else
    if (aBlockAlignment & Qt::AlignBottom)
    {
        aBlockVerticalAlignment="AlignBottom";
    }

    int aBlockLineHeightType=mTextBlockFormat.lineHeightType();
    QString aBlockLineHeightTypeStr;

    if (aBlockLineHeightType==QTextBlockFormat::SingleHeight)
    {
        aBlockLineHeightTypeStr="SingleHeight";
    }
    else
    if (aBlockLineHeightType==QTextBlockFormat::ProportionalHeight)
    {
        aBlockLineHeightTypeStr="ProportionalHeight";
    }
    else
    if (aBlockLineHeightType==QTextBlockFormat::FixedHeight)
    {
        aBlockLineHeightTypeStr="FixedHeight";
    }
    else
    if (aBlockLineHeightType==QTextBlockFormat::MinimumHeight)
    {
        aBlockLineHeightTypeStr="MinimumHeight";
    }
    else
    if (aBlockLineHeightType==QTextBlockFormat::LineDistanceHeight)
    {
        aBlockLineHeightTypeStr="LineDistanceHeight";
    }
    else
    {
        Q_ASSERT(false);
    }



    // GENERAL
    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aTypeStr));
    ui->layoutDirectionComboBox->setCurrentIndex(ui->layoutDirectionComboBox->findText(aLayoutDirectionStr));
    ui->objectIndexSpinBox->setValue(mTextFormat.objectIndex());
    ui->typeStackedWidget->setCurrentIndex(ui->typeComboBox->currentIndex());



    // BLOCK
    ui->blockNonBreakableLinesCheckBox->setChecked(mTextBlockFormat.nonBreakableLines());
    ui->blockPageBreakPolicyAutoCheckBox->setChecked(aBlockPageBreaks==QTextFormat::PageBreak_Auto);
    ui->blockPageBreakPolicyBeforeCheckBox->setChecked(aBlockPageBreaks & QTextFormat::PageBreak_AlwaysBefore);
    ui->blockPageBreakPolicyAfterCheckBox->setChecked(aBlockPageBreaks & QTextFormat::PageBreak_AlwaysAfter);
    ui->blockLineHeightSpinBox->setValue(mTextBlockFormat.lineHeight());
    ui->blockLineHeightTypeComboBox->setCurrentIndex(ui->blockLineHeightTypeComboBox->findText(aBlockLineHeightTypeStr));
    ui->blockHorizontalAlignmentComboBox->setCurrentIndex(ui->blockHorizontalAlignmentComboBox->findText(aBlockHorizontalAlignment));
    ui->blockVerticalAlignmentComboBox->setCurrentIndex(ui->blockVerticalAlignmentComboBox->findText(aBlockVerticalAlignment));
    ui->blockIndentSpinBox->setValue(mTextBlockFormat.indent());
    ui->blockTextIndentSpinBox->setValue(mTextBlockFormat.textIndent());
    ui->blockLeftMarginSpinBox->setValue(mTextBlockFormat.leftMargin());
    ui->blockTopMarginSpinBox->setValue(mTextBlockFormat.topMargin());
    ui->blockRightMarginSpinBox->setValue(mTextBlockFormat.rightMargin());
    ui->blockBottomMarginSpinBox->setValue(mTextBlockFormat.bottomMargin());


    BLOCK_SIGNALS(false);
}
