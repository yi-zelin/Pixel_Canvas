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
public slots:
signals:
    void imageChanged();

private:
    QImage canvasImage;
};

#endif // MODEL_H
