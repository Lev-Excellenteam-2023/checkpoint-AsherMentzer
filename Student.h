#pragma once
#include <stdlib.h>
#include<string.h>


#define NUM_OF_LEVELS 12
#define NUM_OF_CLASS 10
#define NUM_OF_GRADES 10
#define PHONE_SIZE 11
#define NAME_SIZE 50

typedef struct stusent { 
	char fname[NAME_SIZE];
	char lname[NAME_SIZE];
	char phone[PHONE_SIZE];
	int grades[NUM_OF_GRADES];
} Student;


Student* student_create(char* fname,char* lname, char* phone,int* grades);

void student_free(Student* student);


void print_student(Student* student);

