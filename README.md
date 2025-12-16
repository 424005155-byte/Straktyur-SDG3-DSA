# Straktyur-SDG3-DSA
MediTrack is a comprehensive C++ console application implementing a medicine management system with automated reminders, user authentication, and persistent data storage. The system applies core data structures and algorithms to solve real-world healthcare challenges through efficient data organization and processing.

What the System Can Do (Functional Requirements)

FR-1: Creating an Account
Users can sign up for a new account
Login information gets stored in a file called account.txt
The system won't allow two accounts with the same username

FR-2: Signing In
Users can log in with their username and password
The system checks if the login details match what's saved in account.txt
Login fails if the username or password is wrong

FR-3: Signing Out
Users can log out when they're done
After logging out, users return to the login screen

FR-4: Main Menu Options
After logging in, users see a menu with these choices:
Add new medicine
View medicines
Mark medicines as taken
Delete Medicine
Reset Medicine
Logout

FR-5: Adding Medicines
Users can add medicines by entering:
Name of the medicine
How much to take
What time to take it
Medicine details are saved in medicine.txt
New medicines start with a "Pending" status

FR-6: Viewing Schedule
Users can see all their scheduled medicines
The information comes from the medicine.txt file
FR-7: Recording Medicine Intake
Users can mark whether they took their medicine or not
The status updates and saves to medicine.txt

FR-8: Removing Medicines
Users can delete a medicine by typing its name
The medicine gets permanently removed from medicine.txt

FR-9: Daily Status Reset
All medicine statuses automatically reset to "Pending" when users select option 5

FR-10: Reminders
The system constantly monitors the schedule while users logged in
Users get notified when it's time to take their medicine
Users will be ask after the three notification pop up if he already take the medicine 

FR-11: Closing the Program


How Well the System Works (Non-Functional Requirements)

NFR-1: Easy to Use
Simple menu-based interface anyone can understand
Clear instructions guide users through each action

NFR-2: Speed
Medicine schedules are checked immediately
Logging in and switching menus takes 1-2 seconds or less

NFR-3: Dependability
The system saves and loads data correctly from files
User information and medicine data don't get lost during normal use

NFR-4: Easy to Update
Code is organized into separate sections for:
Login/logout features
Medicine management
Scheduling system

NFR-5: System Compatibility
Works on Windows computers with a C++ compiler
Doesn't need internet connection or database software

NFR-6: Growth Capability
Can handle multiple users through file storage
Can manage growing amounts of medicine records without problems

NFR-7: Always Running
Reminder checking continues as long as the app is open
Notifications appear even when users aren't actively using the system

NFR-8: Data Accuracy
Changes to medicine.txt and account.txt are saved correctly
Prevents incomplete or corrupted file saves

Users can safely exit the application
All background processes stop when exiting


Individual Contributions:

I. Introduction 

1.1. Project Overview & UN SDG Target -  PAJO, HARVEY

1.2. Problem Statement (What real-world problem does the app solve?) - BERMIO, CARL

II. Requirements & Analysis

2.1. Functional Requirements and Non-Functional Requirements (List of features, e.g., FR1, FR2) - NEPA, JASTINE

2.2. Data Requirements (Description of input data structure and size) - PAJO, HARVEY

2.3. Complexity Analysis: Expected Time/Space complexity of the Core Algorithm (justify using Big O notation).- NEPA, JASTINE

III. Design Specification

3.1. Core Data Structures Used (The Five): NEPA, JASTINE
For each of the five required DSA concepts, include a section detailing:
Justification: Why was this specific DSA chosen for its role?
Implementation Details: How did you implement it (e.g., adjacency list for Graph, array for Heap)?

3.2. Algorithm Flowchart: Include the Flowchart for the system's most complex function (the core algorithm using a Finals concept). NEPA, JASTINE

3.3. Module Breakdown: Define the custom C++ classes and how they interact.  
PAJO, HARVEY

IV. Testing and Results (Optional)

4.1. Test Cases (Provide 2-3 sample tests showing input data and expected/actual output.) 
GONZALES, JAIRON

4.2. Performance Test (Prove that NFR1 is met by testing with the 50+ record input.) 
PAJO, HARVEY

V. Conclusion and Contributions

5.1. Conclusion - BERMIO, CARL

CODE: 
Users.h - User.cpp  - PAJO, HARVEY

ReminderTime.h - Reminder.cpp - GONZALES, JAIRON

MedicineList.h - MedicineList.cpp - MALDA, KENNETH

MedicineReminder.h -MedicineReminder.cpp - NEPA, JASTINE

Main.cpp - BERMIO, CARL

GITHUB CREATION - PAJO, HARVEY

OVERALL PPT - NEPA, JASTINE, MALDA, KENNETH

OVERALL WORD - PAJO, HARVEY


