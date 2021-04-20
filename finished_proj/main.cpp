#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include "LinkedList.h"
#include "CLI.h"
//#include "Quicksort.h"
using namespace std;


int main() {
    int menuChoice = 0;
    //nathan: mergesort
    //pascual: cli
    //anthony: quicksort
    ifstream stamps;
    stamps.open("bitstamps.csv");
    string line;
    long timestamp;
    float open, high, low, close;
    string vBTC, vCurr, wPrice;

    LinkedList* BTCLinkedList = new LinkedList(); //our linked list. after the while loop this will contain all of our nodes
    LinkedList* BTCLinkedListQuick = new LinkedList();
    
    
    while(menuChoice == 0) {
    //------------------------CLI
    MainMenu();
       string start, end;
       
       //these functions will probably have to be in the actual main function
       start = enterStart();
       end = enterEnd();
       
       
       
       cout << "unix1: " << start << ", unix2: " << end << endl;
    //CLI DONE
    long counter = 0;
    //we are reading each line of the csv file. this will loop 4,857,378 times for each data entry in the csv file.
    while(getline(stamps, line, '\n')) {

        //=======================================timestamps=======================================

        timestamp = stol(line.substr(0, line.find(',')));    //getting timestamp
        int newStart = stoi(start);
        int newEnd = stoi(end);
        long newnewStart = (long int) newStart;
        long newnewEnd = (long int) newEnd;
        if(timestamp < newnewStart || timestamp > newnewEnd)
            continue;
        //=======================================open=======================================
        line = line.substr(line.find(',')+1);
        if (line.substr(0, line.find(',')) != "NaN") {
            open = stof(line.substr(0, line.find(',')));
        }
        else {
            open = -1;
        }
        //=======================================high=======================================
        line = line.substr(line.find(',') + 1);
        if (line.substr(0, line.find(',')) != "NaN") {
            high = stof(line.substr(0, line.find(',')));
        }
        else {
            continue;
            high = -1;
        }
        //=======================================low=======================================
        line = line.substr(line.find(',') + 1);
        if (line.substr(0, line.find(',')) != "NaN") {
            low = stof(line.substr(0, line.find(',')));
        }
        else {
            low = -1;
        }
        //=======================================close=======================================
        line = line.substr(line.find(',') + 1);
        if (line.substr(0, line.find(',')) != "NaN") {
            close = stof(line.substr(0, line.find(',')));
        }
        else {
            close = -1;
        }
        //=======================================vBTC=======================================
        line = line.substr(line.find(',') + 1);
        vBTC = line.substr(0, line.find(','));

        //=======================================vCurr=======================================
        line = line.substr(line.find(',') + 1);
        vCurr = line.substr(0, line.find(','));
        //=======================================wPrice=======================================
        line = line.substr(line.find(',') + 1);
        wPrice = line.substr(0, line.find(','));
        BTCLinkedList->CreateAndAddNode(timestamp, high);
        BTCLinkedListQuick->CreateAndAddNode(timestamp, high);
        counter++;
        if (counter % 10000 == 0)
            cout << counter << "nodes created..." << endl;
    }
        
        //now, do mergesort
    BTCLinkedList->head = BTCLinkedList->MergeSort(BTCLinkedList->head, BTCLinkedList->tail, BTCLinkedList->GetSize());

    
    //end date is Wed Mar 31 2021 00:00:00 GMT
    cout << "-------------MERGE SORT-----------" << endl;
    cout << "Best Minute to Purchase Bitcoin: " << endl << BTCLinkedList->head->pHigh << endl << "Date and Time: ";
    string time_ = unixTimeToHumanReadable(BTCLinkedList->head->timestamp);
        cout << time_ << endl;
    cout << endl << "Best Minute to Sell Bitcoin: " << endl << BTCLinkedList->tail->pHigh << endl << "Date and Time: ";
    time_ = unixTimeToHumanReadable(BTCLinkedList->tail->timestamp);
        cout << time_ << endl;
        
        cout << endl <<  "-------------QUICK SORT-----------" << endl;
        BTCLinkedListQuick->QuickSort();
        cout << "Best Minute to Purchase Bitcoin: " << endl << BTCLinkedListQuick->head->pHigh << endl << "Date and Time: ";
        time_ = unixTimeToHumanReadable(BTCLinkedListQuick->head->timestamp);
        cout << time_ << endl;
        cout << endl << "Best Minute to Sell Bitcoin: " << endl << BTCLinkedListQuick->tail->pHigh << endl << "Date and Time: ";
        time_ = unixTimeToHumanReadable(BTCLinkedListQuick->tail->timestamp);
        cout << time_ << endl;
    
        
        
        
        
        
    returnMenu();
        string menu;
        std::getline(std::cin, menu);
        if(stoi(menu) == 0)
        {
            menuChoice = 1;
        }
        else
        {
            //DELETE LINKEDLIST HERE!!!
        }
    }
    

    
    return 0;
}
