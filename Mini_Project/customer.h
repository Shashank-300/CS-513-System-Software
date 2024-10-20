#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "accounts.h" // Include the account structure and related functions

void send_customer_menu(int client_sock);
void view_balance(int client_sock, int account_id);
void deposit_money(int client_sock, int account_id, double amount);

#endif // CUSTOMER_H
