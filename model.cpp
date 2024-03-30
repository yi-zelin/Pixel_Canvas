#include "model.h"

Model::Model() {
}

Model::~Model() {
}

void Model::addFrame(const QString& framePath) {
    frames.append(framePath);
}

void Model::removeFrame(int index) {
    if (index >= 0 && index < frames.size()) {
        frames.removeAt(index);
    }
}

QString Model::getFrame(int index) const {
    if (index >= 0 && index < frames.size()) {
        return frames[index];
    }
    return QString();
}

int Model::frameCount() const {
    return frames.size();
}

QString Model::exportToJson() const {
    QJsonArray framesArray;
    for (const auto& framePath : frames) {
        framesArray.append(framePath);
    }

    QJsonObject rootObj;
    rootObj["frames"] = framesArray;
    QJsonDocument doc(rootObj);
    return QString(doc.toJson(QJsonDocument::Compact));
}

void Model::importFromJson(const QString& jsonStr) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject rootObj = doc.object();
    QJsonArray framesArray = rootObj["frames"].toArray();

    frames.clear();
    for (int i = 0; i < framesArray.size(); ++i) {
        frames.append(framesArray[i].toString());
    }
}
