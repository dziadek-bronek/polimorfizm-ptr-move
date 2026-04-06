#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

struct CChildSelectorIf {
  static CChildSelectorIf* createNew(void* selectorConfigVoidPtr);
  virtual ~CChildSelectorIf() {}
  virtual void* getConfig() { return nullptr; }

  virtual void* newChildBasedOnEvent(int event) { return nullptr; }
};

#endif
