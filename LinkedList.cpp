#include "LinkedList.h"

//Default Constructor
LinkedList::LinkedList()
{
	head = nullptr; tail = nullptr; size = 0;
}
LinkedList::~LinkedList()
{
	Node* iter = head;
	Node* temp = iter->next;
	while (iter != nullptr)
	{
		delete iter;
		iter = temp;
		
		if (iter == nullptr)
		{
			break;
		}
		temp = iter->next;
	}
}

//Add a node to the linked list
void LinkedList::CreateAndAddNode(long timestamp, float high)
{
	//node creation
	Node* node = new Node(timestamp, high);

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

	size++;
}

LinkedList LinkedList::fragmentList(long start, long end)
{
	LinkedList nuLinkedList = LinkedList();
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

//Prints the linked list
void LinkedList::Print()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		cout << iter->pHigh << " ";
		iter = iter->next;
	}
	cout << endl;
	cout << endl;
}
void LinkedList::Print(int num)
{
	Node* iter = head;
	for (int i = 0; i < num; i++)
	{
		cout << iter->pHigh << " ";
		iter = iter->next;
	}
	cout << endl;
	cout << endl;
}

////====================\\\\
///=====Merge Sort ======\\\
//========================\\

//Brings two pieces together and sorts them
LinkedList::Node* LinkedList::Merge(Node* leftList, Node* rightList, int leftLength, int rightLength) {
	Node* root = nullptr;
	Node* iter = nullptr;
	Node* leftIter = leftList;
	Node* rightIter = rightList;
	Node* rightEnd = rightIter;
	Node* leftEnd = leftIter;

	if (leftIter->pHigh < rightIter->pHigh)
	{
		root = leftIter->Clone();
		leftIter = leftIter->next;
	}
	else {
		root = rightIter->Clone();
		rightIter = rightIter->next;
	}

	iter = root;

	//Setting up the bounds for the end of the lists
	for (int i = 0; i < leftLength; i++)
	{
		leftEnd = leftEnd->next;
	}
	for (int i = 0; i < rightLength; i++)
	{
		rightEnd = rightEnd->next;
	}

	while (leftIter != leftEnd && rightIter != rightEnd)
	{
		if (leftIter->pHigh < rightIter->pHigh)
		{
			iter->next = leftIter->Clone();
			iter->next->prev = iter;
			iter = iter->next;
			leftIter = leftIter->next;
		}
		else
		{
			iter->next = rightIter->Clone();
			iter->next->prev = iter;
			iter = iter->next;
			rightIter = rightIter->next;
		}
	}
	//If left list is not empty
	if (leftIter != rightList && leftIter != nullptr)
	{
		while (leftIter != rightList && leftIter != nullptr)
		{
			iter->next = leftIter->Clone();
			iter->next->prev = iter;
			leftIter = leftIter->next;
			iter = iter->next;
		}
	}
	//If right list is not empty
	else if (rightIter != rightEnd && rightIter != nullptr)
	{
		while (rightIter != rightEnd && rightIter != nullptr)
		{
			iter->next = rightIter->Clone();
			iter->next->prev = iter;
			iter = iter->next;
			rightIter = rightIter->next;
		}
	}

	tail = iter;
	return root;
}
//Sorts from start node to end node given the length in between them
LinkedList::Node* LinkedList::MergeSort(Node* start, Node* end, int length) {
	Node* middle = start;
	int dist = 1;
	Node* left = nullptr;
	Node* right = nullptr;

	if (length == 1)
	{
		return start;
	}
	else if (length == 2)
	{
		return Merge(start, end, 1, 1);
	}

	for (int i = 0; i < length / 2; i++)
	{
		middle = middle->next;
		dist++;
	}

	left = MergeSort(start, middle, dist);
	right = MergeSort(middle->next, end, length - dist);
	return(Merge(left, right, dist, length - dist));
}
//Sets the tail to the correct value
void LinkedList::setTail(Node* root)
{
	while (root->next != nullptr)
	{
		root = root->next;
	}
	tail = root;
}

////==================\\\\
///=====Quick Sort=====\\\
//======================\\

LinkedList::Node* LinkedList::lastNode(Node* root)
{
	while (root && root->next)
		root = root->next;
	return root;
}

void LinkedList::swap(Node* a, Node* b)
{
	//swaps nodes a with b.
		//cout << "swapping: " << a->pClose << "and " << b->pClose << endl;
	long tTime = a->timestamp;
	//float tpOpen = a->pOpen;
	float tpHigh = a->pHigh;
	//float tpLow = a->pLow;
	//float tpClose = a->pClose;
	//string tvBTC = a->vBTC;
	//string tvCurr = a->vCurr;
	//string twPrice = a->wPrice;

	a->timestamp = b->timestamp;
	//a->pOpen = b->pOpen;
	a->pHigh = b->pHigh;
	//a->pLow = b->pLow;
	//a->pClose = b->pClose;
	//a->vBTC = b->vBTC;
	//a->vCurr = b->vCurr;
	//a->wPrice = b->wPrice;

	b->timestamp = tTime;
	//b->pOpen = tpOpen;
	b->pHigh = tpHigh;
	//b->pLow = tpLow;
	//b->pClose = tpClose;
	//b->vBTC = tvBTC;
	//b->vCurr = tvCurr;
	//b->wPrice = twPrice;

	//cout << "a close: " << a->pClose << " | b close: " << b->pClose << endl;
}

LinkedList::Node* LinkedList::partition(Node* l, Node* h)
{
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

void LinkedList::_QuickSort(Node* l, Node* h)
{
	if (h != nullptr && l != h && l != h->next) {
		Node* p = partition(l, h);
		_QuickSort(l, p->prev);
		_QuickSort(p->next, h);
	}
}

void LinkedList::QuickSort()
{
	cout << "Starting QuickSort..." << endl;
	Node* h = lastNode(head);
	_QuickSort(head, h);
	cout << "QuickSort done." << endl;
}