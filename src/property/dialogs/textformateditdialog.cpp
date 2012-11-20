#include "textformateditdialog.h"
#include "ui_textformateditdialog.h"

#include <QScrollBar>
#include <QTimer>

#include "brusheditdialog.h"
#include "../widgets/tabframe.h"

TextFormatEditDialog::TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextFormatEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);



    mCharUnderlineColorArea=new ColorArea(this);
    mCharUnderlineColorArea->setMinimumSize(20, 20);
    mCharUnderlineColorArea->setMaximumSize(20, 20);
    mCharUnderlineColorArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mCharUnderlineColorArea->setTransparentBlockSize(5);
    ui->charUnderlineColorLayout->insertWidget(0, mCharUnderlineColorArea);

    connect(mCharUnderlineColorArea, SIGNAL(colorChanged(QColor)), this, SLOT(charUnderlineColorChanged(QColor)));



    mDividerSplitter = new QSplitter(Qt::Horizontal, this);
    ui->dividerLayout->removeWidget(ui->generalWidget);
    ui->dividerLayout->removeWidget(ui->typeStackedWidget);

    mDividerSplitter->addWidget(ui->generalWidget);
    mDividerSplitter->addWidget(ui->typeStackedWidget);
    mDividerSplitter->setChildrenCollapsible(false);

    ui->dividerLayout->addWidget(mDividerSplitter);



    QTimer::singleShot(0, this, SLOT(hideCategories()));



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
    charDrawTextOutlinePen();
}

TextFormatEditDialog::~TextFormatEditDialog()
{
    delete ui;
}

QTextFormat TextFormatEditDialog::resultValue() const
{
    return mTextFormat;
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

void TextFormatEditDialog::drawBackgroundBrush()
{
    drawBrush(mTextFormat.background(), ui->backgroundIconLabel);
}

void TextFormatEditDialog::drawForegroundBrush()
{
    drawBrush(mTextFormat.foreground(), ui->foregroundIconLabel);
}

void TextFormatEditDialog::charDrawTextOutlinePen()
{
    QPixmap aPenPixmap=QPixmap(16, 16);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setPen(mTextCharFormat.textOutline());
    aPainter.drawLine(aPenPixmap.width(), 0, 0, aPenPixmap.height());
    aPainter.end();

    ui->charTextOutlineIconLabel->setPixmap(QIcon(aPenPixmap).pixmap(18, 18));
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

void TextFormatEditDialog::hideCategories()
{
    int aOriginalIndex=ui->typeStackedWidget->currentIndex();

    // BLOCK
    ui->typeStackedWidget->setCurrentIndex(0);
    on_blockAlignmentButton_clicked();
    on_blockMarginsButton_clicked();
    on_blockIndentationButton_clicked();
    on_blockLineHeightButton_clicked();
    on_blockPageBreakButton_clicked();
    on_blockTabPositionsButton_clicked();

    // CHAR
    ui->typeStackedWidget->setCurrentIndex(1);
    on_charFontCategoryButton_clicked();
    on_charSpacingButton_clicked();
    on_charStyleButton_clicked();
    on_charAnchorButton_clicked();
    on_charOthersButton_clicked();

    ui->typeStackedWidget->setCurrentIndex(aOriginalIndex);
}

inline void TextFormatEditDialog::showOrHideCategory(QWidget *aCategory, QToolButton *aButton)
{
    aCategory->setVisible(!aCategory->isVisible());
    aButton->setArrowType(aCategory->isVisible()? Qt::UpArrow : Qt::DownArrow);
}

void TextFormatEditDialog::on_blockAlignmentButton_clicked()
{
    showOrHideCategory(ui->blockAlignmentFrame, ui->blockAlignmentButton);
}

void TextFormatEditDialog::on_blockMarginsButton_clicked()
{
    showOrHideCategory(ui->blockMarginsFrame, ui->blockMarginsButton);
}

void TextFormatEditDialog::on_blockIndentationButton_clicked()
{
    showOrHideCategory(ui->blockIndentationFrame, ui->blockIndentationButton);
}

void TextFormatEditDialog::on_blockLineHeightButton_clicked()
{
    showOrHideCategory(ui->blockLineHeightFrame, ui->blockLineHeightButton);
}

void TextFormatEditDialog::on_blockPageBreakButton_clicked()
{
    showOrHideCategory(ui->blockPageBreakFrame, ui->blockPageBreakButton);
}

void TextFormatEditDialog::on_blockTabPositionsButton_clicked()
{
    showOrHideCategory(ui->blockTabPositionsScrollArea, ui->blockTabPositionsButton);
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

void TextFormatEditDialog::on_blockTopMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setTopMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setTopMargin(aValue);
}

void TextFormatEditDialog::on_blockBottomMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setBottomMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setBottomMargin(aValue);
}

void TextFormatEditDialog::on_blockLeftMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setLeftMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setLeftMargin(aValue);
}

