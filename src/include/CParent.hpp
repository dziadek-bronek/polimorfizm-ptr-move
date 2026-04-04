#ifndef CPARENT_HPP
#define CPARENT_HPP

/*
struct CParent {
  virtual ~CParent() {}

  virtual void action() = 0;
  virtual void* action(void* actionParameter) = 0;
  virtual void constr() = 0;
  virtual void destr() = 0;
};
*/

struct CParent {
  virtual ~CParent() {}

  virtual void action(){}
  virtual void* action(void* actionParameter){return nullptr;}
  virtual void constr(){}
  virtual void destr(){}
};



CParent* createNewChild(int number);

#endif
