#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Convert grade to grade point
float getGradePoint(string grade) {
    if (grade == "A")  return 4.00;
    if (grade == "A-") return 3.75;
    if (grade == "B+") return 3.50;
    if (grade == "B")  return 3.00;
    if (grade == "B-") return 2.75;
    if (grade == "C+") return 2.50;
    if (grade == "C")  return 2.00;
    if (grade == "F")  return 0.00;
    return -1; // invalid
}

int main() {
    string studentName, studentID;
    int totalSemesters;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Enter Student ID: ";
    getline(cin, studentID);

    cout << "\nHow many semesters to calculate CGPA? ";
    cin >> totalSemesters;

    float overallQualityPoints = 0;
    float overallCreditHours = 0;

    for (int s = 1; s <= totalSemesters; s++) {
        int numSubjects;
        cout << "\n--- Semester " << s << " ---\n";
        cout << "Enter number of subjects: ";
        cin >> numSubjects;

        float semesterQP = 0;
        float semesterCH = 0;

        for (int i = 1; i <= numSubjects; i++) {
            string courseCode, grade;
            int creditHour;

            cout << "\nSubject " << i << " Course Code: ";
            cin >> courseCode;

            cout << "Credit Hour: ";
            cin >> creditHour;

            cout << "Grade (A, A-, B+, B, B-, C+, C, F): ";
            cin >> grade;

            float gp = getGradePoint(grade);
            while (gp < 0) {
                cout << "Invalid grade! Enter again: ";
                cin >> grade;
                gp = getGradePoint(grade);
            }

            float QP = gp * creditHour;

            semesterQP += QP;
            semesterCH += creditHour;
        }

        float semesterGPA = semesterQP / semesterCH;

        // Add to overall for CGPA
        overallQualityPoints += semesterQP;
        overallCreditHours += semesterCH;

        cout << fixed << setprecision(2);
        cout << "\nSemester " << s << " GPA: " << semesterGPA << endl;
    }

    float CGPA = overallQualityPoints / overallCreditHours;

    cout << "\n---------------------------------------\n";
    cout << "Student Name : " << studentName << endl;
    cout << "Student ID   : " << studentID << endl;
    cout << "FINAL CGPA   : " << fixed << setprecision(2) << CGPA << endl;
    cout << "---------------------------------------\n";

    return 0;
}

