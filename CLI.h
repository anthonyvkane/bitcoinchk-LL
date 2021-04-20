//
//  CLI.h
//  bit.chk2
//
//  Created by Alejandro Pascual on 4/19/21.
//  Copyright © 2021 Alejandro Pascual. All rights reserved.
// NEED TO INCLUDE TIME ELAPSED IN EACH ALGORITHM
// NEED TO INCLUDE LINKED LIST DELETION

#ifndef CLI_h
#define CLI_h
#include <string>
#include<sstream>
#include <chrono>
using namespace std;

string returnUnix(string &date){
    string temp = date;
    
    temp = temp.substr(0, temp.find('/'));
    int year = stoi(temp);
    
    temp = date;
    temp = temp.substr(date.find('/')+1, date.find('/')-2);
    int month = stoi(temp);
    
    temp = date;
    temp = temp.substr(date.find('/'));
    temp = temp.substr(date.find('/'));
    int day = stoi(temp.substr(0,2));
    temp = temp.substr(2, temp.find(' ') + 1);
    int hour = stoi(temp);
    
    temp = date;
    temp = temp.substr(14,15);
    int minute = stoi(temp);
    
    time_t rawtime;
    struct tm * timeInfo;
    
    time(&rawtime);
    timeInfo = localtime (&rawtime);
    
    timeInfo->tm_year   = year - 1900;
    timeInfo->tm_mon    = month - 1;    //months since January - [0,11]
    timeInfo->tm_mday   = day;          //day of the month - [1,31]
    timeInfo->tm_hour   = hour;         //hours since midnight - [0,23]
    timeInfo->tm_min    = minute;       //minutes after the hour - [0,59]
    timeInfo->tm_sec    = 0;
    
    auto testr = timegm(timeInfo);
    long buster = (long) testr;
    string answer = to_string(buster);
    return answer;
}


//geeksforgeeks unix to timestamp function
string unixTimeToHumanReadable(long int seconds)
{
 
    // Save the time in Human
    // readable format
    string ans = "";
 
    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
 
    long int currYear, daysTillNow, extraTime,
        extraDays, index, date, month, hours,
        minutes, secondss, flag = 0;
 
    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating currrent year
    while (daysTillNow >= 365) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0
                && currYear % 100 != 0)) {
            daysTillNow -= 366;
        }
        else {
            daysTillNow -= 365;
        }
        currYear += 1;
    }
 
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0
            && currYear % 100 != 0))
        flag = 1;
 
    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays
                        - daysOfMonth[index]
                    < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays
                    - daysOfMonth[index]
                < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
 
    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;
 
    ans += to_string(month);
    ans += "/";
    ans += to_string(date);
    ans += "/";
    ans += to_string(currYear);
    ans += " ";
    ans += to_string(hours);
    ans += ":";
    ans += to_string(minutes);
    ans += ":";
    ans += to_string(secondss);
 
    // Return the time
    return ans;
}

string enterStart(){
    string date1;
    cout << endl << "ENTER START DATE: (yyyy/mm/dd hh:mm)" << endl;
    std::getline(std::cin, date1);
    
    string unix1 = returnUnix(date1); //start date
    return unix1;
}

string enterEnd() {
    string date2;
    cout << endl << "ENTER END DATE: (yyyy/mm/dd hh:mm)" << endl;
    std::getline(std::cin, date2);
    
    string unix2 = returnUnix(date2); //end date
    return unix2;
}

void returnMenu() {
    cout << "would you like to run another" << endl;
    cout << "          bitcoin.chk?       " << endl << endl;
    cout << "if YES, enter 1" << endl;
    cout << "if NO, enter 0" << endl;
    
    //if yes then loop program again. this could be unnecessary when we actually submit/upload our video
}

void MainMenu() {
    cout << "-----------------------------" << endl;
    cout << "            bit.chk          " << endl;
    cout << "            =-----=          " << endl << endl;
    cout << "        ──▄▄█▀▀▀▀▀█▄▄── " << endl;
    cout << "        ▄█▀░░▄░▄░░░░▀█▄ " << endl;
    cout << "        █░░░▀█▀▀▀▀▄░░░█ " << endl;
    cout << "        █░░░░█▄▄▄▄▀░░░█ " << endl;
    cout << "        █░░░░█░░░░█░░░█ " << endl;
    cout << "        ▀█▄░▀▀█▀█▀░░▄█▀ " << endl;
    cout << "        ──▀▀█▄▄▄▄▄█▀▀── " << endl;
    cout << " ~for all your BitCoin needs~ " << endl;
    cout << "-----------------------------" << endl;
    cout << "          MAIN MENU          " << endl;
    cout << "-----------------------------" << endl;
    cout << " to begin BitCoin analysis,  " << endl;
    cout << "  please enter a start and   " << endl;
    cout << "           end date:         " << endl;
    cout << endl << "     format should be:"<< endl;
    cout << "      yyyy/mm/dd hh:mm      " << endl;
    cout << "(hours are in 24-hour format)"<< endl;
    cout << "  (April 7, 2019 9:08 PM:   " << endl;
    cout << "     2019/04/07 21:08)      " << endl;
}
#endif /* CLI_h */


