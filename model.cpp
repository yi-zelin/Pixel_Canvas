#include "Model.h"

Model::Model(QObject *parent) : QObject(parent) {
    // 初始化Model时的操作
}

// void Model::createPixelItems(int width, int height) {
//     scene->setSceneRect(0, 0, 100, 100); // 设置画布大小

//     // 创建棋盘格样式的像素项并添加到场景中
//     for (int i = 0; i < 100; ++i) {
//         for (int j = 0; j < 100; ++j) {
//             QColor color = ((i + j) % 2 == 0) ? Qt::white : Qt::black;
//             PixelItem *item = new PixelItem(i, j, color);
//             scene->addItem(item);
//         }
//     }
// }

QList<PixelItem *> Model::getPixelItems() const {
    return pixelItems;
}
