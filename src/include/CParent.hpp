#ifndef CPARENT_HPP
#define CPARENT_HPP

struct CParent {
  virtual ~CParent(){}

  virtual void action() = 0;
  virtual void constr() = 0;
  virtual void destr() = 0;
};

CParent* createNewChild(int number);

#endif
