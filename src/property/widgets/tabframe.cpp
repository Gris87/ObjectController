#include "tabframe.h"
#include "ui_tabframe.h"

TabFrame::TabFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabFrame)
{
    ui->setupUi(this);
}

TabFrame::~TabFrame()
{
    delete ui;
}

void TabFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void TabFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

qreal TabFrame::position() const
{
    return ui->positionSpinBox->value();
}

void TabFrame::setPosition(const qreal &aPosition)
{
    ui->positionSpinBox->setValue(aPosition);
}

QTextOption::TabType TabFrame::type() const
{
    QString aType=ui->typeComboBox->currentText();

    if (aType=="LeftTab")
    {
        return QTextOption::LeftTab;
    }
    else
    if (aType=="RightTab")
    {
        return QTextOption::RightTab;
    }
    else
    if (aType=="CenterTab")
    {
        return QTextOption::CenterTab;
    }
    else
    if (aType=="DelimiterTab")
    {
        return QTextOption::DelimiterTab;
    }
    else
    {
        Q_ASSERT(false);
    }

    return QTextOption::LeftTab;
}

void TabFrame::setType(const QTextOption::TabType &aType)
{
    QString aTypeStr;

    if (aType==QTextOption::LeftTab)
    {
        aTypeStr="LeftTab";
    }
    else
    if (aType==QTextOption::RightTab)
    {
        aTypeStr="RightTab";
    }
    else
    if (aType==QTextOption::CenterTab)
    {
        aTypeStr="CenterTab";
    }
    else
    if (aType==QTextOption::DelimiterTab)
    {
        aTypeStr="DelimiterTab";
    }
    else
    {
        Q_ASSERT(false);
    }

    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aTypeStr));
}

QChar TabFrame::delimiter() const
{
    if (ui->delimiterEdit->text().length()>0)
    {
        return ui->delimiterEdit->text().at(0);
    }

    return QChar();
}

void TabFrame::setDelimiter(const QChar &aDelimiter)
{
    if (aDelimiter==QChar())
    {
        ui->delimiterEdit->setText("");
    }
    else
    {
        ui->delimiterEdit->setText(aDelimiter);
    }
}

QTextOption::Tab TabFrame::tab() const
{
    return QTextOption::Tab(position(), type(), delimiter());
}

void TabFrame::setTab(const QTextOption::Tab &aTab)
{
    setPosition(aTab.position);
    setType(aTab.type);
    setDelimiter(aTab.delimiter);
}

void TabFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void TabFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void TabFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}

void TabFrame::on_positionSpinBox_valueChanged(double /*aValue*/)
{
    emit tabChanged();
}

void TabFrame::on_typeComboBox_currentIndexChanged(const QString &/*aValue*/)
{
    emit tabChanged();
}

void TabFrame::on_delimiterEdit_textEdited(const QString &/*aValue*/)
{
    emit tabChanged();
}
