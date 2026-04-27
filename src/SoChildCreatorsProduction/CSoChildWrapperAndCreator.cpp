#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

#include "createNewCSoChildCeator.hpp"

struct CSoChildWrapper : CParent
{
    CSoChildWrapper(void* soChild_, FPluginDestroyer pluginDestroyer_)
        : soChild((CParent*)soChild_),
          pluginDestroyer(pluginDestroyer_)
    {
    }
    ~CSoChildWrapper()
    {
        pluginDestroyer(soChild);
    }

    virtual void init(void* initParameterVoidPtr)
    {
        soChild->init(initParameterVoidPtr);
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
};

struct CSoChildCreator : CChildCreatorIf
{
    CSoChildCreator(int id_, void* soChildInitParameterVoidPtr_,
                    void* dlHandle_, FPluginCreator pluginCreator_,
                    FPluginDestroyer pluginDestroyer_)
        : id(id_),
          soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
          dlHandle(dlHandle_),
          pluginCreator(pluginCreator_),
          pluginDestroyer(pluginDestroyer_)
    {
        printf("CSoChildCreator id=%i - constuctor\n", id);
    }
    virtual ~CSoChildCreator()
    {
        printf("CSoChildCreator id=%i - destuctor\n", id);
        // TODO
        // push dlHandle do global destrocyer
        // ...
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CSoChildCreator id=%i is creating new soChild\n", id);

            CParent* soChildWrapper(
                new CSoChildWrapper(pluginCreator(), pluginDestroyer));
            soChildWrapper->init(soChildInitParameterVoidPtr);
            return soChildWrapper;
        }
        return nullptr;
    }

  private:
    int id;
    void* soChildInitParameterVoidPtr;
    void* dlHandle;
    FPluginCreator pluginCreator;
    FPluginDestroyer pluginDestroyer;
};

void* createNewCSoChildCreator(int id, void* soChildInitParameterVoidPtr,
                               void* dlHandle, FPluginCreator pluginCreator,
                               FPluginDestroyer pluginDestroyer)
{
    return new CSoChildCreator(id, soChildInitParameterVoidPtr, dlHandle,
                               pluginCreator, pluginDestroyer);
}
