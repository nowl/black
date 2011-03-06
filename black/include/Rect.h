#ifndef __RECT_H__
#define __RECT_H__

class Rect
{
public:
    float left, right, top, bottom, x, y, width, height;


    Rect(float left, float right, float bottom, float top);

    void moveX(float dx);
    void moveY(float dy);
    void setX(float val);
    void setY(float val);
    void setWidth(float val);
    void setHeight(float val);
};

#endif // __RECT_H__
