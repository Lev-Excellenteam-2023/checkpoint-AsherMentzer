#pragma once
#include "Student.h"
#include <stdio.h>

typedef struct studentNode {
	Student* current;
	struct studentNode* next;
}StudentNode;



// display the list
void printList(StudentNode** head);

//insertion at the beginning
void insertatbegin(StudentNode** head, Student* student);

void free_list(StudentNode** head);
