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
		long timestamp;	//timestamp		    - Start time of time window (60s window), in Unix time
		float pHigh;	//price High		- High price within time window
		Node* prev;
		Node* next;

		//Unused parts of the API
		/*float pOpen;	//price Open		- Open price at start time window
		float pLow;	    //price Low		    - Low price within time window
		float pClose;	//price Close		- Close price at end of time window
		string vBTC;	//volume BTC		- Volume of BTC transacted in this window
		string vCurr;	//volume Currency	- Volume of corresponding currency transacted in this window
		string wPrice;	//weighted price	- VWAP - Volume Weighted Average Price

		//vBTC, vCurr, and wPrice are stored as strings because no primative data type in C++ can match the precision necissary to store these data points*/

		Node(long TS, float H) {
			timestamp = TS;
			pHigh = H;
			prev = nullptr;
			next = nullptr;
		}
		Node* Clone()
		{
			return new Node(timestamp, pHigh);
		}
	};

	Node* head;
	Node* tail;

	LinkedList();
	int GetSize() {return size;}

	//node creating and Linked List updating happen in the same step.
	void CreateAndAddNode(long timestamp, float high);
	
	//given a start and end timestamp, returns the shortened linked list between the two given nodes
	//dependendent on start and end timestamps, we will start iteration through head or tail to save time
	//if start or end timestamp is invalid, they are set to the original head or tail respectively
	LinkedList fragmentList(long start, long end);

	void Print();
	void Print(int num);

	//==========================MERGESORT======================
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