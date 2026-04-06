#include "include/CSelectorConfigurator.hpp"
#include <cstdio>
#include <list>
#include <memory>
#include "include/CChildren.hpp"
#include "include/CConfigChild.hpp"
#include "include/child-creators.hpp"
#include "include/throw.hpp"

#include <vector>

struct CChildCreatorExit : CChildCreatorIf {
  CChildCreatorExit(int id_) : id(id_) {
    printf("ChildCreator constructor for  EXIT event %i \n", id);
  }
  virtual ~CChildCreatorExit() {
    printf("ChildCreator destructor for  EXIT event %i \n", id);
  }

  virtual void* createNewChildIfIsNumber(int id_) {
    if (id_ == id) {
      printf("CChildCreator on event %i : exit\n", id);
      THROW2("Clean exit", " (event 'EXIT' on input)");
    }
    return nullptr;
  }

 private:
  int id;
};

static CChildCreatorIf* createCreatorForChildWithNumber(int childClass,
                                                        int event) {
  switch (childClass) {
    case 1:
      return new CChildCreator<CChild1>(event);
    case 2:
      return new CChildCreator<CChild2>(event);
    case 3:
      return new CChildCreator<CChild3>(event);
    case 4:
      return new CChildCreator<CChild4>(event);
  }
  throw;
}

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

void configureSimpleSelection(void* x) {
  CChildCreatorIf** y = (CChildCreatorIf**)x;
  *y = new CChildCreatorSimple;
}

struct CSelectorConfigurator : CSelectorConfiguratorIf {
  using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
  using MapOfUptrChCrIf = std::list<UptrChCrIf>;

  CSelectorConfigurator(void* selectorInitConfigVoidPtr) {
    initConfig = *((std::vector<int>*)selectorInitConfigVoidPtr);
  }

  virtual void* init() {
    map.push_back(UptrChCrIf(new CChildCreator<CConfigChild>(222)));

    int vSize = initConfig.size();

    if (vSize <= 0) {
      map.push_back(UptrChCrIf(new CChildCreatorExit(0)));
      return &map;
    }

    map.push_back(UptrChCrIf(new CChildCreatorExit(initConfig.at(0))));

    for (int i = 1; i < vSize; ++i) {
      int event = initConfig.at(i);
      if (event < 0) {
        continue;
      }
      map.push_back(UptrChCrIf(::createCreatorForChildWithNumber(i, event)));
    }
    return &map;
  }

  virtual void action(int x, void* childCreatorVoidPtr) {
    UptrChCrIf* childCreatorPtr = (UptrChCrIf*)childCreatorVoidPtr;

    map.push_back(std::move(*childCreatorPtr));
  }

 private:
  MapOfUptrChCrIf map;
  std::vector<int> initConfig;
};

CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* selectorInitConfigVoidPtr) {
  return new CSelectorConfigurator(selectorInitConfigVoidPtr);
}
