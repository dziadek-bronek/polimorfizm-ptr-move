#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

template<typename PARENT>
struct CCreatorsRegisterIf  {
    static CCreatorsRegisterIf* createNew();    
    virtual ~CCreatorsRegisterIf() {}      
    virtual void init();
    virtual PARENT* newChildBasedOnEvent(int event) = 0;
};

#endif