struct CSelectorConfiguratorIf {
  virtual ~CSelectorConfiguratorIf() {}

  static CSelectorConfiguratorIf* createNew(void* selectorInitConfigVoidPtr);
  virtual void* getInitConfig() { return nullptr; };
  virtual void setMap(void* _mapVoidPtr) {};
  virtual void action(int x, void* childCreatorVoidPtr) {}
};
