/*
Student Name: Michelle Hardin
Student NetID: amh800
Compiler Used: Visual Studio
Program Description:
This program  simulates preemptive task scheduling. 
It schedules tasks during scheduling mode and 
executes them during simulation mode based on priority, arrival, and length.
*/

#include "Heap.h"
#include "Tokenizer.h"
#include <iostream>
#include <fstream>

using namespace std;

bool processFile(istream& is, bool interactive = true)
{
	string task;
	int priority; 
	int length; 
	int arrival; 
	bool schedule_mode=true;
	bool simulation_mode = false; 
	string line; 
	string command;
	string arg1;
	
	Tokenizer tkn;
	Heap test; 

	while (true)
	{
		if (!interactive)
		{
			if (is.eof())
				return true;
		}
		else 
		{
			if (schedule_mode == true) {
				cout << "schedule >> ";
			}
			else
			{
				cout << "simulation >> ";
			}
		}

		//gets line from input stream
		getline(is, line);
		tkn.setString(line);

		//first word in stream should always be a command
		tkn.readWord(command);

		//Below we start checking if the command is recognized

		if (command == "exit")
		{
			cout << "Exiting ...." << endl;
			return false;
		}

		if (command == "load")
		{
			// load expects a filename .. so read one more word
			if (!tkn.readWord(arg1))
			{
				cout << "Missing file name" << endl;
				continue; // skip back to the top of the read loop
			}

			//Attempts to read input file
			ifstream fin;
			bool status = true;
			fin.open(arg1);
			if (fin.is_open())
			{
				status = processFile(fin, false);
			}
			else
			{
				cout << "Failed to open the file" << endl;
			}
			fin.close();
			if (!status)
				return false;
		}

		//This function command enters the program into schedule mode. 
		if (command == "schedule")
		{
			if (schedule_mode == true) {
				cout << "You are already in scheduling mode." << endl; 
			}
			else {
				test.schedule(); 
				schedule_mode = true;
				simulation_mode = false;
			}
		}

		//This command enter the program into simulation mode. 
		if (command == "simulate") {

			if (simulation_mode == true) {
				cout << "You are already in simulation mode." << endl; 
			}
			else {
				test.simulation();
				simulation_mode = true;
				schedule_mode = false;
			}
		}

		//This command will register a task if it is in schedule mode and meets the required priority, length, and arrival. 
		if (command == "register")
		{
			if (schedule_mode == true) {
				if (tkn.readWord(task)) {

					if (tkn.readInteger(priority)) {
						if (priority > 0 && priority < 101) {

							if (tkn.readInteger(length)) {

								if (length > 0) {

									if (tkn.readInteger(arrival)) {

										if (arrival > -1) {

											test.regTask(task, priority, length, arrival);

										}
										else
											cout << "Invalid arrival time -- cannot be negative" << endl;
									}
								}
								else
									cout << "Invalid length -- please enter a length greater than 0" << endl;
							}
						}
						else
							cout << "Invalid priority value -- please enter a priority between 1 and 100" << endl;
					}

				}
				else
					cout << "Task name must be a string" << endl;
			}
			else
				cout << "This function is only supported in schedule mode." << endl;
		}

		//This command will remove an item from the schedule -- requires to be in schedule mode. 
		if (command == "remove")
		{
			if (schedule_mode == true) {
				if (tkn.readWord(task)) {
					bool remove = test.remove(task);

					if (remove == true) {
						cout << "Task removed." << endl;
					}
					else
						cout << "No task exist in the schedule matches " << task << endl;

				}
				cout << endl;
			}
			else
				cout << "This function is only supported in schedule mode." << endl; 
		}

		//This command displays the schedule or priority queue task, depending on which mode you are in. 
		if (command == "display")
		{
			if (schedule_mode == true) {
				test.displaySchedule(test);
			}
			else
			{
				test.displaySim(test);
			}
		}

		//This command is supported in simulation mode, and will either step once or by a specified step amount. 
		if (command == "step")
		{
			if (simulation_mode == true) {
				if (tkn.readInteger(length)) {
					for (int i = 0; i < length; i++) {
						test.step();
					}
				}
				else
					test.step(); 
			}
			else
				cout << "This function is only supported in simulation mode." << endl;
		}

		//This command is supported in simulation mode, and will either run completely through the queue or until a specified time. 
		if (command == "run")
		{
			if (simulation_mode == true) {
				if (tkn.readInteger(length)) {
					test.run_until(length);
				}
				else
					test.run(); 
			}
			else
				cout << "This function is only supported in simulation mode." << endl;
		}

		//This command clears the schedule -- must be in schedule mode. 
		if (command == "clear")
		{
			if (schedule_mode == true) {
				test.clearHeap();
				cout << "Schedule has been cleared" << endl << endl; 
			}
			else
				cout << "This function is only supported in schedule mode." << endl;
		}

		//This command will reset the simulation to it's first values, reseting the clock and queue. 
		if (command == "reset")
		{
			if (simulation_mode == true) {
				test.reset();
			}
			else
				cout << "This function is only supported in simulation mode." << endl;
		}
		

		//This ensures that the command input is valid. 
		if (command != "schedule" && command != "simulate" && command != "register" && command != "display" && command != "step" && command != "run" && command != "remove" && command != "clear" && command != "load" && command != "reset" && command != "exit")
			cout << "Invalid Input" << endl;
	}

};



int main()
{

cout << "Welcome. The following commands are supported: " << endl;
cout << "By default, we will start in schedule mode." << endl; 
cout << endl; 

cout << "Schedule Mode: " << endl; 
cout << "   register <task> <priority> <length> <arrival>" << endl;
cout << "   remove <task>" << endl;
cout << "   clear" << endl << endl;
cout << "Simulation Mode: " << endl;
cout << "   step" << endl;
cout << "   step <time>" << endl;
cout << "   run" << endl;
cout << "   run <time>" << endl;
cout << "   reset" << endl << endl;
cout << "Commands supported in either mode: " << endl; 
cout << "   schedule" << endl;
cout << "   simulate" << endl;
cout << "   load <filename>.txt" << endl;
cout << "   display" << endl;
cout << "   exit" << endl << endl;

processFile(cin);

};