#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <string.h>

#define CHILD_STACK_SIZE 1024 * 1024
static char child_stack[CHILD_STACK_SIZE];

int child_func(void *args)
{
    const char *new_hostname = (char *)args;
    struct utsname uts;

    // change host info
    printf("child : setting new hostname (%s)\n", new_hostname);
    sethostname(new_hostname, strlen(new_hostname));

    // get (new) host information
    if (uname(&uts) == -1) {
        fprintf(stderr, "child : Could not get uname info\n");
        exit(errno);
    }
    printf("child : hostname=%s\n", uts.nodename);

    sleep(10);
    return 0;
}

int main(int argc, char *argv[])
{
    int child;
    char *temp_new_hostname;
    struct utsname uts;

    if (argc > 1) {
        temp_new_hostname = argv[1];
    } else {
        temp_new_hostname = "new-hostname";
    }

    printf("Program to demonstrate different hostnames in different processes\n");

    printf("parent: Cloning\n");
    child = clone(child_func, child_stack + CHILD_STACK_SIZE,
            CLONE_NEWUTS | SIGCHLD, temp_new_hostname);

    if (child == -1) {
        fprintf(stderr, "parent: Could not create child process\n");
        fprintf(stderr, "parent: Could be caused by not enough permissions (run with sudo)\n");
        exit(errno);
    }

    // allow child some time to change hostname
    sleep(1);

    // get host information
    if (uname(&uts) == -1) {
        fprintf(stderr, "parent: Could not get uname info\n");
        exit(errno);
    }
    printf("parent: hostname=%s\n", uts.nodename);

    sleep(10);
    return 0;
}
