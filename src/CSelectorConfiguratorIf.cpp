#include "include/CSelectorConfiguratorIf.hpp"
#include <cstdio>

#include "include/CDlGlobalHandle.hpp"
#include <dlfcn.h>
extern CDlGlobalHandle dlCSelectorConfiguratorGlobalHandle;

CSelectorConfiguratorIf::~CSelectorConfiguratorIf() {}

struct CSelectorConfiguratorWrapper : CSelectorConfiguratorIf
{
    using CreateNewPlugin = CSelectorConfiguratorIf* (*)();
    using DeletePlugin = void (*)(CSelectorConfiguratorIf*);

    CSelectorConfiguratorWrapper(const char* dlFileName,
                                 const char* constructorName,
                                 const char* destructorName)
        : plugin(nullptr),
          dlHandle(nullptr),
          createNewPlugin(nullptr),
          deletePlugin(nullptr)
    {

        dlHandle = dlopen(dlFileName, RTLD_NOW | RTLD_GLOBAL);

        if (nullptr == dlHandle)
        {
            printf("                           dlHandle is nullptr in "
                   "wraper constructor\n");
            return;
        }
        printf("                           GOT dlHandle!!!\n");
        createNewPlugin = (CreateNewPlugin)dlsym(dlHandle, constructorName);

        if (nullptr == createNewPlugin)
        {
            printf("                           createNewPlugin is nullptr in "
                   "wraper constructor\n");
            return;
        }
        printf("                           GOT CreateNewPlugin()!!!\n");

        deletePlugin = (DeletePlugin)dlsym(dlHandle, destructorName);

        if (nullptr == deletePlugin)
        {
            printf("                           deletePlugin is nullptr in "
                   "wraper constructor\n");
            return;
        }
        printf("                           GOT deletePlugin()!!!\n");

        plugin = createNewPlugin();
        if (nullptr == plugin)
        {
            printf("                           plugin is nullptr in wraper "
                   "constructor\n");
            return;
        }
        printf("                           GOT PLUGIN!!!\n");
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
    CSelectorConfiguratorWrapper* configuratorWrapper;
    if (nullptr == initConfigVoidPtr)
    {

        configuratorWrapper = new CSelectorConfiguratorWrapper(
            "./libselectorConfigurator.so",
            "createNewCSimpleSelectorConfiguratorExternC",
            "deleteCSelectorConfiguratorExternC");
    }
    else
    {

        configuratorWrapper = new CSelectorConfiguratorWrapper(
            "./libselectorConfigurator.so",
            "createNewCSelectorConfiguratorExternC",
            "deleteCSelectorConfiguratorExternC");
    }

    if (nullptr != configuratorWrapper->plugin)
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
    return nullptr;
}
