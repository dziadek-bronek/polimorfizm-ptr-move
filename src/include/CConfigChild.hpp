#ifndef CONFIG_CHILD_HPP
#define CONFIG_CHILD_HPP

#include "CParent.hpp"

struct CConfigChild  : CParent {
  virtual void* action(void* actionParameterVoidPtr) override;
};

#endif
