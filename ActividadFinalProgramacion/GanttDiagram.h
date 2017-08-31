#pragma once
#include <iostream>
#include "Process.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>

class GanttDiagram{
private:
	//Mapa que guarda la informacion de la ready queue en varios tiempo
	std::map<float, std::vector<Process*> > queues;
	//Mapa que guarda los bloques que se desean dibujar de GanttDiagram
	std::map<float, std::string> blocks;
public:
	//Constructor
	GanttDiagram();
	//Funcion para anadir un bloque
	void addBlock(float, std::string);
	//Funcion para anadir un queue
	void addQueue(float, std::vector<Process*>);
	//Funcion para escribir el archivo con los diagramas
	void drawDiagram(char, std::vector<Process*>);
};

GanttDiagram::GanttDiagram(){}

void GanttDiagram::addBlock(float time, std::string name){
	blocks[time] = name;
}

void GanttDiagram::addQueue(float time, std::vector<Process*> queue){
	queues[time] = queue;
}

void GanttDiagram::drawDiagram(char a, std::vector<Process*> processes){
	//Variable para escribir un archivo
	std::ofstream out;
	if(a == 'R'){
		//En caso de que sea el Gantt diagram de Round Robin
		out.open("GanttDiagramRoundRobin.txt");
		out << "\n\t\tR O U N D   R O B I N\n";
	}
	else{
		//En caso de que sea el Gantt diagram de Priority
		out.open("GanttDiagramPriority.txt");
		out << "\n\t\tP R I O R I T Y\n";
	}

	//"Dibujar" los bloques en el archivo 
	out << "\nGANTT DIAGRAM:\n";
	for(int i = 0; i < blocks.size(); i++) out << "------------";
	out << "\n";
	for(std::map<float,std::string>::iterator it = blocks.begin(); it != blocks.end(); it++) out << "| " << it->second << " |";
	out << "\n";
	for(int i = 0; i < blocks.size(); i++) out << "------------";
	out << "\n0";
	for(std::map<float,std::string>::iterator it = blocks.begin(); it != blocks.end(); it++) out << std::setw(12) << it->first;
	std::map<float, std::vector<Process*> >::iterator it = queues.begin();
	std::string name;
	std::vector<Process*> current;
	//"Dibujar" los queues en el archivo
	out << "\n\nREADY QUEUES:\n";
	out << "0:\n\n->\n\n";
	while(it != queues.end()){
		current = it->second;
		out << it->first << ":\n  ";
		for(int i = 0; i < current.size(); i++) out << "----";
		out << "\n->";
		for(int i = current.size()-1; i >= 0; i--){
			name = current[i]->getName();
			name.erase(name.begin()+1,name.end()-1);
			out << "|" << name << "|";
			if(i == 0) out << "->";
		}
		out << "\n";
		for(int i = 0; i < current.size(); i++){
			if(i == 0) out << "  ----";
			else out << "----";
		}
		out << "\n\n";
		it++;
	}

	//Escribir los tiempos de espera de cada proceso
	out << "WAITING TIMES:\n";
	for(int i = 0; i < processes.size(); i++) out << "Waiting time of " << processes[i]->getName() << ": " << processes[i]->getWaitTime() << std::endl;
	out << "\n";
	out.close();
}