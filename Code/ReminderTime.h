#ifndef REMINDER_TIME_H
#define REMINDER_TIME_H

#include <string>

std::string getCurrentTimeHHMM();
std::string makeKey(const std::string& userID, const std::string& medName, const std::string& time);

#endif
