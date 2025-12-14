#include "MedicineList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ReminderTime.h"

using namespace std;

unordered_map<string, Medicine*> medicineTable;

void loadMedicines() {
    // free previous memory
    for (auto &pair : medicineTable) {
        Medicine* curr = pair.second;
        while (curr) {
            Medicine* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        pair.second = nullptr;
    }

    ifstream file("medicine.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string userID, name, dose, time, status;
        getline(ss, userID, '|');
        getline(ss, name, '|');
        getline(ss, dose, '|');
        getline(ss, time, '|');
        getline(ss, status, '|');

        Medicine* m = new Medicine{name, dose, time, status, nullptr};

        Medicine*& head = medicineTable[userID];
        if (!head || head->time > m->time) {
            m->next = head;
            head = m;
        } else {
            Medicine* curr = head;
            while (curr->next && curr->next->time <= m->time) curr = curr->next;
            m->next = curr->next;
            curr->next = m;
        }
    }
}

void saveMedicines() {
    ofstream out("medicine.txt", ios::trunc);
    for (auto &pair : medicineTable) {
        string userID = pair.first;
        Medicine* curr = pair.second;
        while (curr) {
            out << userID << "|" << curr->name << "|" << curr->dose << "|" << curr->time << "|" << curr->status << "\n";
            curr = curr->next;
        }
    }
}

void addMedicine(const string& userID) {
    string name, dose, time;
    cout << "\nMedicine Name: "; getline(cin, name);
    cout << "Dose: "; getline(cin, dose);
    cout << "Time (HH:MM): "; getline(cin, time);

    Medicine* m = new Medicine{name, dose, time, "Pending", nullptr};
    Medicine*& head = medicineTable[userID];
    if (!head || head->time > time) {
        m->next = head;
        head = m;
    } else {
        Medicine* curr = head;
        while (curr->next && curr->next->time <= time) curr = curr->next;
        m->next = curr->next;
        curr->next = m;
    }

    saveMedicines();
    cout << "✅ Medicine added!\n";
}

void viewMedicines(const string& userID) {
    Medicine* curr = medicineTable[userID];
    if (!curr) { cout << "(No medicines found)\n"; return; }

    while (curr) {
        cout << curr->time << " - " << curr->name << " | Dose: " << curr->dose << " | Status: " << curr->status << "\n";
        curr = curr->next;
    }
}

void markAsTaken(const string& userID) {
    Medicine* curr = medicineTable[userID];
    bool updated = false;

    while (curr) {
        if (curr->status == "Pending") {
            cout << "Mark \"" << curr->name << "\" (" << curr->time << ") as taken? (yes/no): ";
            string choice; getline(cin, choice);
            if (choice == "yes") {
                curr->status = "Taken";
                updated = true;
            }
        }
        curr = curr->next;
    }

    if (updated) { saveMedicines(); cout << "✅ Updated!\n"; }
    else cout << "No medicine marked.\n";
}

void deleteMedicine(const string& userID) {
    cout << "Enter medicine name to delete: ";
    string name; getline(cin, name);

    Medicine* curr = medicineTable[userID];
    Medicine* prev = nullptr;
    while (curr) {
        if (curr->name == name) {
            if (prev) prev->next = curr->next;
            else medicineTable[userID] = curr->next;
            delete curr;
            saveMedicines();
            cout << "✅ Deleted!\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Medicine not found.\n";
}

void resetAllMedicinesToPending(const string& userID) {
    Medicine* curr = medicineTable[userID];
    if (!curr) { cout << "No medicines to reset.\n"; return; }
    while (curr) { curr->status = "Pending"; curr = curr->next; }
    saveMedicines();
    cout << "✅ All medicines reset!\n";
}
