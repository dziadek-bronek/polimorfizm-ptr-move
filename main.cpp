#include"include/parent-creator.hpp"
#include"include/child-creators-register.hpp"

#include<cstdio>
#include<memory>
#include<vector>
#include<list>
#include<iostream>

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
            throw "Exit on error: invalid index of event";
        }

        if (sequenceOfEvents->size() <= indexOfCurrentEvent) {
            throw "Clean exit: no more events";
        }

        currentEvent = (*sequenceOfEvents)[indexOfCurrentEvent];
        if(0 == currentEvent) {
            throw "Clean exit: event 'EXIT' in sequenceOfEvents";
        }
    }
};

int main() {
    try {

        CInput input;
        input.init(std::unique_ptr<std::vector<int>> (new std::vector<int>{1,3,2,2,1,2,1,1,2,5}));

        /* register of creators of children */
        std::list<std::unique_ptr<CParentCreator>> mapOfEventsAndChildrenCreators;
        registerChildCreators(mapOfEventsAndChildrenCreators);

        for(int event = input.getCurrentEvent(); ;
                event = input.nextCurrentEvent() /* input++*/ )
        {
            std::unique_ptr<CParent> child
                    = newChildBasedOnEvent(event, mapOfEventsAndChildrenCreators);
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
