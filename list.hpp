#pragma once
#include <iostream>

using std::ostream;

template <typename T>
class List;
template <typename T>
ostream& operator<<(ostream &stream, const List<T> &list);

template <typename T>
class Node {
public:
    using Node = Node<T>;
public:
    T data;

    Node(T val): data(val) {}
    // This copy constructor is quite important.
    Node(Node& node): data(node.data) {}

    // Relational Operators
    bool operator==(const Node& node) {
        return data == node.data;
    }
    bool operator<=(const Node& node) {
        return data <= node.data;
    }
    bool operator>=(const Node& node) {
        return data >= node.data;
    }
    bool operator<(const Node& node) {
        return data < node.data
    }
    bool operator>(const Node& node) {
        return data > node.data
    }
    bool operator!=(const Node& node) {
        return !(data == node.data)
    }

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
    List (const List<T>& lst);
    ~List();

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
    void remove(T val);
    int  index(T val);
    void insert(int idx, T val);
    void extend(List<T>& lst);
    void empty();
    bool isEmpty() {
        if (head == nullptr) { return true; }
        return false;
    }

    Node& operator[](size_t idx);
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t length = 0;

    Node* _nthNode(unsigned int idx) {
        Node* temp = head;
        for (int i = 0; i < idx; temp = temp->next, i++) {}
        return temp;
    }

    friend ostream& operator<< <T>(ostream &stream, const List<T> &list);
};

// Constructors
template <typename T>
List<T>::List(const List<T>& list) {
    // Creating head and tial
    head = new Node(list.head);
    tail = head;
    Node *temp = list.head->next;

    for (int i = 1; i < list.length; i++, temp = temp->next) {
        Node* copy = new Node(temp);
        tail->next = copy;
        copy->prev = tail;
        tail = copy;
    }
    tail->next = head;
    head->prev = tail;
    length = list.length;
} 

// Destructor
template <typename T>
List<T>::~List() {
    head->prev = nullptr;
    tail->next = nullptr;
    Node* nextNode = head;
    for (int i = 0; i < length; i++, head = nextNode) {
        nextNode = head->next;
        delete head;
    }
}

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
    length -= 1;
    return temp;
}
template <typename T>
void List<T>::remove(T val) {
    Node* temp = head;
    int i = 0;
    for (; i < length || temp->data != val; temp = temp->next, i++) {}
    if (i == length) { return; }
    Node* preNode = temp->prev;
    Node* nextNode = temp->next;
    preNode->next = nextNode;
    nextNode->prev = preNode;
    delete temp;
}
template <typename T>
int List<T>::index(T val) {
    Node* temp = head;
    int idx = 0;
    for (; idx < length || temp->data != val; temp - temp->next, idx++) {}
    if (idx == length) {throw "Value not found."}
    return idx;
}
template <typename T>
void List<T>::insert(int idx, T val) {
    size_t calc_idx = (idx < 0) ? length + idx : idx;
    if (calc_idx < 0) {
        throw std::out_of_range("Can't access out of range index.");
    }
    Node* temp = new Node(val);
    Node* nextNode = _nthNode(calc_idx);
    Node* prevNode = nextNode->prev;
    temp->next = nextNode;
    nextNode->prev = temp;
    temp->prev = prevNode;
    prevNode->next = temp;
}
template <typename T>
void List<T>::empty() {
    head->prev = nullptr;
    tail->next = nullptr;
    tail = nullptr;
    Node* temp = head->next;
    for (int i = 0; i < length; head = temp, i++) {
        temp = temp->next;
        delete head;
    }
}

// Subscript Operator Overload
template <typename T>
Node<T>& List<T>::operator[](size_t idx) {
    size_t calc_idx = (idx < 0) ? length + idx : idx;
    if (calc_idx < 0) {
        throw std::out_of_range("Can't access out of range index.");
    }
    return *_nthNode(calc_idx)
}

// Inserter Operator Overload
template <typename T>
ostream& operator<< (ostream& stream, const List<T> &list) {
    Node<T>* temp = list.head;
    stream << "[ ";
    for (int i = 0; i < list.length; i++, temp = temp.next)
        stream << temp->data << " ";
    stream << std::endl;
    return stream;
}