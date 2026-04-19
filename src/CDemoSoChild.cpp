
struct CDemoSoChild : CParent
{
    CDemoSoChild()
    {
        printf("child CDemoSoChild constructor\n");
    }

    CDemoSoChild(void* constructorParameterVoidPtr) {}

    virtual ~CDemoSoChild()
    {
        printf("child CDemoSoChild destructor\n");
    }

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }

    virtual void action()
    {
        printf("-------------------    behavior specific for CDemoSoChild\n");
    }

    virtual void* action(void* actionParameterVoidPtr)
    {
        return nullptr;
    }
};
