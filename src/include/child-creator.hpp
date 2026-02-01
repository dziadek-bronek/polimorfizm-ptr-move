#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

struct CChildCreatorIf {
    static void initMapWithCreators(void* mapVoidPtr);
    virtual void* createNewChildIfIsNumber(int number_) = 0;
    virtual ~CChildCreatorIf() {}
};

#endif
