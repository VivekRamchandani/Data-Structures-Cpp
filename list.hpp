#pragma once
#include <iostream>

template <typename T>
class Node {
public:
    using Node = Node<T>;
public:
    T data;

    Node(T val): data(val) {}

    friend class List;
private:
    Node *next = nullptr;
    Node *prev = nullptr;
};

template <typename T>
class List {
public:
    using Node = Node<T>;
public:
    List() {}
    List (T val) {
        head = new Node(val);
        head->next = head;
        head->prev = head;
        tail = head;
        length = 1;
    }
    List (List<T>& lst) 
        :head(lst.head), tail(lst.tail), len(lst.len) {}
    

    Node& front() {
        if (head) {
            return *head;
        }
        throw nullptr;
    }
    Node& back() {
        if (tail) {
            return *tail;
        }
        throw nullptr;
    }
    void len() {return length;}

    void append(T val);
    void push(T val);
    void pop();
    void remove(T val);
    void index(T val);
    void insert(int idx, T val);
    void extend(const List<T>& lst);
    void empty();
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t length = 0;
};

// Methods
template <typename T>
void List<T>::append(T val) {
    Node* temp = new Node(val);
    if !(tail) {
        head = temp;
        head->next = head;
        head->prev = head;
        tail = head;
        length = 1; 
        return;
    }
    temp->next = tail->next;
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
    length += 1;
}
template <typename T>
void List<T>::push(T val) {
    Node* temp = new Node(val);
    if !(head) {
        head = temp;
        head->next = head;
        head->prev = head;
        tail = head;
        length = 1; 
        return;
    }
    temp->prev = head->prev;
    head->prev = temp;
    temp->next = head;
    head = temp;
}