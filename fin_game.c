#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DOLLAR 80;
#define EURO 90;
#define RUBBLE 1;
#define DOLLAR_SIGN '$';
#define EURO_SIGN 'Є';
#define RUBBLE_SIGN '₽';

struct User
{
    char name[100];
    char currency;
    struct Progress
    {
        int balance;
        int days;
    } progress;
    struct Date{
        unsigned short day;
        unsigned short month;
        unsigned short year;
    } date;
    
};

void help(void) {
    printf("This is a 365 financial challenge!\n");
    printf("It will help you to save some money for a purchase\n");
    printf("or an emergency fund. You can save in three currencies:\n");
    printf("rubbles, dollars, euros. The rules are simple:\n");
    printf("Put money away every day until a year has passed\n");
    printf("You should deposit money according to the number of day you are on.\n");
    printf("It may be more but not less. Lastly, you should not withdraw your money,\n");
    printf("unless there is a great need to. However, mind the consequences!\n");
    printf("Good luck on your financial journey!!!\n\n");
}

struct User fill_info_ab_user(char user_name[100], char user_curr, int user_balance, int user_days, short user_start_day,
short user_start_month, short user_start_year){
    struct User user;
    strcpy(user.name, user_name);
    user.currency = user_curr;
    user.progress.balance = user_balance;
    user.progress.days = user_days;
    user.date.day = user_start_day;
    user.date.month = user_start_month;
    user.date.year = user_start_year;
    return user;
}

void print_user_info(struct User user_struct){
    printf("Name of the player: %s\n", user_struct.name);
    printf("Savings currency: %c\n", user_struct.currency);
    printf("Amount of savings: %d\n", user_struct.progress.balance);
    printf("The date of the beginning of the game: %hu/%hu/%hu\n", user_struct.date.day, user_struct.date.month, user_struct.date.year);
    printf("The progress of the journey: %d out of 365 days\n\n", user_struct.progress.days);

}

void save_progress(struct User user){
    FILE *fp;
    char filename[255];
    sprintf(filename, "%s_fin_progress.txt", user.name);
    fp = fopen(filename, "w+");
    fprintf(fp, "Name: %s\n", user.name);
    fprintf(fp, "Saving currency: %c\n", user.currency);
    fprintf(fp, "Current balance: %d\n", user.progress.balance);
    fprintf(fp, "Progress: %d out of 365 days\n", user.progress.days);
    fprintf(fp, "Starting date: %hu/%hu/%hu", user.date.day, user.date.month, user.date.year);
    fclose(fp);
    printf("File was created and saved!\n");
}


int main() {
    //help(); help func
    time_t t = time(NULL);
    struct tm time_data = *localtime(&t);
    short curr_day = time_data.tm_mday;
    short curr_month = 1+time_data.tm_mon;
    short curr_year = 1900+time_data.tm_year;
    struct User test_user;
    char name[100] = "Jake";
    char currency = DOLLAR_SIGN;
    int balance = 0;
    int days = 0;
    test_user = fill_info_ab_user(name, currency, balance, days, curr_day, curr_month, curr_year);
    print_user_info(test_user);
    save_progress(test_user);
    return 0;
}