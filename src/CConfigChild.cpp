#include "include/CConfigChild.hpp"
#include <list>
#include <memory>

#include <cstdio>
#include "include/child-creators.hpp"

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

void* CConfigChild::action(void* actionParameterVoidPtr) {
  struct CAddParams {
    MapOfUptrChCrIf* mapPtr;
    UptrChCrIf* creator;
  };

  printf("configChild adding \n");
  CAddParams* x = ((CAddParams*)(actionParameterVoidPtr));

  (x->mapPtr)->push_back(std::move(*(x->creator)));

  return nullptr;
}
