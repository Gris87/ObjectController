#include "textformateditdialog.h"
#include "ui_textformateditdialog.h"

#include <QScrollBar>
#include <QTimer>
#include <QFontDialog>

#include "brusheditdialog.h"
#include "stringlisteditdialog.h"
#include "peneditdialog.h"
#include "textlengtheditdialog.h"
#include "../widgets/tabframe.h"
#include "../widgets/textlengthframe.h"

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

    updateProperties();

    drawBackgroundBrush();
    drawForegroundBrush();
    charDrawFont();
    charDrawTextOutlinePen();
    frameDrawBorderBrush();
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

void TextFormatEditDialog::charDrawFont()
{
    QFont aFont=((QTextCharFormat *)&mTextFormat)->font();
    aFont.setPixelSize(32);

    QFontMetrics aMetrics(aFont);

    int aSize=qMax(aMetrics.width('A'), aMetrics.height())-6;

    if (aSize<1)
    {
        aSize=1;
    }

    QRect aBoundingRect(0, 0, aSize, aSize);

    QPixmap aPenPixmap=QPixmap(aSize, aSize);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setFont(aFont);
    aPainter.drawText(aBoundingRect, Qt::AlignCenter, "A", &aBoundingRect);
    aPainter.end();

    if (aSize<32)
    {
        ui->charFontIconLabel->setPixmap(QIcon(aPenPixmap.scaled(32, 32)).pixmap(18, 18));
    }
    else
    {
        ui->charFontIconLabel->setPixmap(QIcon(aPenPixmap).pixmap(18, 18));
    }
}

void TextFormatEditDialog::charDrawTextOutlinePen()
{
    QPixmap aPenPixmap=QPixmap(16, 16);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setPen(((QTextCharFormat *)&mTextFormat)->textOutline());
    aPainter.drawLine(aPenPixmap.width(), 0, 0, aPenPixmap.height());
    aPainter.end();

    ui->charTextOutlineIconLabel->setPixmap(QIcon(aPenPixmap).pixmap(18, 18));
}

void TextFormatEditDialog::frameDrawBorderBrush()
{
    drawBrush(((QTextFrameFormat *)&mTextFormat)->borderBrush(), ui->frameBorderBrushIconLabel);
}

void TextFormatEditDialog::on_okButton_clicked()
{
    accept();
}

void TextFormatEditDialog::on_cancelButton_clicked()
{
    reject();
}

void TextFormatEditDialog::copyFromTextFormat(QTextFormat aTextFormat)
{
    aTextFormat.setBackground(mTextFormat.background());
    aTextFormat.setForeground(mTextFormat.foreground());
    aTextFormat.setLayoutDirection(mTextFormat.layoutDirection());
    aTextFormat.setObjectIndex(mTextFormat.objectIndex());

    mTextFormat=aTextFormat;
}

void TextFormatEditDialog::putWidgetToLayout(QWidget *aWidget, QBoxLayout *aLayout)
{
    aLayout->insertWidget(0, aWidget);
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
        putWidgetToLayout(ui->charWidget, ui->charLayout);
    }
    else
    if (aValue=="FrameFormat")
    {
        copyFromTextFormat(mTextFrameFormat);
        putWidgetToLayout(ui->frameWidget, ui->frameLayout);
    }
    else
    if (aValue=="ImageFormat")
    {
        copyFromTextFormat(mTextImageFormat);
        putWidgetToLayout(ui->charWidget, ui->imageLayout);
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
        putWidgetToLayout(ui->charWidget, ui->tableCellLayout);
    }
    else
    if (aValue=="TableFormat")
    {
        copyFromTextFormat(mTextTableFormat);
        putWidgetToLayout(ui->frameWidget, ui->tableLayout);
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

    // FRAME
    ui->typeStackedWidget->setCurrentIndex(2);
    on_framePositionButton_clicked();
    on_frameBorderButton_clicked();
    on_frameMarginsButton_clicked();
    on_frameSizeButton_clicked();
    on_framePageBreakButton_clicked();

    // IMAGE
    ui->typeStackedWidget->setCurrentIndex(3);
    on_imageImageButton_clicked();

    // LIST
    ui->typeStackedWidget->setCurrentIndex(4);
    on_listListButton_clicked();

    // TABLE CELL
    ui->typeStackedWidget->setCurrentIndex(5);
    on_tableCellButton_clicked();

    // TABLE
    ui->typeStackedWidget->setCurrentIndex(6);
    on_tableTableButton_clicked();
    on_tableAlignmentButton_clicked();
    on_tableColumnWidthConstraintsButton_clicked();

    ui->typeStackedWidget->setCurrentIndex(aOriginalIndex);



    switch (aOriginalIndex)
    {
        case 1: putWidgetToLayout(ui->charWidget,  ui->charLayout);      break;
        case 2: putWidgetToLayout(ui->frameWidget, ui->frameLayout);     break;
        case 3: putWidgetToLayout(ui->charWidget,  ui->imageLayout);     break;
        case 5: putWidgetToLayout(ui->charWidget,  ui->tableCellLayout); break;
        case 6: putWidgetToLayout(ui->frameWidget, ui->tableLayout);     break;
    }
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

#define BLOCK_MODIFICATION(action) \
    mTextBlockFormat.action; \
    ((QTextBlockFormat *)&mTextFormat)->action;

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

    BLOCK_MODIFICATION(setAlignment(aHorizontalAlignment | aVerticalAlignment));
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
    BLOCK_MODIFICATION(setTopMargin(aValue));
}

void TextFormatEditDialog::on_blockBottomMarginSpinBox_valueChanged(double aValue)
{
    BLOCK_MODIFICATION(setBottomMargin(aValue));
}

void TextFormatEditDialog::on_blockLeftMarginSpinBox_valueChanged(double aValue)
{
    BLOCK_MODIFICATION(setLeftMargin(aValue));
}

void TextFormatEditDialog::on_blockRightMarginSpinBox_valueChanged(double aValue)
{
    BLOCK_MODIFICATION(setRightMargin(aValue));
}

void TextFormatEditDialog::on_blockTextIndentSpinBox_valueChanged(double aValue)
{
    BLOCK_MODIFICATION(setTextIndent(aValue));
}

