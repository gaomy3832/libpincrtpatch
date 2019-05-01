#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef SYS_getsockopt
int getsockopt(int sockfd, int level, int optname,
        void *optval, socklen_t *optlen) {
    return syscall(SYS_getsockopt, sockfd, level, optname, optval, optlen);
}
#endif  // SYS_getsockopt

#ifdef SYS_setsockopt
int setsockopt(int sockfd, int level, int optname,
        const void *optval, socklen_t optlen) {
    return syscall(SYS_setsockopt, sockfd, level, optname, optval, optlen);
}
#endif  // SYS_setsockopt

#ifdef SYS_recvfrom
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
#ifdef PIN_CRT
        const struct sockaddr *addr,  // PinCRT prototype
#else  // !PIN_CRT
        struct sockaddr *addr,  // glibc prototype
#endif  // PIN_CRT
        socklen_t *addrlen) {
    return syscall(SYS_recvfrom, sockfd, buf, len, flags, addr, addrlen);
}
#endif  // SYS_recvfrom

int getaddrinfo(const char *name, const char *service,
        const struct addrinfo *hints, struct addrinfo **pai) {
    // Not implemented.
    (void)name;
    (void)service;
    (void)hints;
    (void)pai;
    return EAI_SYSTEM;
}

// From glibc/sysdeps/posix/getaddrinfo.c
void freeaddrinfo(struct addrinfo *ai) {
    struct addrinfo *p;
    while (ai != NULL)
    {
        p = ai;
        ai = ai->ai_next;
        free (p->ai_canonname);
        free (p);
    }
}

