#include "include/CSelectorIf.hpp"
#include "include/CSimpleSelector.hpp"
#include "include/CSelector.hpp"

CSelectorIf* CSelectorIf::createNew(void* initConfigVoidPtr) {
  if (nullptr == initConfigVoidPtr) {
    return createNewCSimpleSelector();
  }

    return createNewCSelector(initConfigVoidPtr);
}

CSelectorIf::~CSelectorIf() {}
