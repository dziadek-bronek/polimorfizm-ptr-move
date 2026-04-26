#include <cstdio>
#include <list>
#include <memory>
#include <vector>

#include "include/throw.hpp"

#include "CChildren/CChildren.hpp"
#include "include/CParent.hpp"

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

struct CConfigurator : CSelectorConfiguratorIf
{
    virtual ~CConfigurator() = default;

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

            std::unique_ptr<CParent> soChildCreatorsProducer;

            {
                UptrChCrIf creatorOfSoChildCreatorsProducer(
                    (CChildCreatorIf*)
                        createNewCSoChildCreatorsProducerChildCreator());
                soChildCreatorsProducer = std::unique_ptr<CParent>(
                    (CParent*)(creatorOfSoChildCreatorsProducer
                                   ->createNewChildIfIsNumber(221)));

                selectorCoreMap->push_back(
                    std::move(creatorOfSoChildCreatorsProducer));
                printf("CChildCreator id=221, for SoChildCreatorsProducer - "
                       "added to selector\n");
                fflush(NULL);
            }

            {
                struct
                {
                    const char* fileName;
                    const char* constructorName;
                    const char* destructorName;
                    int id;
                    void* initParameterVoidPtr;
                } adderSoChildData{
                    "./libCConfigSoChild.so", "createNewCConfigSoChildExternC",
                    "deleteCConfigSoChildExternC", 222, selectorCoreMap};

                selectorCoreMap->push_back(UptrChCrIf(
                    (CChildCreatorIf*)(soChildCreatorsProducer->action(
                        &adderSoChildData))));
                printf("CSoChildCreator id=222 added to selector\n");
                fflush(NULL);
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
            int creatorId = initConfig->at(i);
            if (creatorId < 0)
            {
                continue;
            }
            selectorCoreMap->push_back(UptrChCrIf(
                (CChildCreatorIf*)createChildCreatorWithId(i, creatorId)));
            printf(
                "CChildCreator, id=%i added to selector based on init config\n",
                creatorId);
            fflush(NULL);
        }

        return createNewCSelector(selectorCoreMap);
    }

  private:
    std::vector<int>* initConfig;
    MapOfUptrChCrIf* selectorCoreMap;
};

struct CSimpleConfigurator : CSelectorConfiguratorIf
{
    CSimpleConfigurator() {}

    virtual ~CSimpleConfigurator() = default;

    virtual void init(void*) {}

    virtual void* initializeSelector()
    {
        return createNewCSimpleSelector();
    }
};

void* createNewCSimpleSelectorConfigurator()
{
    return new CSimpleConfigurator;
}

void* createNewCSelectorConfigurator()
{

    return new CConfigurator;
}

extern "C" void* createNewCSimpleSelectorConfiguratorExternC()
{
    return new CSimpleConfigurator;
}

extern "C" void* createNewCSelectorConfiguratorExternC()
{
    return new CConfigurator();
}

extern "C" void deleteCSelectorConfiguratorExternC(void* configuratorPtr)
{
    delete (CSelectorConfiguratorIf*)configuratorPtr;
}
