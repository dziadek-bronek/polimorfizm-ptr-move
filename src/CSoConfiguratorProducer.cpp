#include "CSelectorConfigurator/CSelectorConfiguratorIf.hpp"
#include <cstdio>
#include <memory>

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
extern CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

using CreateNewSoConfigurator = CSelectorConfiguratorIf* (*)();
using DeleteSoConfigurator = void (*)(CSelectorConfiguratorIf*);

struct CSoConfiguratorWrapper : CSelectorConfiguratorIf
{

    CSoConfiguratorWrapper(CSelectorConfiguratorIf* soConfigurator_,
                           DeleteSoConfigurator deleteSoConfigurator_,
                           void* dlHandle_)
        : soConfigurator(soConfigurator_),
          deleteSoConfigurator(deleteSoConfigurator_),
          dlHandle(dlHandle_)
    {
    }

    ~CSoConfiguratorWrapper()
    {
        if (nullptr != soConfigurator)
        {
            deleteSoConfigurator(soConfigurator);
            soConfigurator == nullptr;
        }
        printf("\t~CSoConfiguratorWrapper(); DESTRUCTING\n");
        soConfigurator = nullptr;

        // destruction of resources delegated
        dlCSelectorConfiguratorGlobalHandle.set(dlHandle);
        dlHandle = nullptr;
    }

    virtual void init(void* initConfigVoidPtr)
    {
        soConfigurator->init(initConfigVoidPtr);
    }

    virtual void* initializeSelector()
    {
        return soConfigurator->initializeSelector();
    }

    // private:
    CSelectorConfiguratorIf* (*createNewConfigurator)();
    void (*deleteSoConfigurator)(CSelectorConfiguratorIf*);

    void* dlHandle;
    CSelectorConfiguratorIf* soConfigurator;
};

CSelectorConfiguratorIf* produceNewCSoConfigurator(void* initConfigVoidPtr)
{
    do
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

        CDlHandle dlHandle(
            dlopen("./libCSelectorConfigurator.so", RTLD_NOW | RTLD_GLOBAL));

        if (nullptr == dlHandle.ptr)
        {
            printf("\t\tsoConfigurator: dlHandle is nullptr\n");
            break;
        }
        printf("\tsoConfigurator: GOT dlHandle!!!\n");

        CreateNewSoConfigurator createNewConfigurator = nullptr;
        if (nullptr == initConfigVoidPtr)
        {
            createNewConfigurator = (CreateNewSoConfigurator)dlsym(
                dlHandle.ptr, "createNewCSimpleSelectorConfiguratorExternC");
        }
        else
        {
            createNewConfigurator = (CreateNewSoConfigurator)dlsym(
                dlHandle.ptr, "createNewCSelectorConfiguratorExternC");
        }

        if (nullptr == createNewConfigurator)
        {
            printf("\t\tsoConfigurator: createNewConfigurator is nullptr\n");
            break;
        }
        printf("\tGOT createNewConfigurator!!!\n");

        DeleteSoConfigurator deleteSoConfigurator = nullptr;
        deleteSoConfigurator = (DeleteSoConfigurator)dlsym(
            dlHandle.ptr, "deleteCSelectorConfiguratorExternC");

        if (nullptr == deleteSoConfigurator)
        {
            printf(
                "                           deleteSoConfigurator is nullptr\n");
            break;
        }
        printf("                           GOT deleteSoConfigurator!!!\n");

        std::unique_ptr<CSoConfiguratorWrapper> soConfiguratorWrapper(
            new CSoConfiguratorWrapper(createNewConfigurator(),
                                       deleteSoConfigurator, dlHandle.ptr));

        if (nullptr != soConfiguratorWrapper)
        {
            dlHandle.ptr = nullptr;

            if (nullptr == soConfiguratorWrapper->soConfigurator)
            {
                printf("                           soConfigurator is nullptr "
                       "in wraper\n");
                break;
            }

            printf("                           GOT PLUGIN!!!\n");

            soConfiguratorWrapper->init(initConfigVoidPtr);
            return soConfiguratorWrapper.release();
        }
    } while (0);

#if 0
    if (nullptr != initConfigVoidPtr)
    {
        return createNewCSimpleSelectorConfigurator();
    }

    CSelectorConfiguratorIf* x = nullptr;
    x = createNewCSelectorConfigurator();
    if (nullptr != x) {
    	x->init(initConfigVoidPtr);
	    return nullptr;
    }
#endif
    return nullptr;
}
