#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <iostream>

struct Message
{
    GameObject *sender;
    GameObject *receiver;
    unsigned long type;
    void *data;

    Message(unsigned long type, void *data, GameObject *receiver=NULL, GameObject *sender = NULL);
    Message(const char *type, void *data, GameObject *receiver=NULL, GameObject *sender = NULL);
};

std::ostream& operator<<(std::ostream& out, const Message& message);

#endif // __MESSAGE_H__
