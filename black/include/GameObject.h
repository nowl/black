#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <map>
#include <string>
#include <vector>

template<int N, class T> class vect;
class IRenderable;
class Message;
class HashedString;

class GameObject
{
public:
    GameObject(const std::string name);
    virtual ~GameObject();

    void getScreenLoc(vect<2, float>& loc);
    void setScreenLoc(const vect<2, float>& loc);
    void getWorldLoc(vect<2, float>& loc);
    void setWorldLoc(const vect<2, float>& loc);
    void invalidate();
    std::string getName() const;
    unsigned long getHash() const;
    void setRenderer(IRenderable *renderer, bool owns = true);

    virtual void update(GameObject *obj, unsigned int tick);
    virtual bool receive(const Message& message);
    virtual void render(GraphicsContext &context, float interpolation);

protected:
    IRenderable *Renderer;
    HashedString Name;
    bool OwnsRenderer;
};

#endif // __GAME_OBJECT_H__
