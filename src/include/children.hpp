#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include "CParent.hpp"

struct CChild1 : CParent {
  CChild1() {constr();};
  virtual ~CChild1() {destr();}
  virtual void action() override;
  virtual void constr() override;
  virtual void destr() override;
};

struct CChild2 : CParent {
  CChild2() {constr();}
  virtual ~CChild2() {destr();}
  virtual void action() override;
  virtual void constr() override;
  virtual void destr() override;
};

struct CChild3 : CParent {
  CChild3() {constr();};
  virtual ~CChild3() {destr();}
  virtual void action() override;
  virtual void constr() override;
  virtual void destr() override;
};

struct CChild4 : CParent {
  CChild4() {constr();}
  virtual ~CChild4() {destr();}
  virtual void action() override;
  virtual void constr() override;
  virtual void destr() override;
};

#endif
