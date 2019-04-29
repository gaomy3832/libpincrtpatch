libpin3c_nonshared: Non-shared libc linked with PinCRT
======================================================

PinCRT provides its own libc called `libc-dynamic.so`, and pin tools must link
with it. However PinCRT's `libc-dynamic.so` misses some references, such as
`stat`, `creat`, etc. This library provides the implementations for these
missing references, through wrappers of syscalls.
