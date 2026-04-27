#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include "createNewCSoChildCeator.hpp"
#include <cstdio>
#include <dlfcn.h>

struct CSoChildCreatorsProducerChild : CParent
{
    CSoChildCreatorsProducerChild()
        : dlHandle(nullptr)
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

        CreateNewPlugin createNewPlugin = nullptr;
        createNewPlugin =
            (CreateNewPlugin)dlsym(dlHandle.ptr, soChild->constructorName);
        if (nullptr == createNewPlugin)
        {
            printf("                           createNewPlugin is nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT createNewPlugin "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        DeletePlugin deletePlugin = nullptr;

        deletePlugin =
            (DeletePlugin)dlsym(dlHandle.ptr, soChild->destructorName);
        if (nullptr == deletePlugin)
        {
            printf("                           deletePlugin if nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT deletePlugin "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        void* x(nullptr);
        /*
            x = new CSoChildCreator(soChild->id, soChild->initParameterVoidPtr,
                                    dlHandle.ptr, createNewPlugin,
           deletePlugin);
        */

        x = createNewCSoChildCreator(soChild->id, soChild->initParameterVoidPtr,
                                     dlHandle.ptr, createNewPlugin,
                                     deletePlugin);
        if (nullptr == x)
        {
            return nullptr;
        }
        dlHandle.ptr = nullptr;
        return x;
    }
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
    } dlHandle;

    CActionParams* soChild;
};

void* createNewCSoChildCreatorsProducerChildCreator()
{
    return new CChildCreator<CSoChildCreatorsProducerChild>(221);
}
