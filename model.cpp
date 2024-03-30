#include "model.h"



Model::Model(QObject *parent)
    : QObject(parent) {

}




Model::~Model() {
}


void Model::drawPixel(int x, int y, const QColor &color) {
    frames[nowediting].setPixel(x, y, color);
}

