

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

struct CSoCreatorsProducerChild : CParent
{
	CSoCreatorsProducerChild(): dlHandle(nullptr) {}
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

        return produceSoCreator();
    }

  private:
    CChildCreatorIf* produceSoCreator()
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

        CreateNewSoChild createNewSoChild = nullptr;
        createNewSoChild =
            (CreateNewSoChild)dlsym(dlHandle.ptr, soChild->constructorName);
        if (nullptr == createNewSoChild)
        {
            printf("                           createNewSoChild is nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT createNewSoChild "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        DeleteSoChild deleteSoChild = nullptr;

        deleteSoChild =
            (DeleteSoChild)dlsym(dlHandle.ptr, soChild->destructorName);
        if (nullptr == deleteSoChild)
        {
            printf("                           deleteSoChild if nullptr "
                   "produceSoCreator()\n");
            fflush(NULL);
            return nullptr;
        }
        printf("                           GOT deleteSoChild "
               "produceSoCreator()!!!\n");
        fflush(NULL);

        CChildCreatorIf* x(nullptr);
        x = new CSoChildCreator(soChild->id, soChild->initParameterVoidPtr,
                                dlHandle.ptr, createNewSoChild, deleteSoChild);
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


