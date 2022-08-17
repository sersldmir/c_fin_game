#include <stdio.h>
#include <string.h>

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
    
};

void help(void) {
    printf("This is a 365 financial challenge!\n");
    printf("It will help you to save some money for a purchase\n");
    printf("or an emergency fund. You can save in three currencies:\n");
    printf("rubbles, dollars, euros. The rules are simple:\n");
    printf("Put money away every day until a year has passed\n");
    printf("You should deposit money according to the number of day you are on.\n");
    printf("It may be more but not less. Lastly, you should not withdraw your money,\n");
    printf("unless there is a great need to. If you do this, your progress will be\n");
    printf("decreased. Good luck on your financial journey!!!\n\n");
}

struct User fill_info_ab_user(char user_name[100], char user_curr, int user_balance, int user_days){
    struct User user;
    strcpy(user.name, user_name);
    user.currency = user_curr;
    user.progress.balance = user_balance;
    user.progress.days = user_days;
    return user;
}

void print_user_info(struct User user_struct){
    printf("Name of the player: %s\n", user_struct.name);
    printf("Savings currency: %c\n", user_struct.currency);
    printf("Amount of savings: %d\n", user_struct.progress.balance);
    printf("The progress of the journey: %d out of 365\n\n", user_struct.progress.days);

}

void save_progress(struct User user){
    
}


int main() {
    //help(); help func
    struct User test_user;
    char name[100] = "Jake";
    char currency = DOLLAR_SIGN;
    int balance = 0;
    int days = 0;
    test_user = fill_info_ab_user(name, currency, balance, days);
    print_user_info(test_user);
    return 0;
}