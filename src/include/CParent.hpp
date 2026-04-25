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

struct CParent
{
    virtual ~CParent() = default;

    virtual void init(void* initParameterVoidPtr) {}
    virtual void action() {}
    virtual void* action(void* actionParameterVoidPtr) { return nullptr; }
};

CParent* createNewChild(int number);

#endif
