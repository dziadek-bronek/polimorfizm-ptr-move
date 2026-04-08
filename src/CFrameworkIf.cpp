#include "include/CFrameworkIf.hpp"

// not implemented
CFrameworkIf* newCFrameworkIfSO(void* selectorInitConfigVoidPtr) {
  CFrameworkIf* frameworkIfObjectPtr = nullptr;
  // here open .so library and get custom class implementation
  // return shared object

  return frameworkIfObjectPtr;
}

CFrameworkIf* newCFramework(void* selectorInitConfigVoidPtr);

CFrameworkIf* CFrameworkIf::createNew(void* selectorInitConfigVoidPtr) {
  // not implemented:
  // return newCFrameworkIfSharedObject();

  // expect static 'newCFramework'
  return newCFramework(selectorInitConfigVoidPtr);
}
CFrameworkIf::~CFrameworkIf() {}
