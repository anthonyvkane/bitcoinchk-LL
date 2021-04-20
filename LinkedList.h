#pragma once
#include <string>
#include <iostream>
using namespace std;

class LinkedList {
private:
	int size;            //The size of the linked list
public:
	struct Node {
	public:
		long timestamp;	//			        - Start time of time window (60s window), in Unix time
		float pOpen;	//price Open		- Open price at start time window
		float pHigh;	//price High		- High price within time window
		float pLow;	    //price Low		    - Low price within time window
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
		Node* Clone()
		{
			return new Node(timestamp, pOpen, pHigh, pLow, pClose, vBTC, vCurr, wPrice);
		}
	};

	Node* head;
	Node* tail;

	LinkedList();
	int GetSize() {return size;}

	//node creating and Linked List updating happen in the same step.
	void CreateAndAddNode(long timestamp, float open, float high, float low, float close, string vBTC, string vCurr, string wPrice);
	
	//given a start and end timestamp, returns the shortened linked list between the two given nodes
	//dependendent on start and end timestamps, we will start iteration through head or tail to save time
	//if start or end timestamp is invalid, they are set to the original head or tail respectively
	LinkedList fragmentList(long start, long end);

	void Print();
	void Print(int num);

	//Sorted based on high price
	Node* Merge(Node* leftList, Node* rightList, int leftLength, int rightLength);
	Node* MergeSort(Node* start, Node* end, int length);

	//==========================QUICKSORT======================
	//inspiration from https://www.geeksforgeeks.org/quicksort-for-linked-list/
	Node* lastNode(Node* root);
	void swap(Node* a, Node* b);
	Node* partition(Node* l, Node* h);
	void _QuickSort(Node* l, Node* h);

	void QuickSort();
};
