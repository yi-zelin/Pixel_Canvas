#include "Model.h"

Model::Model() {
}

Model::~Model() {
}

void Model::addFrame(const Canvas& frame) {
    frames.append(frame);
}

void Model::removeFrame(int index) {
    if (index >= 0 && index < frames.size()) {
        frames.removeAt(index);
    }
}

Canvas Model::getFrame(int index) const {
    if (index >= 0 && index < frames.size()) {
        return frames.at(index);
    }
    // 如果索引无效，返回一个默认构造的Canvas对象
    return Canvas(0, 0); // 注意：你可能需要确保Canvas有一个默认构造函数或这里提供合适的参数
}

int Model::frameCount() const {
    return frames.size();
}