void TextFormatEditDialog::on_blockIndentSpinBox_valueChanged(int aValue)
{
    BLOCK_MODIFICATION(setIndent(aValue));
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

    BLOCK_MODIFICATION(setLineHeight(aHeight, aHeightType));
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
    BLOCK_MODIFICATION(setNonBreakableLines(checked));
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

        BLOCK_MODIFICATION(setPageBreakPolicy(QTextFormat::PageBreak_Auto));
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

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysBefore;
        BLOCK_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
    else
    {
        if (!ui->blockPageBreakPolicyAfterCheckBox->isChecked())
        {
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->blockPageBreakPolicyAutoCheckBox->setChecked(true);
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysBefore;
        BLOCK_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
}

void TextFormatEditDialog::on_blockPageBreakPolicyAfterCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->blockPageBreakPolicyAutoCheckBox->setChecked(false);
        ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysAfter;
        BLOCK_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
    else
    {
        if (!ui->blockPageBreakPolicyBeforeCheckBox->isChecked())
        {
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->blockPageBreakPolicyAutoCheckBox->setChecked(true);
            ui->blockPageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysAfter;
        BLOCK_MODIFICATION(setPageBreakPolicy(aPolicy));
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

    BLOCK_MODIFICATION(setTabPositions(aTabs));
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
    showOrHideCategory(ui->charFontCategoryFrame, ui->charFontCategoryButton);
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

#define CHAR_MODIFICATION(action) \
    mTextCharFormat.action; \
    mTextImageFormat.action; \
    mTextTableCellFormat.action; \
    ((QTextCharFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_charFontButton_clicked()
{
    QFontDialog dialog(((QTextCharFormat *)&mTextFormat)->font(), this);

    if (dialog.exec())
    {
        CHAR_MODIFICATION(setFont(dialog.selectedFont()));
        charUpdateProperties();
        charDrawFont();
    }
}

void TextFormatEditDialog::on_charFontFamilyEdit_textEdited(const QString &aValue)
{
    CHAR_MODIFICATION(setFontFamily(aValue));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontPointSizeSpinBox_valueChanged(double aValue)
{
    CHAR_MODIFICATION(setFontPointSize(aValue));
    charUpdateProperties();
}

void TextFormatEditDialog::on_charFontWeightSpinBox_valueChanged(int aValue)
{
    CHAR_MODIFICATION(setFontWeight(aValue));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontItalicCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontItalic(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontFixedPitchCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontFixedPitch(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontStrikeOutCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontStrikeOut(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontKerningCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontKerning(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontOverlineCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontOverline(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charFontUnderlineCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setFontUnderline(checked));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::on_charUnderlineStyleComboBox_currentIndexChanged(const QString &aValue)
{
    QTextCharFormat::UnderlineStyle aStyle=QTextCharFormat::NoUnderline;

    if (aValue=="NoUnderline")
    {
        aStyle=QTextCharFormat::NoUnderline;
    }
    else
    if (aValue=="SingleUnderline")
    {
        aStyle=QTextCharFormat::SingleUnderline;
    }
    else
    if (aValue=="DashUnderline")
    {
        aStyle=QTextCharFormat::DashUnderline;
    }
    else
    if (aValue=="DotLine")
    {
        aStyle=QTextCharFormat::DotLine;
    }
    else
    if (aValue=="DashDotLine")
    {
        aStyle=QTextCharFormat::DashDotLine;
    }
    else
    if (aValue=="DashDotDotLine")
    {
        aStyle=QTextCharFormat::DashDotDotLine;
    }
    else
    if (aValue=="WaveUnderline")
    {
        aStyle=QTextCharFormat::WaveUnderline;
    }
    else
    if (aValue=="SpellCheckUnderline")
    {
        aStyle=QTextCharFormat::SpellCheckUnderline;
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setUnderlineStyle(aStyle));
    charUpdateProperties();
    charDrawFont();
}

void TextFormatEditDialog::charUnderlineColorChanged(QColor aValue)
{
    CHAR_MODIFICATION(setUnderlineColor(aValue));
}

void TextFormatEditDialog::on_charFontLetterSpacingSpinBox_valueChanged(double aValue)
{
    CHAR_MODIFICATION(setFontLetterSpacing(aValue));
}

void TextFormatEditDialog::on_charFontWordSpacingSpinBox_valueChanged(double aValue)
{
    CHAR_MODIFICATION(setFontWordSpacing(aValue));
}

void TextFormatEditDialog::on_charFontStyleHintComboBox_currentIndexChanged(const QString &aValue)
{
    QFont::StyleHint aStyleHint=QFont::AnyStyle;

    if (aValue=="AnyStyle")
    {
        aStyleHint=QFont::AnyStyle;
    }
    else
    if (aValue=="Helvetica")
    {
        aStyleHint=QFont::Helvetica;
    }
    else
    if (aValue=="Times")
    {
        aStyleHint=QFont::Times;
    }
    else
    if (aValue=="Courier")
    {
        aStyleHint=QFont::Courier;
    }
    else
    if (aValue=="OldEnglish")
    {
        aStyleHint=QFont::OldEnglish;
    }
    else
    if (aValue=="Monospace")
    {
        aStyleHint=QFont::Monospace;
    }
    else
    if (aValue=="Fantasy")
    {
        aStyleHint=QFont::Fantasy;
    }
    else
    if (aValue=="Cursive")
    {
        aStyleHint=QFont::Cursive;
    }
    else
    if (aValue=="System")
    {
        aStyleHint=QFont::System;
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setFontStyleHint(aStyleHint));
}

void TextFormatEditDialog::charSetStyleStrategy(const QString &aStrategy, const QString &aFlag)
{
    QFont::StyleStrategy aStyleStrategy=QFont::PreferDefault;

    if (aStrategy=="PreferDefault")
    {
        aStyleStrategy=QFont::PreferDefault;
    }
    else
    if (aStrategy=="PreferBitmap")
    {
        aStyleStrategy=QFont::PreferBitmap;
    }
    else
    if (aStrategy=="PreferDevice")
    {
        aStyleStrategy=QFont::PreferDevice;
    }
    else
    if (aStrategy=="PreferOutline")
    {
        aStyleStrategy=QFont::PreferOutline;
    }
    else
    if (aStrategy=="ForceOutline")
    {
        aStyleStrategy=QFont::ForceOutline;
    }
    else
    if (aStrategy=="NoAntialias")
    {
        aStyleStrategy=QFont::NoAntialias;
    }
    else
    if (aStrategy=="PreferAntialias")
    {
        aStyleStrategy=QFont::PreferAntialias;
    }
    else
    if (aStrategy=="OpenGLCompatible")
    {
        aStyleStrategy=QFont::OpenGLCompatible;
    }
    else
    if (aStrategy=="NoFontMerging")
    {
        aStyleStrategy=QFont::NoFontMerging;
    }
    else
    {
        Q_ASSERT(false);
    }

    if (aFlag=="No flag")
    {
        // Nothing
    }
    else
    if (aFlag=="PreferMatch")
    {
        aStyleStrategy=(QFont::StyleStrategy)(aStyleStrategy | QFont::PreferMatch);
    }
    else
    if (aFlag=="PreferQuality")
    {
        aStyleStrategy=(QFont::StyleStrategy)(aStyleStrategy | QFont::PreferQuality);
    }
    else
    if (aFlag=="ForceIntegerMetrics")
    {
        aStyleStrategy=(QFont::StyleStrategy)(aStyleStrategy | QFont::ForceIntegerMetrics);
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setFontStyleStrategy(aStyleStrategy));
}

void TextFormatEditDialog::on_charFontStyleStrategyComboBox_currentIndexChanged(const QString &aValue)
{
    charSetStyleStrategy(aValue, ui->charFontStyleStrategyFlagComboBox->currentText());
}

void TextFormatEditDialog::on_charFontStyleStrategyFlagComboBox_currentIndexChanged(const QString &aValue)
{
    charSetStyleStrategy(ui->charFontStyleStrategyComboBox->currentText(), aValue);
}

void TextFormatEditDialog::on_charAnchorCheckBox_toggled(bool checked)
{
    CHAR_MODIFICATION(setAnchor(checked));
}

void TextFormatEditDialog::on_charAnchorHrefLineEdit_textEdited(const QString &aValue)
{
    CHAR_MODIFICATION(setAnchorHref(aValue));
}

void TextFormatEditDialog::on_charAnchorNamesButton_clicked()
{
    StringListEditDialog dialog(((QTextCharFormat *)&mTextFormat)->anchorNames(), this);

    if (dialog.exec())
    {
        CHAR_MODIFICATION(setAnchorNames(dialog.resultValue()));
        charUpdateProperties();
    }
}

void TextFormatEditDialog::on_charFontCapitalizationComboBox_currentIndexChanged(const QString &aValue)
{
    QFont::Capitalization aCapitalization=QFont::MixedCase;

    if (aValue=="MixedCase")
    {
        aCapitalization=QFont::MixedCase;
    }
    else
    if (aValue=="AllUppercase")
    {
        aCapitalization=QFont::AllUppercase;
    }
    else
    if (aValue=="AllLowercase")
    {
        aCapitalization=QFont::AllLowercase;
    }
    else
    if (aValue=="SmallCaps")
    {
        aCapitalization=QFont::SmallCaps;
    }
    else
    if (aValue=="Capitalize")
    {
        aCapitalization=QFont::Capitalize;
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setFontCapitalization(aCapitalization));
}

void TextFormatEditDialog::on_charFontHintingPreferenceComboBox_currentIndexChanged(const QString &aValue)
{
    QFont::HintingPreference aHintingPreference=QFont::PreferDefaultHinting;

    if (aValue=="PreferDefaultHinting")
    {
        aHintingPreference=QFont::PreferDefaultHinting;
    }
    else
    if (aValue=="PreferNoHinting")
    {
        aHintingPreference=QFont::PreferNoHinting;
    }
    else
    if (aValue=="PreferVerticalHinting")
    {
        aHintingPreference=QFont::PreferVerticalHinting;
    }
    else
    if (aValue=="PreferFullHinting")
    {
        aHintingPreference=QFont::PreferFullHinting;
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setFontHintingPreference(aHintingPreference));
}

void TextFormatEditDialog::on_charVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{
    QTextCharFormat::VerticalAlignment aVerticalAlignment=QTextCharFormat::AlignNormal;

    if (aValue=="AlignNormal")
    {
        aVerticalAlignment=QTextCharFormat::AlignNormal;
    }
    else
    if (aValue=="AlignSuperScript")
    {
        aVerticalAlignment=QTextCharFormat::AlignSuperScript;
    }
    else
    if (aValue=="AlignSubScript")
    {
        aVerticalAlignment=QTextCharFormat::AlignSubScript;
    }
    else
    if (aValue=="AlignMiddle")
    {
        aVerticalAlignment=QTextCharFormat::AlignMiddle;
    }
    else
    if (aValue=="AlignBottom")
    {
        aVerticalAlignment=QTextCharFormat::AlignBottom;
    }
    else
    if (aValue=="AlignTop")
    {
        aVerticalAlignment=QTextCharFormat::AlignTop;
    }
    else
    if (aValue=="AlignBaseline")
    {
        aVerticalAlignment=QTextCharFormat::AlignBaseline;
    }
    else
    {
        Q_ASSERT(false);
    }

    CHAR_MODIFICATION(setVerticalAlignment(aVerticalAlignment));
}

void TextFormatEditDialog::on_charTextOutlineButton_clicked()
{
    PenEditDialog dialog(((QTextCharFormat *)&mTextFormat)->textOutline(), this);

    if (dialog.exec())
    {
        CHAR_MODIFICATION(setTextOutline(dialog.resultValue()));
        charDrawTextOutlinePen();
    }
}

void TextFormatEditDialog::on_charTooltipEdit_textEdited(const QString &aValue)
{
    CHAR_MODIFICATION(setToolTip(aValue));
}

void TextFormatEditDialog::on_framePositionButton_clicked()
{
    showOrHideCategory(ui->framePositionFrame, ui->framePositionButton);
}

void TextFormatEditDialog::on_frameBorderButton_clicked()
{
    showOrHideCategory(ui->frameBorderFrame, ui->frameBorderButton);
}

void TextFormatEditDialog::on_frameMarginsButton_clicked()
{
    showOrHideCategory(ui->frameMarginsFrame, ui->frameMarginsButton);
}

void TextFormatEditDialog::on_frameSizeButton_clicked()
{
    showOrHideCategory(ui->frameSizeFrame, ui->frameSizeButton);
}

void TextFormatEditDialog::on_framePageBreakButton_clicked()
{
    showOrHideCategory(ui->framePageBreakFrame, ui->framePageBreakButton);
}

#define FRAME_MODIFICATION(action) \
    mTextFrameFormat.action; \
    mTextTableFormat.action; \
    ((QTextFrameFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_framePositionComboBox_currentIndexChanged(const QString &aValue)
{
    QTextFrameFormat::Position aPosition=QTextFrameFormat::InFlow;

    if (aValue=="InFlow")
    {
        aPosition=QTextFrameFormat::InFlow;
    }
    else
    if (aValue=="FloatLeft")
    {
        aPosition=QTextFrameFormat::FloatLeft;
    }
    else
    if (aValue=="FloatRight")
    {
        aPosition=QTextFrameFormat::FloatRight;
    }
    else
    {
        Q_ASSERT(false);
    }

    FRAME_MODIFICATION(setPosition(aPosition));
}

void TextFormatEditDialog::on_frameBorderSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setBorder(aValue));
}

void TextFormatEditDialog::on_frameBorderBrushButton_clicked()
{
    BrushEditDialog dialog(((QTextFrameFormat *)&mTextFormat)->borderBrush(), this);

    if (dialog.exec())
    {
        FRAME_MODIFICATION(setBorderBrush(dialog.resultValue()));
        frameDrawBorderBrush();
    }
}

void TextFormatEditDialog::on_frameBorderStyleComboBox_currentIndexChanged(const QString &aValue)
{
    QTextFrameFormat::BorderStyle aBorderStyle=QTextFrameFormat::BorderStyle_None;

    if (aValue=="BorderStyle_None")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_None;
    }
    else
    if (aValue=="BorderStyle_Dotted")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Dotted;
    }
    else
    if (aValue=="BorderStyle_Dashed")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Dashed;
    }
    else
    if (aValue=="BorderStyle_Solid")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Solid;
    }
    else
    if (aValue=="BorderStyle_Double")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Double;
    }
    else
    if (aValue=="BorderStyle_DotDash")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_DotDash;
    }
    else
    if (aValue=="BorderStyle_DotDotDash")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_DotDotDash;
    }
    else
    if (aValue=="BorderStyle_Groove")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Groove;
    }
    else
    if (aValue=="BorderStyle_Ridge")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Ridge;
    }
    else
    if (aValue=="BorderStyle_Inset")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Inset;
    }
    else
    if (aValue=="BorderStyle_Outset")
    {
        aBorderStyle=QTextFrameFormat::BorderStyle_Outset;
    }
    else
    {
        Q_ASSERT(false);
    }

    FRAME_MODIFICATION(setBorderStyle(aBorderStyle));
}

void TextFormatEditDialog::on_frameMarginSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setMargin(aValue));
    frameUpdateProperties();
}

