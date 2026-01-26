#include<list>
#include"include/child-creators-register.hpp"

template <typename CHILD>
struct CChildCreator : CParentCreator {
    CChildCreator() = delete;
    CChildCreator(int number): CParentCreator(number) {
        printf("childCreator constructor %i\n", number);
    }
    virtual std::unique_ptr<CParent> createNew() {
        return std::unique_ptr<CParent> (new CHILD);
    }
    virtual ~CChildCreator() {
        printf("childCreator destructor %i\n", number);
        }
};

template<typename CHILD>
void assignChildCreatorToEvent(int event,
        std::list<std::unique_ptr<CParentCreator>>& map)
{
    map.push_back(std::unique_ptr<CParentCreator>(new CChildCreator<CHILD>(event)));
}

std::unique_ptr<CParent> newChildBasedOnEvent(
        int event,std::list<std::unique_ptr<CParentCreator>>& map)
{
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

#include"include/children.hpp"
/* implementation requires to know: all Child  */
void registerChildCreators(std::list<std::unique_ptr<CParentCreator>>& map) {
        assignChildCreatorToEvent<CChild1>(1, map);
        assignChildCreatorToEvent<CChild2>(2, map);
        assignChildCreatorToEvent<CChild3>(3, map);
}
