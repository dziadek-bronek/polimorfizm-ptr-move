#include "../include/CParent.hpp"
#include "../include/VOID.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

#include "createNewCSoChildCeator.hpp"

struct CSoChildWrapper : CParent
{
    using CParent::CParent;
#if 0
    CSoChildWrapper(void* initParametersVoidPtr)

    {
        struct CInitParams
        {
            void* soChildInitParameterVoidPtr;
            void* dlHandle;
            FPluginCreator pluginCreator;
            FPluginDestroyer pluginDestroyer;
        }* initParams = (CInitParams*)initParametersVoidPtr;

        pluginCreator = initParams->pluginCreator;
        pluginDestroyer = initParams->pluginDestroyer;

        soChild = (CParent*)pluginCreator();

        soChild->init(initParams->soChildInitParameterVoidPtr);
    }
#endif

    ~CSoChildWrapper()
    {
        pluginDestroyer(soChild);
    }

    virtual void init(void* initParametersVoidPtr)
    {

        struct CInitParams : VOID
        {
            void* soChildInitParameterVoidPtr;
            void* dlHandle;
            FPluginCreator pluginCreator;
            FPluginDestroyer pluginDestroyer;
        }* initParams = (CInitParams*)initParametersVoidPtr;

        pluginCreator = initParams->pluginCreator;
        pluginDestroyer = initParams->pluginDestroyer;

        soChild = (CParent*)pluginCreator();

        soChild->init(initParams->soChildInitParameterVoidPtr);
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
    FPluginDestroyer pluginDestroyer;
    FPluginCreator pluginCreator;
};

void* createNewCSoChildCreator(int id, void* soChildInitParameterVoidPtr,
                               void* dlHandle, FPluginCreator pluginCreator,
                               FPluginDestroyer pluginDestroyer)
{

    struct CInitParams : VOID
    {
        CInitParams(void* soChildInitParameterVoidPtr_, void* dlHandle_,
                    FPluginCreator pluginCreator_,
                    FPluginDestroyer pluginDestroyer_)
            : soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
              dlHandle(dlHandle_),
              pluginCreator(pluginCreator_),
              pluginDestroyer(pluginDestroyer_)
        {
            printf("\t\t\tINIT PARAMS CONSTRUCTOR\n");
        }
        virtual ~CInitParams()
        {
            printf("\t\t\tINIT PARAMS DESTRUCTOR\n");
        }
        void* soChildInitParameterVoidPtr;
        void* dlHandle;
        FPluginCreator pluginCreator;
        FPluginDestroyer pluginDestroyer;
    }* initParamsPtr = new CInitParams{soChildInitParameterVoidPtr, dlHandle,
                                       pluginCreator, pluginDestroyer};
    /* where it is to be destroyed */

    return new CChildCreator<CSoChildWrapper>(id, initParamsPtr);
}
