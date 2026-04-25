#ifndef CCREATORSELECTORIF_HPP
#define CCREATORSELECTORIF_HPP

struct CSelectorIf
{
    // static CSelectorIf* createNew(...);
    virtual ~CSelectorIf() = default;

    virtual void* at(int event) = 0;
};

#endif