void TextFormatEditDialog::on_frameTopMarginSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setTopMargin(aValue));
}

void TextFormatEditDialog::on_frameBottomMarginSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setBottomMargin(aValue));
}

void TextFormatEditDialog::on_frameLeftMarginSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setLeftMargin(aValue));
}

void TextFormatEditDialog::on_frameRightMarginSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setRightMargin(aValue));
}

void TextFormatEditDialog::on_framePaddingSpinBox_valueChanged(double aValue)
{
    FRAME_MODIFICATION(setPadding(aValue));
}

void TextFormatEditDialog::on_frameWidthButton_clicked()
{
    TextLengthEditDialog dialog(((QTextFrameFormat *)&mTextFormat)->width(), this);

    if (dialog.exec())
    {
        FRAME_MODIFICATION(setWidth(dialog.resultValue()));
        frameUpdateProperties();
    }
}

void TextFormatEditDialog::on_frameHeightButton_clicked()
{
    TextLengthEditDialog dialog(((QTextFrameFormat *)&mTextFormat)->height(), this);

    if (dialog.exec())
    {
        FRAME_MODIFICATION(setHeight(dialog.resultValue()));
        frameUpdateProperties();
    }
}

void TextFormatEditDialog::on_framePageBreakPolicyAutoCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->framePageBreakPolicyBeforeCheckBox->blockSignals(true);
        ui->framePageBreakPolicyAfterCheckBox->blockSignals(true);

        ui->framePageBreakPolicyBeforeCheckBox->setChecked(false);
        ui->framePageBreakPolicyAfterCheckBox->setChecked(false);

        ui->framePageBreakPolicyBeforeCheckBox->blockSignals(false);
        ui->framePageBreakPolicyAfterCheckBox->blockSignals(false);

        FRAME_MODIFICATION(setPageBreakPolicy(QTextFormat::PageBreak_Auto));
    }
    else
    {
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->framePageBreakPolicyAutoCheckBox->setChecked(true);
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(false);
    }
}

