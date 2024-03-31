#include <QList>
#include <QPoint>
#include <QColor>

class Stroke {
public:
    void addPoint(const QPoint& point);
    const QList<QPoint>& getPoints() const;
    void setColor(const QColor& color);
    const QColor& getColor() const;

private:
    QList<QPoint> points;
    QColor color;
};
