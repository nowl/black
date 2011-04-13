#include "Black.h"

using namespace std;

ObjectManager::ObjectManager()
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
ObjectManager::getObject(unsigned long hash)
{
    return Objects[hash];
}

GameObject*
ObjectManager::getObject(std::string name)
{
    HashedString hs(name);
    return Objects[hs.getHash()];
}

void
ObjectManager::addManagedObject(GameObject *obj)
{
    unsigned int hash = obj->getHash();

    if(Objects.find(hash) != Objects.end())
        delete Objects[hash];

    Objects[hash] = obj;
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
ObjectManager::render(float interpolation, RenderType renderType)
{
    GraphicsContext *gc = BlackEngine::get()->getGraphicsContext();
    Camera *camera = BlackEngine::get()->getCamera();
    ObjectIter iter = Objects.begin();
    for(; iter != Objects.end(); iter++)
    {
        GameObject *obj = iter->second;

        glPushMatrix();

        glLoadIdentity();

        // set up view and perspective if available
        if(camera)
        {
            camera->setPerspectiveView(obj, renderType);
            camera->setView(obj, renderType);
        }

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
