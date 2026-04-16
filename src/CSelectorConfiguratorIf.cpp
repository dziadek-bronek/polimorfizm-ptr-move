#include "include/CSelectorConfiguratorIf.hpp"
#include <cstdio>
#include <memory>

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
extern CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

using CreateNewPlugin = CSelectorConfiguratorIf* (*)();
using DeletePlugin = void (*)(CSelectorConfiguratorIf*);

struct CSelectorConfiguratorWrapper : CSelectorConfiguratorIf
{

    CSelectorConfiguratorWrapper(void* dlHandle_, DeletePlugin deletePlugin_,
                                 CSelectorConfiguratorIf* plugin_)
        : dlHandle(dlHandle_),
          deletePlugin(deletePlugin_),
          plugin(plugin_)
    {
    }

    ~CSelectorConfiguratorWrapper()
    {
        if (nullptr != plugin)
        {
            deletePlugin(plugin);
            plugin == nullptr;
        }
        printf("                         ~CSelectorConfiguratorWrapper() "
               "DESTRUCTING\n");
        plugin = nullptr;

        // destruction of resources delegated
        dlCSelectorConfiguratorGlobalHandle.set(dlHandle);
        dlHandle = nullptr;
    }

    virtual void init(void* initConfigVoidPtr)
    {
        plugin->init(initConfigVoidPtr);
    }

    virtual void* initializeSelector()
    {
        return plugin->initializeSelector();
    }

    // private:
    CSelectorConfiguratorIf* (*createNewPlugin)();
    void (*deletePlugin)(CSelectorConfiguratorIf*);

    void* dlHandle;
    CSelectorConfiguratorIf* plugin;
};

// #include "include/old/CSelectorConfigurator.hpp"
CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* initConfigVoidPtr)
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
            CSelectorConfiguratorIf* plugin;
        };

        CDlHandle dlHandle(
            dlopen("./libselectorConfigurator.so", RTLD_NOW | RTLD_GLOBAL));

        if (nullptr == dlHandle.ptr)
        {
            printf("                           dlHandle is nullptr\n");
            break;
        }
        printf("                           GOT dlHandle!!!\n");

        CreateNewPlugin createNewPlugin(nullptr);
        if (nullptr == initConfigVoidPtr)
        {
            createNewPlugin = (CreateNewPlugin)dlsym(
                dlHandle.ptr, "createNewCSimpleSelectorConfiguratorExternC");
        }
        else
        {
            createNewPlugin = (CreateNewPlugin)dlsym(
                dlHandle.ptr, "createNewCSelectorConfiguratorExternC");
        }

        if (nullptr == createNewPlugin)
        {
            printf("                           createNewPlugin is nullptr\n");
            break;
        }
        printf("                           GOT CreateNewPlugin!!!\n");

        DeletePlugin deletePlugin = (DeletePlugin)dlsym(
            dlHandle.ptr, "deleteCSelectorConfiguratorExternC");

        if (nullptr == deletePlugin)
        {
            printf("                           deletePlugin is nullptr\n");
            break;
        }
        printf("                           GOT deletePlugin!!!\n");

        std::unique_ptr<CSelectorConfiguratorWrapper> configuratorWrapper(
            new CSelectorConfiguratorWrapper(dlHandle.ptr, deletePlugin,
                                             createNewPlugin()));

        if (nullptr != configuratorWrapper)
        {
            dlHandle.ptr = nullptr;

            if (nullptr == configuratorWrapper->plugin)
            {
                printf(
                    "                           plugin is nullptr in wraper\n");
                break;
            }

            printf("                           GOT PLUGIN!!!\n");

            configuratorWrapper->init(initConfigVoidPtr);
            return configuratorWrapper.release();
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
