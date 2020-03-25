#ifndef SEMS_DYNARRAY_H
#define SEMS_DYNARRAY_H

#include<iostream>
using namespace std;

template<typename T>
class dynArr
{
private:
    int cap;
    int numOfElem;
    T **arr;

public:
    dynArr(int size = 10);
    ~dynArr();

    void init(int from);
    void expand();
    void push(const T &element);
    void pop(int index);
    const int& space()const { return this->cap; }

    const int& size()const { return this->numOfElem; }

    T& operator[] (int index);
};

//Constructor
template<typename T>
dynArr<T>::dynArr(int size)
{
    this->cap = size;
    this->numOfElem = 0;
    this->arr = new T*[this->cap];

    init(this->numOfElem);
}

//Destruct
template<typename T>
dynArr<T>::~dynArr()
{
    for (size_t i = 0; i < numOfElem; i++)
    {
        delete this->arr[i];
    }
    //delete[]this->arr;
}

//Operator
template<typename T>
T& dynArr<T>::operator[](int index)
{
    if (index < 0 || index >= this->numOfElem)
        throw("Out of bounds!");

    return *this->arr[index];
}

//initialize
template<typename T>
void dynArr<T>::init(int from)
{
    for (size_t i = from; i < cap; i++)
    {
        this->arr[i] = nullptr;
    }
}

//increase memory amount
template<typename T>
void dynArr<T>::expand()
{
    this->cap += 10;

    T **tempArr = new T *[this->cap];

    for (size_t i = 0; i < this->numOfElem; i++) {
        tempArr[i] = this->arr[i];
    }

    delete[]this->arr;

    this->arr = tempArr;

    init(this->numOfElem);
}

//add to the end
template<typename T>
void dynArr<T>::push(const T& element)
{
    if (this->numOfElem >= this->cap)
    {
        this->expand();
    }

    this->arr[this->numOfElem++] = new T(element);
}

//delete by index
template<typename T>
void dynArr<T>::pop(int index){
    if (index < 0 || index >= this->numOfElem)
        throw("Out of bounds!");

    for (int i = index; i <= this->numOfElem; ++i) {
        this->arr[i]=this->arr[i+1];
    };
    this->numOfElem--;
}


/*int main()
{
    dynArr<int> arr;

    arr.push(13);
    arr.push(145);
    arr.push(46532);
    arr.push(24365);
    arr.push(867);
    arr.push(456);
    arr.push(27);
    arr.push(2);

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
    cout<< arr.space() <<endl;
    cout<< arr.size()<<endl;

    return 0;
}*/

#endif //SEMS_DYNARRAY_H
