#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
using namespace std;

int main() {

	ifstream stamps;
	stamps.open("bitstamps.csv");
	string line;
	getline(stamps, line, '\n'); //burns the first line of the csv which is "Timestamp,Open,High,Low,Close,Volume_(BTC),Volume_(Currency),Weighted_Price"
	long timestamp;
	float open, high, low, close;
	string vBTC, vCurr, wPrice;

	LinkedList BTCLinkedList = LinkedList();

	//long counter = 0;
	//we are reading each line of the csv file. this will loop 4,857,378 times for each data entry in the csv file.

	while(getline(stamps, line, '\n')) {
		//=======================================timestamps=======================================

		timestamp = stol(line.substr(0, line.find(',')));	//getting timestamp

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

		BTCLinkedList.CreateAndAddNode(timestamp, open, high, low, close, vBTC, vCurr, wPrice);
		//counter++;
		//if (counter % 10000 == 0)
		//	cout << counter << "nodes created..." << endl;
	}
	return 0;
}