#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef SYS_creat
int creat(const char* pathname, mode_t mode) {
    return open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
#endif  // SYS_creat

#ifdef SYS_creat64
int creat64(const char* pathname, mode_t mode) {
    return open64(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
#endif  // SYS_creat64

