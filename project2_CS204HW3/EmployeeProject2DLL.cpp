//
// Created by Mertcan Bakır on 26.03.2024.
//
#include <iostream>
#include <string>
#include "EmployeeProject2DLL.h"

using namespace std;

bool EmployeeProject2DLL :: isEmployeeAssignedToProject(string employee_name,string project_name){
    EmployeeNode* curremploy = employtop;

    while (curremploy != nullptr) { // until its null, go to the next element
        ProjectNode* currproj = curremploy->head;

        while (currproj != nullptr) { // until its null, go to the next element
            if (currproj->project_name == project_name && curremploy->employee_name == employee_name) { // checks that is that employee assigned to that project
                return true; // if it is assigned return true
            }
            currproj = currproj->next;
        }
        curremploy = curremploy->down;
    }
    return false; // it is not assigned return false
}


bool EmployeeProject2DLL :: updateProjectPriority(string employee_name,string project_name, int &project_priority){
    EmployeeNode* ptr = employtop;

    // Go to the next element until the employee names are the same or you reach the end of the list
    while (ptr != nullptr && ptr->employee_name != employee_name) {
        ptr = ptr->down;
    }

    if (ptr == nullptr) {// checks if the employee is not found
        cout << "Employee not found." << endl;
        return false;
    }

    ProjectNode* checker = ptr->head;
    // Go to the next element until find a project with the same priority
    while (checker != nullptr && checker->project_priority != project_priority) {
        checker = checker->next;
    }

    // Checks if a project with the same priority is found and the project names are different
    if (checker != nullptr && checker->project_name != project_name) {
        cout << "The project priority has not been updated because there is another project with the same priority." << endl;
        return false;
    }

    ProjectNode* curproj = ptr->head;
    ProjectNode* prevproj = nullptr;

    // Go to the next element until list is empty or project names are same
    while (curproj != nullptr && curproj->project_name != project_name) {
        prevproj = curproj;
        curproj = curproj->next;
    }

    // If the projects priority are same as the new priority
    if (curproj != nullptr && curproj->project_priority == project_priority) {
        cout << "The project priority is already the same as the new priority." << endl;
        return false;
    }

    // checks if it is first element or not
    if (prevproj == nullptr) {
        ptr->head = curproj->next;
        if (ptr->head == nullptr) { // check if it is one project or not
            ptr->tail = nullptr;
        } else { // means it has more than one element
            ptr->head->prev = nullptr;
        }
    } else { // means it is in the middle or last element
        prevproj->next = curproj->next;
        if (curproj->next != nullptr) { // checks is it last element or not
            curproj->next->prev = prevproj;
        } else {
            ptr->tail = prevproj;
        }
    }

    int previous_priority = curproj->project_priority;

    delete curproj; // delete the node

    ProjectNode* newnode = new ProjectNode();
    newnode->project_name = project_name;
    newnode->project_priority = project_priority;

    curproj = ptr->head;
    prevproj = nullptr;

    // Go to the next element until project priorities are less than the new priority
    while (curproj != nullptr && curproj->project_priority < newnode->project_priority) {
        prevproj = curproj;
        curproj = curproj->next;
    }

    // checks is it first element or not
    if (prevproj == nullptr) {
        newnode->next = ptr->head;
        if (ptr->head != nullptr) { // checks is it empty or not
            ptr->head->prev = newnode; // Corrected
        } else {
            ptr->tail = newnode;
        }
        ptr->head = newnode;
    } else { // means it is not the first element
        prevproj->next = newnode;
        newnode->prev = prevproj;
        newnode->next = curproj;

        if (curproj == nullptr) { // means it is last element
            ptr->tail = newnode;
        } else { // means it is in the middle
            curproj->prev = newnode;
        }
    }
    project_priority = previous_priority;

    return true;
}



bool EmployeeProject2DLL::assignEmployeeToProject(string employee_name, string project_name, int project_priority) {
    EmployeeNode* checker = employtop;

    if (checker != nullptr) { // checks if the list is empty or not
        while (checker != nullptr && checker->employee_name != employee_name) { // go to the next element until it is empty or names are not equal
            checker = checker->down;
        }
        if (checker != nullptr){ //checks if the list is empty or not
            ProjectNode* checkproj = checker->head;
            while (checkproj != nullptr) { // while project list is empty go to the next element
                if (checkproj->project_priority == project_priority) { // checks if project priorities are same or not
                    cout << "The project has not been added because there is another project with the same priority." << endl;
                    return false;
                }
                checkproj = checkproj->next;
            }
        }
    }

    EmployeeNode* new_employee = new EmployeeNode();
    new_employee->employee_name = employee_name;
    new_employee->down = nullptr;
    new_employee->head = nullptr;
    new_employee->tail = nullptr;

    ProjectNode* new_project = new ProjectNode();
    new_project->project_name = project_name;
    new_project->project_priority = project_priority;
    new_project->next = nullptr;
    new_project->prev = nullptr;

    if (employtop == nullptr || employee_name < employtop->employee_name) { // checks it is first element or list is empty
        new_employee->down = employtop;
        employtop = new_employee;
        new_employee->head = new_project;
        new_employee->tail = new_project;
        return true;
    }

    EmployeeNode* current = employtop;
    EmployeeNode* prev = nullptr;

    while (current != nullptr && current->employee_name != employee_name) { // go to the next element until list is empty or employee names are same
        prev = current;
        current = current->down;
    }

    if (current != nullptr && current->employee_name == employee_name) { // checks that if it is empty or names are same
        ProjectNode* currProject = current->head;
        ProjectNode* prevProject = nullptr;

        while (currProject != nullptr && currProject->project_priority < project_priority) { // look to project priorities and move to the next element
            prevProject = currProject;
            currProject = currProject->next;
        }

        new_project->next = currProject;
        new_project->prev = prevProject;

        if (prevProject != nullptr) { //checks prev node is empty or not. Checks is it first element or not
            prevProject->next = new_project;
        } else {
            current->head = new_project;
        }

        if (currProject != nullptr) { // Checks is it last element or not
            currProject->prev = new_project;
        } else {
            current->tail = new_project;
        }
        return true;
    }

    // If there is no match after checking all elements, add the new element to the appropriate place in alphabetical order
    current = employtop;
    prev = nullptr;
    while (current != nullptr && current->employee_name < employee_name) { // go to the next element until list is empty or employee name is smaller correctly ordered
        prev = current;
        current = current->down;
    }
    new_employee->down = prev->down;
    prev->down = new_employee;
    new_employee->head = new_project;
    new_employee->tail = new_project;
    return true;
}

