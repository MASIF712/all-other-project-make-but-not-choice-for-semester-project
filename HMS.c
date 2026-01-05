#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

#define MAX_ROOMS 100
#define MAX_FOOD_ITEMS 50
#define MAX_GUESTS 200
#define ADMIN_USER "admin"
#define ADMIN_PASS "admin123"
#define HOTEL_NAME "GRAND LUXURY HOTEL 2026"

typedef struct {
    int id;
    char name[50];
    float price;
    int available; 
} FoodItem;

typedef struct {
    int room_number;
    char type[30]; 
    float rate_per_hour;
    int status; 
    char guest_id[30]; 
} Room;

typedef struct {
    char id[30];
    char name[50];
    char phone[20];
    char email[50];
    char address[100];
    char nationality[30];
    char cnic[30];
    int is_premium; 
    char password[30];
    float balance; 
    int room_assigned;
    time_t check_in_time;
} Guest;

Room rooms[MAX_ROOMS];
int room_count = 0;
FoodItem menu[MAX_FOOD_ITEMS];
int food_count = 0;
Guest guests[MAX_GUESTS];
int guest_count = 0;

void mainMenu();
void adminLogin();
void guestLogin();
void adminDashboard();
void guestDashboard(int g_idx);
void manageRooms();
void manageFoodMenu();
void manageGuests();
void viewRecords();
void addRoom();
void deleteRoom();
void editRoom();
void addFood();
void deleteFood();
void editFood();
void bookRoom(int g_idx);
void orderFood(int g_idx);
void viewAvailableRooms();
void viewBill(int g_idx);
void checkout(int g_idx);
void clearScreen();
void printHeader(const char* title);
void saveRooms();
void loadRooms();
void saveFood();
void loadFood();
void saveGuests();
void loadGuests();
void logHistory(const char* message);
void generatePassword(char* id, char* password);
void sendNotification(Guest g, const char* message);
void getString(char* buffer, int size);
void getCurrentDateTime(char* buffer);

