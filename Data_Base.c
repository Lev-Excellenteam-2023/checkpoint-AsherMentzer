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
    if (fopen_s(&file, filename, mode) != 0) {
        printf("Failed to open the file.\n");
        return 1;
    }
   
    //Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        char fname[NAME_SIZE];
        char lname[NAME_SIZE];
        char phone[PHONE_SIZE];
        int grades[NUM_OF_GRADES];
        int level;
        int class_num;
        char* context = NULL;
        //Use strtok to split the line into individual strings based on spaces
        token = strtok_s(line, ", ",&context);
        strcpy_s(fname, sizeof(fname), token);
        token = strtok_s(NULL, ", ", &context);
        strcpy_s(lname, sizeof(lname), token);
        token = strtok_s(NULL, ", ", &context);
        strcpy_s(phone, sizeof(phone), token);
        token = strtok_s(NULL, ", ", &context);
        level = atoi(token);
        token = strtok_s(NULL, ", ", &context);
        class_num = atoi(token);
        for (int i = 0; i < NUM_OF_GRADES; ++i) {
            token = strtok_s(NULL, ", ", &context);
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
            free_list(school[level_num][class_num]);
        }
    }
}

