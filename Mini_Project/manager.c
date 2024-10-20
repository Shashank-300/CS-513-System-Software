#include "manager.h"

void send_manager_menu(int client_sock) {
    char menu[] = "\nManager Menu:\n1. Activate/Deactivate Customer Accounts\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}
