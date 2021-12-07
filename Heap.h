#include <iostream>
#include <vector>
#include <algorithm>

#include "Process.h"

using namespace std;
using std::exception; 

class Heap {
public: 
	string task; 
	int priority; 
	int length; 
	int arrival; 

	int time; 
	int count; 
	int elements; 

	vector <Process> heapvec; 
	vector <Process> heap;  

	Process current;

	void simulation();
	void schedule(); 

	void regTask(string t, int p, int l, int a);
	void displaySchedule(Heap& input);
	void displaySim(Heap& input);
	bool remove(string t);
	bool removeSim(string t, int position);
	void clearHeap();

	Heap();

	void step();
	void run(); 
	void run_until(int time); 
	void reset(); 

private: 
	void regTask(Process temp);
};


