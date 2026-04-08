struct CFrameworkIf {
  static CFrameworkIf* createNew(void* selectorInitConfigVoidPtr);
  virtual ~CFrameworkIf() = 0;

  virtual void configAction(int, void*) = 0;
  virtual void mainLoop(void* inputVoidPtr) = 0;
};
