#include"include/child-creators-register.hpp"

#include"include/child-creator.hpp"
#include<list>
#include<memory>
#include"include/throw.hpp"

struct CCreatorsRegister: CCreatorsRegisterIf {
        CCreatorsRegister(){printf("The register of child creators: constructing\n");}
        virtual ~CCreatorsRegister(){printf("The register of child creators: destructing\n");}

        virtual void init();
        virtual CParent* newChildBasedOnEvent(int event);

    private:
        std::list<std::unique_ptr<CChildCreatorIf<CParent>>> map; /* mapOfEventsAndChildrenCreators; */
};

void registerChildCreators(std::list<std::unique_ptr<CChildCreatorIf<CParent>>>& map);
void CCreatorsRegister::init() {
    registerChildCreators(map);
}

CParent* CCreatorsRegister::newChildBasedOnEvent(int event) {
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }

    for(std::unique_ptr<CChildCreatorIf<CParent>>& childCreator : map) {
        CParent* x = childCreator->createNewChildIfIsNumber(event);
        if(nullptr != x) {
            printf("The register of child creators: new child created based on event %i\n",
                        event);
            return x;
        }
    }

    THROW2("Exit", " on error: unknown event");
}

CCreatorsRegisterIf* CCreatorsRegisterIf::createNew() {
    return new CCreatorsRegister();
} 

