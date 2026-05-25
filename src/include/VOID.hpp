#ifndef VOID_HPP
#define VOID_HPP
#include <cstdio>
#include <memory>
struct VOID
{
    virtual ~VOID()
    {
        printf("VOID DESTRUCTOR\n");
    } //= default;
};

#define PACK_1(STRUCT_ID, OBJ_U_PTR_ID, F_A_TYPE, F_A, F_A_INIT)               \
    struct STRUCT_ID : VOID                                                    \
    {                                                                          \
        F_A_TYPE F_A_ID;                                                       \
    };                                                                         \
    std::unique_ptr<STRUCT_ID> OBJ_U_PTR_ID(new STRUCT_ID);                    \
    OBJ_U_PTR_ID->F_A_ID = F_A_INIT

template <typename T> struct CWrapperVOID_1 : VOID
{
    CWrapperVOID_1(T xInit)
        : x(std::move(xInit))
    {
    }
    T x;
};

#endif /* ifndef VOID_HPP */