void TextFormatEditDialog::on_framePageBreakPolicyBeforeCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->framePageBreakPolicyAutoCheckBox->setChecked(false);
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(false);

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysBefore;
        FRAME_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
    else
    {
        if (!ui->framePageBreakPolicyAfterCheckBox->isChecked())
        {
            ui->framePageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->framePageBreakPolicyAutoCheckBox->setChecked(true);
            ui->framePageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysBefore;
        FRAME_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
}

void TextFormatEditDialog::on_framePageBreakPolicyAfterCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(true);
        ui->framePageBreakPolicyAutoCheckBox->setChecked(false);
        ui->framePageBreakPolicyAutoCheckBox->blockSignals(false);

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() | QTextFormat::PageBreak_AlwaysAfter;
        FRAME_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
    else
    {
        if (!ui->framePageBreakPolicyBeforeCheckBox->isChecked())
        {
            ui->framePageBreakPolicyAutoCheckBox->blockSignals(true);
            ui->framePageBreakPolicyAutoCheckBox->setChecked(true);
            ui->framePageBreakPolicyAutoCheckBox->blockSignals(false);
        }

        QTextFormat::PageBreakFlags aPolicy=((QTextBlockFormat *)&mTextFormat)->pageBreakPolicy() & ~QTextFormat::PageBreak_AlwaysAfter;
        FRAME_MODIFICATION(setPageBreakPolicy(aPolicy));
    }
}

