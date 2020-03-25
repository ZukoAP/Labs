#ifndef SEMS_STUDENT_H
#define SEMS_STUDENT_H


class Student {
public:
    Student();
    ~Student() = default;
    Student(string, int);
    string getName();
    int getGroup();
    void setName(string _name);
    void setGroup(int _group);
private:
    string name;
    int group;
};

//def constructor
Student::Student() {
    this->name = "";
    this->group=0;
}

Student::Student(string _name, int _group) : name(_name), group(_group){
}

//getting info
inline string Student::getName() {
    return this->name;
}
inline int Student::getGroup() {
    return group;
}

//setting new info
inline void Student::setName(string _name) {
    name = _name;
}
inline void Student::setGroup(int _group) {
    group = _group;
}


#endif //SEMS_STUDENT_H
