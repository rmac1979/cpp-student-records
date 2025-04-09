/*
Author: Ryan McCamy
Assignment: Student Record Assignment
Description: Program will process student data that was input by the user
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Define enum for grade levels
enum GradeLevel {
    FRESHMAN = 1,
    SOPHOMORE,
    JUNIOR,
    SENIOR
};

// Typedef for simplified type usage
using GPA = double;

// Struct for Student
struct Student {
    string name;
    GradeLevel grade;
    GPA gpa;
};

// Custom namespace for student utilities
namespace StudentUtils {
    void formatName(string &name) {
        for (char &ch : name) {
            ch = toupper(ch);
        }
    }

    string gradeLevelToString(GradeLevel grade) {
        switch (grade) {
            case FRESHMAN: return "Freshman";
            case SOPHOMORE: return "Sophomore";
            case JUNIOR: return "Junior";
            case SENIOR: return "Senior";
            default: return "Unknown";
        }
    }

    void displayStudentInfo(const Student &student) {
        cout << "Student Record:\n";
        cout << "Name: " << student.name << "\n";
        cout << "Grade Level: " << gradeLevelToString(student.grade) << "\n";
        cout << "GPA: " << std::fixed << std::setprecision(2) << student.gpa << "\n\n";
    }

    bool isValidGPA(GPA gpa) {
        return gpa >= 0.0 && gpa <= 4.0;
    }

    // Sort comparator by name
    bool compareByName(const Student &a, const Student &b) {
        return a.name < b.name;
    }
}

int main() {
    vector<Student> students;
    char choice;

    do {
        Student student;

        cout << "Enter student name: ";
        std::getline(cin, student.name);
        StudentUtils::formatName(student.name);

        int gradeInput;
        cout << "Enter grade level (1=Freshman, 2=Sophomore, 3=Junior, 4=Senior): ";
        cin >> gradeInput;
        while (gradeInput < 1 || gradeInput > 4) {
            cout << "Invalid grade level. Enter again (1-4): ";
            cin >> gradeInput;
        }
        student.grade = static_cast<GradeLevel>(gradeInput);

        cout << "Enter GPA: ";
        cin >> student.gpa;
        while (!StudentUtils::isValidGPA(student.gpa)) {
            cout << "Invalid GPA. Enter a value between 0.00 and 4.00: ";
            cin >> student.gpa;
        }

        cin.ignore(); // clear newline from input buffer
        students.push_back(student);

        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y' || choice == 'Y');

    // Sort students by name
    std::sort(students.begin(), students.end(), StudentUtils::compareByName);

    cout << "\n--- All Student Records (Sorted Alphabetically) ---\n\n";
    for (const auto &student : students) {
        StudentUtils::displayStudentInfo(student);
    }

    return 0;
}
