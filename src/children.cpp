#include "include/children.hpp"
#include <cstdio>

CChild1::CChild1() { printf("child 1 constructor\n"); }
void CChild1::action() { printf("behavior specific for child 1\n"); }
CChild1::~CChild1() { printf("child 1 destructor\n"); }

CChild2::CChild2() { printf("child 2 constructor\n"); }
void CChild2::action() { printf("behavior specific for child 2\n"); }
CChild2::~CChild2() { printf("child 2 destructor\n"); }

CChild3::CChild3() { printf("child 3 constructor\n"); }
void CChild3::action() { printf("behavior specific for child 3\n"); }
CChild3::~CChild3() { printf("child 3 destructor\n"); }

CChild4::CChild4() { printf("child 4 constructor\n"); }
void CChild4::action() { printf("behavior specific for child 4\n"); }
CChild4::~CChild4() { printf("child 4 destructor\n"); }
