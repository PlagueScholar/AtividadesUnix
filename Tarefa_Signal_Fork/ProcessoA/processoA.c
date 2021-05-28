#include<stdio.h>
#include<unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void sigusr1();

int main(void)
{

 const char *fname = "./teste.x";
 
    FILE * fp;
    int i;
     /* open the file for writing*/
    
    signal(SIGUSR1, sigusr1);
    
    fp = fopen ("./pid.txt","w");
    fprintf (fp, "%ld",(long)getpid());
    fclose (fp);

    for(;;);
     

 
 

 return 0;
}

void sigusr1()
{
    signal(SIGUSR1, sigusr1);
    printf("ok \n");
}