//
//  CLI.h
//  bit.chk2
//
//  Created by Alejandro Pascual on 4/19/21.
//  Copyright © 2021 Alejandro Pascual. All rights reserved.
//

#ifndef CLI_h
#define CLI_h
#include <string>
#include<sstream>
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
    cout << endl << "     format should be:" << endl;
    cout << "      yyyy/mm/dd,hh:mm     " << endl;
    cout << "(hours are in 24-hour format)" << endl;
    cout << "(September 29, 2019 2:00 PM: " << endl;
    cout << "     2019/09/29 14:00 )      " << endl;
    
    string start, end;
    
    //these functions will probably have to be in the actual main function
    start = enterStart();
    end = enterEnd();
    
    
    cout << "unix1: " << start << ", unix2: " << end << endl;
    
    //print out sorting algorithms, etc.
    
    cout << "would you like to run another" << endl;
    cout << "          bitcoin.chk?       " << endl << endl;
    cout << "if YES, enter 1" << endl;
    cout << "if NO, enter 0" << endl;
    
    //if yes then loop program again. this could be unnecessary when we actually submit/upload our video
    
    
}
#endif /* CLI_h */


