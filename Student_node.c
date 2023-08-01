#include "Student_node.h"

void printList(StudentNode* head) {
	StudentNode* p = head;
	printf("\n[");

	//start from the beginning
	while (p != NULL) {
		print_student(p->current);
		p = p->next;
	}
	printf("]");
}
//insertion at the beginning
void insertatbegin(StudentNode** head, Student* newStudent) {
	if (head == NULL) {
		printf("Error: Invalid head pointer.\n");
		return;
	}
	StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
	if (newNode == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}
	newNode->current = newStudent;
	newNode->next = *head;
	*head = newNode;
	
}

void free_list(StudentNode* head)
{
	 StudentNode* current = head;
	 StudentNode* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

}

