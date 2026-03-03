#include<iostream>
#include "Student_Class.h"
using namespace std;

Student::Student(int id, string name, float gpa)
{
    this -> id = id;
    this -> name = name;
    this -> gpa = gpa; 
}

int Student:: Student_ID()
{
    return id;
}

string Student:: Student_NAME()
{
    return name;
}

float Student:: Student_GPA()
{
    return gpa;
}