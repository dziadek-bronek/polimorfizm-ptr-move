#include"include/child-creators.hpp"
#include"include/children.hpp"

#include<list>
#include<memory>

template<typename CHILD, typename PARENT>
static void pushBackChildCreator(std::list<std::unique_ptr<CChildCreatorIf<PARENT>>>& map, int number){
    map.push_back(std::unique_ptr<CChildCreatorIf<PARENT>>(new CChildCreator<CHILD, PARENT>(number)));
}

void registerChildCreators(std::list<std::unique_ptr<CChildCreatorIf<CParent>>>& map) {
    pushBackChildCreator<CChild1, CParent>(map, 1);
    pushBackChildCreator<CChild2, CParent>(map, 2);
    pushBackChildCreator<CChild3, CParent>(map, 3);
}