#include <fcntl.h>
#include <kvm.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/user.h>


#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc,char** args) {
	kvm_t* kd;

	// Get a handle to libkvm interface
	kd = kvm_open(NULL, "/dev/null", NULL, O_RDONLY, "error: ");

	pid_t pid;
	pid = getpid();

	struct kinfo_proc * kp;
	int p_count;

	// Get the kinfo_proc for this process by its pid
	kp = kvm_getprocs(kd, KERN_PROC_PID, pid, &p_count);

	printf("got %i kinfo_proc for pid %i\n", p_count, pid);

	// /usr/include/sys/user.h details the kinfo_proc struct
	time_t proc_start_time;
	proc_start_time = kp->ki_start.tv_sec;
	kvm_close(kd);

	printf("sleeping for 15 seconds\n");
	sleep(15);

	time_t current_time;
	current_time = time(NULL);
	printf("Process started at      %s\n", ctime(&proc_start_time));
	printf("Current time after nap  %s\n", ctime(&current_time));


	return 0;
}


