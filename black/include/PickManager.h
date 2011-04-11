#ifndef __PICK_MANAGER_H__
#define __PICK_MANAGER_H__

#include <vector>
#include <string>

class PickManager
{
public:
    static PickManager* get();

    void getPicks(int x, int y, std::vector<std::string>& objs);

private:
    PickManager();
    ~PickManager();

    PickManager(const PickManager&);
    PickManager operator=(const PickManager&);

    static PickManager *Instance;
};

#endif // __PICK_MANAGER_H__
