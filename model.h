#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QColor>

class Model : public QObject {
    Q_OBJECT

public:
    explicit Model(int width, int height, QObject *parent = nullptr);
    void setPixel(int x, int y, const QColor &color);
    QColor getPixel(int x, int y) const;
    const QImage& getCanvasImage() const;
    void clearImage();
    QImage canvasImage;
    QSize getSize();
signals:
    void imageChanged();

protected:

};


#endif // MODEL_H
