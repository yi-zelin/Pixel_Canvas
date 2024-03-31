#include "Stroke.h"

void Stroke::addPoint(const QPoint& point) {
    points.append(point);
}

const QList<QPoint>& Stroke::getPoints() const {
    return points;
}

void Stroke::setColor(const QColor& color) {
    this->color = color;
}

const QColor& Stroke::getColor() const {
    return color;
}
