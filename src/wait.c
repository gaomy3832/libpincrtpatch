#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef SYS_waitid
int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options) {
    return syscall(SYS_waitid, idtype, id, infop, options);
}
#endif  // SYS_waitid

