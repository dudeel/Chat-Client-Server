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
    void openImageFrame(QImage _image);

private:
    Ui::ImageForm* _ui;
    QImage _currentImage;
    void changeSize(int width, int height);

public slots:
    void resizeEvent(QResizeEvent* event);
};

#endif // IMAGEFORM_H
