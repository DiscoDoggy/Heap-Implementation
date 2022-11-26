#include <iostream>
#include <string>
#include <cstdlib>
#include "Heap.h"
#include "PrintJob.h"

using namespace std;

Heap::Heap() {
	numItems = 0;
}

void Heap::enqueue ( PrintJob* usrJob) {
	PrintJob *temp1 = nullptr;
	//PrintJob *temp2 = nullptr;
	int index = 0;
	
//checks if adding an element would go out of range
	if (numItems + 1 > MAX_HEAP_SIZE) {
		cout << "cannot enqueue. Print job queue is full" << endl;
		return;
	}
//adds first element if intial array is empty
	else if (numItems == 0) {
		arr[0] = usrJob;
		numItems = numItems + 1;
		return;
	}
	else {
		arr[numItems] = usrJob;
		numItems = numItems + 1;
		// should be last element in array which should be the user job element
		index  = numItems - 1;
	// there shold always be a parent because of the else if case above
		temp1 = arr[getParent(index)]; // parent node


		//while usrJob is not at root and 
		//whlie parent priority is less than user job, swap
		while (index != 0 && temp1->getPriority() < usrJob->getPriority()) {
			
			if (index > 0 && temp1 -> getPriority() < usrJob -> getPriority()) {
				
				swap(arr[index], arr[getParent(index)]);
				index = getParent(index);

				if (index > 0) {
					temp1 = arr[getParent(index)];
				}
			}
		}
	}

}

void Heap::dequeue () {
	if (numItems == 0) {
		return;
	}
	else {
		swap(arr[numItems - 1], arr[0]);
		numItems = numItems - 1;

		if (numItems > 0) {
			trickleDown(0);
		} 
	}
}



void Heap::trickleDown(int currIndex) {
	//currIndex is currently 0
	PrintJob *currIndexPtr = arr[currIndex];
	PrintJob *biggerPriority = nullptr;
	PrintJob *temp1 = nullptr;
	//PrintJob *temp2 = nullptr;
	int biggerIndex = 0;

	while (getLeftChild(currIndex) < numItems) { //while a left child exists
		//setting up to make a comparison with right side if it exists
		biggerPriority = arr[getLeftChild(currIndex)];
		biggerIndex = getLeftChild(currIndex);

		if (getRightChild(currIndex) < numItems) { //if right child exists
			temp1 = arr[getRightChild(currIndex)];
			
			//if right priority bigger than left set bigger priority equal to right
			if (temp1->getPriority() > biggerPriority -> getPriority()) { 
				biggerPriority = arr[getRightChild(currIndex)];
				biggerIndex = getRightChild (currIndex);
			}
		}
			// if already in correct place return
		if (currIndexPtr-> getPriority() > biggerPriority->getPriority()) {
			return;
		}
		else { //not in correct place so we swap and reset the currIndex
			swap (arr[currIndex], arr[biggerIndex]);
			currIndex = biggerIndex;
		}



	}
}




PrintJob* Heap::highest () {
	if (numItems == 0) {
		return nullptr;
	}
	else {
		return arr[0];
	}
}


void Heap::print () {
	PrintJob *highestPriority = nullptr;

	if (numItems == 0) {
		return;
	}
	else {
		highestPriority = arr[0];
		
		cout
			<< "Priority: " << highestPriority-> getPriority() 
			<< " Job Number: " << highestPriority -> getJobNumber() 
			<< " Number of Pages: " << highestPriority -> getPages() 
			<< endl; 
	}
		
}

int Heap::getParent(int currIndex) {
	return (currIndex - 1) / 2;
}
int Heap::getLeftChild(int currIndex) {
	return (2 * currIndex) + 1;
}
int Heap::getRightChild(int currIndex) {
	return (2 * currIndex) + 2;
}