void TextFormatEditDialog::on_blockRightMarginSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setRightMargin(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setRightMargin(aValue);
}

void TextFormatEditDialog::on_blockTextIndentSpinBox_valueChanged(double aValue)
{
    mTextBlockFormat.setTextIndent(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setTextIndent(aValue);
}

void TextFormatEditDialog::on_blockIndentSpinBox_valueChanged(int aValue)
{
    mTextBlockFormat.setIndent(aValue);
    ((QTextBlockFormat *)&mTextFormat)->setIndent(aValue);
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

void TextFormatEditDialog::on_blockTabPositionsAddButton_clicked()
{
    blockAddTabPosition();
    blockUpdateTabPositions();
}

void TextFormatEditDialog::blockUpdateTabPositions()
{
    QList<QTextOption::Tab> aTabs;

    for (int i=0; i<ui->blockTabPositionsLayout->count(); ++i)
    {
        aTabs.append(((TabFrame *)ui->blockTabPositionsLayout->itemAt(i)->widget())->tab());
    }

    mTextBlockFormat.setTabPositions(aTabs);
    ((QTextBlockFormat *)&mTextFormat)->setTabPositions(aTabs);
}

void TextFormatEditDialog::blockAddTabPosition()
{
    TabFrame *aFrame=new TabFrame(this);

    if (ui->blockTabPositionsLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(ui->blockTabPositionsLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),     this, SLOT(blockTabPositionUp()));
    connect(aFrame, SIGNAL(downPressed()),   this, SLOT(blockTabPositionDown()));
    connect(aFrame, SIGNAL(deletePressed()), this, SLOT(blockTabPositionDelete()));
    connect(aFrame, SIGNAL(tabChanged()),    this, SLOT(blockTabPositionChanged()));

    ui->blockTabPositionsLayout->addWidget(aFrame);
    ui->blockTabPositionsScrollArea->verticalScrollBar()->setValue(ui->blockTabPositionsScrollArea->verticalScrollBar()->maximum());
}

void TextFormatEditDialog::blockTabPositionUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->blockTabPositionsLayout->indexOf(aWidget);

    if (index==1)
    {
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->blockTabPositionsLayout->count()-1)
    {
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->blockTabPositionsLayout->removeWidget(aWidget);
    ui->blockTabPositionsLayout->insertWidget(index-1, aWidget);

    blockUpdateTabPositions();
}

void TextFormatEditDialog::blockTabPositionDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->blockTabPositionsLayout->indexOf(aWidget);

    if (index==0)
    {
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->blockTabPositionsLayout->count()-2)
    {
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->blockTabPositionsLayout->removeWidget(aWidget);
    ui->blockTabPositionsLayout->insertWidget(index+1, aWidget);

    blockUpdateTabPositions();
}

void TextFormatEditDialog::blockTabPositionDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->blockTabPositionsLayout->count()>1)
    {
        int index=ui->blockTabPositionsLayout->indexOf(aWidget);

        if (index==0)
        {
            ((TabFrame *)ui->blockTabPositionsLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->blockTabPositionsLayout->count()-1)
        {
            ((TabFrame *)ui->blockTabPositionsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;

    blockUpdateTabPositions();
}

void TextFormatEditDialog::blockTabPositionChanged()
{
    blockUpdateTabPositions();
}

void TextFormatEditDialog::on_charFontCategoryButton_clicked()
{
    showOrHideCategory(ui->charFontFrame, ui->charFontCategoryButton);
}

void TextFormatEditDialog::on_charSpacingButton_clicked()
{
    showOrHideCategory(ui->charSpacingFrame, ui->charSpacingButton);
}

void TextFormatEditDialog::on_charStyleButton_clicked()
{
    showOrHideCategory(ui->charStyleFrame, ui->charStyleButton);
}

void TextFormatEditDialog::on_charAnchorButton_clicked()
{
    showOrHideCategory(ui->charAnchorFrame, ui->charAnchorButton);
}

void TextFormatEditDialog::on_charOthersButton_clicked()
{
    showOrHideCategory(ui->charOthersFrame, ui->charOthersButton);
}

void TextFormatEditDialog::on_charFontButton_clicked()
{

}

void TextFormatEditDialog::on_charFontFamilyEdit_textEdited(const QString &aValue)
{

}

void TextFormatEditDialog::on_charFontPointSizeSpinBox_valueChanged(double aValue)
{

}

void TextFormatEditDialog::on_charFontWeightSpinBox_valueChanged(int aValue)
{

}

void TextFormatEditDialog::on_charFontItalicCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charFontFixedPitchCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charFontStrikeOutCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charFontKerningCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charFontOverlineCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charFontUnderlineCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charUnderlineStyleComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::charUnderlineColorChanged(QColor aValue)
{

}

void TextFormatEditDialog::on_charFontLetterSpacingSpinBox_valueChanged(double aValue)
{

}

void TextFormatEditDialog::on_charFontWordSpacingSpinBox_valueChanged(double aValue)
{

}

void TextFormatEditDialog::on_charFontStyleHintComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charFontStyleStrategyComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charFontStyleStrategyFlagComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charAnchorCheckBox_toggled(bool checked)
{

}

void TextFormatEditDialog::on_charAnchorHrefLineEdit_textEdited(const QString &aValue)
{

}

void TextFormatEditDialog::on_charAnchorNamesButton_clicked()
{

}

void TextFormatEditDialog::on_charFontCapitalizationComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charFontHintingPreferenceComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{

}

void TextFormatEditDialog::on_charTextOutlineButton_clicked()
{

}

void TextFormatEditDialog::on_charTooltipEdit_textEdited(const QString &aValue)
{

}

void TextFormatEditDialog::copyFromTextFormat(QTextFormat aTextFormat)
{
    aTextFormat.setBackground(mTextFormat.background());
    aTextFormat.setForeground(mTextFormat.foreground());
    aTextFormat.setLayoutDirection(mTextFormat.layoutDirection());
    aTextFormat.setObjectIndex(mTextFormat.objectIndex());

    mTextFormat=aTextFormat;
}

#define BLOCK_BLOCK_SIGNALS(aLock) \
    ui->blockHorizontalAlignmentComboBox->blockSignals(aLock); \
    ui->blockVerticalAlignmentComboBox->blockSignals(aLock); \
    ui->blockTopMarginSpinBox->blockSignals(aLock); \
    ui->blockBottomMarginSpinBox->blockSignals(aLock); \
    ui->blockLeftMarginSpinBox->blockSignals(aLock); \
    ui->blockRightMarginSpinBox->blockSignals(aLock); \
    ui->blockTextIndentSpinBox->blockSignals(aLock); \
    ui->blockIndentSpinBox->blockSignals(aLock); \
    ui->blockLineHeightSpinBox->blockSignals(aLock); \
    ui->blockLineHeightTypeComboBox->blockSignals(aLock); \
    ui->blockNonBreakableLinesCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyAutoCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyBeforeCheckBox->blockSignals(aLock); \
    ui->blockPageBreakPolicyAfterCheckBox->blockSignals(aLock);

void TextFormatEditDialog::blockUpdateProperties()
{
    BLOCK_BLOCK_SIGNALS(true);

    Qt::Alignment aAlignment=((QTextBlockFormat *)&mTextFormat)->alignment();
    QString aHorizontalAlignment="AlignLeft";
    QString aVerticalAlignment="AlignTop";

    if (aAlignment & Qt::AlignHCenter)
    {
        aHorizontalAlignment="AlignHCenter";
    }
    else
    if (aAlignment & Qt::AlignRight)
    {
        aHorizontalAlignment="AlignRight";
    }
    else
    if (aAlignment & Qt::AlignJustify)
    {
        aHorizontalAlignment="AlignJustify";
    }
    else
    if (aAlignment & Qt::AlignAbsolute)
    {
        aHorizontalAlignment="AlignAbsolute";
    }

    if (aAlignment & Qt::AlignVCenter)
    {
        aVerticalAlignment="AlignVCenter";
    }
    else
    if (aAlignment & Qt::AlignBottom)
    {
        aVerticalAlignment="AlignBottom";
    }

    int aLineHeightType=((QTextBlockFormat *)&mTextFormat)->lineHeightType();
    QString aLineHeightTypeStr;

    if (aLineHeightType==QTextBlockFormat::SingleHeight)
    {
        aLineHeightTypeStr="SingleHeight";
    }
    else
    if (aLineHeightType==QTextBlockFormat::ProportionalHeight)
    {
        aLineHeightTypeStr="ProportionalHeight";
    }
    else
    if (aLineHeightType==QTextBlockFormat::FixedHeight)
    {
        aLineHeightTypeStr="FixedHeight";
    }
    else
    if (aLineHeightType==QTextBlockFormat::MinimumHeight)
    {
        aLineHeightTypeStr="MinimumHeight";
    }
    else
    if (aLineHeightType==QTextBlockFormat::LineDistanceHeight)
    {
        aLineHeightTypeStr="LineDistanceHeight";
    }
    else
    {
        Q_ASSERT(false);
    }

    QTextFormat::PageBreakFlags aPageBreaks=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy();



    ui->blockHorizontalAlignmentComboBox->setCurrentIndex(ui->blockHorizontalAlignmentComboBox->findText(aHorizontalAlignment));
    ui->blockVerticalAlignmentComboBox->setCurrentIndex(ui->blockVerticalAlignmentComboBox->findText(aVerticalAlignment));
    ui->blockTopMarginSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->topMargin());
    ui->blockBottomMarginSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->bottomMargin());
    ui->blockLeftMarginSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->leftMargin());
    ui->blockRightMarginSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->rightMargin());
    ui->blockTextIndentSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->textIndent());
    ui->blockIndentSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->indent());
    ui->blockLineHeightSpinBox->setValue(((QTextBlockFormat *)&mTextFormat)->lineHeight());
    ui->blockLineHeightTypeComboBox->setCurrentIndex(ui->blockLineHeightTypeComboBox->findText(aLineHeightTypeStr));
    ui->blockNonBreakableLinesCheckBox->setChecked(((QTextBlockFormat *)&mTextFormat)->nonBreakableLines());
    ui->blockPageBreakPolicyAutoCheckBox->setChecked(aPageBreaks==QTextFormat::PageBreak_Auto);
    ui->blockPageBreakPolicyBeforeCheckBox->setChecked(aPageBreaks & QTextFormat::PageBreak_AlwaysBefore);
    ui->blockPageBreakPolicyAfterCheckBox->setChecked(aPageBreaks & QTextFormat::PageBreak_AlwaysAfter);


    while (ui->blockTabPositionsLayout->count()>0)
    {
        delete ui->blockTabPositionsLayout->takeAt(0)->widget();
    }

    QList<QTextOption::Tab> aBlockTabs=((QTextBlockFormat *)&mTextFormat)->tabPositions();

    for (int i=0; i<aBlockTabs.count(); ++i)
    {
        blockAddTabPosition();

        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(i)->widget())->blockSignals(true);
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(i)->widget())->setTab(aBlockTabs.at(i));
        ((TabFrame *)ui->blockTabPositionsLayout->itemAt(i)->widget())->blockSignals(false);
    }

    BLOCK_BLOCK_SIGNALS(false);
}

