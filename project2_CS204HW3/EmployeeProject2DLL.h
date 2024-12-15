//
// Created by Mertcan Bakır on 26.03.2024.
//

#ifndef CS204_HW3_EMPLOYEEPROJECT2DLL_H
#define CS204_HW3_EMPLOYEEPROJECT2DLL_H

#include <iostream>
#include <string>
using namespace std;


struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;

};

struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;

};

class EmployeeProject2DLL{

public:

    bool isEmployeeAssignedToProject(string employee_name,string project_name);

    bool updateProjectPriority(string employee_name,string project_name, int &project_priority);

    bool assignEmployeeToProject(string employee_name, string project_name, int project_priority);

    bool withdrawEmployeeFromProject(string employee_name, string project_name, int &project_priority);

    void printTheEntireList();

    void printEmployeeProjects(string employee_name, int order);

    void undo(char operation, string employee_name, string project_name, int project_priority);

    void clear();

private:
    EmployeeNode* employtop = nullptr;
};

#endif //CS204_HW3_EMPLOYEEPROJECT2DLL_H