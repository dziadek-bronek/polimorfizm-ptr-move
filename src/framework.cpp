
#include"include/parent.hpp"
#include"include/child-creators-register.hpp"

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

    void CFramework::mainLoop(CInput& input, void* regConfigVoidPtr) {
        creatorsRegister = 
                std::unique_ptr<CCreatorsRegisterIf>(CCreatorsRegisterIf::createNew(regConfigVoidPtr));
        for(int event = input.getCurrentEvent(); ;
                event = input.nextCurrentEvent() /* input++*/ )
        {
            std::unique_ptr<CParent> child((CParent*)(creatorsRegister->newChildBasedOnEvent(event)));
            child->action();
        }
    }

