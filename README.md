libpincrtpatch: Patch to PinCRT
===============================

PinCRT provides its own libc called `libc-dynamic.so`, and pin tools must link
with it. However PinCRT's `libc-dynamic.so` misses some references. In
addition, its implementations of some functions are buggy. This library
patches the implementations for these missing or buggy references.


Supplied missing references
---
- `stat`, `fstat`, `lstat`, `stat64`, `fstat64`, `lstat64`
- `creat`, `creat64`
- `getsockopt`, `setsockopt`, `recvfrom`, `getaddrinfo` (not implemented),
  `freeaddrinfo`
- `waitid`


Fixed buggy references
---
- `calloc` (v3.13 - ): Infinite recursive calls.
- `mktime` (v3.13 - ): Overflow bug in an old version of tz. See
  [ICANN mailing list](https://mm.icann.org/pipermail/tz/2015-March/022074.html) and
  [Github](https://github.com/eggert/tz/commit/4c8309661d861d838e42b2277e0d43b16d62e061)
- `strtof` (v3.13 - ): A value with fractional part equal to 1/2^n (e.g., 3.5,
  4.125) is converted to `inf`. This also affects `scanf`, etc..

