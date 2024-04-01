#include "stroke.h"
#include "qjsonarray.h"

Stroke::Stroke(QColor color) : color(color)  {
    points = new vector<pair<int,int>>;
}

QJsonObject Stroke::toJson() {
    QJsonObject strokeJSON;
    QJsonArray pointsArray;
    for (auto point : *points) {
        QJsonObject pointObject;
        pointObject["x"] = point.first;
        pointObject["y"] = point.second;
        pointsArray.append(pointObject);
    }
    strokeJSON["points"] = pointsArray;
    strokeJSON["color"] = color.name(QColor::HexArgb);

    return strokeJSON;
}
