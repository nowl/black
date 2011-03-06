#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <map>
#include <vector>

template<int N, class T> class vect;
class IRenderable;
class Message;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    void getScreenLoc(vect<2, float>& loc);
    void setScreenLoc(const vect<2, float>& loc);
    void getWorldLoc(vect<2, float>& loc);
    void setWorldLoc(const vect<2, float>& loc);
    void invalidate();
    void setID(unsigned int id);
    void setRenderer(IRenderable *renderer);

    virtual void update(GameObject *obj, unsigned int tick);
    virtual bool receive(const Message& message);
    virtual void render(GraphicsContext &context, float interpolation);

protected:
    unsigned int ID;
    IRenderable *Renderer;
};

#endif // __GAME_OBJECT_H__
