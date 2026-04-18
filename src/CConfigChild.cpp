#include "include/CConfigChild.hpp"
#include <list>
#include <memory>

#include "include/child-creators.hpp"
#include <cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigChild::action(void* childCreatorUptrVoidPtr)
{
    UptrChCrIf* creator = (UptrChCrIf*)childCreatorUptrVoidPtr;

    printf("configChild is adding creator\n");

    ((MapOfUptrChCrIf*)mapVoidPtr)->push_back(std::move(*(creator)));

    return nullptr;
}

extern "C" CParent* createNewCConfigChildExternC() {
	return new CConfigChild();
}

extern "C" void deleteCConfigChildExternC(CParent* configChildPtr) {
	delete configChildPtr;
}
