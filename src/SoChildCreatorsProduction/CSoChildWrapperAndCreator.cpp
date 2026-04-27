#include "../include/CParent.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>

/*******************************************/

using CreateNewPlugin = CParent* (*)();
using DeletePlugin = void (*)(CParent*);

struct CSoChildWrapper : CParent
{
    CSoChildWrapper(CParent* soChild_, DeletePlugin deleteSoChild_)
        : soChild((CParent*)soChild_),
          deleteSoChild(deleteSoChild_)
    {
    }
    ~CSoChildWrapper()
    {
        deleteSoChild(soChild);
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
    DeletePlugin deleteSoChild;
};

struct CSoChildCreator : CChildCreatorIf
{
    CSoChildCreator(int id_, void* soChildInitParameterVoidPtr_,
                    void* dlHandle_, CreateNewPlugin createNewSoChild_,
                    DeletePlugin deleteSoChild_)
        : id(id_),
          soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
          dlHandle(dlHandle_),
          createNewSoChild(createNewSoChild_),
          deleteSoChild(deleteSoChild_)
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
                new CSoChildWrapper(createNewSoChild(), deleteSoChild));
            soChildWrapper->init(soChildInitParameterVoidPtr);
            return soChildWrapper;
        }
        return nullptr;
    }

  private:
    int id;
    void* soChildInitParameterVoidPtr;
    void* dlHandle;
    CreateNewPlugin createNewSoChild;
    DeletePlugin deleteSoChild;
};

void* createNewCSoChildCreator(int id, void* soChildInitParameterVoidPtr,
                               void* dlHandle,
                               CreateNewPlugin createNewSoChild,
                               DeletePlugin deleteSoChild)
{
    return new CSoChildCreator(id, soChildInitParameterVoidPtr, dlHandle,
                               createNewSoChild, deleteSoChild);
}
