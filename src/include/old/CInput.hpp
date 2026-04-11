#ifndef CINPUT_HPP
#define CINPUT_HPP

#include <memory>
#include <vector>

struct CInputIf
{
    virtual ~CInputIf()
    {
    }

    int indexOfCurrentEvent{0};
    std::unique_ptr<std::vector<int>> sequenceOfEvents;
    int currentEvent{0};

    virtual void init(void* sequenceOfEvents_) = 0;

    virtual int getCurrentEvent() = 0;

    virtual int nextCurrentEvent() = 0;

    virtual void setCurrentEvent() = 0;
};

#endif
