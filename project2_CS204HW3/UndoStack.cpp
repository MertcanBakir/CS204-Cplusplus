//
// Created by Mertcan Bakır on 26.03.2024.
//
#include <iostream>
#include <string>
#include "UndoStack.h"


using namespace std;

void UndoStack::push(char operation, string employee_name, string project_name, int project_priority) {
    StackNode* stacknode = new StackNode();
    stacknode->operation = operation;
    stacknode->employee_name = employee_name;
    stacknode->project_name = project_name;
    stacknode->project_priority = project_priority;
    stacknode->next = nullptr;

    if (isEmpty()) {
        top = stacknode;
        stacknode->next = nullptr;
    } else {
        stacknode -> next = top;
        top = stacknode;
    }
}

void UndoStack::pop(char &operation, string &employee_name, string &project_name, int &project_priority) {

        if (isEmpty()) { //Looks is it empty or not
            cout << "Stack is empty." << endl;
        }else{
            StackNode* node = top;
            operation = node->operation;
            employee_name = node->employee_name;
            project_name = node->project_name;
            project_priority = node->project_priority;
            top = node->next;
            delete node;  // deletes the node
        }
}

bool UndoStack::isEmpty() {
    if(top == nullptr){
        return true;
    }
    return false;
}

void UndoStack::clear() {
    while (!isEmpty()) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }

}