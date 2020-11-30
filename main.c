#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\nSIGINT received\nExiting...\n\n");
        int out = open("sig.out", O_CREAT | O_WRONLY, 0644); 
        if (out == -1) 
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }

        char message[21] = "Exited due to SIGINT\n";
        lseek(out, 0, SEEK_END);
        int k = write(out, message, sizeof(message));

        if (k == -1)
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }
        close(out);
        exit(0);

    }
    if (signo == SIGUSR1)
    {
        printf("\nSIGUSR1 received\nParent PID: %d\n\n", getppid());
    } 
}

int main() 
{
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while(1)
    {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
}