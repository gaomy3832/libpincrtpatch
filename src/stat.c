#include <sys/stat.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef SYS_stat
int stat(const char* pathname, struct stat* statbuf) {
    return syscall(SYS_stat, pathname, statbuf);
}
#endif  // SYS_stat

#ifdef SYS_fstat
int fstat(int fd, struct stat* statbuf) {
    return syscall(SYS_fstat, fd, statbuf);
}
#endif  // SYS_fstat

#ifdef SYS_lstat
int lstat(const char* pathname, struct stat* statbuf) {
    return syscall(SYS_lstat, pathname, statbuf);
}
#endif  // SYS_lstat

#ifdef SYS_stat64
int stat64(const char* pathname, struct stat* statbuf) {
    return syscall(SYS_stat64, pathname, statbuf);
}
#endif  // SYS_stat64

#ifdef SYS_fstat64
int fstat64(int fd, struct stat* statbuf) {
    return syscall(SYS_fstat64, fd, statbuf);
}
#endif  // SYS_fstat64

#ifdef SYS_lstat64
int lstat64(const char* pathname, struct stat* statbuf) {
    return syscall(SYS_lstat64, pathname, statbuf);
}
#endif  // SYS_lstat64

