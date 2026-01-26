// #include"include/child-creators.hpp"
#include"include/registering.hpp"

#include"include/child-creators.hpp"

/* implementation requires to know: map  */
template<typename CHILD>
void assignChildCreatorToEvent(int event,
        std::list<std::unique_ptr<CChildCreatorP>>& map)
{
    map.push_back(std::unique_ptr<CChildCreatorP>(new CChildCreator<CHILD>(event)));
}

void registerChildCreators(std::list<std::unique_ptr<CChildCreatorP>>& map) {
        assignChildCreatorToEvent<CChild1>(1, map);
        assignChildCreatorToEvent<CChild2>(2, map);
        assignChildCreatorToEvent<CChild3>(3, map);
}