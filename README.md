# AtividadesUnix


- Tarefa Signal - Fork :
-   No caso , acabei me confundindo e criei o B como o daemon e o A como o processo normal em foreground.
-   Como eu não sabia como pegar um pid de um processo normal aleatorio a partir de outro processo ( neste caso daemon) em que não há relação de parentesco,
-   resolvi guardar o pid do processo A em um txt, e no processo B (daemon) ler ele para pode enviar o sinal SIGUSR1.
