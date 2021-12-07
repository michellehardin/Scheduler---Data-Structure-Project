#include "Heap.h"

Heap::Heap() {
	time = -1; 
	count = 0; 
}

//The following function registers/schedules a task. 
void Heap::regTask(string t, int p, int l, int a) {

	//First we look to see if that task has already previously been registered. 
	for (int i = 0; i < heapvec.size(); i++) {
		if (heapvec[i].getTask() == t) {
			cout << "Tasks already in schedule. Please remove and re-register, if you want to change it." << endl << endl;
			return; 
		}
	}

	//Else we create a Process type to hold the task information and then push it onto our heap vector. 
	Process temp(t, p, l, a);
	heapvec.push_back(temp);
	cout << "Task registered." << endl; 

	//We sort the vector by the longest length or most elapsed time. 
	sort(heapvec.begin(), heapvec.end(), [](const Process& lhs, const Process& rhs) {
		return lhs.length > rhs.length;
		});

	//We then sort the vector first on the task arrival time. 
	sort(heapvec.begin(), heapvec.end(), [](const Process& lhs, const Process& rhs) {
		return lhs.arrival < rhs.arrival;
		});

	//Secondly, we sort the vector on the priority level. This ensures that we have prioritized the heap, first by priority then by arrival. 
	sort(heapvec.begin(), heapvec.end(), [](const Process& lhs, const Process& rhs) {
		return lhs.priority < rhs.priority;
		});

	cout << endl; 
}

//This private function is called upon when we are moving from the heapvec to simulation mode. 
void Heap::regTask(Process temp) {

	for (int i = 0; i < heap.size(); i++) {
		if (heap[i].getTask() == temp.task) {
			return;
		}
	}

	heap.push_back(temp);
	
	//We sort this vector to make sure the tasks implement a priority queue. 
	sort(heap.begin(), heap.end(), [](const Process& lhs, const Process& rhs) {
		return lhs.priority < rhs.priority;
		});
}

//The display function shows the current schedule (in schedule mode). 
void Heap::displaySchedule(Heap& temp) {

	//If nothing has been scheduled, return. 
	if (heapvec.empty() == true) {
		cout << "No scheduled task(s)" << endl << endl; 
		return; 
	}
	
	cout << endl; 
	cout << "Current scheduled task(s): " << endl;

	for (Process entry : heapvec) {
		cout << "     Task name: " << entry.getTask() << "  Priority: " << entry.getPriority() << "  Length: " << entry.getLength() << "  Arrival: " << entry.getArrival() << endl;
	}
	cout << endl; 
}

//This displays the information required during the simulation mode when the tasks are being stepped through. 
void Heap::displaySim(Heap& temp) {

	//If the heap is empty, return. 
	if (heap.empty() == true) {
		cout << "No tasks left to execute." << endl << endl;
		return; 
	}

	//If the time is -1, no steps have been taken yet. They are just entering simulation mode. 
	if (time == -1) {
		cout << endl; 
		cout << "Clock has not started / No steps have occured" << endl;
	}
	else
		cout << "Current time: " << time << endl; 

	//If the current is null, the current task is none.
	if (current.priority == NULL) {
		cout << "Current Task: None" << endl; 
	}
	//Else if, the current has a status of false, it hasn't arrived. This is just a fail safe -- just in case. 
	else if (current.getStatus() == false) {
		cout << "Current Task: None" << endl; 
	}
	//Else display the current task being executed. 
	else
		cout << "Current Task: " << current.task << " of Priority " << current.priority << " of Length " << current.length << " arrival at " << current.arrival << endl;

	//Display all remaining tasks that have not yet arrived -- waiting to enter. 
	for (Process entry : heap) {
		if (entry.getStatus() == false) {
			cout << "Waiting to be Executed --- " << "Task name: " << entry.getTask() << "  Priority: " << entry.getPriority() << "  Length: " << entry.getLength() << "  Arrival: " << entry.getArrival() << endl;
		}
	}

	cout << endl; 
}

