#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <libnotify/notify.h> // Compilar com utilizando o comando: g++ mainfinal.c -o main  `pkg-config --cflags --libs libnotify`

long int sum = 0, idle, lastSum = 0, lastIdle = 0;




// Calculo do uso de CPU 
double cpucalc()
{

    char str[100];
    const char d[2] = " ";
    char *token;
    int i, times, lag;

    double idleFraction;

    FILE *fp = fopen("/proc/stat", "r");
    i = 0;
    fgets(str, 100, fp);
    fclose(fp);
    token = strtok(str, d);
    sum = 0;
    while (token != NULL)
    {
        token = strtok(NULL, d);
        if (token != NULL)
        {
            sum += atoi(token);

            if (i == 3)
                idle = atoi(token);

            i++;
        }
    }
    idleFraction = 100 - (idle - lastIdle) * 100.0 / (sum - lastSum);
    lastIdle = idle;
    lastSum = sum;
    

    return idleFraction;
}

// Leitura de Memoria disponivel , diretamente do arquivo meminfo do sistema.
long getmem()
{

    long mem_d;
    char name1[20];

    static const char filename[] = "/proc/meminfo";
    FILE *file = fopen(filename, "r");
    int count = 0;
    if (file != NULL)
    {
        char line[256];

        fgets(line, sizeof(line), file);
        fgets(line, sizeof(line), file);
        fgets(line, sizeof(line), file);
        sscanf(line, "%s %lu", name1, &mem_d);

        fclose(file);
    }
    else
    {
        //arquivo não existe
    }

    printf("%lu MB\n", mem_d / 1024);
    return mem_d / 1024;
}

int main(int argC, char *argV[])
{
    /* ID do processso e ID da sessão */
    pid_t pid, sid;

    /* Forka o processo pai */
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    /* Se temos um bom pid , então prosseguimos  */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    /* Troca o mask do file mod */
    umask(0);

    /* Cria um novo SID para o processo filho */
    sid = setsid();
    if (sid < 0)
    {
        /* Loga a falha caso ocorra */
        exit(EXIT_FAILURE);
    }

    /* Troca o diretório de trabalho */
    if ((chdir("/")) < 0)
    {
        /* Loga a falha caso ocorra */
        exit(EXIT_FAILURE);
    }

    /*Fecha os file descriptors padrões*/
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);


    /* ******* Inicialização do DAEMON ******* */
    long mem;
    double cpu;
    notify_init("Sample");

    int cpuLim = atoi(argV[1]);
    int memLim = atoi(argV[2]);

    while (1)
    {
        // código fonte do daemon
        mem = getmem();
        cpu = cpucalc();

        if (cpu > cpuLim)
        {
            NotifyNotification *nCPU = notify_notification_new("ALERTA",
                                                               "Alto uso de CPU",
                                                               0);
            notify_notification_set_timeout(nCPU, 10000); // 10 segundos
            if (!notify_notification_show(nCPU, 0))
            {
                return -1;
            }
        }

        if (mem > memLim)
        {
            NotifyNotification *nMEM = notify_notification_new("ALERTA",
                                                               "Alto uso RAM",
                                                               0);
            notify_notification_set_timeout(nMEM, 10000); // 10 segundos
            if (!notify_notification_show(nMEM, 0))
            {
                return -1;
            }
        }

        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
