#ifndef CSELECTORCONFIGURATORIF_HPP
#define CSELECTORCONFIGURATORIF_HPP

struct CSelectorConfiguratorIf
{
#ifndef CSELECTORCONFIGURATORIF_IMPLEMENTATION
    static CSelectorConfiguratorIf* createNew(void* initConfigVoidPtr);
#endif

    virtual ~CSelectorConfiguratorIf() = default;

    virtual void init(void* initConfigVoidPtr) = 0;
    virtual void* initializeSelector() = 0;
};

#if 0
alternatywa: dla default (o ile inna metoda ma juz =0 tzn zapewnia ze jest pure virtual
w deklaracji:

= 0;
inline CSelectorConfiguratorIf::~CSelectorConfiguratorIf() {}
#endif

#endif
