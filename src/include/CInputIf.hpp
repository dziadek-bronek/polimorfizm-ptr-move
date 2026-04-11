#ifndef CINPUTIF_HPP
#define CINPUTIF_HPP

#include <memory>
#include <vector>

struct CInputIf
{
    static CInputIf *createNew();
    virtual ~CInputIf();

    virtual void init(void *sequenceOfEvents_) = 0;

    virtual int getCurrentEvent() = 0;

    virtual int nextCurrentEvent() = 0;

    virtual void setCurrentEvent() = 0;
};

#endif
