
#include"include/child-creators-register.hpp"

std::unique_ptr<CParent> newChildBasedOnEvent(
        int event,std::list<std::unique_ptr<CChildCreatorP>>& map)
{
    if (0 == event) {
        throw "Clean exit: event 'EXIT' in newChildBasedOnEvent";
    }

    for(std::unique_ptr<CChildCreatorP>& childCreator : map)
    {
        if(childCreator->number == event) {
            return std::unique_ptr<CParent>(childCreator->createNew());
        }
    }

    throw "Exit on error: unknown event";
}

#include"include/registering.hpp"
void registerRegisterChildCreators(std::list<std::unique_ptr<CChildCreatorP>>& map) {
    registerChildCreators(map);
}
