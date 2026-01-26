#ifndef CHILD_CREATORS_REGISTER_HPP
#define CHILD_CREATORS_REGISTER_HPP

#include"parent-creator.hpp"

#include<list>
#include<memory>


std::unique_ptr<CParent> newChildBasedOnEvent(
        int event,std::list<std::unique_ptr<CChildCreatorP>>& map);

void registerRegisterChildCreators(std::list<std::unique_ptr<CChildCreatorP>>& map);

#endif