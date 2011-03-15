#include "Black.h"

using namespace std;

GameObject::GameObject(const std::string name)
    : Renderer(NULL), Name(name)
{
    BlackEngine::get()->getActiveGameState()->addManagedObject(this);
}

GameObject::~GameObject()
{
    if(Renderer && OwnsRenderer)
        delete Renderer;
}

void
GameObject::render(GraphicsContext &context, float interpolation)
{
    if(Renderer)
        Renderer->Render(context, interpolation, this);
}

void
GameObject::setRenderer(IRenderable *renderer, bool owns)
{
    if(Renderer && OwnsRenderer)
        delete Renderer;

    OwnsRenderer = owns;
    Renderer = renderer;
}

void
GameObject::update(GameObject *obj, unsigned int tick)
{

}

bool
GameObject::receive(const Message& message)
{
    return false;
}

string
GameObject::getName() const
{
    return Name.getString();
}

unsigned long 
GameObject::getHash() const
{
    return Name.getHash();
}

