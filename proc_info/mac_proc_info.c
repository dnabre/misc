#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <err.h>
#include <unistd.h>

static void
getstarttime(struct timeval *ptv)
{
    static time_t   start; /* We cache this value */
    int             mib[4];
    size_t          len;
    struct kinfo_proc   kp;

    ptv->tv_usec = 0;   /* Not using microseconds at all */

    if (start != 0) {
        ptv->tv_sec = start;
        return;
    }
    ptv->tv_sec = 0;

    len = 4;
    if (sysctlnametomib("kern.proc.pid", mib, &len) != 0) {
        warn("Unable to obtain script start-time: %s",
            "sysctlnametomib");
        return;
    }
    mib[3] = getpid();
    len = sizeof(kp);
    if (sysctl(mib, 4, &kp, &len, NULL, 0) != 0) {
        warn("Unable to obtain script start-time: %s",
            "sysctl");
        return;
    }

//    start = ptv->tv_sec = kp.ki_start.tv_sec;
      start = kp.kp_proc.p_un.__p_starttime.tv_sec;

        printf("sleeping for 15 seconds\n");
        sleep(15);

        time_t current_time;
        current_time = time(NULL);
        printf("Process started at      %s\n", ctime(&start));
        printf("Current time after nap  %s\n", ctime(&current_time));

	

}

int main() 
{
	struct timeval tv;
	getstarttime(&tv);
	return 0;

}
