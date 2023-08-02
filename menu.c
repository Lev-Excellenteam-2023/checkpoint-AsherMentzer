#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Data_base.h"


#define MAX_LENGTH 300 // Maximum length of the input string


void insertNewStudent();
void deleteStudent();
void searchStudent();
void editStudentGrade();
void printTopNStudentsPerCourse();
void printUnderperformedStudents();
int findLowestIndex(StudentNode** topN, int n, int course_num);
void printAverage();

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

void menu() {
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
            case Insert:
                insertNewStudent();
                break;
            case Delete:
                deleteStudent();
                break;
            case Edit:
                editStudentGrade();
                break;
            case Search:
                searchStudent();
                break;
            case Showall:
                print_school();
                break;
            case Top10:
                printTopNStudentsPerCourse();
                break;
            case UnderperformedStudents:
                printUnderperformedStudents();
                break;
            case Average:
                printAverage();
                break;
            case Export:
                //exportDatabase();
                break;
            case Exit:
                //handleClosing();
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                       input);
                getc(stdin);
                getc(stdin);
                break;
        }
    } while (input != Exit);
}


int main() {
    read_from_file();
    //print_school();
    menu();
    school_free();
    return 0;
}

void insertNewStudent()
{
    char input[MAX_LENGTH];
    printf("Enter a line of text: ");
    // Use fgets to read input from the user
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove the newline character at the end of the input (if present)
        int length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }
    }
        char fname[NAME_SIZE];
        char lname[NAME_SIZE];
        char phone[PHONE_SIZE];
        int grades[NUM_OF_GRADES];
        int level;
        int class_num;
        char* token;
        //char* context = NULL;
        //Use strtok to split the line into individual strings based on spaces
        token = strtok(input, " ");
        strcpy(fname, token);
        token = strtok(NULL, " ");
        strcpy(lname, token);
        token = strtok(NULL, " ");
        strcpy(phone, token);
        token = strtok(NULL, " ");
        level = atoi(token);
        token = strtok(NULL, " ");
        class_num = atoi(token);
        for (int i = 0; i < NUM_OF_GRADES; ++i) {
            token = strtok(NULL, " ");
            int grade = atoi(token);
            grades[i] = grade;
        }
        Student* newStudent = student_create(fname, lname, phone, grades);
        insertatbegin(&school[level - 1][class_num - 1], newStudent);
        print_school();



        /*printf("Enter student details (firstName lastName phone grade1 grade2 ... grade10):\n");
        fgets(line, sizeof(line), stdin);

        int numScanned = sscanf(line, "%s %s %u %d %d %d %d %d %d %d %d %d %d %d",
            newStudent->fname, newStudent->lname, newStudent->phone,
            newStudent->grades[0], &student.grades[1], &student.grades[2],
            &student.grades[3], &student.grades[4], &student.grades[5],
            &student.grades[6], &student.grades[7], &student.grades[8],
            &student.grades[9]);

        // Check if all expected values were successfully scanned
        if (numScanned != 13) {
            printf("Invalid input format. Please enter all required data.\n");
            return 1;
        }*/
}

void deleteStudent()
{
    char input[MAX_LENGTH];
    printf("Enter student details (phone number):\n");
    // Use fgets to read input from the user
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove the newline character at the end of the input (if present)
        int length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }
    }
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            StudentNode* student = findNodeByPhone(&school[level_num][class_num], input);
            if (student != NULL) {
                deleteNode(&school[level_num][class_num], student);
                printf("student deleted successfully.\n");
                return;
            }
        }
    }
    printf("student not found.\n");
}

