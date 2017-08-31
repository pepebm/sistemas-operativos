#pragma once
#include <vector>
#include "GanttDiagram.h"
#include "PriorityQueue.h"
#include "Process.h"

class RoundRobin{
private:
	//Priority queue que representa la ready queue
	PriorityQueue<Process*> readyQueue;

	//Vector con los procesos
	std::vector<Process*> processes;

	//Funcion que se usara para calcular el tiempo total de ejecucion
	float calculateTotalTime();

	//Variable para guardar el quantum
	float quantum; 
public:
	//Constructor
	RoundRobin(std::vector<Process*>, float);

	//Funcion que simula el algoritma de Round Robin
	void simulate();
};

// Constructor
RoundRobin::RoundRobin(std::vector<Process*> ps, float q) : processes(ps), quantum(q), readyQueue('R') {}

float RoundRobin::calculateTotalTime(){
	float suma = 0;
	for(int i = 0; i < processes.size(); i++) suma += processes[i]->getLife();
	return suma;
}

void RoundRobin::simulate(){
	//Variable para hacer el diagrama de Gantt
	GanttDiagram diagram;
	//Variables que usara ls simulacion
	float totalTime = calculateTotalTime();
	for(int i = 0; i < processes.size(); i++) processes[i]->setWaitTime(processes[i]->getLife());
	int idx = 1;
	float currentTime = 0;
	readyQueue.push(processes[0]);
	Process* current = readyQueue.pop()->getData();
	std::string processName;
	//Ciclo donde se realiza la simulacion
	while(currentTime != totalTime){
		processName = current->getName();
		//En caso de que no hayan llegado todos los procesos
		if(idx != processes.size()){
			//Validacion del proceso actual, si la vida de dicho proceso es mayor al quantum
			if(current->getLife() > quantum){
				//Actualizar variables
				currentTime += quantum;
				current->setLife(current->getLife() - quantum);
				//Checar si llego otro proceso
				for(int i = idx; i < processes.size(); i++){
					if(processes[i]->getArrival() <= currentTime){
						readyQueue.push(processes[i]);
						idx++;
					}
				}
				//Introducir proceso actual al queue
				readyQueue.push(current);
			}
			else{
				//Actualizar variables
				currentTime += current->getLife();
				current->setLife(0);
				current->setWaitTime(currentTime - current->getArrival() - current->getWaitTime());
				//Checar si llego otro proceso
				for(int i = idx; i < processes.size(); i++){
					if(processes[i]->getArrival() <= currentTime){
						readyQueue.push(processes[i]);
						idx++;
					}
				}
			}
		}
		//En caso de que ya hayan llegado todos los procesos
		else{
			//Validacion del proceso actual, si la vida de dicho proceso es mayor al quantum
			if(current->getLife() > quantum){
				//Actualizar variables
				currentTime += quantum;
				current->setLife(current->getLife() - quantum);
				readyQueue.push(current);
			}
			else{
				//Actualizar variables
				currentTime += current->getLife();
				current->setLife(0);
				current->setWaitTime(currentTime - current->getArrival() - current->getWaitTime());
			}
		}

		//Proceso actual se iguala al que sigue en el queue si la queue no esta vacia
		if(!readyQueue.isEmpty()) current = readyQueue.pop()->getData();
		else{
			//Si la queue esta vacia y el proceso actual ya termino se sale del while
			if(current->getLife() == 0) break;
		}

		//Anadir bloque y queue al diagrama de Gantt
		diagram.addBlock(currentTime,processName);
		diagram.addQueue(currentTime, readyQueue.toVector());
	}
	processName = current->getName();
	diagram.addBlock(currentTime,processName);

	//Crea los diagramas correspondientes
	diagram.drawDiagram('R',processes);
}