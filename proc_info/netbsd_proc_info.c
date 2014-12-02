#include <fcntl.h>
#include <kvm.h>
#include <sys/sysctl.h>


#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc,char** args) {
	kvm_t* kd;

	// Get a handle to libkvm interface
	kd = kvm_open(NULL, NULL, NULL, KVM_NO_FILES, "error: ");

	pid_t pid;
	pid = getpid();

	struct kinfo_proc2 * kp;
	int p_count;

	// Get the kinfo_proc2 for this process by its pid
	kp = kvm_getproc2(kd, KERN_PROC_PID, pid, sizeof(struct kinfo_proc2), &p_count);

	printf("got %i kinfo_proc2 for pid %i\n", p_count, pid);


	// /usr/include/sys/sysctl.h details the kinfo_proc2 struct
	time_t proc_start_time;
	proc_start_time = kp->p_ustart_sec;
	kvm_close(kd);


	printf("sleeping for 15 seconds\n");
	sleep(15);
	printf("Process started at      %s\n", ctime(&proc_start_time));

	time_t current_time;
	current_time = time(NULL);
	printf("Current time after nap  %s\n", ctime(&current_time));

		


	return 0;
}


