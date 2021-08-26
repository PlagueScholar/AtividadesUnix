Acreditei de início que informações do computador como temperatura da cpu, tensão/corrente nos componenetes fossem algo mais simples de se conseguir. Mas após pesquisas descobri que é necessário conhecimento de registradores especificos do hardware de cada computador.
Por hora , inclui apenas leitura de memoria disponivel e uso de cpu. Estes podem ser facilmente adquiridos através de arquivos do próprio sistema ( no caso utilizei o Ubuntu 20.04)

O programa utiliza as bibliotecas:

<stdlib.h>
<string.h>
<unistd.h>
<stdio.h><sys/sysinfo.h>
<sys/stat.h>
<libnotify/notify.h> 

Esta ultima torna necessario compilar utilizando o comando: g++ mainfinal.c -o main  `pkg-config --cflags --libs libnotify` "limite de uso de cpu5" "limite de memoria disponivel" 

Esses limites são os parametros para que as notificações venham a ser geradas.
