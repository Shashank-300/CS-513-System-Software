#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "accounts.h" // Include the account structure and related functions

void send_employee_menu(int client_sock);

#endif // EMPLOYEE_H
