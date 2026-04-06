struct CSelectorConfiguratorIf {
  virtual ~CSelectorConfiguratorIf() {}

  static CSelectorConfiguratorIf* createNew(void* selectorInitConfigVoidPtr);
  virtual void* init() { return nullptr; };
  virtual void action(int x, void* childCreatorVoidPtr) {}
};

void configureSimpleSelection(void*);
