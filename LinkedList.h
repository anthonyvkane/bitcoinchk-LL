#pragma once
using namespace std;


class LinkedList {

private:

public:
	
	struct Node {
	public:
		long timestamp;	//					- Start time of time window (60s window), in Unix time
		float pOpen;	//price Open		- Open price at start time window
		float pHigh;	//price High		- High price within time window
		float pLow;		//price Low			- Low price within time window
		float pClose;	//price Close		- Close price at end of time window
		string vBTC;		//volume BTC		- Volume of BTC transacted in this window
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

	//given a start and end timestamp, returns the shortened linked list between the two given nodes
	//dependendent on start and end timestamps, we will start iteration through head or tail to save time
	//if start or end timestamp is invalid, they are set to the original head or tail respectively
	LinkedList fragmentList(long start, long end) {
		LinkedList nuLinkedList =  LinkedList();
		//thought for time saving below
		/*long startDif = start - head->timestamp;	 //distance from first node in new list from head
		long endDif = tail->timestamp - end;		 //distance from last node in new list to tail
		bool reverse = false;

		if (endDif < startDif) {
			reverse = true;
		}

		Node* iterNode;
		if (reverse == false) { //we are starting from head going forwards
			iterNode = head;
			while (iterNode != nullptr) {

				iterNode = iterNode->next;
			}
		}

		else {
			iterNode = tail;
			while (iterNode != nullptr) { //we are starting from tail going backwards

				iterNode = iterNode->next;
			}
		}*/

		long startDif = start - head->timestamp;	 //distance from first node in new list from head
		long endDif = tail->timestamp - end;		 //distance from last node in new list to tail
		bool reverse = false;

		if (endDif < startDif) {
			reverse = true;
		}

		Node* iterNode;

		if (reverse == false) {

			iterNode = head;
			while (iterNode != nullptr) {	//starting from head and moving next

				if (iterNode->timestamp == start)
					nuLinkedList.head = iterNode;
				if (iterNode->timestamp == end)
					nuLinkedList.tail = iterNode;

				iterNode = iterNode->next;
				if (nuLinkedList.head != nullptr && nuLinkedList.tail != nullptr) //break case to save time if we found new head and tail already
					break;
			}
		}
		else {
			iterNode = tail;
			while (iterNode != nullptr) {	//starting from tail and moving prev

				if (iterNode->timestamp == start)
					nuLinkedList.head = iterNode;
				if (iterNode->timestamp == end)
					nuLinkedList.tail = iterNode;

				iterNode = iterNode->prev;
				if (nuLinkedList.head != nullptr && nuLinkedList.tail != nullptr)
					break;
			}
		}

		if (nuLinkedList.head == nullptr) {
			cout << "Incorrect From Date Input. From date has been set to first recorded timestamp." << endl;
			nuLinkedList.head = head;
		}
		if (nuLinkedList.tail == nullptr) {
			cout << "Incorrect To Date Input. To date has been set to last recorded timestamp." << endl;
			nuLinkedList.tail = tail;
		}

		return nuLinkedList;
	}

	void printList() {
		Node* temp = head;
		cout << "Starting Print..." << endl;
		while (temp != nullptr) {
			cout << "Time: " << temp->timestamp << "at: $" << temp->pHigh << endl;
			temp = temp->next;
		}
		cout << "Printing done." << endl;
	}



	//==========================QUICKSORT======================
	//inspiration from https://www.geeksforgeeks.org/quicksort-for-linked-list/
	Node* lastNode(Node* root) {
		while (root && root->next)
			root = root->next;
		return root;
	}

	void swap(Node* a, Node* b) {//swaps nodes a with b.
		//cout << "swapping: " << a->pClose << "and " << b->pClose << endl;
		long tTime = a->timestamp;
		float tpOpen = a->pOpen;
		float tpHigh = a->pHigh;
		float tpLow = a->pLow;
		float tpClose = a->pClose;
		string tvBTC = a->vBTC;
		string tvCurr = a->vCurr;
		string twPrice = a->wPrice;

		a->timestamp = b->timestamp;
		a->pOpen = b->pOpen;
		a->pHigh = b->pHigh;
		a->pLow = b->pLow;
		a->pClose = b->pClose;
		a->vBTC = b->vBTC;
		a->vCurr = b->vCurr;
		a->wPrice = b->wPrice;

		b->timestamp = tTime;
		b->pOpen = tpOpen;
		b->pHigh = tpHigh;
		b->pLow = tpLow;
		b->pClose = tpClose;
		b->vBTC = tvBTC;
		b->vCurr = tvCurr;
		b->wPrice = twPrice;

		//cout << "a close: " << a->pClose << " | b close: " << b->pClose << endl;
	}

	Node* partition(Node* l, Node* h) {
		// Node* l(ast) is pivot

		float hHigh = h->pHigh;	//sorting based on the high price in each interval

		Node* i = l->prev;

		for (Node* iter = l; iter != h; iter = iter->next) {
			if (iter->pHigh <= hHigh) {				//if current node has a lower price than the pivot,
				i = (i == nullptr) ? l : i->next;	//if i is null, place l there, if not keep going.
				swap(i, iter);
			}
		}
		i = (i == nullptr) ? l : i->next;
		swap(i, h);
		return i;
	}

	void _QuickSort(Node* l, Node* h) {
		if (h != nullptr && l != h && l != h->next) {
			Node* p = partition(l, h);
			_QuickSort(l, p->prev);
			_QuickSort(p->next, h);
		}
	}

	void QuickSort() {
		cout << "Starting QuickSort..." << endl;
		Node* h = lastNode(head);
		_QuickSort(head, h);
		cout << "QuickSort done." << endl;
	}
};
