#ifndef STROKE_H
#define STROKE_H
/*
Stroke header for Stroke class
By Kai-Chen Chiang,jinchao liang, Rishen Cao, Zelin Yi, Shuangji Li,Yuang sun
*/
#include "qcolor.h"
#include "qjsonobject.h"
#include <utility>
#include <vector>
using std::pair;
using std::vector;

class Stroke
{
public:
    Stroke(QColor color);
    vector<pair<int,int>> *points;
    QColor color;
    QJsonObject toJson();

};

#endif // STROKE_H
