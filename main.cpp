#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include "LinkedList.h"
//#include "Quicksort.h"
using namespace std;


int main() {

	ifstream stamps;
	stamps.open("bitstamps.csv");
	string line;
	long timestamp;
	float open, high, low, close;
	string vBTC, vCurr, wPrice;

	LinkedList* BTCLinkedList = new LinkedList(); //our linked list. after the while loop this will contain all of our nodes

	long counter = 0;
	//we are reading each line of the csv file. this will loop 4,857,378 times for each data entry in the csv file.
	auto startClock = chrono::steady_clock::now();
	while (getline(stamps, line, '\n')) {

		//if (counter > 10)
		//	break;
		//=======================================timestamps=======================================

		timestamp = stol(line.substr(0, line.find(',')));	//getting timestamp

		//=======================================open=======================================
		line = line.substr(line.find(',') + 1);
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
		counter++;
		if (counter % 10000 == 0)
			cout << counter << "nodes created..." << endl;
	}
	auto endClock = chrono::steady_clock::now();
	cout << "Time taken to create LinkedList: " << chrono::duration_cast<chrono::milliseconds>(endClock - startClock).count() << " ms" << endl;

	//BTCLinkedList->Print();
	startClock = chrono::steady_clock::now();
	BTCLinkedList->QuickSort();
	endClock = chrono::steady_clock::now();
	cout << "Time taken for Quicksort: " << chrono::duration_cast<chrono::milliseconds>(endClock - startClock).count() << " ms" << endl;
	//BTCLinkedList->Print();
	cout << "Head: " << BTCLinkedList->head->pHigh << endl;
	cout << "Head Next: " << BTCLinkedList->head->next->pHigh << endl;
	cout << "Head Next Prev (Just Head): " << BTCLinkedList->head->next->prev->pHigh << endl;
	cout << "Tail: " << BTCLinkedList->tail->pHigh << endl;
	cout << "Tail Prev: " << BTCLinkedList->tail->prev->pHigh << endl;
	cout << "Tail Prev Next (Just Tail): " << BTCLinkedList->tail->prev->next->pHigh << endl;
	return 0;
}
