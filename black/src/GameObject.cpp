#include "Black.h"

GameObject::GameObject()
    : Renderer(NULL)
{
    BlackEngine::get()->getObjectManager()->addManagedObject(this);
}

GameObject::~GameObject()
{

}

void
GameObject::render(GraphicsContext &context, float interpolation)
{
    if(Renderer)
        Renderer->Render(context, interpolation, this);
}

void
GameObject::setRenderer(IRenderable *renderer)
{
    Renderer = renderer;
}

void
GameObject::setID(unsigned int id)
{
    ID = id;
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
