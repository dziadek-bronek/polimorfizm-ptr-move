#ifndef CREATE_NEW_C_SO_CHILD_CREATOR_HPP
#define CREATE_NEW_C_SO_CHILD_CREATOR_HPP

#include "../include/VOID.hpp"
#include <memory>
using FPluginCreator = void* (*)();
using FPluginDestroyer = void (*)(void*);

void* createNewCSoChildCreator(
    int id, std::unique_ptr<VOID> soChildInitParameterVoidPtr, void* dlHandle,
    FPluginCreator pluginCreator, FPluginDestroyer pluginDestroyer);
#endif
