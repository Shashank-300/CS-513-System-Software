#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define Admin structure
struct Admin {
    int adminID;
    char name[50];
    char password[50];
};

// Function to load admin from file
int load_admin(int adminID, struct Admin *admin) {
    FILE *admin_file = fopen("admin.txt", "rb");
    if (admin_file == NULL) {
        printf("Error opening admin.txt file.\n");
        return 0;
    }

    // Search for the admin by adminID
    while (fread(admin, sizeof(struct Admin), 1, admin_file)) {
        if (admin->adminID == adminID) {
            fclose(admin_file);
            return 1;  // Admin found
        }
    }

    fclose(admin_file);
    return 0;  // Admin not found
}

// Function to validate admin login
int validate_admin_login(int adminID, char *password) {
    struct Admin admin;
    if (load_admin(adminID, &admin)) {
        if (strcmp(admin.password, password) == 0) {
            return 1;  // Login successful
        } else {
            printf("Invalid password.\n");
            return 0;  // Invalid password
        }
    } else {
        printf("Admin not found.\n");
        return 0;  // Admin not found
    }
}

int main() {
    struct Admin admin;
    int adminID;
    char password[50];

    // Example prompt for admin login
    printf("Enter Admin ID: ");
    scanf("%d", &adminID);

    printf("Enter Password: ");
    scanf("%s", password);

    // Validate admin login
    if (validate_admin_login(adminID, password)) {
        printf("Admin logged in successfully!\n");
        // Call the admin menu here
    } else {
        printf("Login failed.\n");
    }

    return 0;
}
