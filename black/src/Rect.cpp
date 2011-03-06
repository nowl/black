#include "Black.h"

Rect::Rect(float left, float right, float bottom, float top)
    : left(left), right(right), top(top), bottom(bottom)
{
    x = (left+right)/2;
    y = (top+bottom)/2;
    width = right-left;
    height = top-bottom;
}

void
Rect::moveX(float dx)
{
    x += dx;
    left += dx;
    right += dx;
}

void
Rect::moveY(float dy)
{
    y += dy;
    top += dy;
    bottom += dy;
}

void
Rect::setX(float val)
{
    float dx = val - x;
    x = val;
    left += dx;
    right += dx;
}

void
Rect::setY(float val)
{
    float dy = val - y;
    y = val;
    top += dy;
    bottom += dy;
}

void
Rect::setWidth(float val)
{
    width = val;
    left = x - width/2;
    right = x + width/2;
}

void
Rect::setHeight(float val)
{
    height = val;
    bottom = x - height/2;
    top = x + height/2;
}
