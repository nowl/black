#include "Black.h"

Message::Message(unsigned long type, void *data, GameObject *receiver, GameObject *sender)
    : receiver(receiver), sender(sender), type(type), data(data)
{}

Message::Message(const char *type, void *data, GameObject *receiver, GameObject *sender)
    : receiver(receiver), sender(sender), data(data)
{
    HashedString hash(type);
    this->type = hash.getHash();
}

#ifdef LOG_MESSAGES
std::ostream& operator<<(std::ostream& out, const Message& message)
{
    out << "type: \"" << HashedString::reverse(message.type) << "\" sender: " << message.sender << " receiver: " << message.receiver;
    return out;
}
#endif
