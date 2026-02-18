#ifndef THROW
#define THROW2(napisA, napisB)              \
  {                                         \
    printf("Exiting%s.\n......\n", napisB); \
    throw napisA napisB;                    \
  }

#endif