#include "imageform.h"
#include "ui_imageform.h"
#include <QDebug>
#include <QResizeEvent>

ImageForm::ImageForm(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ImageForm)
{
    _ui->setupUi(this);
}

ImageForm::~ImageForm()
{
    delete _ui;
}

void ImageForm::openImageFrame(QImage _image)
{
    _currentImage = _image;
    _ui->imagePreview->setPixmap( QPixmap::fromImage(_currentImage) );

    changeSize(500, 600);
}

void ImageForm::resizeEvent(QResizeEvent* event)
{ changeSize(event->size().width() , event->size().height()); }

void ImageForm::changeSize(int width, int height)
{
    if( !_currentImage.isNull() )
    {
        _ui->imagePreview->setPixmap(QPixmap::fromImage(_currentImage).scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _ui->imagePreview->resize(width, height);
    }
}
