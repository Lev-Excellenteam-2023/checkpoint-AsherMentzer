#ifndef STUDENTS_NODE_H // Include guard to prevent multiple inclusions
#define STUDENTS_NODE_H

#include "Student.h"
#include <stdio.h>

typedef struct studentNode {
	Student* current;
	struct studentNode* next;
}StudentNode;



// display the list
void printList(StudentNode* head);

//insertion at the beginning
void insertatbegin(StudentNode** head, Student* student);

void free_list(StudentNode* head);

// Function to delete a node from the linked list
void deleteNode(StudentNode** head, StudentNode* nodeToDelete);

// Function to find and return the node with a specific value
StudentNode* findNodeByPhone(StudentNode** head, char* phone_num);

// Function to find and return the node with a specific value
StudentNode* findNodeByName(StudentNode** head, char* fname, char* lname);


#endif