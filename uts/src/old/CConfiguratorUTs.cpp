
struct CChecker
{
    virtual void CSimpleConfiguratorConstructor()
    {
    }
    virtual void CConfiguratorConstructor()
    {
    }
    virtual void CSimpleConfiguratorDestructor()
    {
    }
    virtual void CConfiguratorDestructor()
    {
    }
};

struct CCheckerMock : CChecker
{
    MOCK_METHOD(void, CSimpleConfiguratorConstructor, (), (override));
    MOCK_METHOD(void, CConfiguratorConstructor, (), (override));
    MOCK_METHOD(void, CSimpleConfiguratorDestructor, (), (override));
    MOCK_METHOD(void, CConfiguratorDestructor, (), (override));
};

CCheckerMock* checkerMockPtr;
int* checkerIntPtr;

TEST(CSelectorConfiguratorUTs, CConfiguratorInitializesSelector){
	std::vector<int> initConfig{7, 3};
	std::unique_ptr<CSelectorConfiguratorIf> configurator((CSelectorConfiguratorIf*)createNewCConfigurator(&initConfig));
	std::unique_ptr<CChildSelectorIf> selector((CChildSelectorIf*)selector->initialize());
}

TEST(CConfiguratorUTs, CreateConfigChild){
}

TEST(CConfiguratorUTs, CreateConfigChild){
}
