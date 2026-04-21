#include "../include/CParent.hpp"
#include <cstdio>
#include <list>
#include <memory>

#include "../include/child-creators.hpp"

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

    virtual void init(void* initParameterVoidPtr) {}

    virtual void action()
    {
        printf("-------------------    behavior specific for CDemoSoChild\n");
    }

    virtual void* action(void* actionParameterVoidPtr)
    {
        return nullptr;
    }
};

extern "C" CParent* createNewCDemoSoChildExternC()
{
    return new CDemoSoChild;
}
extern "C" void deleteCDemoSoChildExternC(CParent* demoSoChild)
{
    delete demoSoChild;
}
