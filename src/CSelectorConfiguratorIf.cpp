#include "include/CSelectorConfiguratorIf.hpp"
#include <cstdio>
#include <dlfcn.h>
// #include "include/old/CSelectorConfigurator.hpp"

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

        dlHandle = dlopen(dlFileName, RTLD_LAZY);

        if (nullptr == dlHandle)
        {
            printf("                           createNewPlugin is nullptr in "
                   "wraper constructor\n");
            return;
        }
        // printf("                           GOT dlHandle!!!\n");
        createNewPlugin = (CreateNewPlugin)dlsym(dlHandle, constructorName);

        if (nullptr == createNewPlugin)
        {
            printf("                           createNewPlugin is nullptr in "
                   "wraper constructor\n");
            return;
        }
        // printf("                           GOT CreateNewPlugin()!!!\n");

        deletePlugin = (DeletePlugin)dlsym(dlHandle, destructorName);

        if (nullptr == deletePlugin)
        {
            printf("                           deletePlugin is nullptr in "
                   "wraper constructor\n");
            return;
        }
        // printf("                           GOT deletePlugin()!!!\n");

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
        // dlclose(dlHandle);
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

CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* initConfigVoidPtr)
{
    CSelectorConfiguratorWrapper* configuratorWrapper;
    if (nullptr == initConfigVoidPtr)
    {

        configuratorWrapper = new CSelectorConfiguratorWrapper(
            "/home/dtstgseete/CSelectorConfigurator.cpp.so",
            "createNewCSimpleSelectorConfiguratorExternC",
            "deleteCSelectorConfiguratorExternC");
    }
    else
    {

        configuratorWrapper = new CSelectorConfiguratorWrapper(
            "/home/dtstgseete/CSelectorConfigurator.cpp.so",
            "createNewCSelectorConfiguratorExternC",
            "deleteCSelectorConfiguratorExternC");
    }

    if (nullptr != configuratorWrapper->plugin)
    {
        configuratorWrapper->init(initConfigVoidPtr);
        return configuratorWrapper;
    }

    CSelectorConfiguratorIf* x = nullptr;
#if 0
    if (nullptr == initConfigVoidPtr)
    {
        return createNewCSimpleSelectorConfigurator();
    }

    CSelectorConfiguratorIf* x = createNewCSelectorConfigurator();
    if (nullptr == x) {
	    return nullptr;
    }
    x->init(initConfigVoidPtr);
#endif
    return x;
}
