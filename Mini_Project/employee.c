#include "employee.h"

void send_employee_menu(int client_sock) {
    char menu[] = "\nEmployee Menu:\n1. Add New Customer\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}
