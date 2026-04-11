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
    CSelector(void **selectorCoreVoidPtrVoidPtr)
        : map(nullptr)
    {
        printf("The selector of child creators: constructing\n");
        *selectorCoreVoidPtrVoidPtr = &map;
    }

    virtual ~CSelector()
    {
        printf("The selector of child creators: destructing\n");
        delete map;
        map = nullptr;
    }

#if 0
    virtual void* init()
    {
        initializeSelector(map, selectorInitConfig);
        return map;
    }
#endif

    virtual void *at(int event)
    {
        for (std::unique_ptr<CChildCreatorIf> &childCreator : *map)
        {
            void *childPtr = childCreator->createNewChildIfIsNumber(event);
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
    MapOfUptrChCrIf *map;
    std::vector<int> *selectorInitConfig;
};

CSelectorIf *createNewCSelector(void **selectorCoreVoidPtrVoidPtr)
{
    return new CSelector(selectorCoreVoidPtrVoidPtr);
}
