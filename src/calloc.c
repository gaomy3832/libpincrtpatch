#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef NOINLINE
#if defined(__GNUC__)
#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE
#endif
#endif  // NOINLINE

// A hack to prevent the compiler from fusing malloc and memset back to calloc.
static void* NOINLINE _malloc_noinline(size_t size) {
    return malloc(size);
}

void* calloc(size_t num, size_t size) {
    size_t tot = num * size;
    void* p = _malloc_noinline(tot);
    memset(p, 0, tot);
    return p;
}

/* Used for ld option --wrap. */
void* __wrap_calloc(size_t num, size_t size) {
    return calloc(num, size);
}

