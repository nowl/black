#include "Black.h"

using namespace std;

GameState::GameState(const string name)
    : Name(name)
{
}

GameState::~GameState()
{
}

string
GameState::getName() const
{
    return Name;
}

GameObject*
GameState::getObject(unsigned long hash)
{
    return OM.getObject(hash);
}

GameObject*
GameState::getObject(string name)
{
    return OM.getObject(name);
}

void
GameState::addManagedObject(GameObject *obj)
{
    OM.addManagedObject(obj);
}

void
GameState::update(unsigned int tick)
{
    OM.update(tick);
}

void
GameState::render(float interpolation, ObjectManager::RenderType type)
{
    OM.render(interpolation, type);
}

void
GameState::sendSync(const Message& message)
{
    OM.sendSync(message);
}

void
GameState::sendASync(const Message& message)
{
    OM.sendASync(message);
}

void
GameState::registerBroadcastReceiver(const char *type, GameObject* obj)
{
    OM.registerBroadcastReceiver(type, obj);
}

