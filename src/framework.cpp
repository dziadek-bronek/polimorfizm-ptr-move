
#include"include/parent.hpp"
#include"include/child-selector.hpp"

#include"include/throw.hpp"

#include"include/framework.hpp"

#include<memory>
#include<vector>

    void CInput::init(std::vector<int>* sequenceOfEvents_) {
        sequenceOfEvents = std::unique_ptr<std::vector<int>> (sequenceOfEvents_);
	    setCurrentEvent();
    }

    int CInput::getCurrentEvent() {
        return currentEvent;
    }

    int CInput::nextCurrentEvent() {
	    ++indexOfCurrentEvent;
        setCurrentEvent();
        return currentEvent;
    }

    void CInput::setCurrentEvent() {
        if (indexOfCurrentEvent < 0) {
            THROW2("Exit",  " on error: invalid index of event");
        }

        if (sequenceOfEvents->size() <= indexOfCurrentEvent) {
            THROW2("Clean exit", " (no more events)");
        }

        currentEvent = (*sequenceOfEvents)[indexOfCurrentEvent];
    }

struct CFramework : CFrameworkIf{
    ~CFramework(){ printf("CFramework destructor\n"); }
     
    virtual void mainLoop(CInput& input, void* selectorConfigVoidPtr) {
        childSelector =  std::unique_ptr<CChildSelectorIf>(
                        CChildSelectorIf::createNew(selectorConfigVoidPtr)
                    );
        for(int event = input.getCurrentEvent(); ;
                event = input.nextCurrentEvent() /* input++*/ )
        {
            std::unique_ptr<CParent> child(
                        (CParent*)(childSelector->newChildBasedOnEvent(event))
                    );
            child->action();
        }
    }
    private:
    std::unique_ptr<CChildSelectorIf> childSelector;
};

CFrameworkIf* CFrameworkIf::createNew() {
    return new CFramework;
}