int main() {
    loadRooms();
    loadFood();
    loadGuests();
    mainMenu();
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void getCurrentDateTime(char* buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", t);
}

void printHeader(const char* title) {
    char dt[50];
    getCurrentDateTime(dt);
    printf(CYAN "====================================================================\n" RESET);
    printf(BOLD YELLOW "            %s\n" RESET, HOTEL_NAME);
    printf(CYAN "            %s\n" RESET, dt);
    printf(CYAN "--------------------------------------------------------------------\n" RESET);
    printf(BOLD MAGENTA "            %s\n" RESET, title);
    printf(CYAN "====================================================================\n" RESET);
}

void getString(char* buffer, int size) {
    fflush(stdin);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void generatePassword(char* id, char* password) {
    srand(time(NULL));
    int random_num = rand() % 9000 + 1000;
    sprintf(password, "%s%d", id, random_num);
}

void sendNotification(Guest g, const char* message) {
    printf(MAGENTA "\n[NOTIFICATION SENT TO %s (%s)]\n" RESET, g.name, g.phone);
    printf("Message: %s\n", message);
    printf("Sent via: WhatsApp, SMS, Email\n");
    sleep(1);
}

void logHistory(const char* message) {
    FILE *fp = fopen("history.txt", "a");
    if (fp) {
        char dt[50];
        getCurrentDateTime(dt);
        fprintf(fp, "[%s] %s\n", dt, message);
        fclose(fp);
    }
}

void saveRooms() {
    FILE *fp = fopen("rooms.txt", "w");
    if (fp) {
        fprintf(fp, "%d\n", room_count);
        for(int i=0; i<room_count; i++) {
            fprintf(fp, "%d|%s|%.2f|%d|%s\n", 
                rooms[i].room_number, rooms[i].type, rooms[i].rate_per_hour, 
                rooms[i].status, rooms[i].guest_id[0] == '\0' ? "NONE" : rooms[i].guest_id);
        }
        fclose(fp);
    }
}

void loadRooms() {
    FILE *fp = fopen("rooms.txt", "r");
    if (fp) {
        fscanf(fp, "%d\n", &room_count);
        for(int i=0; i<room_count; i++) {
            char gid[30];
            fscanf(fp, "%d|%[^|]|%f|%d|%s\n", 
                &rooms[i].room_number, rooms[i].type, &rooms[i].rate_per_hour, 
                &rooms[i].status, gid);
            if(strcmp(gid, "NONE") == 0) rooms[i].guest_id[0] = '\0';
            else strcpy(rooms[i].guest_id, gid);
        }
        fclose(fp);
    } else {
        room_count = 5;
        rooms[0] = (Room){101, "Single Luxury", 15.0, 0, ""};
        rooms[1] = (Room){102, "Double Executive", 25.0, 0, ""};
        rooms[2] = (Room){201, "Royal Suite", 60.0, 0, ""};
        rooms[3] = (Room){202, "Deluxe Family", 45.0, 0, ""};
        rooms[4] = (Room){301, "Presidential Penthouse", 150.0, 0, ""};
        saveRooms();
    }
}

void saveFood() {
    FILE *fp = fopen("food.txt", "w");
    if (fp) {
        fprintf(fp, "%d\n", food_count);
        for(int i=0; i<food_count; i++) {
            fprintf(fp, "%d|%s|%.2f|%d\n", menu[i].id, menu[i].name, menu[i].price, menu[i].available);
        }
        fclose(fp);
    }
}

void loadFood() {
    FILE *fp = fopen("food.txt", "r");
    if (fp) {
        fscanf(fp, "%d\n", &food_count);
        for(int i=0; i<food_count; i++) {
            fscanf(fp, "%d|%[^|]|%f|%d\n", &menu[i].id, menu[i].name, &menu[i].price, &menu[i].available);
        }
        fclose(fp);
    } else {
        food_count = 25;
        char* names[] = {"Zinger Burger", "Pepperoni Pizza", "Alfredo Pasta", "Ribeye Steak", "Greek Salad", "Tomato Soup", "French Fries", "Coca Cola", "Green Tea", "Cappuccino", 
                         "Club Sandwich", "Cheese Omelette", "Blueberry Pancakes", "Salmon Sushi", "Beef Tacos", "Spicy Noodles", "Fried Rice", "Grilled Chicken", "Fish & Chips", "Vanilla Ice Cream",
                         "Chocolate Cake", "Orange Juice", "Strawberry Milkshake", "Mineral Water", "Fresh Fruit Bowl"};
        float prices[] = {6.5, 14.0, 10.0, 30.0, 7.5, 5.0, 4.0, 2.5, 2.0, 3.5, 
                          8.5, 5.5, 7.5, 18.0, 10.0, 9.5, 6.5, 15.0, 16.0, 5.0, 
                          6.0, 4.5, 6.5, 1.5, 8.0};
        for(int i=0; i<25; i++) {
            menu[i].id = i+1;
            strcpy(menu[i].name, names[i]);
            menu[i].price = prices[i];
            menu[i].available = 1;
        }
        saveFood();
    }
}

void saveGuests() {
    FILE *fp = fopen("guests.txt", "w");
    if (fp) {
        fprintf(fp, "%d\n", guest_count);
        for(int i=0; i<guest_count; i++) {
            fprintf(fp, "%s|%s|%s|%s|%s|%s|%s|%d|%s|%.2f|%d|%ld\n", 
                guests[i].id, guests[i].name, guests[i].phone, guests[i].email, 
                guests[i].address, guests[i].nationality, guests[i].cnic, 
                guests[i].is_premium, guests[i].password, guests[i].balance, 
                guests[i].room_assigned, guests[i].check_in_time);
        }
        fclose(fp);
    }
}

void loadGuests() {
    FILE *fp = fopen("guests.txt", "r");
    if (fp) {
        fscanf(fp, "%d\n", &guest_count);
        for(int i=0; i<guest_count; i++) {
            fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%f|%d|%ld\n", 
                guests[i].id, guests[i].name, guests[i].phone, guests[i].email, 
                guests[i].address, guests[i].nationality, guests[i].cnic, 
                &guests[i].is_premium, guests[i].password, &guests[i].balance, 
                &guests[i].room_assigned, &guests[i].check_in_time);
        }
        fclose(fp);
    } else {
        guest_count = 0;
    }
}

void mainMenu() {
    int choice;
    while (1) {
        clearScreen();
        printHeader("WELCOME TO THE MAIN PORTAL");
        printf(BLUE "1. " RESET "Admin Management Login\n");
        printf(BLUE "2. " RESET "Guest Services Login\n");
        printf(RED "3. " RESET "Exit System\n");
        printf(YELLOW "\nSelect an option: " RESET);
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: guestLogin(); break;
            case 3: 
                saveRooms();
                saveFood();
                saveGuests();
                printf(GREEN "Allah hafiz. Goodbye!\n" RESET);
                exit(0);
            default: printf(RED "Invalid selection!\n" RESET); sleep(1);
        }
    }
}

