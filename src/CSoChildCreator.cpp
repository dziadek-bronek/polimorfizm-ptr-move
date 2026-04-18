struct CSoChildWrapper : CParent
{
    CSoChildWrapper(CParent* childPluginPtr_, DeleteSoChild deleteSoChild_)
        : childPluginPtr(childPluginPtr_),
          deleteSoChild(deleteSoChild_)
    {
    }
    ~CSoChildWrapper()
    {
        deleteSoChild(childPluginPtr);
    }

    virtual void action()
    {
        childPluginPtr->action();
    }
    virtual void* action(void* actionParameter)
    {
        childPluginPtr->action(actionParameter);
    }

    CParent* childPluginPtr DeleteSoChild deleteSoChild;
};

struct CSoChildCreator : CChildCreatorIf
{
    CSoChildCreator(const char* fileName, chonst char* constructorName,
                    const char* destructorName)
    {
    }

    virtual ~CSoChildCreator()
    {
        // delegate dlHandle destruction
    }

    CreateNewSoChild createNewSoChild;
    DeleteSoChild deleteSoChild;

    dlHandle;

    virtual void* createNewChildIfIsNumber(int number_)
    {
        new CSoChildWrapper(createNewSoChild(), deleteSoChild)
    }
};
