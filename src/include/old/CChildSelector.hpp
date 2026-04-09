#ifndef CSELECTOR_HPP
#define CSELECTOR_HPP

struct CChildSelectorIf {
  static CChildSelectorIf* createNew(void* selectorInitConfigVoidPtr);
  virtual ~CChildSelectorIf() = 0;

  virtual void* init() = 0;
  virtual void* newChildBasedOnEvent(int event) = 0;
};

#endif
