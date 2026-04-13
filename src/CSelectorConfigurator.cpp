#include "include/CSelectorConfigurator.hpp"
#include "include/CChildren.hpp"
#include "include/CConfigChild.hpp"
#include "include/child-creators.hpp"
#include "include/throw.hpp"
#include <cstdio>
#include <list>
#include <memory>

#include "include/CSelector.hpp"
#include "include/CSelectorIf.hpp"
#include "include/CSimpleSelector.hpp"
#include <vector>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;
struct CChildCreatorExit : CChildCreatorIf
{
    CChildCreatorExit(int id_)
        : id(id_)
    {
        printf("ChildCreator constructor for  EXIT event %i \n", id);
    }
    virtual ~CChildCreatorExit()
    {
        printf("ChildCreator destructor for  EXIT event %i \n", id);
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator on event %i : exit\n", id);
            THROW2("Clean exit", " (event 'EXIT' on input)");
        }
        return nullptr;
    }

  private:
    int id;
};

static CChildCreatorIf* createCreatorForChildWithNumber(int childClass,
                                                        int event)
{
    switch (childClass)
    {
    case 1:
        return new CChildCreator<CChild1>(event);
    case 2:
        return new CChildCreator<CChild2>(event);
    case 3:
        return new CChildCreator<CChild3>(event);
    case 4:
        return new CChildCreator<CChild4>(event);
    }
    throw;
}

struct CChildCreatorConfig : CChildCreatorIf
{
    CChildCreatorConfig(int number, void* mapVoidPtr)
        : id(number),
          mapPtr((MapOfUptrChCrIf*)mapVoidPtr)
    {
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator on event %i is creating new CConfigChild\n",
                   id);
            return new CConfigChild(mapPtr);
        }
        return nullptr;
    }

  private:
    int id;
    MapOfUptrChCrIf* mapPtr;
};

struct CConfigurator : CSelectorConfiguratorIf
{
    CConfigurator(void* initConfigVoidPtr)
        : initConfig((std::vector<int>*)initConfigVoidPtr),
          selectorCoreMap(nullptr)
    {
    }
    virtual void* initializeSelector()
    {
        selectorCoreMap = new MapOfUptrChCrIf;

        selectorCoreMap->push_back(
            UptrChCrIf(new CChildCreatorConfig(222, selectorCoreMap)));

        if (nullptr == initConfig)
        {
            return createNewCSelector(selectorCoreMap);
        }

        int vSize = initConfig->size();

        if (vSize <= 0)
        {
            selectorCoreMap->push_back(UptrChCrIf(new CChildCreatorExit(0)));
            return createNewCSelector(selectorCoreMap);
        }

        selectorCoreMap->push_back(
            UptrChCrIf(new CChildCreatorExit(initConfig->at(0))));

        for (int i = 1; i < vSize; ++i)
        {
            int event = initConfig->at(i);
            if (event < 0)
            {
                continue;
            }
            selectorCoreMap->push_back(
                UptrChCrIf(::createCreatorForChildWithNumber(i, event)));
        }

        return createNewCSelector(selectorCoreMap);
    }

  private:
    std::vector<int>* initConfig;
    MapOfUptrChCrIf* selectorCoreMap;
};

struct CSimpleConfigurator : CSelectorConfiguratorIf
{
    CSimpleConfigurator()
        : selectorCoreSimpleCreator(nullptr)
    {
    }
    virtual void* initializeSelector()
    {
        struct CChildCreatorSimple : CChildCreatorIf
        {
            virtual ~CChildCreatorSimple()
            {
                printf("ChildCreatorSimpleSelection destructor\n");
            }

            virtual void* createNewChildIfIsNumber(int id_)
            {
                switch (id_)
                {
                case 0:
                    THROW2("Clean exit", " (event 'EXIT' on input)");
                case 1:
                    return new CChild1;
                case 2:
                    return new CChild2;
                case 3:
                    return new CChild3;
                case 4:
                    return new CChild4;
                }
                return nullptr;
            }
        };

        selectorCoreSimpleCreator = new CChildCreatorSimple;
        return createNewCSimpleSelector(selectorCoreSimpleCreator);
    }

  private:
    CChildCreatorIf* selectorCoreSimpleCreator;
};

CSelectorConfiguratorIf* createNewCSimpleSelectorConfigurator()
{
    return new CSimpleConfigurator;
}

CSelectorConfiguratorIf* createNewCSelectorConfigurator(void* initConfigVoidPtr)
{
    return new CConfigurator(initConfigVoidPtr);
}
