#include<cstdio>
#include<memory>
#include<vector>
#include<iostream>

struct CParent {
    virtual void action() = 0;
};

struct CParentCreator {
    virtual std::unique_ptr<CParent> createNew() = 0;
};

template <typename T>
struct CChildCreator : CParentCreator {
    virtual std::unique_ptr<CParent> createNew() {return std::unique_ptr<CParent> (new T);}
};

std::vector<CParentCreator*> mapOfEventsAndChildren{0,0,0,0,0};

template<typename CHILD>
void mapChildCreatorToEvent(int event ) {
    mapOfEventsAndChildren[event] = new CChildCreator<CHILD>;
}

std::unique_ptr<CParent> resolveEventToAChild(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in resolveEventToAChild";
    }

    for(int i = 1; i < mapOfEventsAndChildren.size(); ++i) {
        if(i == event) {
            if(mapOfEventsAndChildren[i]) {
                return std::unique_ptr<CParent>( ( (mapOfEventsAndChildren[i])-> createNew() ));
            }
        }
    }

    throw "Exit on error: unknown event";
}

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

struct CChild1 : CParent {
    virtual void action() { printf("behavior specific for child 1\n"); }
};

struct CChild2 : CParent {
    virtual void action() { printf("behavior specific for child 2\n"); }
};

struct CChild3 : CParent {
    virtual void action() { printf("behavior specific for child 3\n"); }
};

void registerChildren() {
        mapChildCreatorToEvent<CChild1>(1);
        mapChildCreatorToEvent<CChild2>(2);
        mapChildCreatorToEvent<CChild3>(3);
}

int main() {
    try {

        CInput input;
        input.init(std::unique_ptr<std::vector<int>> (new std::vector<int>{1,3,2,2,1,2,1,1,2,5}));

        registerChildren();

        for(int event = input.getCurrentEvent(); ;  event = input.nextCurrentEvent() /* input++*/ ) {
            resolveEventToAChild(event)->action();
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
