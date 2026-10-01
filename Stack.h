#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

//stack class implemented using a LinkedList as the underlying container
template<typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(const T& val) { list.push_front(val); }

    T pop() { return list.pop_front(); }

    T& top() { return list.front(); }
    const T& top() const { return list.front(); }

    bool isEmpty() const { return list.isEmpty(); }
    int size() const { return list.size(); }
};

#endif