void TextFormatEditDialog::on_imageImageButton_clicked()
{
    showOrHideCategory(ui->imageImageFrame, ui->imageImageButton);
}

#define IMAGE_MODIFICATION(action) \
    mTextImageFormat.action; \
    ((QTextImageFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_imageNameEdit_textEdited(const QString &aValue)
{
    IMAGE_MODIFICATION(setName(aValue));
}

void TextFormatEditDialog::on_imageWidthSpinBox_valueChanged(double aValue)
{
    IMAGE_MODIFICATION(setWidth(aValue));
}

void TextFormatEditDialog::on_imageHeightSpinBox_valueChanged(double aValue)
{
    IMAGE_MODIFICATION(setHeight(aValue));
}

void TextFormatEditDialog::on_listListButton_clicked()
{
    showOrHideCategory(ui->listListFrame, ui->listListButton);
}

#define LIST_MODIFICATION(action) \
    mTextListFormat.action; \
    ((QTextListFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_listStyleComboBox_currentIndexChanged(const QString &aValue)
{
    QTextListFormat::Style aStyle=QTextListFormat::ListStyleUndefined;

    if (aValue=="ListDisc")
    {
        aStyle=QTextListFormat::ListDisc;
    }
    else
    if (aValue=="ListCircle")
    {
        aStyle=QTextListFormat::ListCircle;
    }
    else
    if (aValue=="ListSquare")
    {
        aStyle=QTextListFormat::ListSquare;
    }
    else
    if (aValue=="ListDecimal")
    {
        aStyle=QTextListFormat::ListDecimal;
    }
    else
    if (aValue=="ListLowerAlpha")
    {
        aStyle=QTextListFormat::ListLowerAlpha;
    }
    else
    if (aValue=="ListUpperAlpha")
    {
        aStyle=QTextListFormat::ListUpperAlpha;
    }
    else
    if (aValue=="ListLowerRoman")
    {
        aStyle=QTextListFormat::ListLowerRoman;
    }
    else
    if (aValue=="ListUpperRoman")
    {
        aStyle=QTextListFormat::ListUpperRoman;
    }
    else
    if (aValue=="ListStyleUndefined")
    {
        aStyle=QTextListFormat::ListStyleUndefined;
    }
    else
    {
        Q_ASSERT(false);
    }

    LIST_MODIFICATION(setStyle(aStyle));
}

void TextFormatEditDialog::on_listIndentSpinBox_valueChanged(int aValue)
{
    LIST_MODIFICATION(setIndent(aValue));
}

void TextFormatEditDialog::on_listPrefixEdit_textEdited(const QString &aValue)
{
    LIST_MODIFICATION(setNumberPrefix(aValue));
}

void TextFormatEditDialog::on_listSuffixEdit_textEdited(const QString &aValue)
{
    LIST_MODIFICATION(setNumberSuffix(aValue));
}

void TextFormatEditDialog::on_tableCellButton_clicked()
{
    showOrHideCategory(ui->tableCellFrame, ui->tableCellButton);
}

#define TABLE_CELL_MODIFICATION(action) \
    mTextTableCellFormat.action; \
    ((QTextTableCellFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_tableCellTopPaddingSpinBox_valueChanged(double aValue)
{
    TABLE_CELL_MODIFICATION(setTopPadding(aValue));
}

void TextFormatEditDialog::on_tableCellBottomPaddingSpinBox_valueChanged(double aValue)
{
    TABLE_CELL_MODIFICATION(setBottomPadding(aValue));
}

void TextFormatEditDialog::on_tableCellLeftPaddingSpinBox_valueChanged(double aValue)
{
    TABLE_CELL_MODIFICATION(setLeftPadding(aValue));
}

void TextFormatEditDialog::on_tableCellRightPaddingSpinBox_valueChanged(double aValue)
{
    TABLE_CELL_MODIFICATION(setRightPadding(aValue));
}

void TextFormatEditDialog::on_tableTableButton_clicked()
{
    showOrHideCategory(ui->tableTableFrame, ui->tableTableButton);
}

void TextFormatEditDialog::on_tableAlignmentButton_clicked()
{
    showOrHideCategory(ui->tableAlignmentFrame, ui->tableAlignmentButton);
}

void TextFormatEditDialog::on_tableColumnWidthConstraintsButton_clicked()
{
    showOrHideCategory(ui->tableColumnWidthConstraintsScrollArea, ui->tableColumnWidthConstraintsButton);
}

#define TABLE_MODIFICATION(action) \
    mTextTableFormat.action; \
    ((QTextTableFormat *)&mTextFormat)->action;

void TextFormatEditDialog::on_tableHeaderRowsSpinBox_valueChanged(int aValue)
{
    TABLE_MODIFICATION(setHeaderRowCount(aValue));
}

void TextFormatEditDialog::on_tableColumnsSpinBox_valueChanged(int aValue)
{
    TABLE_MODIFICATION(setColumns(aValue));
}

void TextFormatEditDialog::on_tableCellsSpacingSpinBox_valueChanged(double aValue)
{
    TABLE_MODIFICATION(setCellSpacing(aValue));
}

void TextFormatEditDialog::on_tableCellsPaddingSpinBox_valueChanged(double aValue)
{
    TABLE_MODIFICATION(setCellPadding(aValue));
}

void TextFormatEditDialog::tableSetAlignment(const QString &aHorizontal, const QString &aVertical)
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

    TABLE_MODIFICATION(setAlignment(aHorizontalAlignment | aVerticalAlignment));
}

void TextFormatEditDialog::on_tableHorizontalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{
    tableSetAlignment(aValue, ui->tableVerticalAlignmentComboBox->currentText());
}

void TextFormatEditDialog::on_tableVerticalAlignmentComboBox_currentIndexChanged(const QString &aValue)
{
    tableSetAlignment(ui->tableHorizontalAlignmentComboBox->currentText(), aValue);
}

void TextFormatEditDialog::on_tableColumnWidthConstraintsAddButton_clicked()
{
    tableAddColumnWidthConstraint();
    tableUpdateColumnWidthConstraints();
}

void TextFormatEditDialog::tableUpdateColumnWidthConstraints()
{
    QVector<QTextLength> aTextLengths;

    for (int i=0; i<ui->tableColumnWidthConstraintsLayout->count(); ++i)
    {
        aTextLengths.append(((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(i)->widget())->value());
    }

    TABLE_MODIFICATION(setColumnWidthConstraints(aTextLengths));
}

void TextFormatEditDialog::tableAddColumnWidthConstraint()
{
    TextLengthFrame *aFrame=new TextLengthFrame(this);

    if (ui->tableColumnWidthConstraintsLayout->count()==0)
    {
        aFrame->setUpEnabled(false);
    }
    else
    {
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(ui->tableColumnWidthConstraintsLayout->count()-1)->widget())->setDownEnabled(true);
    }

    aFrame->setDownEnabled(false);

    connect(aFrame, SIGNAL(upPressed()),     this, SLOT(tableColumnWidthConstraintUp()));
    connect(aFrame, SIGNAL(downPressed()),   this, SLOT(tableColumnWidthConstraintDown()));
    connect(aFrame, SIGNAL(deletePressed()), this, SLOT(tableColumnWidthConstraintDelete()));
    connect(aFrame, SIGNAL(tabChanged()),    this, SLOT(tableColumnWidthConstraintChanged()));

    ui->tableColumnWidthConstraintsLayout->addWidget(aFrame);
    ui->tableColumnWidthConstraintsScrollArea->verticalScrollBar()->setValue(ui->tableColumnWidthConstraintsScrollArea->verticalScrollBar()->maximum());
}

void TextFormatEditDialog::tableColumnWidthConstraintUp()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->tableColumnWidthConstraintsLayout->indexOf(aWidget);

    if (index==1)
    {
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->tableColumnWidthConstraintsLayout->count()-1)
    {
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(index)->widget())->setDownEnabled(true);
    }

    ui->tableColumnWidthConstraintsLayout->removeWidget(aWidget);
    ui->tableColumnWidthConstraintsLayout->insertWidget(index-1, aWidget);

    tableUpdateColumnWidthConstraints();
}

void TextFormatEditDialog::tableColumnWidthConstraintDown()
{
    QWidget *aWidget=(QWidget *)sender();

    int index=ui->tableColumnWidthConstraintsLayout->indexOf(aWidget);

    if (index==0)
    {
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(0)->widget())->setUpEnabled(true);
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(1)->widget())->setUpEnabled(false);
    }

    if (index==ui->tableColumnWidthConstraintsLayout->count()-2)
    {
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(index)->widget())->setDownEnabled(false);
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(index+1)->widget())->setDownEnabled(true);
    }

    ui->tableColumnWidthConstraintsLayout->removeWidget(aWidget);
    ui->tableColumnWidthConstraintsLayout->insertWidget(index+1, aWidget);

    tableUpdateColumnWidthConstraints();
}

