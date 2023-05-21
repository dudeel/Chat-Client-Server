#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ImageForm;
}

class ImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageForm(QWidget* parent = 0);
    ~ImageForm();

private:
    Ui::ImageForm* _ui;
    QImage _currentImage;
    int _width;
    int _height;


public slots:
    void openImageFrame(QImage _image);
    void resizeEvent(QResizeEvent* event);
};

#endif // IMAGEFORM_H
