#include "include/selector-config.hpp"
#include "include/CChildren.hpp"
#include "include/CConfigChild.hpp"
#include "include/child-creator.hpp"
#include "include/throw.hpp"

#include <list>
#include <memory>
#include <vector>

#include <cstdio>
#include "include/child-creators.hpp"

struct CChildCreatorSimple : CChildCreatorIf {
  virtual ~CChildCreatorSimple() {
    printf("ChildCreatorSimpleSelection destructor\n");
  }

  virtual void* createNewChildIfIsNumber(int id_) {
    switch (id_) {
      case 0:
        THROW2("Clean exit", " (event 'EXIT' on input)");
      case 1:
        return new CChild1;
      case 2:
        return new CChild2;
      case 3:
        return new CChild3;
      case 4:
        return new CChild4;
    }
    return nullptr;
  }
};

void* configureSimpleSelection() {
  return new CChildCreatorSimple;
}
