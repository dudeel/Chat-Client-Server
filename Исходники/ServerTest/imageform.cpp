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
    _width = _ui->imagePreview->width();
    _height = _ui->imagePreview->height();

    _currentImage = _image;

    _ui->imagePreview->setPixmap( QPixmap::fromImage(_currentImage) );

    if( !_currentImage.isNull() )
    {
        _ui->imagePreview->setPixmap(QPixmap::fromImage(_currentImage).scaled(500, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _ui->imagePreview->resize(500, 600);
    }
}

void ImageForm::resizeEvent(QResizeEvent* event)
{
    if( !_currentImage.isNull() )
    {
        _ui->imagePreview->setPixmap(QPixmap::fromImage(_currentImage).scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _ui->imagePreview->resize(event->size());
    }
}
