struct CSelectorConfiguratorIf {
  virtual ~CSelectorConfiguratorIf() {}

  static CSelectorConfiguratorIf* createNew(void* selectorInitConfigVoidPtr);
  virtual void init(void* mapPtrVoidPtr) {};
  virtual void initSimple(void*) {}

  virtual void action(int x, void* childCreatorVoidPtr) {}
};
