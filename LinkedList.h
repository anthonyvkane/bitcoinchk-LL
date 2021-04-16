#pragma once
using namespace std;

/*
Create Node		
Create Header
Create AddHead
1,048,575
*/

class LinkedList {

private:

public:
	
	struct Node {
	public:
		long timestamp;	//			- Start time of time window (60s window), in Unix time
		float pOpen;	//price Open		- Open price at start time window
		float pHigh;	//price High		- High price within time window
		float pLow;	//price Low		- Low price within time window
		float pClose;	//price Close		- Close price at end of time window
		string vBTC;	//volume BTC		- Volume of BTC transacted in this window
		string vCurr;	//volume Currency	- Volume of corresponding currency transacted in this window
		string wPrice;	//weighted price	- VWAP - Volume Weighted Average Price

		//vBTC, vCurr, and wPrice are stored as strings because no primative data type in C++ can match the precision necissary to store these data points

		Node* prev;
		Node* next;
		Node(long TS, float O, float H, float L, float C, string VB, string VC, string WP) {
			timestamp = TS; pOpen = O; pHigh = H; pLow = L; pClose = C; vBTC = VB; vCurr = VC; wPrice = WP;
			prev = nullptr;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

	LinkedList() {	//default constructor
		head = nullptr; tail = nullptr;
	};

	/*
	long timestamp;
	float open, high, low, close;
	string vBTC, vCurr, wPrice;
	*/

	//node creating and Linked List updating happen in the same step.
	void CreateAndAddNode(long timestamp, float open, float high, float low, float close, string vBTC, string vCurr, string wPrice) {

		//node creation
		Node* node = new Node(timestamp, open, high, low, close, vBTC, vCurr, wPrice);

		if (head == nullptr) {	//if no head, insert a head
			head = node;
		}
		if (tail == nullptr)	//if no tail, insert a tail
			tail = node;
		else {
			tail->next = node;		//old tail next will be new tail
			node->prev = tail;		//new tail prev will be old tail
			node->next = nullptr;	//new tail next will be nullptr
			tail = node;
		}
	};

};
