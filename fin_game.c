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

struct Last_tr{
    int l_day;
    int l_month;
    int l_year;
};

struct User{
    char name[100];
    char currency[10];
    struct Progress *progress;
    struct Date *date;
    struct Last_tr *last_tr;
    
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

void create_user(struct User * user_info, struct Progress * progress_info, struct Date * date_info, struct Last_tr * l_tr_info){
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
    char name[100];
    printf("What's your name?\n");
    scanf("%s", name);
    printf("\n");
    strcpy(user_info->name, name);
    char cur[10];
    while (1){
        printf("In what currency are you going to save?\n");
        printf("Supported: dollar, euro, rubble\n");
        scanf("%s", cur);
        printf("\n");
        if ((strcmp(cur, dol)==0) || (strcmp(cur, eur)==0)|| (strcmp(cur, rub)==0)){
            break;
        }
        else{
            printf("Not supported!\n");
        }
    }
    if (strcmp(cur, dol)==0) {
        strcpy(user_info->currency, dol);
    }
    else if(strcmp(cur, eur)==0){
        strcpy(user_info->currency, eur);
    }
    else if(strcmp(cur, rub)==0){
        strcpy(user_info->currency, rub);
    }
    l_tr_info->l_day = 0;
    l_tr_info->l_month = 0;
    l_tr_info->l_year = 0;
    user_info->progress = progress_info;
    user_info->date = date_info;
    user_info->last_tr = l_tr_info;
    printf("New user has been created!\n");
}

void load_user(char * file_name, struct User * user_info, struct Progress * progress_info, struct Date * date_info, struct Last_tr * l_tr_info){
    // initializing
    const char dol[] = "dollar";
    const char eur[] = "euro";
    const char rub[] = "rubble";
    FILE *file_with_save;
    file_with_save = fopen(file_name, "r");
    if (file_with_save==NULL){
        printf("NOT FOUND!");
        exit(EXIT_FAILURE);
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
    user_info->last_tr = l_tr_info;
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
                exit(EXIT_FAILURE);
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
        else if (strcmp(head_token, "Last transaction day")==0){
            user_info->last_tr->l_day = atoi(value_token);
        }
        else if (strcmp(head_token, "Last transaction month")==0){
            user_info->last_tr->l_month = atoi(value_token);
        }
        else if (strcmp(head_token, "Last transaction year")==0){
            user_info->last_tr->l_year = atoi(value_token);
        }
        else{
            printf("Loading went wrong!");
            exit(EXIT_FAILURE);
        }
        c_sleep();
        printf("\n");
    }
    printf("Loading successful!!! Welcome back!\n");
    printf("\n");
}


void print_user_info(struct User * user_struct){
    printf("The info:\n");
    printf("Name of the player: %s\n", user_struct->name);
    printf("Savings currency: %s\n", user_struct->currency);
    printf("Amount of savings: %d\n", user_struct->progress->balance);
    printf("The date of the beginning of the game: %d/%d/%d\n", user_struct->date->day, user_struct->date->month, user_struct->date->year);
    printf("The date of the last transaction: %d/%d/%d\n", user_struct->last_tr->l_day, user_struct->last_tr->l_month, user_struct->last_tr->l_year);
    printf("The progress of the journey: %d out of 365 days\n\n", user_struct->progress->days);

}

void save_progress(struct User * user){
    FILE *fp;
    char filename[255];
    sprintf(filename, "%s_fin_progress.csv", user->name);
    fp = fopen(filename, "w+");
    fprintf(fp, "Name;Saving currency;Current balance;Progress (out of 365 days);Starting day;Starting month;Starting year;Last transaction day;Last transaction month;Last transaction year;\n");
    fprintf(fp, "%s;%s;%d;%d;%d;%d;%d;%d;%d;%d", user->name, user->currency, user->progress->balance, user->progress->days, user->date->day, user->date->month, user->date->year, user->last_tr->l_day, user->last_tr->l_month, user->last_tr->l_year);
    fclose(fp);
    printf("Progress saved!\n");
}

void update_user(struct User * user){

}



int main() {
    // initializing pointers
    struct User* st_ptr = NULL;
    struct Progress* pr_ptr = NULL;
    struct Date* date_ptr = NULL;
    struct Last_tr* l_tr_ptr = NULL; 
    struct Date dat;
    date_ptr = &dat;
    struct Progress pr;
    pr_ptr = &pr;
    struct User test_user;
    st_ptr = &test_user;
    struct Last_tr l_tr;
    l_tr_ptr = &l_tr;
    //the game itself
    while (1) {
        printf("Would you like to load the saved progress or create a new user?\n");
        char answer[255];
        printf("Type 'create' or 'load'\n");
        scanf("%s", answer);
        if ((strcmp(answer, "create")==0) || (strcmp(answer, "load")==0)){
            if (strcmp(answer, "create")==0) {
                create_user(st_ptr, pr_ptr, date_ptr, l_tr_ptr);
                break;
                }   
            if (strcmp(answer, "load")==0) {
                char file_name[255];
                printf("Insert the full name of the file\n");
                scanf("%s", file_name);
                load_user(file_name, st_ptr, pr_ptr, date_ptr, l_tr_ptr);
                break;
                }
        }
        else{
            printf("Wrong answer!\n");
        }
    }
    while (1) {
        printf("Now that youn are loaded in, you have 2 options:\n");
        printf("1) Update your progress\n");
        printf("2) Save and exit\n");
        printf("3) Help\n");
        printf("4) Print info\n");
        char ans_num[3];
        while(1){
            printf("Insert the number of option below\n");
            scanf("%s", ans_num);
            if (strcmp(ans_num, "1")==0 || strcmp(ans_num, "2")==0 || strcmp(ans_num, "3")==0 || strcmp(ans_num, "4")==0){
                printf("\n");
                break;
            }
            else{
                printf("Wrong choice!!");
            }
        }
        if (strcmp(ans_num, "1")==0){
            update_user(st_ptr);
            c_sleep();
            printf("\n");
        }
        if (strcmp(ans_num, "2")==0){
            save_progress(st_ptr);
            c_sleep();
            break;
        }
        if (strcmp(ans_num, "3")==0){
            help();
            c_sleep();
            printf("\n");
        }
        if (strcmp(ans_num, "4")==0){
            print_user_info(st_ptr);
            c_sleep();
            printf("\n");
        }
    }
    //functions
    // help();
    // create_user(st_ptr, pr_ptr, date_ptr);
    // print_user_info(st_ptr);
    //load func
    // char file_n[]="Jake_fin_progress.csv";
    // load_user(file_n, st_ptr, pr_ptr, date_ptr);
    // print_user_info(st_ptr);
    return 0;
}