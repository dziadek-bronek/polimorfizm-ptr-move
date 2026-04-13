#include "include/CMap.hpp"
#include "include/child-creator.hpp"
#include <cstdio>
#include <list>
#include <memory>

struct CMapList : CMapIf
{
    ~CMapList() {}

    virtual void* at(int number)
    {
        for (std::unique_ptr<CChildCreatorIf>& childCreator : map)
        {
            void* tryToGetChild =
                childCreator->createNewChildIfIsNumber(number);
            if (nullptr != tryToGetChild)
            {
                printf("The selector of child creators: new child created "
                       "based on event "
                       "%i\n",
                       number);
                return tryToGetChild;
            }
        }
        return nullptr;
    }
    virtual void push_back(void*) {}

    std::list<std::unique_ptr<CChildCreatorIf>> map;
};

CMapIf* createNewCMapList()
{
    return new CMapList();
}
