#include <stdlib.h>

float strtof(const char* str, char** str_end) {
    double v = strtod(str, str_end);
    return (float)v;
}

/* Used for ld option --wrap. */
float __wrap_strtof(const char* str, char** str_end) {
    return strtof(str, str_end);
}

