#ifndef CSELECTORCONFIGURATOR_HPP
#define CSELECTORCONFIGURATOR_HPP

#include "CSelectorConfiguratorIf.hpp"

CSelectorConfiguratorIf* createNewCSimpleSelectorConfigurator();

CSelectorConfiguratorIf* createNewCSelectorConfigurator(
    void* initConfigVoidPtr);

#endif
