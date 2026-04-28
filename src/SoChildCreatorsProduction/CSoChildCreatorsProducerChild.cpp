#include "../include/CParent.hpp"
#include "../include/VOID.hpp"
#include "../include/child-creators.hpp"
#include "createNewCSoChildCreator.hpp"
#include <cstdio>
#include <dlfcn.h>
#include <list>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;
struct CSoChildCreatorsProducerChild : CParent
{
    using CParent::CParent;
    CSoChildCreatorsProducerChild()
    {
        printf("constructor of CSoChildCreatorsProducerChild\n");
    }

    ~CSoChildCreatorsProducerChild()
    {
        printf("destructor of CSoChildCreatorsProducerChild\n");
    }
    struct CActionParams
    {
        const char* fileName;
        const char* creatorName;
        const char* destroyerName;
        int id;
        std::unique_ptr<VOID> initParameterVoidUPtr;
    };

    virtual void init(void* initParametersVoidPtr) override
    {
        struct X : VOID
        {
            MapOfUptrChCrIf* selectorCoreMapVoidPtr;
        };
        mapPtr = ((X*)initParametersVoidPtr)->selectorCoreMapVoidPtr;
    }

    void* action(void* actionParameterVoidPtr)
    {
        soChild = (CActionParams*)actionParameterVoidPtr;
        printf("behavior specific for CSoChildCreatorsProducerChild: producing "
               "CSoChildCreator of id=%i\n",
               soChild->id);

        return produceSoCreator();
    }

  private:
    void* produceSoCreator()
    {
        dlHandle.ptr = dlopen(soChild->fileName, RTLD_NOW | RTLD_GLOBAL);
        if (nullptr == dlHandle.ptr)
        {
            printf("                           dlHandle.ptr is nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT dlHandle "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        FPluginCreator pluginCreator = nullptr;
        pluginCreator =
            (FPluginCreator)dlsym(dlHandle.ptr, soChild->creatorName);
        if (nullptr == pluginCreator)
        {
            printf("                           pluginCreator is nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT pluginCreator "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        FPluginDestroyer pluginDestroyer = nullptr;

        pluginDestroyer =
            (FPluginDestroyer)dlsym(dlHandle.ptr, soChild->destroyerName);
        if (nullptr == pluginDestroyer)
        {
            printf("                           pluginDestroyer if nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT pluginDestroyer "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        CChildCreatorIf* x = nullptr;

        x = (CChildCreatorIf*)createNewCSoChildCreator(
            soChild->id, std::move(soChild->initParameterVoidUPtr),
            dlHandle.ptr, pluginCreator, pluginDestroyer);
        if (nullptr == x)
        {
            return nullptr;
        }
        dlHandle.ptr = nullptr;
        fflush(NULL);
        mapPtr->push_back(UptrChCrIf(x));
        return x;
    }

    struct CDlHandle
    {
        CDlHandle()
            : ptr(nullptr)
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
    } dlHandle;

    CActionParams* soChild;
    MapOfUptrChCrIf* mapPtr;
};

void* createNewCSoChildCreatorsProducerChildCreator(
    std::unique_ptr<VOID> initParametersVoidUPtr)
{
    return new CChildCreator<CSoChildCreatorsProducerChild>(
        221, std::move(initParametersVoidUPtr));
}
