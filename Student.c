#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

Student* student_create( char* fname,  char* lname, char* phone ,int* grades)
{
	Student* student = (Student*) malloc(sizeof(Student));
	strcpy(student->fname, fname);
	strcpy(student->lname,  lname);
	strcpy(student->phone,  phone);
	
	for (int i = 0; i < NUM_OF_GRADES; ++i) {
		student->grades[i] = grades[i];
	}
	return student;
}

void student_free(Student* student)
{
	free(student);
}

void print_student(Student* student)
{
	printf("name: %s%s ,phone: %s ", student->fname, student->lname, student->phone);
	for (int i = 0; i < NUM_OF_GRADES; ++i) {
		printf("%d", student->grades[i]);
	}
	printf("\n");
}





