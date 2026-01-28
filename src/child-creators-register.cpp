
#include"include/child-creators-register.hpp"

#include"include/child-creator.hpp"


struct CCreatorsRegister: CCreatorsRegisterIf {
        virtual std::unique_ptr<CParent> newChildBasedOnEvent(int event);

        virtual void init();
    private:
        std::list<std::unique_ptr<CChildCreator>> map; /* mapOfEventsAndChildrenCreators; */

};

void CCreatorsRegister::init() { /* delegate to child creators parents - CChildCreator */
    registerChildCreators(map);
}

std::unique_ptr<CParent> CCreatorsRegister::newChildBasedOnEvent(int event)
{
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }

    for(std::unique_ptr<CChildCreator>& childCreator : map)
    {
        if(childCreator->number == event) {
            return std::unique_ptr<CParent>(childCreator->createNewChild());
        }
    }

    throw "Exit on error: unknown event";
}

std::unique_ptr<CCreatorsRegisterIf> CCreatorsRegisterIf::createNew() {
    return std::unique_ptr<CCreatorsRegisterIf>(new CCreatorsRegister());
} 