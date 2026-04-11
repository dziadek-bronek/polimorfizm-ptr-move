#include "include/CFramework.hpp"

// not implemented
CFrameworkIf* newCFrameworkIfSO(void* selectorInitConfigVoidPtr)
{
    CFrameworkIf* frameworkIfObjectPtr = nullptr;
    // here open .so library and get custom class implementation
    // return shared object

    return frameworkIfObjectPtr;
}

CFrameworkIf* CFrameworkIf::createNew(void* selectorInitConfigVoidPtr)
{
    // not implemented:
    // return newCFrameworkIfSharedObject();

    // expect static 'newCFramework'
    return createNewCFramework(selectorInitConfigVoidPtr);
}
CFrameworkIf::~CFrameworkIf()
{
}
