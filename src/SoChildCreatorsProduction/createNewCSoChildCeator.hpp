#ifndef CREATE_NEW_C_SO_CHILD_CREATOR_HPP
#define CREATE_NEW_C_SO_CHILD_CREATOR_HPP

using FPluginCreator = void* (*)();
using FPluginDestroyer = void (*)(void*);

void* createNewCSoChildCreator(int id, void* soChildInitParameterVoidPtr,
                               void* dlHandle, FPluginCreator pluginCreator,
                               FPluginDestroyer pluginDestroyer);
#endif
