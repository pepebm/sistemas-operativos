#pragma once
#include <vector>
#include "GanttDiagram.h"
#include "PriorityQueue.h"
#include "Process.h"


class Priority{
private:
	//Priority queue que representa la ready queue
	PriorityQueue<Process*> readyQueue;
	//Vector con los procesos
	std::vector<Process*> processes;
	//Funcion que se usara para calcular el tiempo total de ejecucion
	float calculateTotalTime();
	
public:
	//Constructor
	Priority(std::vector<Process*>);
	//Funcion que simula el algoritma de Round Robin
	void simulate();
};

//Constructor
Priority::Priority(std::vector<Process*> ps) : processes(ps), readyQueue('P') {}

float Priority::calculateTotalTime(){
	float suma = 0;
	for(int i = 0; i < processes.size(); i++) suma += processes[i]->getLife();
	return suma;
}

void Priority::simulate(){
	//Variable para hacer el diagrama de Gantt
	GanttDiagram diagram;
	//Variables que usara ls simulacion
	float totalTime = calculateTotalTime();
	for(int i = 0; i < processes.size(); i++) processes[i]->setWaitTime(processes[i]->getLife());
	int idx = 0;
	float runTime = 0;
	float currentTime = 0;
	readyQueue.push(processes[0]);
	Process* current = readyQueue.pop()->getData();
	Process* next;
	std::string processName;
	//Ciclo donde se realiza la simulacion
	while(currentTime != totalTime){
		processName = current->getName();
		//En caso de que no hayan llegado todos los procesos
		if(idx + 1 != processes.size()){
			next = processes[idx + 1];
			//Checar si la vida del proceso actual es mayor o igual que el tiempo hasta la proxima interrupcion
			if(current->getLife() >= (runTime = next->getArrival() - currentTime)){
				//Actualizar variables
				currentTime += runTime;
				current->setLife(current->getLife() - runTime);

				//Comparar prioridades y ver que proceso se introduce al queue
				if(current->getPriority() < next->getPriority()) readyQueue.push(next);
				else{
					if(current->getLife() > 0) readyQueue.push(current);
					current = next;
				}
				idx++;
			}
			else{
				//Actualizar variables
				//Unproceso acabo
				currentTime += current->getLife();
				current->setLife(0);
				current->setWaitTime(currentTime - current->getArrival() - current->getWaitTime());
				current = readyQueue.pop()->getData();
			}
		}
		//En caso de que ya hayan llegado todos los procesos
		else{
			//Actualizar variables
			//En este punto solo se van sacando todos los procesos del ready queue hasta que este vacia
			currentTime += current->getLife();
			current->setLife(0);
			current->setWaitTime(currentTime - current->getArrival() - current->getWaitTime());
			if(!readyQueue.isEmpty()) current = readyQueue.pop()->getData();
			else break;
		}
		//Anadir bloque y queue al diagrama de Gantt
		diagram.addBlock(currentTime,processName);
		diagram.addQueue(currentTime,readyQueue.toVector());
	}
	processName = current->getName();
	diagram.addBlock(currentTime,processName);
	//Crea los diagramas correspondientes
	diagram.drawDiagram('P',processes);
}
