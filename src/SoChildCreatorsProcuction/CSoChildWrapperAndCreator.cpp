


/*******************************************/

using CreateNewSoChild = CParent* (*)();
using DeleteSoChild = void (*)(CParent*);


struct CSoChildWrapper : CParent
{
    CSoChildWrapper(CParent* soChild_, DeleteSoChild deleteSoChild_)
        : soChild(soChild_),
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
    DeleteSoChild deleteSoChild;
};

struct CSoChildCreator : CChildCreatorIf
{
    CSoChildCreator(int id_, void* soChildInitParameterVoidPtr_,
                    void* dlHandle_, CreateNewSoChild createNewSoChild_,
                    DeleteSoChild deleteSoChild_)
        : id(id_),
          soChildInitParameterVoidPtr(soChildInitParameterVoidPtr_),
          dlHandle(dlHandle_),
          createNewSoChild(createNewSoChild_),
          deleteSoChild(deleteSoChild_)
    {
        printf("CSoChildCreator constructor for event %i \n", id);
    }
    virtual ~CSoChildCreator()
    {
        printf("CSoChildCreator destructor for event %i \n", id);
        // TODO
        // push dlHandle do global destrocyer
        // ...
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator on event %i is creating new CConfigChild\n",
                   id);

            CParent* x(new CSoChildWrapper(createNewSoChild(), deleteSoChild));
            x->init(soChildInitParameterVoidPtr);
            return x;
        }
        return nullptr;
    }

  private:
    int id;
    void* soChildInitParameterVoidPtr;
    void* dlHandle;
    CreateNewSoChild createNewSoChild;
    DeleteSoChild deleteSoChild;
};


void* createNewCSoChildCreator(int id, void* soChildInitParameterVoidPtr, void* dlHandle, CreateNewSoChild createNewSoChild, DeleteSoChild deleteSoChild);
{
	return CSoChildCreator(id, soChildInitParameterVoidPtr, dlHandle, createNewSoChild, deleteSoChild);
}