//The remove functions removes a task IF it has been scheduled. 
bool Heap::remove(string input) {


	for (int i = 0; i < heapvec.size(); i++) {

		string comp = heapvec[i].getTask(); 

		//If the task is found in the vector, we are going to erase that (determined by i, it's position) 
		if (comp == input) { 
			heapvec.erase(heapvec.begin() + i);
			return true;
		}
	}

	return false;
}

//The removeSim task removes items from the priority queue after they have completed execution. 
bool Heap::removeSim(string input, int position) {

	for (int i = 0; i < heap.size(); i++) {

		string temp = heap[i].getTask();

		//if the task at i equals the input, we delete it from the heap. 
		if (temp == input) {
			cout << "Task " << heap[i].getTask()<< " completed. Item removed." << endl << endl;
			heap.erase((heap.begin() + position)); 
			return true;
		}
	}

	return false;
}

//This clears our vector -- used during scheduling mode. 
void Heap::clearHeap() {
	heapvec.clear();
}

//This moves all of our tasks from the vector to the heap.
void Heap::simulation() {
	cout << endl; 
	for (int i = 0; i < heapvec.size(); i++) {
		Process temp = heapvec[i];
		regTask(temp);
	}

}

void Heap::schedule() {
	clearHeap(); 
	time = -1;
	heap.clear();
	current.task = " ";
	current.priority = NULL;
	current.length = NULL;
	current.arrival = NULL;
	
}

//This function steps through task.
void Heap::step() {
	time = time + 1;	//First we increment our time. 
	cout << "Current Time: " << time << endl;	

	//If the heap is empty, no tasks were scheduled when we entered simulation mode. 
	if (heap.empty() == true) {
		return;
	}

	//This guarantees that the function is registered and no longer waiting to be executed. 
	for (int i = count; i < heap.size(); i++) {
		if (heap[i].getArrival() <= time && heap[i].getStatus() == false) {
			heap[i].setStatus(true);
			cout << "Task " << heap[i].getTask() << " has arrived." << endl; 
		}
	}

	//If heap has tasks, we traverse through them until the task arrival equals the time (or steps passed). 
	for (int i = count; i < heap.size(); i++) {

		if (heap[i].getArrival() <= time) {

			//The set Length function (defined in the Process.h file) increments the task's length by 1. 
			heap[i].setLength(heap[i].getLength());
			heap[i].setCount();
			cout << "Current Task: " << heap[i].getTask() << " of Priority " << heap[i].getPriority() << " at " << heap[i].getCount() << " of " << heap[i].getOriginalLength() << endl;
			cout << endl; 

			//We make sure that the heap is not empty. If not, we set the current to the current task @ heap[i]
			if (heap.empty() == false) {
				current = heap[i];
			}

			//If the tasks has completed, we remove it from the heap. 
			if (heap[i].getLength() == 0) {
				removeSim(heap[i].getTask(), i);

				for (int j = 0; j < heap.size(); j++) {
					if (heap[j].getStatus() == true) {
						current = heap[j];
						return;
					}
				}

				current.task = " ";
				current.priority = NULL;
				current.length = NULL;
				current.arrival = NULL;
			}

			return;
		}
	}

}

//This function will run the simulation until all tasks have been completed and removed. 
void Heap::run() {

	while (heap.empty() == false) {
		step(); 
	}

};

//This function will run the simulation until the specified time. 
void Heap::run_until(int input_time) {

	do{
		step(); 
	} while (time < input_time);

};

//This resets the heap by resetting the time to -1, clearing the heap, and resetting the heap to all items stored in vector.
//It all resets the current. 
void Heap::reset() {

	time = -1; 
	heap.clear();
	simulation(); 
	current.task = " ";
	current.priority = NULL; 
	current.length = NULL; 
	current.arrival = NULL; 

};


