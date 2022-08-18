#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



int main() {
    char *str_point = NULL;
    char file_name[8] = "hey.txt";
    printf("The string: %s\n", file_name);
    str_point = file_name;
    printf("The first symbol: %c\n", *str_point);
    printf("The second symbol: %c\n", *(str_point+1));
    printf("The third symbol: %c\n", *(str_point+2));
    printf("The fourth symbol: %c\n", *(str_point+3));
    printf("The fifth symbol: %c\n", *(str_point+4));
    printf("The sixth symbol: %c\n", *(str_point+5));
    printf("The seventh symbol: %c\n", *(str_point+6));
    printf("The whole string: %s\n", str_point);
    return 0;
}