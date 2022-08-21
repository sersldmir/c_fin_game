#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



int main() {
    // char *str_point = NULL;
    // char file_name[8] = "hey.txt";
    // printf("The string: %s\n", file_name);
    // str_point = file_name;
    // printf("The first symbol: %c\n", *str_point);
    // printf("The second symbol: %c\n", *(str_point+1));
    // printf("The third symbol: %c\n", *(str_point+2));
    // printf("The fourth symbol: %c\n", *(str_point+3));
    // printf("The fifth symbol: %c\n", *(str_point+4));
    // printf("The sixth symbol: %c\n", *(str_point+5));
    // printf("The seventh symbol: %c\n", *(str_point+6));
    // printf("The whole string: %s\n", str_point);
    // char num_str[]="234";
    // int num_int = atoi(num_str);
    // printf("String num: %s\nInteger: %d\n", num_str, num_int);
    int day1, mon1, year1,
        day2, mon2, year2;

    int day_diff, mon_diff, year_diff;
    
    day1 = 20;
    day2 = 19;
    mon1 = 8;
    mon2 = 8;
    year1 = 2021;
    year2 = 2022;


    if(day2 < day1)
    {      
        // borrow days from february
        if (mon2 == 3)
        {
            //  check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) 
            {
                day2 += 29;
            }

            else
            {
                day2 += 28;
            }                        
        }

        // borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) 
        {
           day2 += 30; 
        }

        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }       

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;

    printf("The difference is %d days, %d months and %d years\n", day_diff, mon_diff, year_diff);
    return 0;
}