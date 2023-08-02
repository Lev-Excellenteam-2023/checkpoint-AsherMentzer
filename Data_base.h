#ifndef DATA_BASE_H // Include guard to prevent multiple inclusions
#define DATA_BASE_H

#include "Student_node.h"
extern StudentNode* school[NUM_OF_LEVELS][NUM_OF_CLASS];
void read_from_file();
void print_school();
void school_free();

#endif