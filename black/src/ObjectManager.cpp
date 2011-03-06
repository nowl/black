#include "Black.h"

using namespace std;

ObjectManager::ObjectManager()
    : nextID(0)
{
}

ObjectManager::~ObjectManager()
{
    ObjectIter iter;
    iter = Objects.begin();
    for(; iter != Objects.end(); iter++)
        delete iter->second;
}

GameObject*
ObjectManager::getObject(unsigned int id)
{
    return Objects[id];
}

void
ObjectManager::addManagedObject(GameObject *obj)
{
    obj->setID(nextID);
    Objects[nextID] = obj;
    ++nextID;
}

void
ObjectManager::update(unsigned int tick)
{
    ObjectIter iter = Objects.begin();
    for(; iter != Objects.end(); iter++)
    {
        GameObject *obj = iter->second;
        obj->update(obj, tick);
    }
}

void
ObjectManager::render(float interpolation)
{
    GraphicsContext *gc = BlackEngine::get()->getGraphicsContext();
    ObjectIter iter = Objects.begin();
    for(; iter != Objects.end(); iter++)
    {
        GameObject *obj = iter->second;

        glPushMatrix();

        obj->render(*gc, interpolation);

        glPopMatrix();
    }
}

void
ObjectManager::sendSync(const Message& message)
{
    Messages.push_back(message);
}

void
ObjectManager::sendASync(const Message& message)
{
    GameObject *dest = message.receiver;

#ifdef LOG_MESSAGES
    cout << message << endl;
#endif

    if(dest)
    {
        // if destination message

        dest->receive(message);
    }
    else
    {
        // broadcast message, send based on type
        if(BroadcastReceivers.find(message.type) != BroadcastReceivers.end())
        {
            // have receivers
            vector<GameObject*>& receivers = BroadcastReceivers[message.type];

            vector<GameObject*>::iterator iter;
            for(iter = receivers.begin(); iter != receivers.end(); iter++)
            {
                bool consume = (*iter)->receive(message);

                // if this receiver "consumes" the message then don't send to any other receivers
                if(consume)
                    break;
            }
        }
    }
}

void
ObjectManager::registerBroadcastReceiver(const char *type, GameObject* obj)
{
    HashedString str(type);
    BroadcastReceivers[str.getHash()].push_back(obj);
}

void
ObjectManager::deliverMessages()
{
    vector<Message>::iterator iter;
    for(iter = Messages.begin(); iter != Messages.end(); iter++)
        sendASync(*iter);
    Messages.clear();
}