bool EmployeeProject2DLL :: withdrawEmployeeFromProject(string employee_name, string project_name, int &project_priority){
    EmployeeNode* ptr = employtop;

    // Search for the employee node with the given name
    while (ptr != nullptr && ptr->employee_name != employee_name) {
        ptr = ptr->down;
    }
    if (ptr == nullptr) { // If the employee is not found
        cout << "Employee not found." << endl;
        return false;
    }

    // Search for the project node with the given name
    ProjectNode* curproj = ptr->head;
    ProjectNode* prevproj = nullptr;
    while (curproj != nullptr && curproj->project_name != project_name) {
        prevproj = curproj;
        curproj = curproj->next;
    }
    if (curproj == nullptr) { // If the project is not found
        cout << "Project not found." << endl;
        return false;
    }
    if (prevproj == nullptr) { // If the project is the first one in the employee's project list
        ptr->head = curproj->next;
        if (ptr->head == nullptr) {
            ptr->tail = nullptr;
        } else {
            ptr->head->prev = nullptr;
        }
    } else { // If the project is in the middle or at the end of the employee's project list
        prevproj->next = curproj->next;
        if (curproj->next != nullptr) {
            curproj->next->prev = prevproj;
        } else {
            ptr->tail = prevproj;
        }
    }

    // Store the old project priority before deleting the project node
    int oldpriority = curproj->project_priority;
    delete curproj;

    // Search for the employee node again to check if it has any projects left
    EmployeeNode* cur = employtop;
    EmployeeNode* pre = nullptr;

    while (cur != nullptr && cur->employee_name != employee_name) {
        pre = cur;
        cur = cur->down;
    }
    ProjectNode* pro = cur->head;
    if (pro == nullptr) { // If the employee has no projects left
        if (pre != nullptr) {
            pre->down = cur->down;
        } else {
            employtop = cur->down;
        }

        delete cur;
    }

    project_priority = oldpriority;     // Assign the old project priority to the reference parameter
    return true;
}
void EmployeeProject2DLL :: printTheEntireList(){
    EmployeeNode* empnode = employtop;
    if(empnode == nullptr){  // checks that is the list is empty or not
        cout<<"The list is empty."<<endl;
    }
    else{ // means list is not empty
        while(empnode != nullptr){  // go to the every employee name in the list
            cout << empnode->employee_name << ": ";
            ProjectNode* pronode;
            pronode = empnode->head;
            while(pronode != nullptr){ // go to the every project in the list
                cout << "(" << pronode->project_name << ", " << pronode->project_priority << ") ";
                pronode = pronode->next;
            }
            empnode = empnode->down;
            cout << endl;
        }
    }
}

void EmployeeProject2DLL :: printEmployeeProjects(string employee_name, int order){
    EmployeeNode* employnode = employtop;

    while (employnode != nullptr && employnode->employee_name != employee_name) { // go to the next element until it is empty or until their names are equal
        employnode = employnode->down;
    }
    if (employtop == nullptr) {// Check if the list is empty
        cout << "There are no employees in the list." << endl;
        return;
    }

    if (employnode == nullptr) { // checks that given employee name is in the list or not
        cout << "The employee is not in the list." << endl;
        return;
    }
    if (order == 1) {// Means its ascending order
        ProjectNode* curProject = employnode->head; // starting from first element
        while (curProject != nullptr) { // go all the elements of projects until it is empty
            cout << "(" << curProject->project_name << ", " << curProject->project_priority << ") ";
            curProject = curProject->next;
        }
    } else { // Means its descending order
        ProjectNode* curProject = employnode->tail; // starting from last element
        while (curProject != nullptr) { // go all the elements until list is empty
            cout << "(" << curProject->project_name << ", " << curProject->project_priority << ") ";
            curProject = curProject->prev;
        }
    }
    cout << endl;
}

void EmployeeProject2DLL :: undo(char operation, string employee_name, string project_name, int project_priority){

    if(operation == 'a'){ // checks operation is a or not
        cout << "Undoing the assignment of a project." << endl;
        withdrawEmployeeFromProject(employee_name, project_name, project_priority);
    }
    else if(operation == 'w'){ // checks operation is w or not
        cout << "Undoing the withdrawal of a project." << endl;
        assignEmployeeToProject(employee_name,project_name, project_priority);
    }
    else if(operation == 'u'){ // checks operation is u or not
        cout << "Undoing the update of a project priority." << endl;
        updateProjectPriority(employee_name,project_name,project_priority);
    }
}
void EmployeeProject2DLL :: clear(){
    while (employtop != nullptr) { // go to the next element until it is null
        ProjectNode* projptr = employtop->head;
        while (projptr != nullptr) { // go the next element until project list is null
            ProjectNode* temp = projptr;
            projptr = projptr->next;
            delete temp; // delete the project
        }
        EmployeeNode* temp = employtop;
        employtop = employtop->down;
        delete temp; // delete the employee name
    }
}
