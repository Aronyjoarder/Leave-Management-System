#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Employee structure for linked list
struct Employee {
    string name;
    string gender;
    Employee* next;

    Employee(string n, string g) {
        name = n;
        gender = g;
        next = nullptr;
    }
};

// Leave request structure for stack
struct Leave {
    string empName;
    string leaveType;
    string startDate;
    string endDate;
    bool approved;

    Leave(string name, string type, string start, string end) {
        empName = name;
        leaveType = type;
        startDate = start;
        endDate = end;
        approved = false;
    }
};

// Global variables
Employee* head = nullptr;
stack<Leave> leaveStack;

// Add new employee to linked list
void addEmployee() {
    string name, gender;
    cout << "Enter employee name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter gender: ";
    getline(cin, gender);

    Employee* newEmp = new Employee(name, gender);
    newEmp->next = head;
    head = newEmp;

    cout << "Employee added successfully!\n";
}

// Find employee in linked list
Employee* findEmployee(string name) {
    Employee* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Submit leave request
void submitLeave(string empName) {
    string leaveType, startDate, endDate;

    cout << "Enter leave type(e.g., Casual, Sick, Annual, Emergency): ";
    cin.ignore();
    getline(cin, leaveType);
    cout << "Enter start date (dd/mm/yyyy): ";
    getline(cin, startDate);
    cout << "Enter end date (dd/mm/yyyy): ";
    getline(cin, endDate);

    Leave newLeave(empName, leaveType, startDate, endDate);
    leaveStack.push(newLeave);

    cout << "Leave request submitted!\n";
}

// View employee's own leaves
void viewMyLeaves(string empName) {
    cout << "\n=== My Leave Requests ===\n";

    if (leaveStack.empty()) {
        cout << "No leave requests found.\n";
        return;
    }

    stack<Leave> temp = leaveStack;
    bool found = false;

    while (!temp.empty()) {
        Leave current = temp.top();
        temp.pop();

        if (current.empName == empName) {
            found = true;
            cout << "Type: " << current.leaveType << endl;
            cout << "From: " << current.startDate << " To: " << current.endDate << endl;
            cout << "Status: " << (current.approved ? "Approved" : "Pending") << endl;
            cout << "-------------------\n";
        }
    }

    if (!found) {
        cout << "No leave requests found.\n";
    }
}

// Show all leave requests (admin)
void showAllLeaves() {
    cout << "\n=== All Leave Requests ===\n";

    if (leaveStack.empty()) {
        cout << "No leave requests found.\n";
        return;
    }

    stack<Leave> temp = leaveStack;

    while (!temp.empty()) {
        Leave current = temp.top();
        temp.pop();

        cout << "Employee: " << current.empName << endl;
        cout << "Type: " << current.leaveType << endl;
        cout << "From: " << current.startDate << " To: " << current.endDate << endl;
        cout << "Status: " << (current.approved ? "Approved" : "Pending") << endl;
        cout << "-------------------\n";
    }
}

// Approve leave request
void approveLeave() {
    string empName;
    cout << "Enter employee name to approve leave: ";
    cin.ignore();
    getline(cin, empName);

    stack<Leave> temp;
    bool found = false;

    while (!leaveStack.empty()) {
        Leave current = leaveStack.top();
        leaveStack.pop();

        if (current.empName == empName && !current.approved) {
            current.approved = true;
            found = true;
            cout << "Leave approved for " << empName << endl;
        }
        temp.push(current);
    }

    // Put everything back
    while (!temp.empty()) {
        leaveStack.push(temp.top());
        temp.pop();
    }

    if (!found) {
        cout << "No pending leave found for this employee.\n";
    }
}

// Employee menu
void employeeMenu() {
    string empName;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, empName);

    if (findEmployee(empName) == nullptr) {
        cout << "Employee not found! Please contact admin.\n";
        return;
    }

    cout << "Welcome, " << empName << "!\n";

    int choice;
    do {
        cout << "\n--- Employee Menu ---\n";
        cout << "1. Submit Leave Request\n";
        cout << "2. View My Leaves\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            submitLeave(empName);
        }
        else if (choice == 2) {
            viewMyLeaves(empName);
        }
    } while (choice != 0);
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. View All Leaves\n";
        cout << "3. Approve Leave\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            addEmployee();
        }
        else if (choice == 2) {
            showAllLeaves();
        }
        else if (choice == 3) {
            approveLeave();
        }
    } while (choice != 0);
}

// Main function
int main() {
    cout << "=============================\n";
    cout << "Leave Management System\n";
    cout << "=============================\n";

    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Employee Login\n";
        cout << "2. Admin Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            employeeMenu();
        }
        else if (choice == 2) {
            adminMenu();
        }
        else if (choice == 0) {
            cout << "Thank you!\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