#define CHAR_BLOCK_SIGNALS(aLock) \
    ui->charFontFamilyEdit->blockSignals(aLock); \
    ui->charFontPointSizeSpinBox->blockSignals(aLock); \
    ui->charFontWeightSpinBox->blockSignals(aLock); \
    ui->charFontItalicCheckBox->blockSignals(aLock); \
    ui->charFontFixedPitchCheckBox->blockSignals(aLock); \
    ui->charFontStrikeOutCheckBox->blockSignals(aLock); \
    ui->charFontKerningCheckBox->blockSignals(aLock); \
    ui->charFontOverlineCheckBox->blockSignals(aLock); \
    ui->charFontUnderlineCheckBox->blockSignals(aLock); \
    ui->charUnderlineStyleComboBox->blockSignals(aLock); \
    mCharUnderlineColorArea->blockSignals(aLock); \
    ui->charFontLetterSpacingSpinBox->blockSignals(aLock); \
    ui->charFontWordSpacingSpinBox->blockSignals(aLock); \
    ui->charFontStyleHintComboBox->blockSignals(aLock); \
    ui->charFontStyleStrategyComboBox->blockSignals(aLock); \
    ui->charFontStyleStrategyFlagComboBox->blockSignals(aLock); \
    ui->charAnchorCheckBox->blockSignals(aLock); \
    ui->charAnchorHrefLineEdit->blockSignals(aLock); \
    ui->charFontCapitalizationComboBox->blockSignals(aLock); \
    ui->charFontHintingPreferenceComboBox->blockSignals(aLock); \
    ui->charVerticalAlignmentComboBox->blockSignals(aLock); \
    ui->charTooltipEdit->blockSignals(aLock);

