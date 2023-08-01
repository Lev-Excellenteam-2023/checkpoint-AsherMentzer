#define _CRT_SECURE_NO_WARNINGS
#include "Data_base.h"
#include <stdio.h>

StudentNode* school[NUM_OF_LEVELS][NUM_OF_CLASS] = {0};


void read_from_file()
{
    FILE* file;
    const char* filename = "students_with_class.txt";
    const char* mode = "r";
    char line[300];
    char* token;
    file = fopen(filename, "r");
    //Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        char fname[NAME_SIZE];
        char lname[NAME_SIZE];
        char phone[PHONE_SIZE];
        int grades[NUM_OF_GRADES];
        int level;
        int class_num;
        //char* context = NULL;
        //Use strtok to split the line into individual strings based on spaces
        token = strtok(line, " ");
        strcpy(fname, token);
        token = strtok(NULL, " ");
        strcpy(lname,token);
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
        insertatbegin(&school[level-1][class_num-1], newStudent);;


    }
    fclose(file);


}


void print_school() {
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            printList(school[level_num][class_num]);
        }
    }
}

void school_free() {
    for (int level_num = 0; level_num < NUM_OF_LEVELS; ++level_num) {
        for (int class_num = 0; class_num < NUM_OF_CLASS; ++class_num) {
            //free_list(school[level_num][class_num]);
            StudentNode* current = school[level_num][class_num];
            while (current != NULL) {
                StudentNode* temp = current;
                current = current->next;
                free(temp->current);
                free(temp);

            }
        }
    }
}

