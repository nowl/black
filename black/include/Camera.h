#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera : public GameObject
{
public:
    Camera(const std::string name) : GameObject(name) {}

    virtual ~Camera() {};

    virtual void setView() = 0;
};

#endif  // __CAMERA_H__