void TextFormatEditDialog::charUpdateProperties()
{
    CHAR_BLOCK_SIGNALS(true);

    QTextCharFormat::UnderlineStyle aUnderlineStyle=((QTextCharFormat *)&mTextFormat)->underlineStyle();
    QString aUnderlineStyleStr;

    if (aUnderlineStyle==QTextCharFormat::NoUnderline)
    {
        aUnderlineStyleStr="NoUnderline";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::SingleUnderline)
    {
        aUnderlineStyleStr="SingleUnderline";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::DashUnderline)
    {
        aUnderlineStyleStr="DashUnderline";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::DotLine)
    {
        aUnderlineStyleStr="DotLine";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::DashDotLine)
    {
        aUnderlineStyleStr="DashDotLine";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::DashDotDotLine)
    {
        aUnderlineStyleStr="DashDotDotLine";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::WaveUnderline)
    {
        aUnderlineStyleStr="WaveUnderline";
    }
    else
    if (aUnderlineStyle==QTextCharFormat::SpellCheckUnderline)
    {
        aUnderlineStyleStr="SpellCheckUnderline";
    }
    else
    {
        Q_ASSERT(false);
    }

    QFont::StyleHint aFontStyleHint=((QTextCharFormat *)&mTextFormat)->fontStyleHint();
    QString aFontStyleHintStr;

    if (aFontStyleHint==QFont::AnyStyle)
    {
        aFontStyleHintStr="AnyStyle";
    }
    else
    if (aFontStyleHint==QFont::Helvetica)
    {
        aFontStyleHintStr="Helvetica";
    }
    else
    if (aFontStyleHint==QFont::Times)
    {
        aFontStyleHintStr="Times";
    }
    else
    if (aFontStyleHint==QFont::Courier)
    {
        aFontStyleHintStr="Courier";
    }
    else
    if (aFontStyleHint==QFont::OldEnglish)
    {
        aFontStyleHintStr="OldEnglish";
    }
    else
    if (aFontStyleHint==QFont::Monospace)
    {
        aFontStyleHintStr="Monospace";
    }
    else
    if (aFontStyleHint==QFont::Fantasy)
    {
        aFontStyleHintStr="Fantasy";
    }
    else
    if (aFontStyleHint==QFont::Cursive)
    {
        aFontStyleHintStr="Cursive";
    }
    else
    if (aFontStyleHint==QFont::System)
    {
        aFontStyleHintStr="System";
    }
    else
    {
        Q_ASSERT(false);
    }

    QFont::StyleStrategy aFontStyleStrategy=((QTextCharFormat *)&mTextFormat)->fontStyleStrategy();
    QString aFontStyleStrategyStr="No strategy";
    QString aFontStyleStrategyFlagStr="No flag";

    if (aFontStyleStrategy & QFont::PreferDefault)
    {
        aFontStyleStrategyStr="PreferDefault";
    }
    else
    if (aFontStyleStrategy & QFont::PreferBitmap)
    {
        aFontStyleStrategyStr="PreferBitmap";
    }
    else
    if (aFontStyleStrategy & QFont::PreferDevice)
    {
        aFontStyleStrategyStr="PreferDevice";
    }
    else
    if (aFontStyleStrategy & QFont::PreferOutline)
    {
        aFontStyleStrategyStr="PreferOutline";
    }
    else
    if (aFontStyleStrategy & QFont::ForceOutline)
    {
        aFontStyleStrategyStr="ForceOutline";
    }
    else
    if (aFontStyleStrategy & QFont::NoAntialias)
    {
        aFontStyleStrategyStr="NoAntialias";
    }
    else
    if (aFontStyleStrategy & QFont::PreferAntialias)
    {
        aFontStyleStrategyStr="PreferAntialias";
    }
    else
    if (aFontStyleStrategy & QFont::OpenGLCompatible)
    {
        aFontStyleStrategyStr="OpenGLCompatible";
    }
    else
    if (aFontStyleStrategy & QFont::NoFontMerging)
    {
        aFontStyleStrategyStr="NoFontMerging";
    }

    if (aFontStyleStrategy & QFont::PreferMatch)
    {
        aFontStyleStrategyFlagStr="PreferMatch";
    }
    else
    if (aFontStyleStrategy & QFont::PreferQuality)
    {
        aFontStyleStrategyFlagStr="PreferQuality";
    }
    else
    if (aFontStyleStrategy & QFont::ForceIntegerMetrics)
    {
        aFontStyleStrategyFlagStr="ForceIntegerMetrics";
    }

    QFont::Capitalization aFontCapitalization=((QTextCharFormat *)&mTextFormat)->fontCapitalization();
    QString aFontCapitalizationStr;

    if (aFontCapitalization==QFont::MixedCase)
    {
        aFontCapitalizationStr="MixedCase";
    }
    else
    if (aFontCapitalization==QFont::AllUppercase)
    {
        aFontCapitalizationStr="AllUppercase";
    }
    else
    if (aFontCapitalization==QFont::AllLowercase)
    {
        aFontCapitalizationStr="AllLowercase";
    }
    else
    if (aFontCapitalization==QFont::SmallCaps)
    {
        aFontCapitalizationStr="SmallCaps";
    }
    else
    if (aFontCapitalization==QFont::Capitalize)
    {
        aFontCapitalizationStr="Capitalize";
    }
    else
    {
        Q_ASSERT(false);
    }

    QFont::HintingPreference aFontHintingPreference=((QTextCharFormat *)&mTextFormat)->fontHintingPreference();
    QString aFontHintingPreferenceStr;

    if (aFontHintingPreference==QFont::PreferDefaultHinting)
    {
        aFontHintingPreferenceStr="PreferDefaultHinting";
    }
    else
    if (aFontHintingPreference==QFont::PreferNoHinting)
    {
        aFontHintingPreferenceStr="PreferNoHinting";
    }
    else
    if (aFontHintingPreference==QFont::PreferVerticalHinting)
    {
        aFontHintingPreferenceStr="PreferVerticalHinting";
    }
    else
    if (aFontHintingPreference==QFont::PreferFullHinting)
    {
        aFontHintingPreferenceStr="PreferFullHinting";
    }
    else
    {
        Q_ASSERT(false);
    }

    QTextCharFormat::VerticalAlignment aVerticalAlignment=((QTextCharFormat *)&mTextFormat)->verticalAlignment();
    QString aVerticalAlignmentStr;

    if (aVerticalAlignment==QTextCharFormat::AlignNormal)
    {
        aVerticalAlignmentStr="AlignNormal";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignSuperScript)
    {
        aVerticalAlignmentStr="AlignSuperScript";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignSubScript)
    {
        aVerticalAlignmentStr="AlignSubScript";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignMiddle)
    {
        aVerticalAlignmentStr="AlignMiddle";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignBottom)
    {
        aVerticalAlignmentStr="AlignBottom";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignTop)
    {
        aVerticalAlignmentStr="AlignTop";
    }
    else
    if (aVerticalAlignment==QTextCharFormat::AlignBaseline)
    {
        aVerticalAlignmentStr="AlignBaseline";
    }
    else
    {
        Q_ASSERT(false);
    }



    ui->charFontFamilyEdit->setText(((QTextCharFormat *)&mTextFormat)->fontFamily());
    ui->charFontPointSizeSpinBox->setValue(((QTextCharFormat *)&mTextFormat)->fontPointSize());
    ui->charFontWeightSpinBox->setValue(((QTextCharFormat *)&mTextFormat)->fontWeight());
    ui->charFontItalicCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontItalic());
    ui->charFontFixedPitchCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontFixedPitch());
    ui->charFontStrikeOutCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontStrikeOut());
    ui->charFontKerningCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontKerning());
    ui->charFontOverlineCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontOverline());
    ui->charFontUnderlineCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->fontUnderline());
    ui->charUnderlineStyleComboBox->setCurrentIndex(ui->charUnderlineStyleComboBox->findText(aUnderlineStyleStr));
    mCharUnderlineColorArea->setColor(((QTextCharFormat *)&mTextFormat)->underlineColor());
    ui->charFontLetterSpacingSpinBox->setValue(((QTextCharFormat *)&mTextFormat)->fontLetterSpacing());
    ui->charFontWordSpacingSpinBox->setValue(((QTextCharFormat *)&mTextFormat)->fontWordSpacing());
    ui->charFontStyleHintComboBox->setCurrentIndex(ui->charFontStyleHintComboBox->findText(aFontCapitalizationStr));
    ui->charFontStyleStrategyComboBox->setCurrentIndex(ui->charFontStyleStrategyComboBox->findText(aFontStyleStrategyStr));
    ui->charFontStyleStrategyFlagComboBox->setCurrentIndex(ui->charFontStyleStrategyFlagComboBox->findText(aFontStyleStrategyFlagStr));
    ui->charAnchorCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->isAnchor());
    ui->charAnchorHrefLineEdit->setText(((QTextCharFormat *)&mTextFormat)->anchorHref());

    QStringList aList=((QTextCharFormat *)&mTextFormat)->anchorNames();

    QString anchorNames="[";

    for (int i=0; i<aList.length(); ++i)
    {
        anchorNames.append("\"");
        anchorNames.append(aList.at(i));
        anchorNames.append("\"");

        if (i<aList.length()-1)
        {
            anchorNames.append("; ");
        }
    }

    anchorNames.append("]");

    ui->charAnchorNamesEdit->setText(anchorNames);
    ui->charFontCapitalizationComboBox->setCurrentIndex(ui->charFontCapitalizationComboBox->findText(aFontCapitalizationStr));
    ui->charFontHintingPreferenceComboBox->setCurrentIndex(ui->charFontHintingPreferenceComboBox->findText(aFontHintingPreferenceStr));
    ui->charVerticalAlignmentComboBox->setCurrentIndex(ui->charVerticalAlignmentComboBox->findText(aVerticalAlignmentStr));
    ui->charTooltipEdit->setText(((QTextCharFormat *)&mTextFormat)->toolTip());

    CHAR_BLOCK_SIGNALS(false);
}

#define BLOCK_SIGNALS(aLock) \
    ui->typeComboBox->blockSignals(aLock); \
    ui->layoutDirectionComboBox->blockSignals(aLock); \
    ui->objectIndexSpinBox->blockSignals(aLock);

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

    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aTypeStr));
    ui->layoutDirectionComboBox->setCurrentIndex(ui->layoutDirectionComboBox->findText(aLayoutDirectionStr));
    ui->objectIndexSpinBox->setValue(mTextFormat.objectIndex());
    ui->typeStackedWidget->setCurrentIndex(ui->typeComboBox->currentIndex());

    switch (ui->typeComboBox->currentIndex())
    {
        case 0: blockUpdateProperties(); break;
        case 1: charUpdateProperties();  break;
    }

    BLOCK_SIGNALS(false);
}
