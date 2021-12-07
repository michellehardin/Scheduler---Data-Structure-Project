#include "Process.h"

//Default constructor for Process Class
Process::Process() {

}

//This constuctor initializes and sets up my Process Class to be able to take in task, priority, length and arrival for scheduler. 
Process::Process(string t, int p, int l, int a) {

	task = t;
	priority = p;
	length = l; 
	original_length = l;  
	arrival = a;
	count = 0; 
}

