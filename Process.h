#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

class Process {
public:
	string task;
	int priority;
	int length;
	int original_length;	//used for display purposes only
	int count; 
	int arrival;
	bool registered; 
	vector <Process> tasks;

	Process(string t, int p, int l, int a);

	Process();


	string getTask() { return task; }
	int getPriority() { return priority; }
	int getLength() { return length; }
	int getOriginalLength() { return original_length; }
	int setLength(int input) {
		input = input - 1;
		this->length = input;
		return length;
	}
	int getArrival() { return arrival; }
	int getStatus() { return registered; }
	int getCount() { return count; }
	int setStatus(bool value) {
		this->registered = value; 
		return value;
	}
	int setCount() {
		count++; 
		return count; 
	}

	int clear(); 
};



