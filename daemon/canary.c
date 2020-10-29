/*
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 20 seconds and terminates afterwards.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include "canary.h"

#define DAEMON_NAME canary
#define DAEMON_NAME_STRING "canary"
#define RUN_PATH "/home/dnabre/work/canary"
#define MEG (1024 * 1024)
#define SIZE (1024 * 5)

 char* hunk = NULL;

int sleeping = TRUE;

int KEEP_RUNNING = 1;



void grab_hunk(long mb) {
//	hunk = mmap(0,sizeof(char)*  mb * MEG, PROT_NONE, MAP_ANONYMOUS | MAP_NOCORE |MAP_PRIVATE,0,0);
	hunk = mmap(NULL, mb * MEG, PROT_READ|PROT_WRITE, MAP_ANONYMOUS,-1,0);
	if(hunk == NULL) {

		syslog(LOG_ALERT, "canary HUNK error %s", strerror(errno));

		}


	syslog(LOG_ALERT,"touching alllocated hunk %lu", sizeof(hunk));
	
	char z = 0x01;

	for(long i=0; i < ((mb - 1) *MEG) ;i++) {
		hunk[i] = z;
		z++;
	}
	syslog(LOG_ALERT,"done touching\n");


}



char* get_time_string() {
	static char buffer[80];
	
	time_t rawtime;
	struct tm * timeinfo;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%b %d %H:%M:%S",timeinfo);

	return buffer;
}




static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
//    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
	chdir(RUN_PATH);
    /* Close all open file descriptors */
/*
	int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

 */

    /* Open the log file */
    openlog (DAEMON_NAME_STRING, LOG_PID, LOG_DAEMON);
}


static void sig_usr(int signo) {

	if(signo == SIGUSR1) {
		signal(SIGUSR1, &sig_usr);
		syslog(LOG_ALERT, "canary caugh signal %i", signo);
		sleeping = FALSE;
		system("/home/barrick/bin/mark.sh");

	} else {
		syslog(LOG_ALERT, "canary caught signal %i in else", signo);

	}
}



static void sig_kill(int signo) {
	if((signo!=SIGKILL) && (signo!=SIGTERM)) {
	return;
	}


	if(signo==SIGKILL) {
		signal(SIGKILL, &sig_kill);
		syslog(LOG_ALERT, "canary SWAK, SWAK, SWAK, I'm being killed (SIGKILL)");
	} else {
		signal(SIGTERM, &sig_kill);
		syslog(LOG_ALERT, "canary SWAK, SWAK, SWAK, I'm being killed (SIGTERM)");
	}	


	sleeping=FALSE;
	system("/home/barrick/bin/mark.sh");
	
	system("/home/barrick/bin/small_mark.sh");
	
	 


    syslog (LOG_ALERT, "canary terminated.");
    closelog();

   exit(EXIT_SUCCESS);
	





}


int main()
{
//    printf("%s \n", get_time_string());

	skeleton_daemon();
    syslog (LOG_ALERT, "canary started.");
    
	sleeping = FALSE;

	signal(SIGUSR1, &sig_usr);
	signal(SIGKILL, &sig_kill);
	signal(SIGTERM, &sig_kill);

	grab_hunk(SIZE);

	int n = 0;
	while (KEEP_RUNNING)
    {
    

	system("/home/barrick/bin/small_mark.sh");
	if(sleeping == FALSE) {
		system("/home/barrick/bin/mark.sh");
		sleeping=TRUE;
		syslog(LOG_ALERT, "canary MARK");
	}

	if(n>5) {
		sleeping = FALSE;
		n=0;
	} else { 
		n++;
	}


    	sleep (120);
    


    }

    syslog (LOG_ALERT, "canary terminated.");
    closelog();

    return EXIT_SUCCESS;
}
