struct CFrameworkIf {
  virtual ~CFrameworkIf() {}
  static CFrameworkIf* createNew(void* selectorConfigVoidPtr);

  virtual void configAction(int, void*) = 0;
  virtual void mainLoop(void* inputVoidPtr) = 0;
  virtual void* getChildBasedOnNumber(int n) = 0;
};
