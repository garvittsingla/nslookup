#ifndef COMMON
#define COMMON

struct resolvers {
    int current_index;
    char *primary;
    char *secondary;
    char *tertiary;
};

#endif