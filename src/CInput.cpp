#include "include/CInputIf.hpp"

#include "include/throw.hpp"
#include <cstdio>

struct CInput : CInputIf
{
    virtual void init(void* sequenceOfEvents_);

    virtual int getCurrentEvent();

    virtual int nextCurrentEvent();

    virtual void setCurrentEvent();

  private:
    int indexOfCurrentEvent{0};
    std::unique_ptr<std::vector<int>> sequenceOfEvents;
    int currentEvent{0};
};

void CInput::init(void* sequenceOfEvents_)
{
    sequenceOfEvents =
        std::unique_ptr<std::vector<int>>((std::vector<int>*)sequenceOfEvents_);
    setCurrentEvent();
}

int CInput::getCurrentEvent()
{
    return currentEvent;
}

int CInput::nextCurrentEvent()
{
    ++indexOfCurrentEvent;
    setCurrentEvent();
    return currentEvent;
}

void CInput::setCurrentEvent()
{
    if (indexOfCurrentEvent < 0)
    {
        THROW2("Exit", " on error: invalid index of event");
    }

    if (sequenceOfEvents->size() <= indexOfCurrentEvent)
    {
        THROW2("Clean exit", " (no more events)");
    }

    currentEvent = (*sequenceOfEvents)[indexOfCurrentEvent];
}
CInputIf* createNewCInput()
{
    return new CInput;
};
