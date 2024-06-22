#ifndef UTILS_H
#define UTILS_H

// Reinterpret cast implementation.
// ONLY USE FOR TRIVIAL TYPES!
#define reinterpret_cast(TO, VAR) \
({                                \
    union                         \
    {                             \
        __typeof__((VAR)) source; \
        TO dest;                  \
    } u = { .source = (VAR) };    \
    (TO)u.dest;                   \
})

#endif //UTILS_H