void TextFormatEditDialog::tableColumnWidthConstraintDelete()
{
    QWidget *aWidget=(QWidget *)sender();

    if (ui->tableColumnWidthConstraintsLayout->count()>1)
    {
        int index=ui->tableColumnWidthConstraintsLayout->indexOf(aWidget);

        if (index==0)
        {
            ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(1)->widget())->setUpEnabled(false);
        }

        if (index==ui->tableColumnWidthConstraintsLayout->count()-1)
        {
            ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(index-1)->widget())->setDownEnabled(false);
        }
    }

    delete aWidget;

    tableUpdateColumnWidthConstraints();
}

void TextFormatEditDialog::tableColumnWidthConstraintChanged()
{
    tableUpdateColumnWidthConstraints();
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

    QFont aFont=((QTextCharFormat *)&mTextFormat)->font();

    QTextCharFormat::UnderlineStyle aUnderlineStyle=((QTextCharFormat *)&mTextFormat)->underlineStyle();
    QString aUnderlineStyleStr="NoUnderline";

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
    QString aFontStyleHintStr="AnyStyle";

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
    QString aFontStyleStrategyStr="PreferDefault";
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

    QStringList aAnchors=((QTextCharFormat *)&mTextFormat)->anchorNames();
    QString anchorNames="[";

    for (int i=0; i<aAnchors.length(); ++i)
    {
        anchorNames.append("\"");
        anchorNames.append(aAnchors.at(i));
        anchorNames.append("\"");

        if (i<aAnchors.length()-1)
        {
            anchorNames.append("; ");
        }
    }

    anchorNames.append("]");

    QFont::Capitalization aFontCapitalization=((QTextCharFormat *)&mTextFormat)->fontCapitalization();
    QString aFontCapitalizationStr="MixedCase";

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
    QString aFontHintingPreferenceStr="PreferDefaultHinting";

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
    QString aVerticalAlignmentStr="AlignNormal";

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



    ui->charFontEdit->setText("["+aFont.family()+", "+QString::number(aFont.pointSize())+"]");
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
    ui->charFontStyleHintComboBox->setCurrentIndex(ui->charFontStyleHintComboBox->findText(aFontStyleHintStr));
    ui->charFontStyleStrategyComboBox->setCurrentIndex(ui->charFontStyleStrategyComboBox->findText(aFontStyleStrategyStr));
    ui->charFontStyleStrategyFlagComboBox->setCurrentIndex(ui->charFontStyleStrategyFlagComboBox->findText(aFontStyleStrategyFlagStr));
    ui->charAnchorCheckBox->setChecked(((QTextCharFormat *)&mTextFormat)->isAnchor());
    ui->charAnchorHrefLineEdit->setText(((QTextCharFormat *)&mTextFormat)->anchorHref());
    ui->charAnchorNamesEdit->setText(anchorNames);
    ui->charFontCapitalizationComboBox->setCurrentIndex(ui->charFontCapitalizationComboBox->findText(aFontCapitalizationStr));
    ui->charFontHintingPreferenceComboBox->setCurrentIndex(ui->charFontHintingPreferenceComboBox->findText(aFontHintingPreferenceStr));
    ui->charVerticalAlignmentComboBox->setCurrentIndex(ui->charVerticalAlignmentComboBox->findText(aVerticalAlignmentStr));
    ui->charTooltipEdit->setText(((QTextCharFormat *)&mTextFormat)->toolTip());

    CHAR_BLOCK_SIGNALS(false);
}

