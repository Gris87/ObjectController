#include "textformateditdialog.h"
#include "ui_textformateditdialog.h"

#include "brusheditdialog.h"

TextFormatEditDialog::TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextFormatEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

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
        mTextFormat=mTextBlockFormat;
    }
    else
    if (aValue=="CharFormat")
    {
        mTextFormat=mTextCharFormat;
    }
    else
    if (aValue=="FrameFormat")
    {
        mTextFormat=mTextFrameFormat;
    }
    else
    if (aValue=="ImageFormat")
    {
        mTextFormat=mTextImageFormat;
    }
    else
    if (aValue=="ListFormat")
    {
        mTextFormat=mTextListFormat;
    }
    else
    if (aValue=="TableCellFormat")
    {
        mTextFormat=mTextTableCellFormat;
    }
    else
    if (aValue=="TableFormat")
    {
        mTextFormat=mTextTableFormat;
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

#define BLOCK_SIGNALS(aLock) \
    ui->typeComboBox->blockSignals(aLock);

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

    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aTypeStr));

    BLOCK_SIGNALS(false);
}
