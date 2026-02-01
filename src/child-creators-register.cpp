#include"include/child-creators-register.hpp"
#include"include/child-creators.hpp"
#include"include/children.hpp"

#include<list>
#include<memory>

template<typename CHILD>
static void pushBackChildCreator(std::list<std::unique_ptr<CChildCreatorIf>>& map,
        int number)
{
    map.push_back(std::unique_ptr<CChildCreatorIf>(new CChildCreator<CHILD>(number)));
}

template<>
void CCreatorsRegister<CParent, CChildCreatorIf>::init() {
    pushBackChildCreator<CChild1>(map, 1);
    pushBackChildCreator<CChild2>(map, 2);
    pushBackChildCreator<CChild3>(map, 3);
    pushBackChildCreator<CChild4>(map, 4);
}
