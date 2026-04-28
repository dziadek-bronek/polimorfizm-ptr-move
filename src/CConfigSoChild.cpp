#include "include/CParent.hpp"
#include "include/child-creators.hpp"
#include <cstdio>
#include <list>
#include <memory>
#include "include/VOID.hpp"

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CConfigSoChild : CParent
{
    virtual ~CConfigSoChild();

    virtual void init(void* initParameterVoidPtr)
    {
	    struct X : VOID{
		    MapOfUptrChCrIf* selectorCoreMap;
	    };
        mapVoidPtr = ((X*)initParameterVoidPtr)->selectorCoreMap;
    }
    virtual void* action(void* childCreatorVoidPtr) override;
    void* mapVoidPtr;
};


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

extern "C" void* createNewCConfigSoChildExternC()
{
    return new CConfigSoChild();
}

extern "C" void deleteCConfigSoChildExternC(void* configChildPtr)
{
    delete (CParent*)configChildPtr;
}
