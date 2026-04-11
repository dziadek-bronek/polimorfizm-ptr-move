#include "include/CSelectorConfigurator.hpp"

CSelectorConfiguratorIf::~CSelectorConfiguratorIf()
{
}

CSelectorConfiguratorIf* CSelectorConfiguratorIf::createNew(
    void* initConfigVoidPtr)
{
    if (nullptr == initConfigVoidPtr)
    {
        return createNewCSimpleSelectorConfigurator();
    }
    return createNewCSelectorConfigurator(initConfigVoidPtr);
}
