#include <cstdio>
#include <list>
#include <memory>
#include <vector>

#include "include/throw.hpp"

#include "include/CChildren.hpp"

#include "include/child-creators.hpp"

#include "include/CSelector.hpp"
#include "include/CSimpleSelector.hpp"

#include "include/CSelectorConfiguratorIf.hpp"

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

using CreateNewSoChild = CParent* (*)();
using DeleteSoChild = void (*)(CParent*);

struct CSoChildWrapper : CParent
{
    CSoChildWrapper(CParent* soChild_, DeleteSoChild deleteSoChild_)
        : soChild(soChild_),
          deleteSoChild(deleteSoChild_)
    {
    }
    ~CSoChildWrapper()
    {
        deleteSoChild(soChild);
    }

    virtual void init(void* initParameterVoidPtr)
    {
        soChild->init(initParameterVoidPtr);
    }
    virtual void action()
    {
        soChild->action();
    }
    virtual void* action(void* actionParameterVoidPtr)
    {
        return soChild->action(actionParameterVoidPtr);
    }

    CParent* soChild;
    DeleteSoChild deleteSoChild;
};

struct CSoChildCreator : CChildCreatorIf
{
    CSoChildCreator(int id_, void* soChildInitParameterVoidPtr_,
                    void* dlHandle_, CreateNewSoChild createNewSoChild_,
                    DeleteSoChild deleteSoChild_)
        : id(id_),
          soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
          dlHandle(dlHandle_),
          createNewSoChild(createNewSoChild_),
          deleteSoChild(deleteSoChild_)
    {
        printf("CSoChildCreator constructor for event %i \n", id);
    }
    virtual ~CSoChildCreator()
    {
        printf("CSoChildCreator destructor for event %i \n", id);
        // TODO
        // push dlHandle do global destrocyer
        // ...
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator on event %i is creating new CConfigChild\n",
                   id);

            CParent* x(new CSoChildWrapper(createNewSoChild(), deleteSoChild));
            x->init(soChildInitParameterVoidPtr);
            return x;
        }
        return nullptr;
    }

  private:
    int id;
    void* soChildInitParameterVoidPtr;
    void* dlHandle;
    CreateNewSoChild createNewSoChild;
    DeleteSoChild deleteSoChild;
};

CChildCreatorIf* soCreatorsProducer(const char* fileName,
                                    const char* constructorName,
                                    const char* destructorName, int id,
                                    void* soChildInitParameterVoidPtr)
{
    struct CDlHandle
    {
        CDlHandle(void* ptr_)
            : ptr(ptr_)
        {
        }
        ~CDlHandle()
        {
            if (nullptr != ptr)
            {
                dlclose(ptr);
                ptr = nullptr;
            }
        }
        void* ptr;
    };

    CDlHandle dlHandle(nullptr);

    do
    {
        dlHandle.ptr = dlopen(fileName, RTLD_NOW | RTLD_GLOBAL);
        if (nullptr == dlHandle.ptr)
        {
            printf("                           dlHandle.ptr is nullptr "
                   "soCreatorsProducer()\n");
            fflush(NULL);
            break;
        }
        printf("                           GOT dlHandle "
               "soCreatorsProducer()!!!\n");
        fflush(NULL);

        CreateNewSoChild createNewSoChild = nullptr;
        createNewSoChild =
            (CreateNewSoChild)dlsym(dlHandle.ptr, constructorName);
        if (nullptr == createNewSoChild)
        {
            printf("                           createNewSoChild is nullptr "
                   "soCreatorsProducer()\n");
            fflush(NULL);
            break;
        }
        printf("                           GOT createNewSoChild "
               "soCreatorsProducer()!!!\n");
        fflush(NULL);

        DeleteSoChild deleteSoChild = nullptr;

        deleteSoChild = (DeleteSoChild)dlsym(dlHandle.ptr, destructorName);
        if (nullptr == deleteSoChild)
        {
            printf("                           deleteSoChild if nullptr "
                   "soCreatorsProducer()\n");
            fflush(NULL);
            break;
        }
        printf("                           GOT deleteSoChild "
               "soCreatorsProducer()!!!\n");
        fflush(NULL);

        CChildCreatorIf* x(nullptr);
        x = new CSoChildCreator(id, soChildInitParameterVoidPtr, dlHandle.ptr,
                                createNewSoChild, deleteSoChild);
        if (nullptr != x)
        {
            dlHandle.ptr = nullptr;
            return x;
        }

    } while (0);

    return nullptr;
}

struct CSoCreatorsProducerChild : CParent
{
    void* action(void* actionParameterVoidPtr)
    {

        struct CActionParams
        {
            const char* fileName;
            const char* constructorName;
            const char* destructorName;
            int id;
            void* initParameterVoidPtr;
        };
        CActionParams* soChild = (CActionParams*)actionParameterVoidPtr;

        return soCreatorsProducer(soChild->fileName, soChild->constructorName,
                                  soChild->destructorName, soChild->id,
                                  soChild->initParameterVoidPtr);
    }
};

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
            selectorCoreMap->push_back(
                UptrChCrIf(new CChildCreator<CSoCreatorsProducerChild>(221)));

            {

                CSoCreatorsProducerChild soCreatorsProducer;

                struct CActionParams
                {
                    const char* fileName;
                    const char* constructorName;
                    const char* destructorName;
                    int id;
                    void* coreMapVoidPtr;
                } adderSoChildData{
                    .fileName = "./libCConfigChild.so",
                    .constructorName = "createNewCConfigChildExternC",
                    .destructorName = "deleteCConfigChildExternC",
                    .id = 222,
                    .coreMapVoidPtr = selectorCoreMap};

                selectorCoreMap->push_back(
                    UptrChCrIf((CChildCreatorIf*)soCreatorsProducer.action(
                        &adderSoChildData)));
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
