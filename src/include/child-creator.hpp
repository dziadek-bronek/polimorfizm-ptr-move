#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

struct CChildCreatorIf {
    static void initMapWithCreators(void* mapVoidPtr);
    template<typename CHILD>
    static void registerr(void* mapVoidPtr, int event);
    virtual void* createNewChildIfIsNumber(int number_) = 0;
    virtual ~CChildCreatorIf() {}
};

#endif
