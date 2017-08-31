#pragma once

//Clase para los Procesos
class Process{
private:
	std::string name;
    float arrival;
    float life;
    int priority;
    float waitTime;
public:
    Process(){}
    Process(std::string, float, float, int);
    std::string getName();
    float getArrival();
    int getPriority();
    float getLife();
    void setLife(float);
    float getWaitTime();
    void setWaitTime(float);
    //Sobrecarga de operadores mayor que y menor que
    bool operator< (const Process& other);
    bool operator> (const Process& other);

    //Sobrecarga del operador << para imprimir un proceso
    friend std::ostream& operator<< (std::ostream& stream, const Process& other);
};

Process::Process(std::string n, float a, float l, int p) : name(n), arrival(a), life(l), priority(p), waitTime(0) {}

std::string Process::getName(){
    return name;
}

float Process::getArrival(){
    return arrival;
}

int Process::getPriority(){
    return priority;
}

float Process::getLife(){
    return life;
}

void Process::setLife(float l){
    life = l;
}

float Process::getWaitTime(){
    return waitTime;
}

void Process::setWaitTime(float wt){
    waitTime = wt;
}

bool Process::operator< (const Process& other){
    if(priority > other.priority) return true;
    else return false;
}

bool Process::operator> (const Process& other){
    if(priority < other.priority) return true;
    else return false;
}

std::ostream& operator<< (std::ostream& stream, const Process& other){
    stream << other.name << std::endl;
    stream << "Arrival time: " << other.arrival << std::endl;
    stream << "Process lifetime: " << other.life << std::endl;
    stream << "Priority: " << other.priority << std::endl;
    return stream;
}