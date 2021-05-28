#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>

#define MAXCHAR 1000

void sigusr1();

int main(void)
{

        /* Our process ID and Session ID */
        pid_t pid, sid;

        /* Fork off the parent process */
        pid = fork();
        if (pid < 0)
        {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0)
        {
                exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);

        /* Open any logs here */

        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0)
        {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }

        /* Change the current working directory */
        if ((chdir("/")) < 0)
        {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }

        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        /* Daemon-specific initialization goes here */
        const char *fname = "/home/presto/Pictures/ProcessoB/teste.x"; // aqui vc coloca a pasta que quer monitorar atrás do teste.x
        int flag = 0;
        FILE *fp;
        char str[MAXCHAR];
        char *filename = "/home/presto/Documents/Topicos/Tarefa_Signal_Fork/ProcessoA/build"; // Um arquivo em txt de onde é lido o pid do processo A


        /* The Big Loop */

        while (1)
        {

                

                fp = fopen(filename, "r");
                if (fp == NULL)
                {
                        printf("Could not open file %s", filename);
                        return 1;
                }
                fscanf(fp,"%s", str);
                fclose(fp);


                if (access(fname, F_OK) == 0)
                {

                        if (flag == 0)
                        {
                                kill(atoi(str), SIGUSR1);
                                flag = 1;
                        }
                }
                else if (access(fname, F_OK) != 0)
                {
                        flag = 0;
                }
        }

        exit(EXIT_SUCCESS);
}
