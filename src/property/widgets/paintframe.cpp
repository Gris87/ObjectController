#include "paintframe.h"
#include "ui_paintframe.h"

#include <QFileDialog>

#include "../dialogs/sizeeditdialog.h"

PaintFrame::PaintFrame(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintFrame)
{
    ui->setupUi(this);

    mAttributes=aAttributes;

    mImageView=new PaintView(aValue, this);
    ui->mainLayout->insertWidget(1, mImageView);

    mLeftArea=new ColorArea(mAttributes, this);
    mLeftArea->setColor(QColor(0, 0, 0));
    mLeftArea->setMinimumSize(16, 16);
    mLeftArea->setMaximumSize(16, 16);
    mLeftArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mLeftArea->setTransparentBlockSize(4);
    mLeftArea->setSelectAllowed(!aMono);
    mLeftArea->setPopupAllowed(!aMono);

    ui->standardGridLayout->addWidget(mLeftArea, 0, 0, 1, 1);

    connect(mLeftArea, SIGNAL(colorChanged(QColor)),      this, SLOT(leftColorChanged(QColor)));



    mRightArea=new ColorArea(mAttributes, this);
    mRightArea->setColor(QColor(255, 255, 255));
    mRightArea->setMinimumSize(16, 16);
    mRightArea->setMaximumSize(16, 16);
    mRightArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mRightArea->setTransparentBlockSize(4);
    mRightArea->setSelectAllowed(!aMono);
    mRightArea->setPopupAllowed(!aMono);

    ui->standardGridLayout->addWidget(mRightArea, 1, 1, 1, 1);

    connect(mRightArea, SIGNAL(colorChanged(QColor)),      this, SLOT(rightColorChanged(QColor)));



    if (!aMono)
    {
        QList<QColor> aColors;

        aColors.append(QColor(0,   0,   0));
        aColors.append(QColor(128, 128, 128));
        aColors.append(QColor(128, 0,   0));
        aColors.append(QColor(128, 128, 0));
        aColors.append(QColor(0,   128, 0));
        aColors.append(QColor(0,   128, 128));
        aColors.append(QColor(0,   0,   128));
        aColors.append(QColor(128, 0,   128));
        aColors.append(QColor(128, 128, 64));
        aColors.append(QColor(0,   64,  64));
        aColors.append(QColor(0,   128, 255));
        aColors.append(QColor(0,   64,  128));
        aColors.append(QColor(128, 0,   255));
        aColors.append(QColor(128, 64,  0));

        aColors.append(QColor(255, 255, 255));
        aColors.append(QColor(192, 192, 192));
        aColors.append(QColor(255, 0,   0));
        aColors.append(QColor(255, 255, 0));
        aColors.append(QColor(0,   255, 0));
        aColors.append(QColor(0,   255, 255));
        aColors.append(QColor(0,   0,   255));
        aColors.append(QColor(255, 0,   255));
        aColors.append(QColor(255, 255, 128));
        aColors.append(QColor(0,   255, 128));
        aColors.append(QColor(128, 255, 255));
        aColors.append(QColor(128, 128, 255));
        aColors.append(QColor(255, 0,   128));
        aColors.append(QColor(255, 128, 64));

        if (aAttributes)
        {
            for (int i=0; i<aColors.length(); ++i)
            {
                aColors[i]=aAttributes->colorValue("color"+QString::number(i+1), aColors.at(i));
            }
        }

        for (int i=0; i<2; ++i)
        {
            for (int j=0; j<14; ++j)
            {
                ColorArea *aArea=new ColorArea(0, this);
                aArea->setColor(aColors.at(i*14+j));
                aArea->setMinimumSize(16, 16);
                aArea->setMaximumSize(16, 16);
                aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

                aArea->setTransparentBlockSize(4);
                aArea->setSelectAllowed(false);
                aArea->setPopupAllowed(false);

                ui->additionalGridLayout->addWidget(aArea, i, j, 1, 1);

                connect(aArea, SIGNAL(clicked()),      this, SLOT(colorLeftSelected()));
                connect(aArea, SIGNAL(rightClicked()), this, SLOT(colorRightSelected()));
            }
        }
    }

    if (aAttributes)
    {
        bool aAllowOpen=aAttributes->boolValue("allowOpen", true);
        bool aAllowResize=aAttributes->boolValue("allowResize", true);

        if (aAllowOpen || aAllowResize)
        {
            ui->openButton->setVisible(aAllowOpen);
            ui->resizeButton->setVisible(aAllowResize);
        }
        else
        {
            ui->headerWidget->setVisible(false);
        }
    }
}

PaintFrame::~PaintFrame()
{
    delete ui;
}

void PaintFrame::colorLeftSelected()
{
    mLeftArea->setColor(((ColorArea *)sender())->color());
}

void PaintFrame::colorRightSelected()
{
    mRightArea->setColor(((ColorArea *)sender())->color());
}

void PaintFrame::leftColorChanged(QColor aColor)
{
    mImageView->setFirstColor(aColor);
}

void PaintFrame::rightColorChanged(QColor aColor)
{
    mImageView->setSecondColor(aColor);
}

void PaintFrame::on_openButton_clicked()
{
    QFileDialog dialog(this);

    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);

    if (dialog.exec())
    {
        QPixmap aPixmap(dialog.selectedFiles().at(0));
        mImageView->setImage(aPixmap);

        mLeftArea->setColor(QColor(0, 0, 0));
        mRightArea->setColor(QColor(255, 255, 255));
    }
}

void PaintFrame::on_resizeButton_clicked()
{
    SizeEditDialog dialog(mImageView->image().size(), mAttributes, this);

    dialog.setWindowTitle("Resize");

    if (dialog.exec())
    {
        mImageView->resizeImage(dialog.resultValue());
    }
}

QPixmap PaintFrame::image() const
{
    return mImageView->image();
}

PaintView* PaintFrame::getImageView()
{
    return mImageView;
}
