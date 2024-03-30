#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
    Pixel(); // 默认构造函数
    Pixel(unsigned char r, unsigned char g, unsigned char b); // 带参数的构造函数
    ~Pixel(); // 析构函数

    // 设置颜色值
    void setRGB(unsigned char r, unsigned char g, unsigned char b);

    // 获取颜色值
    unsigned char getR() const;
    unsigned char getG() const;
    unsigned char getB() const;

private:
    unsigned char red, green, blue;
};

#endif // PIXEL_H
