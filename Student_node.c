#include "Student_node.h"

void printList(StudentNode* head) {
	StudentNode* p = head;
	//printf("\n[");

	//start from the beginning
	while (p != NULL) {
		print_student(p->current);
		p = p->next;
	}
	//printf("]");
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
	if(head->next)
		free(head->next);
	free(head);
	 /*StudentNode* current = head;
	 StudentNode* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}*/

}

// Function to delete a node from the linked list
void deleteNode(StudentNode** head, StudentNode* nodeToDelete) {
	if (*head == NULL || nodeToDelete == NULL) {
		return; // Empty list or invalid nodeToDelete
	}

	// If the node to delete is the head node
	if (*head == nodeToDelete) {
		*head = nodeToDelete->next;
		free(nodeToDelete);
		return;
	}

	// Find the previous node of the node to delete
	StudentNode* prevNode = *head;
	while (prevNode->next != NULL && prevNode->next != nodeToDelete) {
		prevNode = prevNode->next;
	}

	// If the node to delete is not present in the list
	if (prevNode->next == NULL) {
		printf("Node not found in the list.\n");
		return;
	}

	// Update the next pointer of the previous node to skip the nodeToDelete
	prevNode->next = nodeToDelete->next;

	// Free the memory of the nodeToDelete
	free(nodeToDelete);
}

StudentNode* findNodeByPhone(StudentNode** head, char* phone_num) {
	if (head == NULL) {
		return NULL;
	}
	StudentNode* current = *head;
	while (current != NULL) {
		if (strcmp(current->current->phone, phone_num)==0) {
			return current;
		}
		current = current->next;
	}
	return NULL; // Value not found in the list
}

StudentNode* findNodeByName(StudentNode** head, char* fname, char* lname)
{
	if (head == NULL) {
		return NULL;
	}
	StudentNode* current = *head;
	while (current != NULL) {
		if ((strcmp(current->current->fname, fname) == 0) && 
			(strcmp(current->current->lname, lname) == 0)) {
			return current;
		}
		current = current->next;
	}
	return NULL; // Value not found in the list
}
