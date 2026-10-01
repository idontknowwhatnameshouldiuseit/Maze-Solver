#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head; //head taill count
    Node* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}//create empty list

    //copy
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* cur = other.head;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this; //self check
        clear();//clear himself
        Node* cur = other.head;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    ~LinkedList() { clear(); }

    void push_front(const T& val) {
        Node* newNode = new Node(val, head);
        if (!head) tail = newNode;
        head = newNode;
        count++;
    }

    void push_back(const T& val) {
        Node* newNode = new Node(val, nullptr);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("pop_front on empty list");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return data;
    }

    T& front() {
        if (!head) throw std::runtime_error("front on empty list");
        return head->data;
    }

    const T& front() const {
        if (!head) throw std::runtime_error("front on empty list");
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }

    //removes all nodes from the linked list and frees their memory
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    template<typename Func>
    void forEach(Func f) const {
        Node* cur = head;
        while (cur) {
            f(cur->data);
            cur = cur->next;
        }
    }
};

#endif