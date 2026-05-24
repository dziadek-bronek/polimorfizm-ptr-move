#include "include/CParent.hpp"
#include <cstdio>
#include <list>
#include <memory>

#include "include/child-creators.hpp"

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

    virtual void init(void* initParameterVoidPtr) override
    {
        struct Y : VOID
        {
            std::unique_ptr<int> x;
        };
        exampleData = *(((Y*)initParameterVoidPtr)->x);
    }

    virtual void action()
    {
        printf(
            "-------------------    behavior specific for CDemoSoChild %i.\n",
            exampleData);
    }

    virtual void* action(void* actionParameterVoidPtr)
    {
        return nullptr;
    }

  private:
    int exampleData;
};

extern "C" void* createNewCDemoSoChildExternC()
{
    return new CDemoSoChild;
}
extern "C" void deleteCDemoSoChildExternC(void* demoSoChild)
{
    delete (CParent*)demoSoChild;
}