void adminLogin() {
    char user[30], pass[30];
    clearScreen();
    printHeader("ADMINISTRATOR AUTHENTICATION");
    printf(CYAN "Username: " RESET); getString(user, 30);
    printf(CYAN "Password: " RESET); getString(pass, 30);

    if (strcmp(user, ADMIN_USER) == 0 && strcmp(pass, ADMIN_PASS) == 0) {
        printf(GREEN "\nAccess Granted. Welcome, Administrator.\n" RESET);
        logHistory("Admin logged in successfully.");
        sleep(1);
        adminDashboard();
    } else {
        printf(RED "\nAccess Denied. Invalid Credentials.\n" RESET);
        logHistory("Failed admin login attempt.");
        sleep(1);
    }
}

void guestLogin() {
    char user[50], pass[30];
    clearScreen();
    printHeader("GUEST SERVICES AUTHENTICATION");
    printf(CYAN "Username (Full Name): " RESET); getString(user, 50);
    printf(CYAN "Password: " RESET); getString(pass, 30);

    int found = -1;
    for (int i = 0; i < guest_count; i++) {
        if (strcmp(guests[i].name, user) == 0 && strcmp(guests[i].password, pass) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf(GREEN "\nWelcome back, %s!\n" RESET, guests[found].name);
        char logMsg[100];
        sprintf(logMsg, "Guest %s logged in.", guests[found].name);
        logHistory(logMsg);
        sleep(1);
        guestDashboard(found);
    } else {
        printf(RED "\nInvalid Name or Password. Please contact the front desk.\n" RESET);
        sleep(1);
    }
}

void adminDashboard() {
    int choice;
    while (1) {
        clearScreen();
        printHeader("ADMINISTRATIVE CONTROL PANEL");
        printf(BLUE "1. " RESET "Room Inventory Management\n");
        printf(BLUE "2. " RESET "Cuisine & Menu Management\n");
        printf(BLUE "3. " RESET "Guest Registration & Records\n");
        printf(BLUE "4. " RESET "View System History Log\n");
        printf(RED "5. " RESET "Logout\n");
        printf(YELLOW "\nEnter choice: " RESET);
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: manageRooms(); break;
            case 2: manageFoodMenu(); break;
            case 3: manageGuests(); break;
            case 4: viewRecords(); break;
            case 5: return;
            default: printf(RED "Invalid choice!\n" RESET); sleep(1);
        }
    }
}

