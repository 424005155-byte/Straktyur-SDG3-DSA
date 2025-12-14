#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
#include <unordered_map>

struct Medicine {
    std::string name;
    std::string dose;
    std::string time;
    std::string status;
    Medicine* next;
};

extern std::unordered_map<std::string, Medicine*> medicineTable;

void loadMedicines();
void saveMedicines();
void addMedicine(const std::string& userID);
void viewMedicines(const std::string& userID);
void markAsTaken(const std::string& userID);
void deleteMedicine(const std::string& userID);
void resetAllMedicinesToPending(const std::string& userID);

#endif
