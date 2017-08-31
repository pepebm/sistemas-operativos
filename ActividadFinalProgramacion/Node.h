#pragma once

template <class T>
class Node{
private:
    T data;
    Node<T>* next;
public:
    Node();
    Node(T _data);
    ~Node();
    void setData(T _data);
    T getData();
    void setNext(Node<T>* _next);
    Node<T>* getNext();
};

template <class T>
Node<T>::Node() : next(nullptr) {}

template <class T>
Node<T>::Node(T _data):data(_data), next(nullptr) {}

template <class T>
Node<T>::~Node(){ 
	next = nullptr; 
}

template <class T>
void Node<T>::setData(T _data){ 
	data = _data; 
}

template <class T>
T Node<T>::getData(){ 
	return data; 
}

template <class T>
void Node<T>::setNext(Node<T>* _next){ 
	next = _next; 
}

template <class T>
Node<T>* Node<T>::getNext(){ 
	return next; 
}