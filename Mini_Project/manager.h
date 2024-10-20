#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "accounts.h" // Include the account structure and related functions

void send_manager_menu(int client_sock);

#endif // MANAGER_H
