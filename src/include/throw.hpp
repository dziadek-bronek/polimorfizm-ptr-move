#ifndef THROW
#define THROW2(napisA, napisB)                                                 \
    {                                                                          \
        printf("Exiting on exception%s.\n......\n", napisB);                   \
        throw napisA napisB;                                                   \
    }

#endif
