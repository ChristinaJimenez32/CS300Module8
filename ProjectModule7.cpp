
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// Structure to store course information
struct Course {
    string courseNumber;               // Course number
    string courseTitle;                // Course title
    vector<string> prerequisites;      // List of prerequisites
};

vector<Course> courses;                // Vector to store all courses

// Function to load data from a file into the courses vector
void loadDataStructure(const string& fileName) {
    ifstream file(fileName);           // Open the file
    if (!file.is_open()) {             // Check if the file is open
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {      // Read each line from the file
        Course course;
        stringstream ss(line);         // Use stringstream to parse the line
        string token;

        // Parse course number
        getline(ss, token, ',');
        course.courseNumber = token;

        // Parse course title
        getline(ss, token, ',');
        course.courseTitle = token;

        // Parse prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses.push_back(course);     // Add the course to the vector
    }

    file.close();                      // Close the file
}

// Function to print the list of courses
void printCourseList() {
    if (courses.empty()) {             // Check if there are no courses loaded
        cout << "No courses loaded." << endl;
        return;
    }

    // Sort courses by course number
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });

    cout << "Courses :" << endl;       // Print each course number and title
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print details of a specific course
void printCourse(const string& courseNumber) {
    if (courses.empty()) {             // Check if there are no courses loaded
        cout << "No courses loaded." << endl;
        return;
    }

    // Find the course by course number
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.courseNumber == courseNumber;
    });

    if (it != courses.end()) {         // If course is found, print details
        cout << it->courseNumber << ", " << it->courseTitle << endl;
        cout << "Prerequisites: ";
        if (it->prerequisites.empty()) {  // Check if there are no prerequisites
            cout << "None" << endl;
        } else {
            // Print prerequisites
            for (size_t i = 0; i < it->prerequisites.size(); ++i) {
                cout << it->prerequisites[i];
                if (i < it->prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    } else {
        cout << "Course not found." << endl;   // If course is not found, print message
    }
}

int main() {
    string fileName;                  // Variable to store the file name
    int choice;                       // Variable to store the user's menu choice
    string courseNumber;              // Variable to store the course number

    do {
        // Display menu options
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;                // Get user's menu choice

        switch(choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> fileName;      // Get file name from user
                loadDataStructure(fileName);  // Load data from the file
                break;
            case 2:
                printCourseList();    // Print the list of courses
                break;
            case 3:
                cout << "What course do you want information on? ";
                cin >> courseNumber;  // Get course number from user
                printCourse(courseNumber);    // Print details of the specified course
                break;
            case 9:
                cout << "Exiting" << endl;  // Print exit message
                break;
            default:
                cout << choice << " is not a valid option." << endl;  // Handle invalid menu choice
        }
    } while (choice != 9);            // Repeat the loop until the user chooses to exit

    return 0;
}
