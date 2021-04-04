#pragma once
#include <iostream>
#include <iomanip>
#include "IIterator.h"

template<typename T>
struct Node
{
    T data;
    Node<T>* next = NULL;
    Node<T>* prev = NULL;
};

template<typename T>
class Queue : public IIterable<T>
{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    Queue() : head(NULL), tail(NULL), size(0) {}
    ~Queue() { this->Clear(); }
    Queue(const Queue<T>& obj);
    void Enqueue(T& data);
    T Dequeue();
    void Clear();
    int GetSize();
    bool Empty();
    T& Peek();
    T& operator[](int index);
    IIterator<T>* getIterator() override;
};


template<typename T>
inline void Queue<T>::Clear() {
    if (this->Empty()) {
        std::cout << " Пусто!" << std::endl;
        return;
    }

    while (this->size != 0) {
        Dequeue();
    }
}



template<typename T>
inline T& Queue<T>::operator[](int index) {
    Node<T>* curr = head;
    if (index >= size || index < 0)
        return curr->data;

    for (int i = 0; i < index; i++) {
        curr = curr->prev;
    }
    return curr->data;
}

template<typename T>
inline IIterator<T>* Queue<T>::getIterator()
{
    CustomIterator<T>* iterator = new CustomIterator<T>(this);
    return iterator;
}

template<typename T>
inline T& Queue<T>::Peek() {
    if (head != NULL)
        return head->data;
    else {
        return T();
    }
}

template<typename T>
inline bool Queue<T>::Empty() {
    return size == 0;
}

template<typename T>
inline int Queue<T>::GetSize() {
    return size;
}

template<typename T>
inline void Queue<T>::Enqueue(T& data)
{
    if (size == 0) {
        head = new Node<T>;
        head->prev = NULL;
        head->next = NULL;
        head->data = data;
        tail = head;
        size++;
        return;
    }
    Node<T>* temp = new Node<T>;
    temp->data = data;
    temp->next = tail;
    tail->prev = temp;
    tail = temp;
    size++;
}

template<typename T>
inline T Queue<T>::Dequeue()
{
    if (!(head))
        return T();

    T data = head->data;
    Node<T>* temp = head;
    head = head->prev;
    if (head)
        head->next = nullptr;
    delete temp;
    size--;
    return data;
}


template<typename T>
inline Queue<T>::Queue(const Queue<T>& obj) {
    this->size = obj.size;
    this->head = obj.head;
    this->tail = obj.tail;
}

