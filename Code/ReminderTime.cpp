#include "ReminderTime.h"
#include <ctime>
#include <string>
#include <sstream>

std::string getCurrentTimeHHMM() {
    time_t now = time(0);
    tm local_tm;
    localtime_s(&local_tm, &now);  // for MSVC
    char buffer[6];
    sprintf_s(buffer, "%02d:%02d", local_tm.tm_hour, local_tm.tm_min);
    return std::string(buffer);
}

std::string makeKey(const std::string& userID, const std::string& medName, const std::string& time) {
    return userID + "|" + medName + "|" + time;
}
