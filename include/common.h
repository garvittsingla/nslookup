#ifndef COMMON
#define COMMON

/**
 * struct to hold the resolvers
 * @param current_index the current index of the resolver
 * @param primary the primary resolver
 * @param secondary the secondary resolver
 * @param tertiary the tertiary resolver
 */

struct resolvers {
    int current_index;
    char *primary;
    char *secondary;
    char *tertiary;
};

#endif