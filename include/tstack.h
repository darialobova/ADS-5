// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T mass[100];
    int top;
 public:
    TStack():top(-1) { }
    T get() const {
      return mass[top];
    }
    bool isEmpty() const {
      return top == -1;
    }
    bool isFull() const {
      return top == size - 1;
    }
    void pop() {
      if (top >= 0)
        top--;
    }
    void push(T item) {
      if (top < size - 1)
        mass[++top] = item;
    }
};
#endif  // INCLUDE_TSTACK_H_
