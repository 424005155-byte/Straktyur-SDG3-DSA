#include "MedicineList.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace chrono;

void generateTestData() {
    ofstream file("medicine.txt");
    for(int i = 1; i <= 60; i++) {
        int hour = 8 + (i % 12);        
        int minute = 10 + (i % 50);     
        
        char timeStr[6];
        sprintf(timeStr, "%02d:%02d", hour, minute);
        
        file << "testUser|Medicine_" << i << "|" 
             << (i % 3 + 1) << " pill(s)|"
             << timeStr << "|Pending\n";
    }
    file.close();
    cout << "Generated 60 test medicine records.\n";
}

void generateTestUser() {
    ofstream file("users.txt");
    file << "Test User|25|testUser|password123\n";
    file.close();
}

void clearTestData() {
    remove("medicine.txt");
    remove("users.txt");
}

void runPerformanceTests() {
    cout << "\n=== PERFORMANCE TEST (60 Records) ===\n";
    cout << "Testing NFR1: All operations under 2 seconds\n\n";
    
    auto start = high_resolution_clock::now();
    loadMedicines();
    auto loadTime = high_resolution_clock::now();
    auto loadDuration = duration_cast<milliseconds>(loadTime - start);
    
    start = high_resolution_clock::now();
    viewMedicines("testUser");
    auto viewTime = high_resolution_clock::now();
    auto viewDuration = duration_cast<milliseconds>(viewTime - start);
    
    start = high_resolution_clock::now();

    Medicine* m = new Medicine{"TestMed", "2 pills", "12:30", "Pending", nullptr};
    Medicine*& head = medicineTable["testUser"];
    if (!head || head->time > m->time) {
        m->next = head;
        head = m;
    } else {
        Medicine* curr = head;
        while (curr->next && curr->next->time <= m->time) curr = curr->next;
        m->next = curr->next;
        curr->next = m;
    }
    saveMedicines();
    auto addTime = high_resolution_clock::now();
    auto addDuration = duration_cast<milliseconds>(addTime - start);
    

    start = high_resolution_clock::now();
    saveMedicines();
    auto saveTime = high_resolution_clock::now();
    auto saveDuration = duration_cast<milliseconds>(saveTime - start);
    

    cout << "\n=== TEST RESULTS ===\n";
    cout << "1. Load Medicines (60 records):  " << loadDuration.count() << " ms\n";
    cout << "2. View Medicines (60 records):  " << viewDuration.count() << " ms\n";
    cout << "3. Add + Save Medicine:         " << addDuration.count() << " ms\n";
    cout << "4. Save Medicines (61 records): " << saveDuration.count() << " ms\n";
    cout << "=================================\n";
    

    bool nfr1Passed = true;
    cout << "\n=== NFR1 VALIDATION ===\n";
    
    if(loadDuration.count() < 2000) {
        cout << "✅ Load Medicines: " << loadDuration.count() << " ms < 2000 ms\n";
    } else {
        cout << "❌ Load Medicines: " << loadDuration.count() << " ms ≥ 2000 ms\n";
        nfr1Passed = false;
    }
    
    if(viewDuration.count() < 2000) {
        cout << "✅ View Medicines: " << viewDuration.count() << " ms < 2000 ms\n";
    } else {
        cout << "❌ View Medicines: " << viewDuration.count() << " ms ≥ 2000 ms\n";
        nfr1Passed = false;
    }
    
    if(addDuration.count() < 2000) {
        cout << "✅ Add Medicine: " << addDuration.count() << " ms < 2000 ms\n";
    } else {
        cout << "❌ Add Medicine: " << addDuration.count() << " ms ≥ 2000 ms\n";
        nfr1Passed = false;
    }
    
    if(saveDuration.count() < 2000) {
        cout << "✅ Save Medicines: " << saveDuration.count() << " ms < 2000 ms\n";
    } else {
        cout << "❌ Save Medicines: " << saveDuration.count() << " ms ≥ 2000 ms\n";
        nfr1Passed = false;
    }
    
    cout << "=================================\n";
    if(nfr1Passed) {
        cout << "🎉 NFR1 PASSED: All operations complete within 2 seconds!\n";
    } else {
        cout << "💥 NFR1 FAILED: Some operations exceeded 2 seconds\n";
    }
}


void runStressTest() {
    cout << "\n=== STRESS TEST (500 Records) ===\n";
    

    ofstream file("medicine.txt");
    for(int i = 1; i <= 500; i++) {
        int hour = i % 24;
        int minute = i % 60;
        char timeStr[6];
        sprintf(timeStr, "%02d:%02d", hour, minute);
        
        file << "stressUser|StressMed_" << i << "|1 pill|"
             << timeStr << "|Pending\n";
    }
    file.close();
    
    auto start = high_resolution_clock::now();
    loadMedicines();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << "Load 500 records: " << duration.count() << " ms\n";
    
    if(duration.count() < 2000) {
        cout << "✅ Stress Test PASSED: 500 records loaded in " 
             << duration.count() << " ms (< 2000 ms)\n";
    } else {
        cout << "⚠️  Stress Test WARNING: 500 records took " 
             << duration.count() << " ms\n";
    }
}

int main() {

    clearTestData();
    generateTestUser();
    generateTestData();
    

    runPerformanceTests();
    runStressTest();
    

    clearTestData();
    
    cout << "\nPress Enter to exit...";
    cin.get();
    return 0;

}
