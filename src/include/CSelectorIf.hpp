#ifndef CSELECTORIF_HPP
#define CSELECTORIF_HPP

struct CSelectorIf
{
    static CSelectorIf *createNew(void *selectorInitConfigVoidPtr);
    virtual ~CSelectorIf() = 0;

    virtual void *init() = 0;
    virtual void *at(int event) = 0;
};

#endif
