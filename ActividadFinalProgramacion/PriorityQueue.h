#pragma once
#include <iostream>
#include <vector>
#include "Node.h"

template <class T>
class PriorityQueue{
private:
	Node<T>* head = nullptr;
	int length = 0;
	//Variable para identificar si el queue es para el algoritmo de round robin o para el de priority apropiativo
	char algorithm;
public:
	PriorityQueue(char);
	~PriorityQueue();
	bool isEmpty();
	void push(T);
	void pushRR(Node<T>*);
	void pushP(Node<T>*);
	Node<T>* top();
	Node<T>* pop();
	void clear();
	std::vector<T> toVector();
};

template <class T>
PriorityQueue<T>::PriorityQueue(char a) : algorithm(a) {}

template <class T>
PriorityQueue<T>::~PriorityQueue(){
	clear();
}

template <class T>
bool PriorityQueue<T>::isEmpty(){
	return (head==nullptr);
}

template <class T>
void PriorityQueue<T>::push(T _data){
	if(algorithm == 'R') pushRR(new Node<T>(_data));
	else pushP(new Node<T>(_data));
}

template <class T>
void PriorityQueue<T>::pushRR(Node<T>* node){
	if(head == nullptr) head = node;
	else {
		Node<T>* element = head;
		while(element->getNext() != nullptr) element = element->getNext();
		element->setNext(node);
	}
	length++;
}

template <class T>
void PriorityQueue<T>::pushP(Node<T>* node){
	if(head == nullptr) head = node;
	else if(head->getNext() == nullptr){
		if(*node->getData() > *head->getData()){
			Node<T>* element = head;
			head = node;
			head->setNext(element);
		}
		else head->setNext(node);
	}
	else{
		if(*node->getData() > *head->getData()){
			Node<T>* element = head;
			head = node;
			head->setNext(element);
			return;
		}
		Node<T>* last = head;
		Node<T>* element = head->getNext();
		while(element != nullptr){
			if(*node->getData() > *element->getData()){
				last->setNext(node);
				node->setNext(element);
				return;
			}
			last = element;
			element = element->getNext();
		}
		last->setNext(node);
	}
	length++;
}

template <class T>
Node<T>* PriorityQueue<T>::top(){
	return head;
}

template <class T>
Node<T>* PriorityQueue<T>::pop(){
	if(head == nullptr) return nullptr;
	Node<T>* node = head;
	head = head->getNext();
	node->setNext(nullptr);
	length--;
	return node;
}

template <class T>
void PriorityQueue<T>::clear(){
	Node<T>* element = head;
	while(element){
		head = element->getNext();
		delete element;
		element = head;
	}
	length = 0;
}

template <class T>
std::vector<T> PriorityQueue<T>::toVector(){
	std::vector<Process*> vec;
	Node<T>* element = head;
	while(element != nullptr){
		vec.push_back(element->getData());
		element = element->getNext();
	}
	return vec;
}