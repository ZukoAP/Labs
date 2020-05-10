#include <iostream>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include <iomanip>
#include <chrono>


using namespace std;

template<typename T>
void fillQueuesInt(Queue<T>* q1,Queue<T>* q2){
    for (int i = 0; i < 5000; ++i) {
        q1->push(rand() % 10000);
    }
    for (int i = 0; i < q1->size(); ++i) {
        q2->push(q1->data->getElement(i));
    }

}template<typename T>
void fillQueuesLinkList(Queue<T>* queueArr,Queue<T>* queueList){
    LinkList<int> a;
    for (int i = 0; i < 2000; ++i) {
        for (int j = 0; j < rand()%2000; ++j) {
            a.append(rand()%5000);
        }
        queueArr->push(a);
        while(a.getSize()!=0){
            a.pop(0);
        }
    }
    for (int i = 0; i < queueArr->size(); ++i) {
        queueList->push(queueArr->data->getElement(i));
    }
}

template <typename T, typename F>
double Tester(Queue<T> queue,F func){
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 1000; ++i) {
        func(queue);
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return time_taken;
}



template <typename T>
double swapTester(Queue<T> queue){
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 1000; ++i) {
        queue.swap(rand() % 5000, rand() % 5000);
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return time_taken;
}

template <typename T>
double popTester(Queue<T> queue){
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 1000; ++i) {
        queue.pop();
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return time_taken;
}

template <typename T>
double pushTester(Queue<T> queue){
    LinkList<int> a;
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 1000; ++i) {
        queue.push(rand()%10000);
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return time_taken;
}

void queueTester(){
    srand(time(nullptr));
    Queue<LinkList<int>> queueArr("array");
    Queue<LinkList<int>> queueList("list");
    ofstream file;
    //fillQueuesInt(&queueArr,&queueList);
    fillQueuesLinkList(&queueArr,&queueList);
    file.open("fillTest.csv", ios::trunc);
    //file<<"swap array,swap list,push array,push list,pop array,pop list"<<endl;
    file<<"swap array,swap list,pop array,pop list"<<endl;
    cout<<"Testing"<<endl;
    for (int i = 0; i < 100; ++i) {
        file<<fixed<<setprecision(0)<<Tester(queueArr,[](Queue<LinkList<int>> &q){
            q.swap(rand() % 2000, rand() % 2000);
        })<<","<<Tester(queueList,[](Queue<LinkList<int>> &q){
            q.swap(rand() % 2000, rand() % 2000);
        })
            //<<","<<pushTester(queueArr)<<","<<pushTester(queueList)
                <<","<<popTester(queueArr)<<","<<popTester(queueList)
                    <<endl;
    }
    cout<<"End of test"<<endl;
    file.close();
    cout<<"queueArr: "<< queueArr<<endl;
    cout<<"queueList: "<< queueList<<endl;
}
