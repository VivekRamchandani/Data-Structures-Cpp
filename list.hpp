#pragma once
#include <iostream>

template <typename T>
class Node {
public:
    using Node = Node<T>;
public:
    T data;

    Node(T val): data(val) {}
    // This copy constructor is quite important.
    Node(Node& node): data(node.data) {}

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
    List (List<T>& lst);    

    Node front() {
        if (head) {
            return *head;
        }
        throw nullptr;
    }
    Node back() {
        if (tail) {
            return *tail;
        }
        throw nullptr;
    }
    void len() {return length;}

    void append(T val);
    void push(T val);
    Node pop();
    Node remove(T val);
    int  index(T val);
    void insert(int idx, T val);
    void extend(List<T>& lst);
    void empty();
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t length = 0;

    Node& _nthNode(unsigned int idx) {
        Node* temp = head;
        for (int i = 0; i < idx; temp = temp->next, i++) {}
        return *temp;
    }
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
    temp->next = head;  // tail->next
    tail->next = temp;
    temp->prev = tail;
    head->prev = temp;
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
    temp->prev = tail;  // head->prev
    head->prev = temp;
    temp->next = head;
    tail->next = temp;
    head = temp;
    length += 1;
}
template <typename T>
void List<T>::extend(List<T>& lst) {
    if !(head) {
        head = lst.head;
        tail = lst.tail;
        length = lst.length        
        return;
    }
    lst.tail->next = head;
    tail->next = lst.head;
    lst.head->prev = tail;
    head->prev = lst.tail;
    length += lst.length;
}
template <typename T>
Node<T> List<T>::pop() {
    // Need to delete last node, so we can't use pointer to that node.
    Node temp = *tail;
    // Need to delete 'cause node is in heap memory
    delete tail;
    tail = temp.prev;
    tail->next = head;
    head->prev = tail;
    return temp;
}