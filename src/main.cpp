#include<cstdio>
#include<iostream>

#include<memory>
#include<vector>

#include"include/throw.hpp"

struct CInput {
    int indexOfCurrentEvent{0};
    std::unique_ptr<std::vector<int>> sequenceOfEvents;
    int currentEvent{0};

    void init(std::unique_ptr<std::vector<int>> sequenceOfEvents_) {
        sequenceOfEvents = std::move(sequenceOfEvents_);
	    setCurrentEvent();
    }

    int getCurrentEvent() {
        return currentEvent;
    }

    int nextCurrentEvent() {
	    ++indexOfCurrentEvent;
        setCurrentEvent();
        return currentEvent;
    }

    void setCurrentEvent() {
        if (indexOfCurrentEvent < 0) {
            THROW2("Exit",  " on error: invalid index of event");
        }

        if (sequenceOfEvents->size() <= indexOfCurrentEvent) {
            THROW2("Clean exit", " (no more events)");
        }

        currentEvent = (*sequenceOfEvents)[indexOfCurrentEvent];
        if(0 == currentEvent) {
            THROW2("Clean exit", " (event 'EXIT' in sequenceOfEvents)");
        }
    }
};

#include"include/child-creators-register.hpp"
int main() {
    try {

        CInput input;
        input.init(std::unique_ptr<std::vector<int>> (new std::vector<int>{2,3,1,0}));

        std::unique_ptr<CCreatorsRegisterIf> creatorsRegister(CCreatorsRegisterIf::createNew());
        creatorsRegister->init();

        for(int event = input.getCurrentEvent(); ;
                event = input.nextCurrentEvent() /* input++*/ )
        {
            std::unique_ptr<CParent> child(creatorsRegister->newChildBasedOnEvent(event));
            child->action();
        }

    } catch(const char* result) {
        printf("%s.\n", result);
        return 0;
    } catch(...) {
        printf("FATAL ERROR! Unhandled exception.");
        return 1;
    }

    return 0;
}