void searchStudent()
{
    char input_name[NAME_SIZE*2];
    char input_fname[NAME_SIZE];
    char input_lname[NAME_SIZE];
    //char input_lname[NAME_SIZE];
    printf("Enter student details (first name last name):\n");
    // Use fgets to read input from the user
    if (fgets(input_name, sizeof(input_name), stdin) != NULL) {
        // Remove the newline character at the end of the input (if present)
        int length = strlen(input_name);
        if (input_name[length - 1] == '\n') {
            input_name[length - 1] = '\0';
        }
    }
    if (sscanf(input_name, "%49s %49s", input_fname, input_lname) == 2) {
        for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
            for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
                StudentNode* student = findNodeByName(&school[level_num][class_num], input_fname, input_lname);
                if (student != NULL) {
                    printf("level: %d  class: %d ", level_num+1, class_num+1);
                    print_student(student->current);
                    return;
                }
            }
        }
        printf("student not found.\n");
        return;
    }
    else {
        printf("Invalid input format. Please enter both first and last names.\n");
    }
    
}

void editStudentGrade()
{
    char input[MAX_LENGTH];
    printf("Enter student details (phone number):\n");
    // Use fgets to read input from the user
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove the newline character at the end of the input (if present)
        int length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }
    }
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            StudentNode* student = findNodeByPhone(&school[level_num][class_num], input);
            if (student != NULL) {
                print_student(student->current);
                printf("Enter course number to edit:\n");
                int course_num;
                scanf("%d", &course_num);
                int new_grade;
                printf("Enter an updated grade: ");
                scanf("%d", &new_grade);
                student->current->grades[course_num-1] = new_grade;
                print_student(student->current);
                return;
            }
        }
    }
    printf("student not found.\n");
    return;
}

void printTopNStudentsPerCourse()
{
    printf("Enter course number to fint top 10:\n");
    int course_num;
    scanf("%d", &course_num);
    printf("Enter number to top students to find\n");
    int n;
    scanf("%d", &n);
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        StudentNode** topN= calloc(n,sizeof(StudentNode*));
        int lowestStudentIndex = 0;
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            StudentNode* head = school[level_num][class_num];
            while (head != NULL) {
                if (topN[lowestStudentIndex] == NULL) {
                    topN[lowestStudentIndex] = head;
                    if (lowestStudentIndex < n-1) {
                        lowestStudentIndex++;
                    }
                    else {
                        lowestStudentIndex = findLowestIndex(topN, n, course_num);
                    }
                }
                else {
                    if (head->current->grades[course_num - 1] >
                        topN[lowestStudentIndex]->current->grades[course_num - 1]) {
                        topN[lowestStudentIndex] = head;
                        lowestStudentIndex = findLowestIndex(topN, n, course_num);
                    }
                }
                head = head->next;
            }
        }
        printf("level %d: \n", level_num + 1);
        for (int i = 0; i < n; ++i) {
            if (topN[i] == NULL)
                break;
            print_student(topN[i]->current);
        }
        free(topN);
    }

}

void printUnderperformedStudents()
{
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            StudentNode* head = school[level_num][class_num];
            while (head != NULL) {
                Student* student = head->current;
                double studentAvg = student_avg_grades(student);
                if (studentAvg < 59) {
                    print_student(student);
                }
                head = head->next;
            }
        }
    }
}

void printAverage()
{
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        int sumOfGrades[10] = { 0 };
        int students_count = 0;
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            StudentNode* head = school[level_num][class_num];
            while (head != NULL) {
                Student* student = head->current;
                students_count++;
                for (int i = 0; i < NUM_OF_GRADES; ++i) {
                    sumOfGrades[i] += student->grades[i];
                }
                head = head->next;
            }
        }
        printf("level num: %d \n", level_num+1);
        for (int i = 0; i < NUM_OF_GRADES; ++i) {
            int avgGrades = sumOfGrades[i] / students_count;
            printf("the average grade of course num %d is %d \n", i+1, avgGrades);
        }
    }
}

int findLowestIndex(StudentNode** topN,int n,int course_num) {
    int lowestIndex = 0;
    int lowestValue = topN[lowestIndex]->current->grades[course_num-1];
    for (int i = 1; i < n; ++i) {
        if (topN[i]->current->grades[course_num - 1] < lowestValue) {
            lowestIndex = i;
            lowestValue = topN[lowestIndex]->current->grades[course_num-1];
        }
    }
    return lowestIndex;
}