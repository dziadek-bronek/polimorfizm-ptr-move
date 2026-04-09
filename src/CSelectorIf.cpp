#include "include/CSelectorIf.hpp"
#include "include/CSimpleSelector.hpp"
#include "include/CSelector.hpp"

CSelectorIf* CSelectorIf::createNew(void* selectorCoreVoidPtr) {
  if (nullptr == selectorCoreVoidPtr) {
    return createNewCSimpleSelector();
  }

    return createNewCSelector(selectorCoreVoidPtr);
}

CSelectorIf::~CSelectorIf() {}
