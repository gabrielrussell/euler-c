#define _GNU_SOURCE
#include "euler.h"
#include "dar.h"
#include "itr.h"
#include "split.h"
#include "18-67.h"

char * example[] = {
    "3",
    "7 4",
    "2 4 6",
    "8 5 9 3",
    NULL,
};

int main (int argc, char ** argv) {
    quietly_checkanswer(23,tri_max(string_array_itr_new( example )),"example for problem 18");
    checkanswer(7273,tri_max(file_itr_new(fopen("67.txt","r"))),"problem 67")
    return 0;
}

