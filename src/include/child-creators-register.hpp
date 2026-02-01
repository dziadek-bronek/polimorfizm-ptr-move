#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

#include<list>
#include<memory>
#include"throw.hpp"


template<typename PARENT, typename CHILD_CREATOR>
struct CCreatorsRegister {
    CCreatorsRegister() {printf("The register of child creators: constructing\n");}
    ~CCreatorsRegister() {printf("The register of child creators: destructing\n");}
    
    void init();

    PARENT* newChildBasedOnEvent(int event) {
        if (0 == event) {
            throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
        }

        for(std::unique_ptr<CHILD_CREATOR>& childCreator : map) {
            PARENT* x = (PARENT*)childCreator->createNewChildIfIsNumber(event);
            if(nullptr != x) {
                printf("The register of child creators: new child created based on event %i\n",
                        event);
                return x;
            }
        }

        THROW2("Exit", " on error: unknown event");
    }

private:
    std::list<std::unique_ptr<CHILD_CREATOR>> map; 
};

#endif