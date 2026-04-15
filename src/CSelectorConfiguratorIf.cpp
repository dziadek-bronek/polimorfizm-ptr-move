#include "include/CSelectorConfiguratorIf.hpp"
#include <cstdio>

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
extern CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

CSelectorConfiguratorIf::~CSelectorConfiguratorIf() {}

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
        deletePlugin(plugin);
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

    void* dlHandle =
        dlopen("./libselectorConfigurator.so", RTLD_NOW | RTLD_GLOBAL);

    if (nullptr == dlHandle)
    {
        printf("                           dlHandle is nullptr\n");
        return nullptr;
    }
    printf("                           GOT dlHandle!!!\n");

    CreateNewPlugin createNewPlugin(nullptr);
    if (nullptr == initConfigVoidPtr)
    {
        createNewPlugin = (CreateNewPlugin)dlsym(
            dlHandle, "createNewCSimpleSelectorConfiguratorExternC");
    }
    else
    {
        createNewPlugin = (CreateNewPlugin)dlsym(
            dlHandle, "createNewCSelectorConfiguratorExternC");
    }

    if (nullptr == createNewPlugin)
    {
        printf("                           createNewPlugin is nullptr\n");
        return nullptr;
    }
    printf("                           GOT CreateNewPlugin()!!!\n");

    DeletePlugin deletePlugin =
        (DeletePlugin)dlsym(dlHandle, "deleteCSelectorConfiguratorExternC");

    if (nullptr == deletePlugin)
    {
        printf("                           deletePlugin is nullptr\n");
        return nullptr;
    }
    printf("                           GOT deletePlugin()!!!\n");

    CSelectorConfiguratorIf* plugin = createNewPlugin();
    if (nullptr == plugin)
    {
        printf("                           plugin is nullptr in wraper\n");
        return nullptr;
    }
    printf("                           GOT PLUGIN!!!\n");

    CSelectorConfiguratorWrapper* configuratorWrapper(nullptr);

    configuratorWrapper =
        new CSelectorConfiguratorWrapper(dlHandle, deletePlugin, plugin);

    if (nullptr != configuratorWrapper)
    {
        configuratorWrapper->init(initConfigVoidPtr);
        return configuratorWrapper;
    }

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
    if (nullptr != plugin)
    {
        deletePlugin(plugin);
    }
    return nullptr;
}
