
TEST(SelectorConfigurator, AdvancedSelectorVsSimpleSelector) {
  struct CSelectorConfigurator : CSelectorConfiguratorIf {
    MOCK_METHOD(void, init, (void*), (override));
  };

  struct CSelectorSimpleConfigurator : CSelectorConfiguratorIf {
    MOCK_METHOD(void, init, (void*), (override));

    try {
      std::vector<int> selectorInitConfig({7, -1, -1, -1, 4});
    };

  } catch (...) {
  }
}
