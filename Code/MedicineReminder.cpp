#include "MedicineReminder.h"
#include "MedicineList.h"
#include "ReminderTime.h"
#include <windows.h>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>

using namespace std;

extern unordered_map<string, Medicine*> medicineTable;
unordered_map<string, int> reminderCount;
mutex reminderMutex;
atomic<bool> reminderRunning(false);
thread reminderThread;

void reminderLoop(const string userID) {
    while (reminderRunning.load()) {
        string now = getCurrentTimeHHMM();
        Medicine* curr = medicineTable[userID];

        while (curr) {
            if (curr->status == "Pending" && curr->time == now) {
                string key = makeKey(userID, curr->name, curr->time);
                int countNow = 0;
                bool notify = false;

                {
                    lock_guard<mutex> lock(reminderMutex);
                    countNow = reminderCount[key];
                    if (countNow < 3) { reminderCount[key] = ++countNow; notify = true; }
                }

                if (notify) {
                    string msg = "Time to take your medicine!\n\n" + curr->name + "\nDose: " + curr->dose + "\nTime: " + curr->time;
                    MessageBoxA(NULL, msg.c_str(), "Medicine Reminder", MB_OK | MB_ICONWARNING);
                }

                if (countNow == 3) {
                    int r = MessageBoxA(NULL, "Have you taken this medicine?", "Confirm", MB_YESNO | MB_ICONQUESTION);
                    if (r == IDYES) {
                        curr->status = "Taken";
                        saveMedicines();
                        lock_guard<mutex> lock(reminderMutex);
                        reminderCount.erase(key);
                        MessageBoxA(NULL, "Marked as taken!", "Done", MB_OK);
                    }
                }
            }
            curr = curr->next;
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void startReminderThread(const string& userID) {
    if (reminderRunning.load()) return;
    reminderRunning.store(true);
    loadMedicines();
    reminderThread = thread(reminderLoop, userID);
}

void stopReminderThread() {
    if (!reminderRunning.load()) return;
    reminderRunning.store(false);
    if (reminderThread.joinable()) reminderThread.join();
}
