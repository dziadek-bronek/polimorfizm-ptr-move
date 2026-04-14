#ifndef CCREATORSELECTORIF_HPP
#define CCREATORSELECTORIF_HPP

struct CSelectorIf
{
    // static CSelectorIf* createNew(...);
    virtual ~CSelectorIf() = 0;

    virtual void* at(int event) = 0;
};

#endif
