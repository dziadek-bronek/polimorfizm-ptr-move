#include "include/CSelectorConfiguratorIf.hpp"
#include <cstdio>
#include <memory>

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
extern CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

using PluginBaseClass = CSelectorConfiguratorIf;

using CreateNewPlugin = void* (*)();
using DeletePlugin = void (*)(void*);

struct CSoConfiguratorWrapper : PluginBaseClass
{

    CSoConfiguratorWrapper(void* plugin_, DeletePlugin deletePlugin_,
                           void* dlHandle_)
        : plugin((PluginBaseClass*)plugin_),
          deletePlugin(deletePlugin_),
          dlHandle(dlHandle_)
    {
    }

    ~CSoConfiguratorWrapper()
    {
        printf("\t~CSoConfiguratorWrapper(); DESTRUCTING\n");
        if (nullptr != plugin)
        {
            deletePlugin(plugin);
            plugin == nullptr;
        }

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
    DeletePlugin deletePlugin;

    void* dlHandle;
    PluginBaseClass* plugin;
};

void* produceNewCSoConfigurator(void* initConfigVoidPtr)
{
    constexpr const char* pluginName = "soConfigurator";
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

        CreateNewPlugin createNewPlugin = nullptr;
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
            printf("\t\tsoConfigurator: createNewPlugin is nullptr\n");
            break;
        }
        printf("\tsoConfigurator: GOT createNewPlugin!!!\n");

        DeletePlugin deletePlugin = nullptr;
        deletePlugin = (DeletePlugin)dlsym(
            dlHandle.ptr, "deleteCSelectorConfiguratorExternC");

        if (nullptr == deletePlugin)
        {
            printf("\t\tsoConfigurator: deletePlugin is nullptr\n");
            break;
        }
        printf("\tsoConfigurator: GOT deletePlugin!!!\n");

        std::unique_ptr<CSoConfiguratorWrapper> soConfiguratorWrapper(
            new CSoConfiguratorWrapper(createNewPlugin(), deletePlugin,
                                       dlHandle.ptr));

        if (nullptr != soConfiguratorWrapper)
        {
            dlHandle.ptr = nullptr;

            if (nullptr == soConfiguratorWrapper->plugin)
            {
                printf("\t\tsoConfigurator: soConfigurator is nullptr "
                       "in wraper\n");
                break;
            }

            printf("\tsoConfigurator: GOT PLUGIN!!!\n");

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
