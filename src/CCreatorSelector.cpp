#include "include/CSelector.hpp"
#include "include/child-creator.hpp"

#include "include/CSelectorConfigurator.hpp"

#include "include/child-creator.hpp"

#include "include/throw.hpp"

#include <cstdio>
#include <list>
#include <memory>
#include <vector>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CSelector : CSelectorIf
{
    CSelector(void* mapVoidPtr)
        : mapPtr((MapOfUptrChCrIf*)mapVoidPtr)
    {
        printf("The selector of child creators: constructing\n");
    }

    virtual ~CSelector()
    {
        printf("The selector of child creators: destructing\n");
        delete mapPtr;
        mapPtr = nullptr;
    }

    virtual void* at(int event)
    {
        for (std::unique_ptr<CChildCreatorIf>& childCreator : *mapPtr)
        {
            void* childPtr = childCreator->createNewChildIfIsNumber(event);
            if (nullptr != childPtr)
            {
                printf("The selector of child creators: new child created "
                       "based on event %i\n",
                       event);
                return childPtr;
            }
        }
        return nullptr;
    }

  private:
    MapOfUptrChCrIf* mapPtr;
};

CSelectorIf* createNewCSelector(void* mapVoidPtr)
{
    return new CSelector(mapVoidPtr);
}
