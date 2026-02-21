#include "include/children.hpp"
#include <cstdio>

void CChild1::constr() {
  printf("child 1 constructor\n");
}
void CChild1::action() {
  printf("behavior specific for child 1\n");
}
void CChild1::destr() {
  printf("child 1 destructor\n");
}

void CChild2::constr() {
  printf("child 2 constructor\n");
}
void CChild2::action() {
  printf("behavior specific for child 2\n");
}
void CChild2::destr() {
  printf("child 2 destructor\n");
}

void CChild3::constr() {
  printf("child 3 constructor\n");
}
void CChild3::action() {
  printf("behavior specific for child 3\n");
}
void CChild3::destr() {
  printf("child 3 destructor\n");
}

void CChild4::constr() {
  printf("child 4 constructor\n");
}
void CChild4::action() {
  printf("behavior specific for child 4\n");
}
void CChild4::destr() {
  printf("child 4 destructor\n");
}
