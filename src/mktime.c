#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* _tz_getenv(const char* name) {
    if (strcmp(name, "TZ") == 0) {
        // Use PIN_CRT_TZDATA as TZ to be consistent with other PinCRT routines.
        char* pin_crt_tzdata = getenv("PIN_CRT_TZDATA");
        if (!pin_crt_tzdata) {
            fprintf(stderr, "PIN_CRT_TZDATA not set!\n");
        }
        return pin_crt_tzdata;
    }
    return getenv(name);
}

#define getenv _tz_getenv
#include "tz/localtime.c"
#undef getenv

/* Used for ld option --wrap. */
time_t __wrap_mktime(struct tm* tmp) {
    return mktime(tmp);
}

