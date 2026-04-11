#ifndef CMAPIF_HPP
#define CMAPIF_HPP

struct CMapIf
{
    static CMapIf *createNew();
    ~CMapIf();

    virtual void *at(int number) = 0;
    virtual void push_back(void *) = 0;
};
#endif
