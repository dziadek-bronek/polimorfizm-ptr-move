#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include "createNewCSoChildCeator.hpp"
#include <cstdio>
#include <dlfcn.h>
#include "../include/VOID.hpp"
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
        const char* constructorName;
        const char* destructorName;
        int id;
        void* initParameterVoidPtr;
    };

    virtual void init(void* initParametersVoidPtr)  override {
	struct InitParamsAgregator : VOID {
		void* selectorCoreMapVoidPtr;
	}* params = (InitParamsAgregator*)initParametersVoidPtr;
	mapPtr = (MapOfUptrChCrIf*)( params->selectorCoreMapVoidPtr);
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
            (FPluginCreator)dlsym(dlHandle.ptr, soChild->constructorName);
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
            (FPluginDestroyer)dlsym(dlHandle.ptr, soChild->destructorName);
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

        x = (CChildCreatorIf*)createNewCSoChildCreator(soChild->id, soChild->initParameterVoidPtr,
                                     dlHandle.ptr, pluginCreator,
                                     pluginDestroyer);
        if (nullptr == x)
        {
            return nullptr;
        }
        dlHandle.ptr = nullptr;
	printf("DUPA DUPA\n"); fflush(NULL);
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

void* createNewCSoChildCreatorsProducerChildCreator(void* selectorCoreMapVoidPtr)
{
	struct InitParamsAgregator : VOID {
		void* selectorCoreMapVoidPtr;
	}* params = new InitParamsAgregator;
	params->selectorCoreMapVoidPtr = selectorCoreMapVoidPtr;
	return new CChildCreator<CSoChildCreatorsProducerChild>(221, params);
}
