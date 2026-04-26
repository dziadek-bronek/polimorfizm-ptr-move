#include "include/CParent.hpp"
#include "include/child-creators.hpp"
#include <cstdio>
#include <list>
#include <memory>

struct CConfigSoChild : CParent
{
    virtual ~CConfigSoChild();

    virtual void init(void* initParameterVoidPtr)
    {
        mapVoidPtr = initParameterVoidPtr;
    }
    virtual void* action(void* childCreatorVoidPtr) override;
    void* mapVoidPtr;
};

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigSoChild::action(void* childCreatorVoidPtr)
{
    UptrChCrIf creator((CChildCreatorIf*)childCreatorVoidPtr);

    printf("behavior specific for CConfigChild: adding ChildCreator to "
           "selector\n");

    ((MapOfUptrChCrIf*)mapVoidPtr)->push_back(std::move(creator));

    return nullptr;
}

CConfigSoChild::~CConfigSoChild()
{
    printf("CConfigSoChild destructing\n");
    fflush(NULL);
}

extern "C" CParent* createNewCConfigSoChildExternC()
{
    return new CConfigSoChild();
}

extern "C" void deleteCConfigSoChildExternC(CParent* configChildPtr)
{
    delete configChildPtr;
}
