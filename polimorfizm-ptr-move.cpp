#include<cstdio>
#include<memory>
#include<vector>
#include<list>
#include<iostream>

struct CParent {
    virtual void action() = 0;
    virtual ~CParent() {};
};

struct CParentCreator {
    CParentCreator(int number): number(number) {}
    virtual std::unique_ptr<CParent> createNew() = 0;
    virtual ~CParentCreator() {};
    int number;
};

template <typename CHILD>
struct CChildCreator : CParentCreator {
    CChildCreator() = delete;
    CChildCreator(int number): CParentCreator(number) {printf("childCreator constructor %i\n", number);}
    virtual std::unique_ptr<CParent> createNew() {return std::unique_ptr<CParent> (new CHILD);}
    virtual ~CChildCreator() {printf("childCreator destructor %i\n", number);}
};

template<typename CHILD>
void assignChildCreatorToEvent(int event, std::list<std::unique_ptr<CParentCreator>>& map) {
    map.push_back(std::unique_ptr<CParentCreator>(new CChildCreator<CHILD>(event)));
}

std::unique_ptr<CParent> newChildBasedOnEvent(int event,std::list<std::unique_ptr<CParentCreator>>& map) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }

    for(std::unique_ptr<CParentCreator>& childCreator : map)
    {
        if(childCreator->number == event) {
            return std::unique_ptr<CParent>(childCreator->createNew());
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
    CChild1() {printf("child 1 constructor\n");}
    virtual void action() { printf("behavior specific for child 1\n"); }
    virtual ~CChild1() {printf("child 1 destructor\n");}
};

struct CChild2 : CParent {
    CChild2() {printf("child 2 constructor\n");}
    virtual void action() { printf("behavior specific for child 2\n"); }
    virtual ~CChild2() {printf("child 2 destructor\n");}
};

struct CChild3 : CParent {
    CChild3() {printf("child 3 constructor\n");}
    virtual void action() { printf("behavior specific for child 3\n"); }
    virtual ~CChild3() {printf("child 3 destructor\n");}
};

void registerChildren(std::list<std::unique_ptr<CParentCreator>>& map) {
        assignChildCreatorToEvent<CChild1>(1, map);
        assignChildCreatorToEvent<CChild2>(2, map);
        assignChildCreatorToEvent<CChild3>(3, map);
}

int main() {
    try {

        CInput input;
        input.init(std::unique_ptr<std::vector<int>> (new std::vector<int>{1,3,2,2,1,2,1,1,2,5}));

        std::list<std::unique_ptr<CParentCreator>> mapOfEventsAndChildrenCreators;
        registerChildren(mapOfEventsAndChildrenCreators);

        for(int event = input.getCurrentEvent(); ;  event = input.nextCurrentEvent() /* input++*/ ) {
            std::unique_ptr<CParent> child = newChildBasedOnEvent(event, mapOfEventsAndChildrenCreators);
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
