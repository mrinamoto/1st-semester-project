#include <stdio.h>
#include <string.h>

#define MAX_BUSES 5
#define MAX_SEATS 40

struct Bus {
    char number[10];
    char destination[30];
    int availableSeats;
} buses[MAX_BUSES] = {
    {"B001", "Dhaka", 40},
    {"B002", "Chittagong", 40},
    {"B003", "Sylhet", 40},
    {"B004", "Rajshahi", 40},
    {"B005", "Khulna", 40}
};

void reserveSeat() {
    char busNo[10];
    int seats;

    printf("Enter Bus Number to Reserve Seats: ");
    scanf("%s", busNo);

    for (int i = 0; i < MAX_BUSES; i++) {
        if (strcmp(buses[i].number, busNo) == 0) {
            printf("Enter Number of Seats to Reserve: ");
            scanf("%d", &seats);

            if (seats <= buses[i].availableSeats) {
                buses[i].availableSeats -= seats;
                printf("Successfully Reserved %d Seats on Bus %s\n", seats, busNo);
            } else {
                printf("Not Enough Seats Available!\n");
            }
            return;
        }
    }
    printf("Bus Not Found!\n");
}

void cancelReservation() {
    char busNo[10];
    int seats;

    printf("Enter Bus Number to Cancel Reservation: ");
    scanf("%s", busNo);

    for (int i = 0; i < MAX_BUSES; i++) {
        if (strcmp(buses[i].number, busNo) == 0) {
            printf("Enter Number of Seats to Cancel: ");
            scanf("%d", &seats);

            if (buses[i].availableSeats + seats <= MAX_SEATS) {
                buses[i].availableSeats += seats;
                printf("Successfully Cancelled %d Seats on Bus %s\n", seats, busNo);
            } else {
                printf("Invalid Number of Seats to Cancel!\n");
            }
            return;
        }
    }
    printf("Bus Not Found!\n");
}

void displaySchedules() {

    printf(" Bus Number     Destination     Seats  \n");
    for (int i = 0; i < MAX_BUSES; i++) {
        printf(" %-12s   %-14s  %d \n", buses[i].number, buses[i].destination, buses[i].availableSeats);
    }
}

void saveDataToFile() {
    FILE *file = fopen("bus_data.txt", "w");
    for (int i = 0; i < MAX_BUSES; i++) {
        fprintf(file, "%s %s %d\n", buses[i].number, buses[i].destination, buses[i].availableSeats);
    }
    fclose(file);
    printf("Data Saved Successfully!\n");
}

void loadDataFromFile() {
    FILE *file = fopen("bus_data.txt", "r");
    if (file == NULL) {
        printf("File Not Found! Starting Fresh.\n");
        return;
    }
    for (int i = 0; i < MAX_BUSES; i++) {
        fscanf(file, "%s %s %d", buses[i].number, buses[i].destination, &buses[i].availableSeats);
    }
    fclose(file);
    printf("Data Loaded Successfully!\n");
}

void menu() {
    int choice;

    printf("Bus Reservation System\n");
    printf("1. Reserve Seats\n");
    printf("2. Cancel Reservation\n");
    printf("3. Display Schedules\n");
    printf("4. Save Data\n");
    printf("5. Load Data\n");
    printf("6. Exit\n");

    for (;;) {
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        if (choice == 1) reserveSeat();
        else if (choice == 2) cancelReservation();
        else if (choice == 3) displaySchedules();
        else if (choice == 4) saveDataToFile();
        else if (choice == 5) loadDataFromFile();
        else if (choice == 6) {
            printf("Exiting System. Goodbye!\n");
            break;
        } else {
            printf("Invalid Choice! Try Again.\n");
        }
    }
}
int main() {
    loadDataFromFile();
    menu();
    saveDataToFile();
    return 0;
}
