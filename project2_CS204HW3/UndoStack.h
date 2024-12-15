//
// Created by Mertcan Bakır on 26.03.2024.
//
#include <iostream>
#include <string>

#ifndef CS204_HW3_UNDOSTACK_H
#define CS204_HW3_UNDOSTACK_H

using namespace std;

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;

};

class UndoStack{

public:

    void push(char operation, string employee_name, string project_name ,int project_priority);
    void pop(char &operation, string &employee_name, string &project_name ,int &project_priority);
    bool isEmpty();
    void clear();

private:
  StackNode* top = nullptr;

};

#endif //CS204_HW3_UNDOSTACK_H