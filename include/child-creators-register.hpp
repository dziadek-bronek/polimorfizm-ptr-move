#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

#include<list>
#include<memory>
#include"parent-creator.hpp"


std::unique_ptr<CParent> newChildBasedOnEvent(
        int event,std::list<std::unique_ptr<CParentCreator>>& map);

void registerChildCreators(std::list<std::unique_ptr<CParentCreator>>& map);
#endif