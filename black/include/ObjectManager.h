#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include <map>
#include <string>
#include <vector>

class GameObject;
class Message;

class ObjectManager
{
public:
    typedef std::map<unsigned long, GameObject*>::iterator ObjectIter;

    ObjectManager();
    ~ObjectManager();

    GameObject* getObject(unsigned long hash);
    GameObject* getObject(std::string name);

    void addManagedObject(GameObject *obj);

    void update(unsigned int tick);
    void render(float interpolation);

    void sendSync(const Message& message);
    void sendASync(const Message& message);

    void registerBroadcastReceiver(const char *type, GameObject* obj);
    //void removeBroadcastReceiver(GameObject* obj);

private:
    ObjectManager(const ObjectManager&);
    ObjectManager operator=(const ObjectManager&);

    void deliverMessages();

    std::map<unsigned long, GameObject*> Objects;
    std::vector<Message> Messages;
    std::map<unsigned long, std::vector<GameObject *> > BroadcastReceivers;
};

#endif    // __OBJECT_MANAGER_H__
