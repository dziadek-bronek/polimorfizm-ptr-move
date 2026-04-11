#ifndef CHILD_CREATOR_HPP
#define CHILD_CREATOR_HPP

struct CChildCreatorIf
{
    virtual void *createNewChildIfIsNumber(int number_)
    {
        return nullptr;
    }
    virtual ~CChildCreatorIf()
    {
    }
};

#endif
