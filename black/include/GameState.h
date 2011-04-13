#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <string>
#include <map>
#include <vector>

#include "ObjectManager.h"

class GameObject;
class Message;

class GameState
{
public:
    GameState(const std::string name);
    ~GameState();

    std::string getName() const;

    GameObject* getObject(unsigned long hash);
    GameObject* getObject(std::string name);

    void addManagedObject(GameObject *obj);

    void update(unsigned int tick);
    void render(float interpolation, ObjectManager::RenderType type);

    void sendSync(const Message& message);
    void sendASync(const Message& message);

    void registerBroadcastReceiver(const char *type, GameObject* obj);
    //void removeBroadcastReceiver(GameObject* obj);

    typedef void (*RenderHook)(void);

private:
    GameState(const GameState&);
    GameState operator=(const GameState&);

    ObjectManager OM;
    std::string Name;
};

#endif    // __GAME_STATE_H__
