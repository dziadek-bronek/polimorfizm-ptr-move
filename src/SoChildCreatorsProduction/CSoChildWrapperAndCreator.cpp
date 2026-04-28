#include "../include/CParent.hpp"
#include "../include/VOID.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

#include "createNewCSoChildCreator.hpp"



    struct CInitParams : VOID
    {
        CInitParams()
        {
            printf("\t\t\tINIT PARAMS CONSTRUCTOR\n");
        }
        virtual ~CInitParams()
        {
            printf("\t\t\tINIT PARAMS DESTRUCTOR\n");
	    // take care of dlHandle
	    // take care of  soChildInitParameterVoidUPtr
        }
	std::unique_ptr<VOID> soChildInitParameterVoidUPtr;
        void* dlHandle;
        FPluginCreator pluginCreator;
        FPluginDestroyer pluginDestroyer;
    };



struct CSoChildWrapper : CParent
{
    using CParent::CParent;
    ~CSoChildWrapper()
    {
        pluginDestroyer(soChild);
    }

    virtual void init(void* initParametersVoidPtr)
    {
        CInitParams* initParams = (CInitParams*)initParametersVoidPtr;

        pluginCreator = initParams->pluginCreator;
        pluginDestroyer = initParams->pluginDestroyer;

        soChild = (CParent*)pluginCreator();

        soChild->init((initParams->soChildInitParameterVoidUPtr).get());
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

void* createNewCSoChildCreator(int id, std::unique_ptr<VOID> soChildInitParameterVoidUPtr,
                               void* dlHandle, FPluginCreator pluginCreator,
                               FPluginDestroyer pluginDestroyer)
{
    std::unique_ptr<CInitParams> initParamsUPtr(new CInitParams);
    initParamsUPtr->soChildInitParameterVoidUPtr = std::move(soChildInitParameterVoidUPtr);
    initParamsUPtr->dlHandle = dlHandle;
    initParamsUPtr->pluginCreator = pluginCreator;
    initParamsUPtr->pluginDestroyer = pluginDestroyer;

    return new CChildCreator<CSoChildWrapper>(id, std::move(initParamsUPtr));
}
