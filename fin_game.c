#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef __unix__
    #include <unistd.h>
    #define ON_LINUX 1
#else
    #include <windows.h>
    #define ON_WINDOWS 1
#endif





#define DOLLAR 80
#define EURO 90
#define RUBBLE 1

struct Progress{
    int balance;
    int days;
};

struct Date{
    int day;
    int month;
    int year;
};

struct User{
    char name[100];
    char currency[10];
    struct Progress *progress;
    struct Date *date;
    
};

void c_sleep(){
    #ifdef ON_LINUX
        sleep(1);
    #endif
    #ifdef ON_WINDOWS
        Sleep(1000);
    #endif
}

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

void create_user(struct User * user_info, struct Progress * progress_info, struct Date * date_info){
    // filling date info
    const char dol[] = "dollar";
    const char eur[] = "euro";
    const char rub[] = "rubble";
    time_t t = time(NULL);
    struct tm time_data = *localtime(&t);
    short curr_day = time_data.tm_mday;
    short curr_month = 1+time_data.tm_mon;
    short curr_year = 1900+time_data.tm_year;
    date_info->day = curr_day;
    date_info->month = curr_month;
    date_info->year = curr_year;
    // filling progress info
    int balance = 0;
    int days = 0;
    progress_info->balance = balance;
    progress_info->days = days;
    // filling user info
    char name[100] = "Jake";
    strcpy(user_info->name, name);
    strcpy(user_info->currency, dol);
    user_info->progress = progress_info;
    user_info->date = date_info;
}

void load_user(char * file_name, struct User * user_info, struct Progress * progress_info, struct Date * date_info){
    // initializing
    const char dol[] = "dollar";
    const char eur[] = "euro";
    const char rub[] = "rubble";
    FILE *file_with_save;
    file_with_save = fopen(file_name, "r");
    if (file_with_save==NULL){
        printf("NOT FOUND!");
        exit(1);
    }
    char contents[2][255];
    int i = 0;
    printf("Reading...\n");
    //reading from a file
    while (!feof(file_with_save) && i<2){
        fgets(contents[i], 255, file_with_save);
        ++i;
    }
    // printing contents
    // for (i=0; i<2; ++i){
    //     printf("%s", contents[i]);
    //     if (i==1){
    //         printf("\n");
    //     }
    // }
    printf("\n");
    // putting values into structs
    char *headers = strdup(contents[0]);
    char *values = strdup(contents[1]);
    char *head_token, *value_token;
    char *the_rest_headers, *the_rest_values;
    the_rest_headers = headers;
    the_rest_values = values;
    user_info->progress = progress_info;
    user_info->date = date_info;
    while ((head_token = strtok_r(the_rest_headers, ";", &the_rest_headers)) && (value_token = strtok_r(the_rest_values, ";", &the_rest_values))){
        printf("Header: %s\nValue: %s\n", head_token, value_token);
        if (strcmp(head_token,"Name")==0){
            strcpy(user_info->name, value_token);
        }
        else if (strcmp(head_token, "Saving currency")==0){
            if (strcmp(value_token, dol)==0 || strcmp(value_token, eur)==0 || strcmp(value_token, rub)==0 ){
                strcpy(user_info->currency, value_token);
            }
            else{
                printf("Loading went wrong!");
                exit(1);
            }
        }
        else if (strcmp(head_token, "Current balance")==0){
            user_info->progress->balance = atoi(value_token);
        }
        else if (strcmp(head_token, "Progress (out of 365 days)")==0){
            user_info->progress->days = atoi(value_token);
        }
        else if (strcmp(head_token, "Starting day")==0){
            user_info->date->day = atoi(value_token);
        }
        else if (strcmp(head_token, "Starting month")==0){
            user_info->date->month = atoi(value_token);
        }
        else if (strcmp(head_token, "Starting year")==0){
            user_info->date->year = atoi(value_token);
        }
        else{
            printf("Loading went wrong!");
            exit(1);
        }
        c_sleep();
        printf("\n");
    }
    printf("Loading successful!!! Welcome back!\n");
}


void print_user_info(struct User * user_struct){
    printf("Name of the player: %s\n", user_struct->name);
    printf("Savings currency: %s\n", user_struct->currency);
    printf("Amount of savings: %d\n", user_struct->progress->balance);
    printf("The date of the beginning of the game: %d/%d/%d\n", user_struct->date->day, user_struct->date->month, user_struct->date->year);
    printf("The progress of the journey: %d out of 365 days\n\n", user_struct->progress->days);

}

void save_progress(struct User * user){
    FILE *fp;
    char filename[255];
    sprintf(filename, "%s_fin_progress.csv", user->name);
    fp = fopen(filename, "w+");
    fprintf(fp, "Name;Saving currency;Current balance;Progress (out of 365 days);Starting day;Starting month;Starting year;\n");
    fprintf(fp, "%s;%s;%d;%d;%hu;%hu;%hu", user->name, user->currency, user->progress->balance, user->progress->days, user->date->day, user->date->month, user->date->year);
    fclose(fp);
    printf("File was created and saved!\n");
}



int main() {
    // initializing pointers
    struct User* st_ptr = NULL;
    struct Progress* pr_ptr = NULL;
    struct Date* date_ptr = NULL;
    struct Date dat;
    date_ptr = &dat;
    struct Progress pr;
    pr_ptr = &pr;
    struct User test_user;
    st_ptr = &test_user;
    //functions
    // help();
    // create_user(st_ptr, pr_ptr, date_ptr);
    // print_user_info(st_ptr);
    // save_progress(st_ptr);
    //load func
    char file_n[]="Jake_fin_progress.csv";
    char *f_ptr = file_n;
    load_user(file_n, st_ptr, pr_ptr, date_ptr);
    print_user_info(st_ptr);
    return 0;
}