#ifndef CREATE_NEW_C_SO_CHILD_CREATOR_HPP
#define CREATE_NEW_C_SO_CHILD_CREATOR_HPP

using CreateNewPlugin = void* (*)();
using DeletePlugin = void (*)(void*);

void* createNewCSoChildCreator(int, void*, void*, CreateNewPlugin,
                               DeletePlugin);
#endif
