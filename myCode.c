#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

        void sigint_handler(int sig)
        {
        printf("\nYou're have been Interrupt To Give A Number\n");
        }

int main(void)
{
  //signal
  struct sigaction sa;
  sa.sa_handler = &sigint_handler;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa, NULL);

  //pipe
  int pipeFileDescriptor[2];

  if(pipe(pipeFileDescriptor) == -1)
  {
        perror("pipe");
        exit(EXIT_FAILURE);
  }

	//fork
     pid_t pid = fork();

        if(pid == 0)    {
                //child process
                close(pipeFileDescriptor[1]);
                int y;
                read(pipeFileDescriptor[0], &y, sizeof(int));
                close(pipeFileDescriptor[0]);
                printf("\n Result from Parent Process: %d\n", y);
                printf("Child process => PPID=%d, PID=%d\n", getppid(), getpid());
        }
        else if(pid > 0)
        {
                //parent process
                close(pipeFileDescriptor[0]);
                int x;
                printf("Parent process => PID=%d\n", getpid());
                printf("Enter a number: ");
                scanf("%d", &x);
                write(pipeFileDescriptor[1], &x, sizeof(int));
                close(pipeFileDescriptor[1]);
        }
        else {

        printf("Job is done.\n");
        }
return EXIT_SUCCESS;
}
