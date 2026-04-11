#include "include/CConfigChild.hpp"
#include <list>
#include <memory>

#include "include/child-creators.hpp"
#include <cstdio>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigChild::action(void* actionParameterVoidPtr)
{
    struct CAddParams
    {
        MapOfUptrChCrIf* mapPtr;
        UptrChCrIf* creator;
    };

    printf("configChild is adding creator\n");
    CAddParams* x = ((CAddParams*)(actionParameterVoidPtr));

    (x->mapPtr)->push_back(std::move(*(x->creator)));

    return nullptr;
}
