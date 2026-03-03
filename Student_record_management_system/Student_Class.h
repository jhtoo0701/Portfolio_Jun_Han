#ifndef STUDENT_CLASS
#define STUDENT_CLASS

#include<string>
using namespace std;

class Student
{
    public:
        Student(int id, string name, float gpa);

        int Student_ID();
        string Student_NAME();
        float Student_GPA();

    private:
        int id;
        string name;
        float gpa;
};

#endif