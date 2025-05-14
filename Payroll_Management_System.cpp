#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int id;
    float baseSalary;

public:
    virtual void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Base Salary: ";
        cin >> baseSalary;
    }

    virtual float calculateSalary() const {
        return baseSalary;
    }

    virtual void display() const {
        cout << "ID: " << id << "\nName: " << name << "\nBase Salary: " << baseSalary << endl;
    }

    virtual string getCategory() const {
        return "General";
    }

    virtual void saveToFile(ofstream& file) const {
        file << getCategory() << "," << id << "," << name << "," << baseSalary << "\n";
    }

    int getId() const {
        return id;
    }

    virtual ~Employee() {}
};

// --- Derived Classes ---
class Manager : public Employee {
    float bonus;

public:
    void input() override {
        Employee::input();
        cout << "Enter Bonus: ";
        cin >> bonus;
    }

    float calculateSalary() const override {
        return baseSalary + bonus;
    }

    void display() const override {
        Employee::display();
        cout << "Bonus: " << bonus << "\nTotal Salary: " << calculateSalary() << endl;
    }

    string getCategory() const override {
        return "Manager";
    }

    void saveToFile(ofstream& file) const override {
        file << getCategory() << "," << id << "," << name << "," << baseSalary << "," << bonus << "\n";
    }
};

class Intern : public Employee {
    int hoursWorked;
    float hourlyRate;

public:
    void input() override {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Hours Worked: ";
        cin >> hoursWorked;
        cout << "Enter Hourly Rate: ";
        cin >> hourlyRate;
        baseSalary = 0;
    }

    float calculateSalary() const override {
        return hoursWorked * hourlyRate;
    }

    void display() const override {
        cout << "ID: " << id << "\nName: " << name
             << "\nHours Worked: " << hoursWorked
             << "\nHourly Rate: " << hourlyRate
             << "\nTotal Salary: " << calculateSalary() << endl;
    }

    string getCategory() const override {
        return "Intern";
    }

    void saveToFile(ofstream& file) const override {
        file << getCategory() << "," << id << "," << name << "," << hoursWorked << "," << hourlyRate << "\n";
    }
};

class Engineer : public Employee {
    float techAllowance;

public:
    void input() override {
        Employee::input();
        cout << "Enter Technical Allowance: ";
        cin >> techAllowance;
    }

    float calculateSalary() const override {
        return baseSalary + techAllowance;
    }

    void display() const override {
        Employee::display();
        cout << "Technical Allowance: " << techAllowance << "\nTotal Salary: " << calculateSalary() << endl;
    }

    string getCategory() const override {
        return "Engineer";
    }

    void saveToFile(ofstream& file) const override {
        file << getCategory() << "," << id << "," << name << "," << baseSalary << "," << techAllowance << "\n";
    }
};

class Clerk : public Employee {
    int overtimeHours;
    float overtimeRate;

public:
    void input() override {
        Employee::input();
        cout << "Enter Overtime Hours: ";
        cin >> overtimeHours;
        cout << "Enter Overtime Rate: ";
        cin >> overtimeRate;
    }

    float calculateSalary() const override {
        return baseSalary + (overtimeHours * overtimeRate);
    }

    void display() const override {
        Employee::display();
        cout << "Overtime Hours: " << overtimeHours << "\nOvertime Rate: " << overtimeRate
             << "\nTotal Salary: " << calculateSalary() << endl;
    }

    string getCategory() const override {
        return "Clerk";
    }

    void saveToFile(ofstream& file) const override {
        file << getCategory() << "," << id << "," << name << "," << baseSalary << "," << overtimeHours << "," << overtimeRate << "\n";
    }
};

// --- Payroll System ---
class PayrollSystem {
    vector<Employee*> employees;

public:
    void addEmployee() {
        if (employees.size() >= 30) {
            cout << "Cannot add more than 30 employees.\n";
            return;
        }

        int choice;
        cout << "Select Employee Type:\n1. General\n2. Manager\n3. Intern\n4. Engineer\n5. Clerk\nChoice: ";
        cin >> choice;

        Employee* emp = nullptr;

        switch (choice) {
            case 1: emp = new Employee(); break;
            case 2: emp = new Manager(); break;
            case 3: emp = new Intern(); break;
            case 4: emp = new Engineer(); break;
            case 5: emp = new Clerk(); break;
            default: cout << "Invalid choice.\n"; return;
        }

        emp->input();
        employees.push_back(emp);
        cout << "Employee added successfully!\n";
    }

    void displayAll() const {
        for (size_t i = 0; i < employees.size(); ++i) {
            cout << "\n--- Employee " << i + 1 << " ---\n";
            employees[i]->display();
        }
    }

    void searchEmployee() const {
        int idToSearch;
        cout << "Enter ID to search: ";
        cin >> idToSearch;

        bool found = false;
        for (auto emp : employees) {
            if (emp->getId() == idToSearch) {
                emp->display();
                found = true;
                break;
            }
        }
        if (!found) cout << "Employee not found.\n";
    }

    void deleteEmployee() {
        int idToDelete;
        cout << "Enter ID to delete: ";
        cin >> idToDelete;

        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == idToDelete) {
                delete *it;
                employees.erase(it);
                cout << "Employee deleted successfully.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void saveToFile() const {
        ofstream file("employees.txt");
        for (auto emp : employees) {
            emp->saveToFile(file);
        }
        file.close();
        cout << "Data saved to file.\n";
    }

    ~PayrollSystem() {
        for (auto emp : employees) {
            delete emp;
        }
    }
};

// --- Main ---
int main() {
    PayrollSystem ps;
    int choice;

    do {
        cout << "\n--- Payroll Menu ---\n"
             << "1. Add Employee\n"
             << "2. Display All\n"
             << "3. Search Employee\n"
             << "4. Delete Employee\n"
             << "5. Save to File\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: ps.addEmployee(); break;
            case 2: ps.displayAll(); break;
            case 3: ps.searchEmployee(); break;
            case 4: ps.deleteEmployee(); break;
            case 5: ps.saveToFile(); break;
            case 0: break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}