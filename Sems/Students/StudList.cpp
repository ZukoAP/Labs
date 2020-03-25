#include <iostream>
#include "DynArray.h"
#include "Student.h"

void addStudent(dynArr<Student>*);
void delByName(dynArr<Student>*);
void delByName(string name, dynArr<Student>* list);
void delGroup(dynArr<Student>*);


int main() {
    dynArr<Student> list;
    int numOfStud;
    cin>>numOfStud;

    for (int i = 0; i <numOfStud; i ++) {
        addStudent(&list);
    }
    cout<<endl<<"Current list: "<<endl;
    for (size_t i = 0; i < list.size(); i++)
    {
        cout<<list[i].getName()<<" "<<list[i].getGroup()<<endl;
    }
    delByName(&list);
    delGroup(&list);
    if (list.size()==0){
        cout<<"List is empty";
        return 0;
    } else {
        for (size_t i = 0; i < list.size(); i++) {
            cout << list[i].getName() << " " << list[i].getGroup() << endl;
        }
        cout << list.space() << endl;
        cout << list.size() << endl;
        return 0;
    }
}



void addStudent(dynArr<Student>* list){
    string name;
    Student curr;
    int group;
    cout << "Enter name and group of the student" << endl;
    std::getline(std::cin >> std::ws, name);
    cin >> group;
    curr = Student(name, group);
    list->push(curr);
}

void delByName(dynArr<Student>* list){
    string name;
    cout<<"Enter name to delete: ";
    std::getline(std::cin >> std::ws, name);
    for (int i = 0; i < list->size(); ++i) {
        if ((*list)[i].getName() == name) {
            list->pop(i);
            cout<<"Successfully deleted"<<endl;
            return;
        }
    }
    cout<<"No match found"<<endl;
}

void delByName(string name, dynArr<Student>* list){
    for (int i = 0; i < list->size(); ++i) {
        if ((*list)[i].getName() == name) {
            list->pop(i);
            cout<<"Successfully deleted"<<endl;
            return;
        }
    }
    cout<<"No match found"<<endl;
}

void delGroup(dynArr<Student>* list){
    int group,k=0;
    string name;
    cout<<"Enter group to delete: ";
    cin>>group;
    for (int i = list->size()-1; i >= 0; --i) {
        if ((*list)[i].getGroup() == group) {
            k+=1;
            name = (*list)[i].getName();
            delByName(name,list);
        }
    }
    if  (k==0)
        cout<<"No match found"<<endl;
    else
        cout<<"Successfully deleted"<<endl;
}