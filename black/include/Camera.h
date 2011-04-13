#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera : public GameObject
{
public:
    Camera(const std::string name) : GameObject(name) {}

    virtual ~Camera() {};

    virtual void setView(GameObject *obj, ObjectManager::RenderType type) = 0;
    virtual void setPerspectiveView(GameObject *obj, ObjectManager::RenderType type) = 0;

    struct Point
    {
        float x, y, z;
    };

    virtual Point getPosition() = 0;
};

#endif  // __CAMERA_H__
