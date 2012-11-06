#include "paintframe.h"
#include "ui_paintframe.h"

#include <QFileDialog>

#include "../dialogs/resizedialog.h"

PaintFrame::PaintFrame(QPixmap aValue, bool aMono, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintFrame)
{
    ui->setupUi(this);

    mImageView=new PaintView(aValue, this);
    ui->mainLayout->insertWidget(1, mImageView);

    mLeftArea=new ColorArea(this);
    mLeftArea->setColor(QColor(0, 0, 0));
    mLeftArea->setMinimumSize(16, 16);
    mLeftArea->setMaximumSize(16, 16);
    mLeftArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mLeftArea->selectAllowed=!aMono;
    mLeftArea->popupAllowed=!aMono;

    ui->standardGridLayout->addWidget(mLeftArea, 0, 0, 1, 1);

    connect(mLeftArea, SIGNAL(colorChanged(QColor)),      this, SLOT(leftColorChanged(QColor)));



    mRightArea=new ColorArea(this);
    mRightArea->setColor(QColor(255, 255, 255));
    mRightArea->setMinimumSize(16, 16);
    mRightArea->setMaximumSize(16, 16);
    mRightArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mRightArea->selectAllowed=!aMono;
    mRightArea->popupAllowed=!aMono;

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

        for (int i=0; i<2; ++i)
        {
            for (int j=0; j<14; ++j)
            {
                ColorArea *aArea=new ColorArea(this);
                aArea->setColor(aColors.at(i*14+j));
                aArea->setMinimumSize(16, 16);
                aArea->setMaximumSize(16, 16);
                aArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

                aArea->selectAllowed=false;
                aArea->popupAllowed=false;

                ui->additionalGridLayout->addWidget(aArea, i, j, 1, 1);

                connect(aArea, SIGNAL(clicked(ColorArea*)),      this, SLOT(colorLeftSelected(ColorArea*)));
                connect(aArea, SIGNAL(rightClicked(ColorArea*)), this, SLOT(colorRightSelected(ColorArea*)));
            }
        }
    }
}

PaintFrame::~PaintFrame()
{
    delete ui;
}

void PaintFrame::colorLeftSelected(ColorArea *aArea)
{
    mLeftArea->setColor(aArea->color());
}

void PaintFrame::colorRightSelected(ColorArea *aArea)
{
    mRightArea->setColor(aArea->color());
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
    ResizeDialog dialog(mImageView->image().size(), this);

    if (dialog.exec())
    {
        mImageView->resizeImage(dialog.newSize());
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