#define FRAME_BLOCK_SIGNALS(aLock) \
    ui->framePositionComboBox->blockSignals(aLock); \
    ui->framePositionComboBox->blockSignals(aLock); \
    ui->frameBorderSpinBox->blockSignals(aLock); \
    ui->frameBorderStyleComboBox->blockSignals(aLock); \
    ui->frameMarginSpinBox->blockSignals(aLock); \
    ui->frameTopMarginSpinBox->blockSignals(aLock); \
    ui->frameBottomMarginSpinBox->blockSignals(aLock); \
    ui->frameLeftMarginSpinBox->blockSignals(aLock); \
    ui->frameRightMarginSpinBox->blockSignals(aLock); \
    ui->framePaddingSpinBox->blockSignals(aLock); \
    ui->framePageBreakPolicyAutoCheckBox->blockSignals(aLock); \
    ui->framePageBreakPolicyBeforeCheckBox->blockSignals(aLock); \
    ui->framePageBreakPolicyAfterCheckBox->blockSignals(aLock);

void TextFormatEditDialog::frameUpdateProperties()
{
    FRAME_BLOCK_SIGNALS(true);

    QTextFrameFormat::Position aPosition=((QTextFrameFormat *)&mTextFormat)->position();
    QString aPositionStr="InFlow";

    if (aPosition==QTextFrameFormat::InFlow)
    {
        aPositionStr="InFlow";
    }
    else
    if (aPosition==QTextFrameFormat::FloatLeft)
    {
        aPositionStr="FloatLeft";
    }
    else
    if (aPosition==QTextFrameFormat::FloatRight)
    {
        aPositionStr="FloatRight";
    }
    else
    {
        Q_ASSERT(false);
    }

    QTextFrameFormat::BorderStyle aBorderStyle=((QTextFrameFormat *)&mTextFormat)->borderStyle();
    QString aBorderStyleStr="BorderStyle_None";

    if (aBorderStyle==QTextFrameFormat::BorderStyle_None)
    {
        aBorderStyleStr="BorderStyle_None";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Dotted)
    {
        aBorderStyleStr="BorderStyle_Dotted";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Dashed)
    {
        aBorderStyleStr="BorderStyle_Dashed";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Solid)
    {
        aBorderStyleStr="BorderStyle_Solid";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Double)
    {
        aBorderStyleStr="BorderStyle_Double";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_DotDash)
    {
        aBorderStyleStr="BorderStyle_DotDash";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_DotDotDash)
    {
        aBorderStyleStr="BorderStyle_DotDotDash";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Groove)
    {
        aBorderStyleStr="BorderStyle_Groove";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Ridge)
    {
        aBorderStyleStr="BorderStyle_Ridge";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Inset)
    {
        aBorderStyleStr="BorderStyle_Inset";
    }
    else
    if (aBorderStyle==QTextFrameFormat::BorderStyle_Outset)
    {
        aBorderStyleStr="BorderStyle_Outset";
    }
    else
    {
        Q_ASSERT(false);
    }

    QTextLength aWidth=((QTextFrameFormat *)&mTextFormat)->width();
    QString aWidthStr="[";

    switch (aWidth.type())
    {
        case QTextLength::VariableLength:   aWidthStr.append("VariableLength");   break;
        case QTextLength::FixedLength:      aWidthStr.append("FixedLength");      break;
        case QTextLength::PercentageLength: aWidthStr.append("PercentageLength"); break;
    }

    aWidthStr.append(", ");
    aWidthStr.append(QString::number(aWidth.rawValue()));
    aWidthStr.append("]");

    QTextLength aHeight=((QTextFrameFormat *)&mTextFormat)->height();
    QString aHeightStr="[";

    switch (aHeight.type())
    {
        case QTextLength::VariableLength:   aHeightStr.append("VariableLength");   break;
        case QTextLength::FixedLength:      aHeightStr.append("FixedLength");      break;
        case QTextLength::PercentageLength: aHeightStr.append("PercentageLength"); break;
    }

    aHeightStr.append(", ");
    aHeightStr.append(QString::number(aHeight.rawValue()));
    aHeightStr.append("]");

    QTextFormat::PageBreakFlags aPageBreaks=((QTextFrameFormat *)&mTextFormat)->pageBreakPolicy();



    ui->framePositionComboBox->setCurrentIndex(ui->framePositionComboBox->findText(aPositionStr));
    ui->frameBorderSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->border());
    ui->frameBorderStyleComboBox->setCurrentIndex(ui->frameBorderStyleComboBox->findText(aBorderStyleStr));
    ui->frameMarginSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->margin());
    ui->frameTopMarginSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->topMargin());
    ui->frameBottomMarginSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->bottomMargin());
    ui->frameLeftMarginSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->leftMargin());
    ui->frameRightMarginSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->rightMargin());
    ui->framePaddingSpinBox->setValue(((QTextFrameFormat *)&mTextFormat)->padding());
    ui->frameWidthEdit->setText(aWidthStr);
    ui->frameHeightEdit->setText(aHeightStr);
    ui->framePageBreakPolicyAutoCheckBox->setChecked(aPageBreaks==QTextFormat::PageBreak_Auto);
    ui->framePageBreakPolicyBeforeCheckBox->setChecked(aPageBreaks & QTextFormat::PageBreak_AlwaysBefore);
    ui->framePageBreakPolicyAfterCheckBox->setChecked(aPageBreaks & QTextFormat::PageBreak_AlwaysAfter);

    FRAME_BLOCK_SIGNALS(false);
}

#define IMAGE_BLOCK_SIGNALS(aLock) \
    ui->imageNameEdit->blockSignals(aLock); \
    ui->imageWidthSpinBox->blockSignals(aLock); \
    ui->imageHeightSpinBox->blockSignals(aLock);

void TextFormatEditDialog::imageUpdateProperties()
{
    IMAGE_BLOCK_SIGNALS(true);

    ui->imageNameEdit->setText(((QTextImageFormat *)&mTextFormat)->name());
    ui->imageWidthSpinBox->setValue(((QTextImageFormat *)&mTextFormat)->width());
    ui->imageHeightSpinBox->setValue(((QTextImageFormat *)&mTextFormat)->height());

    IMAGE_BLOCK_SIGNALS(false);
}

