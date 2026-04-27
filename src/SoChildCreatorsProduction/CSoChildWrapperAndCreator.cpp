#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

#include "createNewCSoChildCeator.hpp"

struct CSoChildWrapper : CParent
{
    using CParent::CParent;
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

    ~CSoChildWrapper()
    {
        pluginDestroyer(soChild);
    }

    virtual void init(void* initParametersVoidPtr)
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

    struct CInitParams
    {
        CInitParams(void* soChildInitParameterVoidPtr_, void* dlHandle_,
                    FPluginCreator pluginCreator_,
                    FPluginDestroyer pluginDestroyer_)
            : soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
              dlHandle(dlHandle_),
              pluginCreator(pluginCreator_),
              pluginDestroyer(pluginDestroyer_)
        {
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
