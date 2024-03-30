#include "model.h"



Model::Model(QObject *parent)
    : QObject(parent) {

}




Model::~Model() {
}


void Model::drawPixel(int x, int y, const QColor &color) {
    frames[nowediting].setPixel(x, y, color);
}

int Model::getXSize() {
    return frames[nowediting].getWidth();
}

int Model::getYSize() {
    return frames[nowediting].getHeight();
}