#define LIST_BLOCK_SIGNALS(aLock) \
    ui->listStyleComboBox->blockSignals(aLock); \
    ui->listIndentSpinBox->blockSignals(aLock); \
    ui->listPrefixEdit->blockSignals(aLock); \
    ui->listSuffixEdit->blockSignals(aLock);

void TextFormatEditDialog::listUpdateProperties()
{
    LIST_BLOCK_SIGNALS(true);

    QTextListFormat::Style aStyle=((QTextListFormat *)&mTextFormat)->style();
    QString aStyleStr="ListStyleUndefined";

    if (aStyle==QTextListFormat::ListDisc)
    {
        aStyleStr="ListDisc";
    }
    else
    if (aStyle==QTextListFormat::ListCircle)
    {
        aStyleStr="ListCircle";
    }
    else
    if (aStyle==QTextListFormat::ListSquare)
    {
        aStyleStr="ListSquare";
    }
    else
    if (aStyle==QTextListFormat::ListDecimal)
    {
        aStyleStr="ListDecimal";
    }
    else
    if (aStyle==QTextListFormat::ListLowerAlpha)
    {
        aStyleStr="ListLowerAlpha";
    }
    else
    if (aStyle==QTextListFormat::ListUpperAlpha)
    {
        aStyleStr="ListUpperAlpha";
    }
    else
    if (aStyle==QTextListFormat::ListLowerRoman)
    {
        aStyleStr="ListLowerRoman";
    }
    else
    if (aStyle==QTextListFormat::ListUpperRoman)
    {
        aStyleStr="ListUpperRoman";
    }
    else
    if (aStyle==QTextListFormat::ListStyleUndefined)
    {
        aStyleStr="ListStyleUndefined";
    }
    else
    {
        Q_ASSERT(false);
    }

    ui->listStyleComboBox->setCurrentIndex(ui->listStyleComboBox->findText(aStyleStr));
    ui->listIndentSpinBox->setValue(((QTextListFormat *)&mTextFormat)->indent());
    ui->listPrefixEdit->setText(((QTextListFormat *)&mTextFormat)->numberPrefix());
    ui->listSuffixEdit->setText(((QTextListFormat *)&mTextFormat)->numberSuffix());

    LIST_BLOCK_SIGNALS(false);
}

#define TABLE_CELL_BLOCK_SIGNALS(aLock) \
    ui->tableCellTopPaddingSpinBox->blockSignals(aLock); \
    ui->tableCellBottomPaddingSpinBox->blockSignals(aLock); \
    ui->tableCellLeftPaddingSpinBox->blockSignals(aLock); \
    ui->tableCellRightPaddingSpinBox->blockSignals(aLock);

void TextFormatEditDialog::tableCellUpdateProperties()
{
    TABLE_CELL_BLOCK_SIGNALS(true);

    ui->tableCellTopPaddingSpinBox->setValue(((QTextTableCellFormat *)&mTextFormat)->topPadding());
    ui->tableCellBottomPaddingSpinBox->setValue(((QTextTableCellFormat *)&mTextFormat)->bottomPadding());
    ui->tableCellLeftPaddingSpinBox->setValue(((QTextTableCellFormat *)&mTextFormat)->leftPadding());
    ui->tableCellRightPaddingSpinBox->setValue(((QTextTableCellFormat *)&mTextFormat)->rightPadding());

    TABLE_CELL_BLOCK_SIGNALS(false);
}

#define TABLE_BLOCK_SIGNALS(aLock) \
    ui->tableHeaderRowsSpinBox->blockSignals(aLock); \
    ui->tableColumnsSpinBox->blockSignals(aLock); \
    ui->tableCellsSpacingSpinBox->blockSignals(aLock); \
    ui->tableCellsPaddingSpinBox->blockSignals(aLock); \
    ui->tableHorizontalAlignmentComboBox->blockSignals(aLock); \
    ui->tableVerticalAlignmentComboBox->blockSignals(aLock);

void TextFormatEditDialog::tableUpdateProperties()
{
    TABLE_BLOCK_SIGNALS(true);

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

    ui->tableHeaderRowsSpinBox->setValue(((QTextTableFormat *)&mTextFormat)->headerRowCount());
    ui->tableColumnsSpinBox->setValue(((QTextTableFormat *)&mTextFormat)->columns());
    ui->tableCellsSpacingSpinBox->setValue(((QTextTableFormat *)&mTextFormat)->cellSpacing());
    ui->tableCellsPaddingSpinBox->setValue(((QTextTableFormat *)&mTextFormat)->cellPadding());
    ui->tableHorizontalAlignmentComboBox->setCurrentIndex(ui->tableHorizontalAlignmentComboBox->findText(aHorizontalAlignment));
    ui->tableVerticalAlignmentComboBox->setCurrentIndex(ui->tableVerticalAlignmentComboBox->findText(aVerticalAlignment));

    while (ui->tableColumnWidthConstraintsLayout->count()>0)
    {
        delete ui->tableColumnWidthConstraintsLayout->takeAt(0)->widget();
    }

    QVector<QTextLength> aColumnWidthConstraints=((QTextTableFormat *)&mTextFormat)->columnWidthConstraints();

    for (int i=0; i<aColumnWidthConstraints.count(); ++i)
    {
        tableAddColumnWidthConstraint();

        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(i)->widget())->blockSignals(true);
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(i)->widget())->setValue(aColumnWidthConstraints.at(i));
        ((TextLengthFrame *)ui->tableColumnWidthConstraintsLayout->itemAt(i)->widget())->blockSignals(false);
    }

    TABLE_BLOCK_SIGNALS(false);
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
    QString aLayoutDirectionStr="LayoutDirectionAuto";

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
        case 2: frameUpdateProperties(); break;
        case 3:
            charUpdateProperties();
            imageUpdateProperties();
        break;
        case 4: listUpdateProperties(); break;
        case 5:
            charUpdateProperties();
            tableCellUpdateProperties();
        break;
        case 6:
            frameUpdateProperties();
            tableUpdateProperties();
        break;
    }

    BLOCK_SIGNALS(false);
}
