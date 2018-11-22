#ifndef STACK_H
#define STACK_H
#include <iostream>

template<class T>
class stack
{
private:
    T element;    // Элемент стэка
    stack * Next; // Указатель на следующий элемент стэка(Следующий, если сверху-вниз)
    stack * Head; // Указатель на вершину стэка
public:
    stack();
    /*
     * Конструктор копирования
     */
    stack(stack const& stk);

    /*
     * Реализация оператора присваивания
     */
    stack & operator =(stack const& stk) {
        if (this != &stk) {
            stack temp(stk); // Создаем временный объект и копируем туда стэк, переданный после оператора присваивания
            temp.swap(*this);// Меняем местами текущий стэк и копию
        }
        return *this; // Возвращаем указатель на текущий объект стэка, в котором уже лежат данные из скопированного
    }

    ~stack();
    void push(const float & val);
    T pop();
    bool isEmpty();
    T & top();
    void clear();
    void show();
    void swap(stack &stk);
};

//====================================================================================
//====================================================================================
//====================================================================================

template<class T>
stack<T>::stack() : element(0),
    Next(0),
    Head(0)
{}

//Конструктор копирования
template<class T>
stack<T>::stack(const stack &stk) : element(stk.element),
    Next(stk.Next),
    Head(stk.Head) {}

// Реализация метода обмена стэками
template<class T>
void stack<T>::swap(stack &stk) {
    T temp = element;
    element = stk.element;
    stk.element = temp;

    stack * temp1 = this->Head;
    Head = stk.Head;
    stk.Head = temp1;

    stack * temp2 = this->Next;
    Next = stk.Next;
    stk.Next = temp2;
}

template<class T>
stack<T>::~stack() {
    while (this->Head) {
        stack * temp = Head;
        Head = Head->Next;
        delete temp;
    }
}

template<class T>
void stack<T>::push(const float &val) {
    stack* temp = new stack;
    temp->element = val;
    temp->Next = this->Head;
    this->Head = temp;
}

template<class T>
void stack<T>::clear() {
    while (this->Head != 0) {
        stack * temp = this->Head->Next;
        delete this->Head;
        this->Head = temp;
    }
}

template<class T>
void stack<T>::show() {
    stack * temp = this->Head;
    while (temp != 0) {
       std::cout << temp->element << std::endl;
       temp = temp->Next;
    }
}

template<class T>
bool stack<T>::isEmpty() {
    return this->Head ? false : true;
}

template<class T>
T stack<T>::pop() {
   if (this->isEmpty()) {
       return -1;
   }
   T temp = Head->element;
   stack * pv = Head;
   Head = Head->Next;
   delete pv;
   return temp;
}

template<class T>
T & stack<T>::top() {
    return this->Head->element;
}

#endif // STACK_H