void manageRooms() {
    int choice;
    while (1) {
        clearScreen();
        printHeader("ROOM INVENTORY MANAGEMENT");
        printf("1. View All Rooms Status\n");
        printf("2. Add New Room\n");
        printf("3. Modify Room Details\n");
        printf("4. Remove Room\n");
        printf("5. Back to Dashboard\n");
        printf(YELLOW "\nEnter choice: " RESET);
        scanf("%d", &choice);
        getchar();

        if (choice == 5) break;
        
        switch (choice) {
            case 1:
                printf("\n%-10s %-25s %-15s %-15s %-15s\n", "Room No", "Type", "Rate/Hr", "Status", "Guest ID");
                printf("--------------------------------------------------------------------------------\n");
                for(int i=0; i<room_count; i++) {
                    printf("%-10d %-25s %-15.2f %-15s %-15s\n", 
                        rooms[i].room_number, rooms[i].type, rooms[i].rate_per_hour, 
                        rooms[i].status ? RED "BOOKED" RESET : GREEN "AVAILABLE" RESET, 
                        rooms[i].status ? rooms[i].guest_id : "N/A");
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 2: addRoom(); break;
            case 3: editRoom(); break;
            case 4: deleteRoom(); break;
        }
    }
}

void addRoom() {
    if (room_count >= MAX_ROOMS) {
        printf(RED "Inventory full!\n" RESET);
        return;
    }
    Room r;
    printf("Enter Room Number: "); scanf("%d", &r.room_number); getchar();
    printf("Enter Room Type: "); getString(r.type, 30);
    printf("Enter Hourly Rate: "); scanf("%f", &r.rate_per_hour); getchar();
    r.status = 0;
    r.guest_id[0] = '\0';
    rooms[room_count++] = r;
    saveRooms();
    char logMsg[100];
    sprintf(logMsg, "New room %d added to inventory.", r.room_number);
    logHistory(logMsg);
    printf(GREEN "Room added successfully!\n" RESET);
    sleep(1);
}

void editRoom() {
    int rno, found = 0;
    printf("Enter Room Number to modify: "); scanf("%d", &rno); getchar();
    for(int i=0; i<room_count; i++) {
        if(rooms[i].room_number == rno) {
            printf("Enter New Type: "); getString(rooms[i].type, 30);
            printf("Enter New Hourly Rate: "); scanf("%f", &rooms[i].rate_per_hour); getchar();
            found = 1;
            break;
        }
    }
    if(found) {
        saveRooms();
        printf(GREEN "Room details updated!\n" RESET);
    } else printf(RED "Room not found!\n" RESET);
    sleep(1);
}

void deleteRoom() {
    int rno, found = 0;
    printf("Enter Room Number to remove: "); scanf("%d", &rno); getchar();
    for(int i=0; i<room_count; i++) {
        if(rooms[i].room_number == rno) {
            for(int j=i; j<room_count-1; j++) rooms[j] = rooms[j+1];
            room_count--;
            found = 1;
            break;
        }
    }
    if(found) {
        saveRooms();
        printf(GREEN "Room removed from inventory!\n" RESET);
    } else printf(RED "Room not found!\n" RESET);
    sleep(1);
}

void manageFoodMenu() {
    int choice;
    while (1) {
        clearScreen();
        printHeader("CUISINE & MENU MANAGEMENT");
        printf("1. View Current Menu\n");
        printf("2. Add New Dish\n");
        printf("3. Edit Dish Details\n");
        printf("4. Remove Dish\n");
        printf("5. Back to Dashboard\n");
        printf(YELLOW "\nEnter choice: " RESET);
        scanf("%d", &choice);
        getchar();

        if (choice == 5) break;

        switch (choice) {
            case 1:
                printf("\n%-5s %-30s %-15s %-15s\n", "ID", "Dish Name", "Price", "Availability");
                printf("---------------------------------------------------------------------\n");
                for(int i=0; i<food_count; i++) {
                    printf("%-5d %-30s %-15.2f %-15s\n", 
                        menu[i].id, menu[i].name, menu[i].price, 
                        menu[i].available ? GREEN "YES" RESET : RED "NO" RESET);
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 2: addFood(); break;
            case 3: editFood(); break;
            case 4: deleteFood(); break;
        }
    }
}

void addFood() {
    if (food_count >= MAX_FOOD_ITEMS) {
        printf(RED "Menu is full!\n" RESET);
        return;
    }
    FoodItem f;
    f.id = food_count + 1;
    printf("Enter Dish Name: "); getString(f.name, 50);
    printf("Enter Price: "); scanf("%f", &f.price); getchar();
    f.available = 1;
    menu[food_count++] = f;
    saveFood();
    printf(GREEN "Dish added to menu!\n" RESET);
    sleep(1);
}

void editFood() {
    int fid, found = 0;
    printf("Enter Dish ID to edit: "); scanf("%d", &fid); getchar();
    for(int i=0; i<food_count; i++) {
        if(menu[i].id == fid) {
            printf("Enter New Name: "); getString(menu[i].name, 50);
            printf("Enter New Price: "); scanf("%f", &menu[i].price);
            printf("Available? (1:Yes, 0:No): "); scanf("%d", &menu[i].available); getchar();
            found = 1;
            break;
        }
    }
    if(found) {
        saveFood();
        printf(GREEN "Menu updated!\n" RESET);
    } else printf(RED "Dish not found!\n" RESET);
    sleep(1);
}

void deleteFood() {
    int fid, found = 0;
    printf("Enter Dish ID to remove: "); scanf("%d", &fid); getchar();
    for(int i=0; i<food_count; i++) {
        if(menu[i].id == fid) {
            for(int j=i; j<food_count-1; j++) menu[j] = menu[j+1];
            food_count--;
            found = 1;
            break;
        }
    }
    if(found) {
        saveFood();
        printf(GREEN "Dish removed from menu!\n" RESET);
    } else printf(RED "Dish not found!\n" RESET);
    sleep(1);
}

void manageGuests() {
    int choice;
    while (1) {
        clearScreen();
        printHeader("GUEST REGISTRATION & RECORDS");
        printf("1. View Registered Guests\n");
        printf("2. Register New Guest\n");
        printf("3. Back to Dashboard\n");
        printf(YELLOW "\nEnter choice: " RESET);
        scanf("%d", &choice);
        getchar();

        if (choice == 3) break;

        if (choice == 1) {
            printf("\n%-15s %-25s %-15s %-10s %-10s\n", "ID", "Full Name", "Phone", "Room", "Balance");
            printf("-------------------------------------------------------------------------------\n");
            for(int i=0; i<guest_count; i++) {
                printf("%-15s %-25s %-15s %-10d %-10.2f\n", 
                    guests[i].id, guests[i].name, guests[i].phone, 
                    guests[i].room_assigned, guests[i].balance);
            }
            printf("\nPress Enter to continue...");
            getchar();
        } else if (choice == 2) {
            if (guest_count >= MAX_GUESTS) {
                printf(RED "Guest capacity reached!\n" RESET);
                continue;
            }
            Guest g;
            printf("Enter Unique ID (Passport/CNIC): "); getString(g.id, 30);
            printf("Enter Full Name: "); getString(g.name, 50);
            printf("Enter Phone Number: "); getString(g.phone, 20);
            printf("Enter Email Address: "); getString(g.email, 50);
            printf("Enter Home Address: "); getString(g.address, 100);
            printf("Enter Nationality: "); getString(g.nationality, 30);
            printf("Enter CNIC Number: "); getString(g.cnic, 30);
            printf("Is Premium Guest? (1:Yes, 0:No): "); scanf("%d", &g.is_premium); getchar();
            g.balance = 0;
            g.room_assigned = -1;
            g.check_in_time = 0;
            generatePassword(g.id, g.password);
            
            guests[guest_count++] = g;
            saveGuests();
            
            char msg[300];
            sprintf(msg, "Welcome to %s, %s! Your credentials are:\nUser: %s\nPass: %s\nPortal: http://grandluzuryhotel2026@businessmail.com", 
                    HOTEL_NAME, g.name, g.name, g.password);
            sendNotification(g, msg);
            
            char logMsg[100];
            sprintf(logMsg, "New guest registered: %s", g.name);
            logHistory(logMsg);
            
            printf(GREEN "\nGuest registered successfully! Credentials sent.\n" RESET);
            sleep(2);
        }
    }
}

void viewRecords() {
    clearScreen();
    printHeader("SYSTEM HISTORY LOG");
    FILE *fp = fopen("history.txt", "r");
    if (!fp) {
        printf(RED "No history records found!\n" RESET);
    } else {
        char line[256];
        while(fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
        fclose(fp);
    }
    printf("\nPress Enter to continue...");
    getchar();
}

void guestDashboard(int g_idx) {
    int choice;
    while (1) {
        clearScreen();
        printHeader("GUEST SERVICES PORTAL");
        printf(BOLD CYAN "Welcome, %s\n" RESET, guests[g_idx].name);
        printf(BOLD YELLOW "Current Balance to Pay: %.2f\n" RESET, guests[g_idx].balance);
        printf("--------------------------------------------------------------------\n");
        printf(BLUE "1. " RESET "Browse Available Rooms\n");
        printf(BLUE "2. " RESET "Book a Luxury Room\n");
        printf(BLUE "3. " RESET "Order Gourmet Food\n");
        printf(BLUE "4. " RESET "View Detailed Bill & Status\n");
        printf(BLUE "5. " RESET "Request Express Checkout\n");
        printf(RED "6. " RESET "Logout\n");
        printf(YELLOW "\nSelect Service: " RESET);
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: viewAvailableRooms(); break;
            case 2: bookRoom(g_idx); break;
            case 3: orderFood(g_idx); break;
            case 4: viewBill(g_idx); break;
            case 5: checkout(g_idx); return;
            case 6: return;
            default: printf(RED "Invalid choice!\n" RESET); sleep(1);
        }
    }
}

void viewAvailableRooms() {
    printf("\n%-10s %-30s %-15s\n", "Room No", "Luxury Type", "Rate/Hr");
    printf("--------------------------------------------------------------------\n");
    int count = 0;
    for(int i=0; i<room_count; i++) {
        if(rooms[i].status == 0) {
            printf("%-10d %-30s %-15.2f\n", rooms[i].room_number, rooms[i].type, rooms[i].rate_per_hour);
            count++;
        }
    }
    if(count == 0) printf(RED "All rooms are currently occupied.\n" RESET);
    printf("\nPress Enter to continue...");
    getchar();
}

void bookRoom(int g_idx) {
    if(guests[g_idx].room_assigned != -1) {
        printf(RED "You already have an active booking (Room %d)!\n" RESET, guests[g_idx].room_assigned);
        sleep(2);
        return;
    }

    int rno, found = 0;
    printf("Enter Room Number to book: "); scanf("%d", &rno); getchar();
    for(int i=0; i<room_count; i++) {
        if(rooms[i].room_number == rno && rooms[i].status == 0) {
            rooms[i].status = 1;
            strcpy(rooms[i].guest_id, guests[g_idx].id);
            guests[g_idx].room_assigned = rno;
            guests[g_idx].check_in_time = time(NULL);
            found = 1;
            break;
        }
    }

    if(found) {
        saveRooms();
        saveGuests();
        char logMsg[100];
        sprintf(logMsg, "Guest %s booked room %d.", guests[g_idx].name, rno);
        logHistory(logMsg);
        printf(GREEN "Room %d has been reserved for you!\n" RESET, rno);
    } else printf(RED "Room not available or invalid selection!\n" RESET);
    sleep(2);
}

void orderFood(int g_idx) {
    if(guests[g_idx].room_assigned == -1) {
        printf(RED "Please book a room first to access room service!\n" RESET);
        sleep(2);
        return;
    }

    int fid, qty;
    printf("\n%-5s %-35s %-15s\n", "ID", "Gourmet Dish", "Price");
    printf("--------------------------------------------------------------------\n");
    for(int i=0; i<food_count; i++) {
        if(menu[i].available)
            printf("%-5d %-35s %-15.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }

    printf("\nEnter Dish ID to order (0 to cancel): "); scanf("%d", &fid); getchar();
    if(fid == 0) return;

    int found = 0;
    for(int i=0; i<food_count; i++) {
        if(menu[i].id == fid && menu[i].available) {
            printf("Enter Quantity: "); scanf("%d", &qty); getchar();
            float cost = menu[i].price * qty;
            
            printf(CYAN "\nTotal Order Cost: %.2f\n" RESET, cost);
            printf("1. Pay Now (Credit/Debit)\n2. Add to Room Bill (Pay Later)\n");
            printf(YELLOW "Choice: " RESET);
            int pay_choice; scanf("%d", &pay_choice); getchar();
            
            if(pay_choice == 2) {
                guests[g_idx].balance += cost;
                printf(GREEN "Order confirmed. Added to your final bill.\n" RESET);
            } else {
                printf(GREEN "Payment processed successfully. Order is on the way!\n" RESET);
            }
            found = 1;
            saveGuests();
            char logMsg[200];
            sprintf(logMsg, "Guest %s ordered %s (Qty: %d).", guests[g_idx].name, menu[i].name, qty);
            logHistory(logMsg);
            break;
        }
    }
    if(!found) printf(RED "Invalid Dish ID!\n" RESET);
    sleep(2);
}

void viewBill(int g_idx) {
    clearScreen();
    printHeader("DETAILED BILLING STATEMENT");
    printf(BOLD "Guest Name: " RESET "%s\n", guests[g_idx].name);
    printf(BOLD "Guest ID:   " RESET "%s\n", guests[g_idx].id);
    
    if(guests[g_idx].room_assigned != -1) {
        printf(BOLD "Room Number: " RESET "%d\n", guests[g_idx].room_assigned);
        time_t now = time(NULL);
        double seconds = difftime(now, guests[g_idx].check_in_time);
        double hours = seconds / 3600.0;
        if (hours < 1.0) hours = 1.0; 

        float rate = 0;
        for(int i=0; i<room_count; i++) {
            if(rooms[i].room_number == guests[g_idx].room_assigned) {
                rate = rooms[i].rate_per_hour;
                break;
            }
        }
        float room_bill = hours * rate;
        printf("Stay Duration:  %.2f hours\n", hours);
        printf("Room Charges:   %.2f\n", room_bill);
        printf("Service Balance: %.2f\n", guests[g_idx].balance);
        printf("--------------------------------------------------------------------\n");
        printf(BOLD YELLOW "Total Outstanding: %.2f\n" RESET, room_bill + guests[g_idx].balance);
    } else {
        printf(RED "No active room reservation.\n" RESET);
        printf(BOLD "Outstanding Balance: " RESET "%.2f\n", guests[g_idx].balance);
    }
    printf("\nPress Enter to continue...");
    getchar();
}

void checkout(int g_idx) {
    if(guests[g_idx].room_assigned == -1) {
        printf(RED "No active booking found for checkout!\n" RESET);
        sleep(2);
        return;
    }

    time_t now = time(NULL);
    double seconds = difftime(now, guests[g_idx].check_in_time);
    double hours = seconds / 3600.0;
    if (hours < 1.0) hours = 1.0;

    float rate = 0;
    int r_idx = -1;
    for(int i=0; i<room_count; i++) {
        if(rooms[i].room_number == guests[g_idx].room_assigned) {
            rate = rooms[i].rate_per_hour;
            r_idx = i;
            break;
        }
    }

    float room_bill = hours * rate;
    float total = room_bill + guests[g_idx].balance;
    float discount = 0;

    if(total > 500 || guests[g_idx].is_premium) {
        discount = total * 0.10;
        total -= discount;
    }

    clearScreen();
    printHeader("FINAL INVOICE & CHECKOUT");
    printf("Guest: %s\n", guests[g_idx].name);
    printf("Room: %d (%s)\n", rooms[r_idx].room_number, rooms[r_idx].type);
    printf("Stay Duration: %.2f hours\n", hours);
    printf("Room Charges:  %.2f\n", room_bill);
    printf("Service Charges: %.2f\n", guests[g_idx].balance);
    printf(CYAN "Discount Applied: %.2f\n" RESET, discount);
    printf("--------------------------------------------------------------------\n");
    printf(BOLD GREEN "Final Amount Paid: %.2f\n" RESET, total);

    char logMsg[150];
    sprintf(logMsg, "Guest %s checked out. Room %d. Total Paid: %.2f", guests[g_idx].name, rooms[r_idx].room_number, total);
    logHistory(logMsg);

    rooms[r_idx].status = 0;
    rooms[r_idx].guest_id[0] = '\0';
    guests[g_idx].room_assigned = -1;
    guests[g_idx].balance = 0;
    guests[g_idx].check_in_time = 0;

    saveRooms();
    saveGuests();

    char msg[300];
    sprintf(msg, "Thank you for choosing %s, %s! Your final bill of %.2f has been settled. We hope to see you again soon!", 
            HOTEL_NAME, guests[g_idx].name, total);
    sendNotification(guests[g_idx], msg);

    printf("\nCheckout successful. We hope you enjoyed your stay!\n");
    printf("Press Enter to return to main menu...");
    getchar();
}
