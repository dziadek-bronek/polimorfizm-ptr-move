#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include "CParent.hpp"

struct CChild1 : CParent {
  CChild1();
  virtual void action();
  virtual ~CChild1();
};

struct CChild2 : CParent {
  CChild2();
  virtual void action();
  virtual ~CChild2();
};

struct CChild3 : CParent {
  CChild3();
  virtual void action();
  virtual ~CChild3();
};

struct CChild4 : CParent {
  CChild4();
  virtual void action();
  virtual ~CChild4();
};

#endif