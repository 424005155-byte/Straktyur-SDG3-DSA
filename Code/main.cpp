#include <iostream>
#include <limits>
#include <string>
#include "User.h"
#include "MedicineList.h"
#include "MedicineReminder.h"

using namespace std;

void userMenu(const string& userID) {
    startReminderThread(userID);
    while (true) {
        cout << "\n==== USER MENU ====\n";
        cout << "1. Add Medicine\n2. View Medicines\n3. Mark Medicine as Taken\n4. Delete Medicine\n5. Reset Medicines\n6. Logout\nChoose: ";
        string choice; getline(cin, choice);

        if (choice=="1") addMedicine(userID);
        else if (choice=="2") viewMedicines(userID);
        else if (choice=="3") markAsTaken(userID);
        else if (choice=="4") deleteMedicine(userID);
        else if (choice=="5") resetAllMedicinesToPending(userID);
        else if (choice=="6") { stopReminderThread(); break; }
        else cout << "❌ Invalid choice!\n";
    }
}

int main() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "\n==== MEDICINE REMINDER SYSTEM ====\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        string choice; getline(cin, choice);

        if (choice=="1") registerUser();
        else if (choice=="2") {
            string userID = loginUser();
            if (!userID.empty()) userMenu(userID);
        }
        else if (choice=="3") { stopReminderThread(); break; }
        else cout << "❌ Invalid choice!\n";
    }
    return 0;
}
