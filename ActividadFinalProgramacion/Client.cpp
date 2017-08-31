#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "RoundRobin.h"
#include "Priority.h"
#include "Process.h"
#include <fstream>

#define  DIRSIZE    1024   /* longitud maxima parametro entrada/salida */
#define  TAMABUFF   1024    //tamano del buffer

//Vector para guardar los procesos para el planificador Round Robin
std::vector<Process*> processesRR;

//Vector para guardar los procesos para el planificador Priority
std::vector<Process*> processesP;

//Variable que guarda el quantum que se usara en Round Robin
float quantum;

//Header de funcion que usara un proceso hijo
void* simulateRoundRobin(void*);

//Header de funcion que usara un proceso hijo
void* simulatePriority(void*);

//Header de funcion que lee el archivo de procesos
void readProcesses(std::string);

int main(int argc, char* argv[]){

  //Variables para el socket
  int puerto;
  int pid;
  int sd,i;      /* descriptores de sockets    */
  struct hostent *hp;      /* estructura del host        */
  struct sockaddr_in sin, pin;     /* direcciones socket        */
  int *status;        /* regreso llamada sistema */
  char *host;          /* nombre del host */

  //Procesos hijos
  pthread_t* threads  = new pthread_t[2];

  //Verificacion de argumentos
  if ( argc != 3) {
     fprintf(stderr,"Error uso: %s <host> <puerto> \n",argv[0]);
     exit(1);
  } 
  host = argv[1];
  puerto = atoi(argv[2]);
/* encontrando todo lo referente acerca de la maquina host */
  if ( (hp = gethostbyname(host)) == 0) {
    perror("gethosbyname");
    exit(1);
  }
/* llenar la estructura de direcciones con la informacion del host */
  pin.sin_family = AF_INET;
  pin.sin_addr.s_addr = ((struct in_addr *) (hp->h_addr))->s_addr;
  pin.sin_port = htons(puerto);
/* obtencion de un socket tipo internet */
  if ( (sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }
/* conectandose al PUERTO en el HOST  */
  if ( connect(sd, (struct sockaddr *)&pin, sizeof(pin)) == -1) {
    perror("connect");
    exit(1);
  }

  //Leer el archivo
  readProcesses("procesos2.txt");
  
  //Mostrar los procesos leidos en la terminal
  for(int i = 0; i < processesRR.size(); i++) std::cout << *processesRR[i] << std::endl;

  //Calcular el tiempo total de ejecucion
  float runningTime = 0;
  for(int i = 0; i < processesRR.size(); i++) runningTime += processesP[i]->getLife();

  //Creacion y ejecucion de procesos hijos
  pthread_create(&threads[0], NULL, simulatePriority, NULL);
  pthread_join(threads[0], NULL);
  pthread_create(&threads[1], NULL, simulateRoundRobin, NULL);
  pthread_join(threads[1], NULL);

  //Obtener tiempos de espera en ambos planificadores
  float waitingTimeRR = 0, waitingTimeP = 0;
  for(int i = 0; i < processesRR.size(); i++) waitingTimeRR += processesRR[i]->getWaitTime();
  for(int i = 0; i < processesP.size(); i++) waitingTimeP += processesP[i]->getWaitTime();

  // Guardar todo el texto que se enviara al socket en esta variable
  char totalTime[100];
  sprintf(totalTime,"Average waiting time Round Robin: %f\nAverage turnaround time Round Robin: %f\nAverage waiting time Priority: %f\nAverage turnaround time Priority: %f",
    (waitingTimeRR/processesRR.size()),((waitingTimeRR + runningTime)/processesRR.size()),
    (waitingTimeP/processesP.size()),((waitingTimeP + runningTime)/processesP.size())
    );

  while(1){
    //Enviar mensaje a socket
    if((pid = send(sd,totalTime,TAMABUFF,0)) == -1) exit(1);
    if(pid < TAMABUFF) break;
    close(sd);
    exit(0);
  }
}

//Cuerpo de funcion que usara un proceso hijo
void* simulateRoundRobin(void* parametros){
  //Creacion de instancia de la clase RoundRobin
  RoundRobin roundRobinScheduler(processesRR, quantum);
  //Llamada al metodo que simula el algoritmo de Round Robin
  roundRobinScheduler.simulate();
  pthread_exit(0);
}

//Cuerpo de funcion que usara un proceso hijo
void* simulatePriority(void* parametros){
  //Creacion de instancia de la clase Priority
  Priority priorityScheduler(processesP);
  //Llamada al metodo que simula el algoritmo de Priority
  priorityScheduler.simulate();
  pthread_exit(0);
}

//Cuerpo de funcion que lee el archivo de procesos
void readProcesses(std::string file){
  std::ifstream in;
  in.open(file);
  if(in.is_open()){
    std::string _name;
    float _arrival, _life;
    int _priority;
    in >> quantum;
    while(in >> _name >> _arrival >> _life >> _priority) {
      processesRR.push_back(new Process(_name, _arrival, _life, _priority));
      processesP.push_back(new Process(_name, _arrival, _life, _priority));
    }
    in.close();
  }
}
