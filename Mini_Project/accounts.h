#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int account_id;
    char username[50];
    char password[50];
    double balance;
} Account;

void initialize_accounts();
int login(int client_sock, const char *role);
void view_balance(int client_sock, int account_id);
void deposit_money(int client_sock, int account_id, double amount);

#endif // ACCOUNT_H
