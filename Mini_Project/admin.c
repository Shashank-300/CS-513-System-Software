#include "admin.h"

void send_admin_menu(int client_sock) {
    char menu[] = "\nAdmin Menu:\n1. Add New Employee\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}
