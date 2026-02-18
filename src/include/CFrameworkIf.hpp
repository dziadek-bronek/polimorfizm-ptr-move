struct CFrameworkIf {
  virtual ~CFrameworkIf() {}
  static CFrameworkIf* createNew(void* selectorConfigVoidPtr);

  virtual void selectorConfigAdd(void*) = 0;
  virtual void mainLoop(void* inputVoidPtr) = 0;
};
