#include "CConfigSoChild.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>
#include <list>
#include <memory>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigSoChild::action(void* childCreatorVoidPtr)
{
    UptrChCrIf creator((CChildCreatorIf*)childCreatorVoidPtr);

    printf("configChild is adding creator\n");

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
