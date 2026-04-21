#include "CConfigChild.hpp"
#include "../include/child-creators.hpp"
#include <cstdio>
#include <list>
#include <memory>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigChild::action(void* childCreatorVoidPtr)
{
    UptrChCrIf creator((CChildCreatorIf*)childCreatorVoidPtr);

    printf("configChild is adding creator\n");

    ((MapOfUptrChCrIf*)mapVoidPtr)->push_back(std::move(creator));

    return nullptr;
}

CConfigChild::~CConfigChild()
{
    printf("CConfigChild destructing\n");
    fflush(NULL);
}

extern "C" CParent* createNewCConfigChildExternC()
{
    return new CConfigChild();
}

extern "C" void deleteCConfigChildExternC(CParent* configChildPtr)
{
    delete configChildPtr;
}
