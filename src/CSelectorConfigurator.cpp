#include <cstdio>
#include <list>
#include <memory>
#include <vector>

#include "include/throw.hpp"

#include "CChildren/CChildren.hpp"

#include "include/child-creators.hpp"

#include "include/CSelector.hpp"
#include "include/CSimpleSelector.hpp"

#include "include/CSelectorConfiguratorIf.hpp"

#include "SoChildCreatorsProduction/CSoChildCreatorsProducerChild.hpp"

#include <dlfcn.h>

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

// #include "SoChildCreatorsProcuction/CSoChildCreatorsProducerChild.cpp"

/*******************************************/

struct CConfigurator : CSelectorConfiguratorIf
{
    CConfigurator()
        : selectorCoreMap(nullptr)
    {
    }
    virtual ~CConfigurator() {}

    virtual void init(void* initConfigVoidPtr)
    {
        initConfig = (std::vector<int>*)initConfigVoidPtr;
    }
    virtual void* initializeSelector()
    {
        selectorCoreMap = new MapOfUptrChCrIf;

        {
            /*
            SoChildCreatorsProducer is of class CChild, which creates Creators
            creating object defined by a certian .so files a creator which
            produces such a soChildCreatorsProducer is created and added to list
                this is for unification of access to soChildCreatorsProducer


                we use this creator x to generate y before pushing; pushing
            destroys x, thus we can not is soChildCreatorsProducer and we hold
            it for a while
                */

            std::unique_ptr<CParent> y;

            {
                UptrChCrIf x(
                    (CChildCreatorIf*)
                        createNewCreatorOfCSoChildCreatorsProducerChild());
                y = std::unique_ptr<CParent>(
                    (CParent*)(x->createNewChildIfIsNumber(221)));

                selectorCoreMap->push_back(std::move(x));
            }

            {
                struct CActionParams
                {
                    const char* fileName;
                    const char* constructorName;
                    const char* destructorName;
                    int id;
                    void* coreMapVoidPtr;
                } adderSoChildData{
                    .fileName = "./libCConfigSoChild.so",
                    .constructorName = "createNewCConfigSoChildExternC",
                    .destructorName = "deleteCConfigSoChildExternC",
                    .id = 222,
                    .coreMapVoidPtr = selectorCoreMap};

                selectorCoreMap->push_back(UptrChCrIf(
                    (CChildCreatorIf*)(y->action(&adderSoChildData))));
            }
        }

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

    virtual ~CSimpleConfigurator() {}

    virtual void init(void*) {}

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

CSelectorConfiguratorIf* createNewCSelectorConfigurator()
{

    return new CConfigurator;
}

extern "C" CSelectorConfiguratorIf*
createNewCSimpleSelectorConfiguratorExternC()
{
    return new CSimpleConfigurator;
}

extern "C" CSelectorConfiguratorIf* createNewCSelectorConfiguratorExternC()
{
    return new CConfigurator();
}

extern "C" void deleteCSelectorConfiguratorExternC(
    CSelectorConfiguratorIf* configuratorPtr)
{
    delete configuratorPtr;
}
