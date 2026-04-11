#ifndef CSELECTORCONFIGURATORIF_HPP
#define CSELECTORCONFIGURATORIF_HPP

struct CSelectorConfiguratorIf
{
    static CSelectorConfiguratorIf* createNew(void* initConfigVoidPtr);

    virtual ~CSelectorConfiguratorIf() = 0;

    virtual void* initializeSelector() = 0;
};

#endif
