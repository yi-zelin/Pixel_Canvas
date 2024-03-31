#include "stroke.h"

Stroke::Stroke(QColor color) : color(color)  {
    points = new vector<pair<int,int>>;
}
