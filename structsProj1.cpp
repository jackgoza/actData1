/*
Name:	Jack Goza, Joshua Ford, Scott Peery
Course:	CS303
Program:	Project 1A
Due Date:	

Description: This is an assignment tracker. It reads in a file as well as takes 
input from a menu based GUI. It will track the number of assignments in three ways. 
1. assigned, 2. completed, 3. completed/uncompleted assignments that are late.
The GUI will allow the user to read in a txt file of assignments and status: this 
includes dates assigned, due, description, and status. The menus will also allow
the user to do the following:
1. add new assignment
2. complete an assignment
3. edit the assignment due date
4. edit the assignment description
5. output number of assignments due
6. output number of assignments late
7. output assignments due in descending order
8. output assignments late in descending order
The output on screen will be as follows:
<date due>, <description>, <date assigned>, <assignment status>
ex: 2-11-2015, linked lists, 2-2-2-15, late

Inputs: Will read in a txt file into a doubly linked list

Outputs: Will output to original txt file, updating and over writing to reflect
changes made. i.e.- new assignments added, assignments completed, assignments late.

Algorithm:

Check that input file exists
Read in file
Check data before adding to lists
Throw exception and handle if bad info
Assign data read to doubly linked list
while reading in data, put in descending order
	this will make searching by date easier as well as adding
	new assignments in the correct order maximizing efficiency
Close file
Do this at opening of program every time to ensure any additions or
	changes are included for the user
Create menu based GUI
	Use switch case to handle choices

Write to file(Update function)
Open file for writing ONLY when output function called
Close file when completed
This will update and overwrite previous file with the lists in descending order,
allowing an O(n) efficiency when imported the next time.

*****SPECIAL NOTE*****
GitHub is not user friendly to noobs, but gives extra credit
Must submit a project report (3-4 pages) with the following information
1. Assumptions, 2. UML class diagram, 3. Efficiency Algorithm, 4. References
Must submit Individual Report

  stuctsProj1.cpp
  dataone*/

#include <stdio.h>
#include "assignment.h"
#include <fstream>
#include <list>
#include <iterator>
#include <limits>

#undef max

using namespace std;

bool inputDate(Date& date){
	string temp;
	string buffer;
	while (true){
		
		try {
			cin >> temp;
			getline(cin, buffer);
			Date check(temp, US);
			if (check.valid_date(check.getYear(), check.getMonth(), check.getDay())){
				date = check;
				return true;
			}
			else{
				throw exception();
			}
		}
		catch (exception){
			cout << "Invalid date\n";
			return false;
		}
	}
}

bool addAssignment(list<assignment> AssignmentList, assignment& newAssn){ // use this to make a new assignment
	string temp;
	char tempC;
	Date date;

	cout << "Assigned Date: (mm-dd-yyyy): ";
	if (!inputDate(date)){ // if date is invalid, do not continue
		cout << "Assignment was not added\n";
		return false;
	}

	newAssn.setAssignedDate(date); // if we're here, date was valid, add it to newAssn and continue
	
	list<assignment>::iterator it = AssignmentList.begin();

	do{
		if (it->getAssignedDate() == newAssn.getAssignedDate()){
			cout << "Assignment already exists, no assignment added";
			return false;
		}
		it++;
	} while (it != AssignmentList.end());

	do{
		cout << endl << "Description: ";
		getline(cin, temp);
		newAssn.setDescription(temp);
	} while (temp == "");

	cout << endl << "Due Date: ";
	if (!inputDate(date)){
		cout << "Assignmnent was not added\n";
		return false;
	}
	if (date <= newAssn.getAssignedDate()){
		cout << "Due date must be later than assigned date, assignment was not added\n";
		return false;
	}

	newAssn.setDueDate(date);
		
	do{
		cout << endl << "Status: " << endl << "1. assigned\n2, completed\n3. late\n";
		cin >> tempC;
		getline(cin, temp);
	}while (temp != "" || (int)tempC < 49 || int(tempC > 51));
	newAssn.setStatus((int)tempC - 48);

	return true;
}

void printAssignments(list<assignment> Assn, list<assignment> Comp){
	
	cout << "Assignments still due: \n";
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++){
		cout << *it << endl;
	}
	
	cout << "Completed assignments:\n";
	for (it = Comp.begin(); it != Comp.end(); it++){
		cout << *it << endl;
	}
	
}

bool completeAssignment(list<assignment>& List, list<assignment>::iterator& it){
	assignment temp;
	Date date;
	cout << "Enter assigned date: ";

	if (!inputDate(date)){
		cout << "No changes were made\n";
		return false;
	}
	for (it = List.begin(); it != List.end(); it++){
		if (it->getAssignedDate() == date){
			if (it->getStatus() != assigned){
				cout << "Assignment already completed, no changes were made\n";
				return false;
			}

			cout << "Enter completion date: ";

			if (!inputDate(date)){
				cout << "No changes were made\n";
				return false;
			}

			if (date < it->getAssignedDate()){
				cout << "Assignment cannot be completed before it is assigned, no changes were made\n";
				return false;
			}

			if (date <= it->getDueDate()){
				it->setStatus(2);
				return true;
			}

			it->setStatus(3);
			return true;
		}
	}
	cout << "Assignment not found, no changes were made\n";
	return false;
}

void save(string File, list<assignment> List){ // overwrite file with new list
	ofstream out(File);                        // fixed so it doesn't add newline to end of file
	list<assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++){
		out << *it;
		if (*it != List.back()){
			out << endl;
		}
	}
	out.close();
}

bool editAssignment(list<assignment>& List,list<assignment>::iterator& it){
	Date date;
	cout << "Enter assigned date to edit assignment: ";
	if (!inputDate(date)){
		cout << "No changes were made\n";
		return false;
	}
	string tempString;
	string buffer;
	char tempChar;

	for (it = List.begin(); it != List.end(); it++){
		if (it->getAssignedDate() == date){

			cout << *it << endl;

			do{
				cout << "Choose what to edit:\n1. Due Date\n2. Description\n3. Status\n";
				cin >> tempChar;
				getline(cin, tempString);
			} while (tempString != "" || (int)tempChar < 49 || int(tempChar > 51));

			switch (tempChar){
			case '1':
				cout << "Enter new due date: ";
				if (!inputDate(date)){
					cout << "No changes were made\n";
					return false;
				}
				if (date <= it->getAssignedDate()){
					cout << "Due date must be after assigned date, no changes were made\n";
					return false;
				}
				it->setDueDate(date);
				return true;
			case '2':
				cout << "Enter new description: ";
				getline(cin, tempString);
				it->setDescription(tempString);
				break;
			case '3':
				do{
					cout << endl << "Select new status: " << endl << "1. assigned\n2, completed\n3. late\n";
					cin >> tempChar;
					getline(cin, tempString);
				} while (tempString != "" || (int)tempChar < 49 || int(tempChar > 51));
				it->setStatus((int)tempChar - 48);
				break;
			}
			return true;
		}
	}
	cout << "Assignment does not exist\n";
	return false;
}

void displayLate(list<assignment> Comp)//diplay number of late status
{
	// On demand, count the number of late assignments.
	// late status should only be in the list of assigned
	int count = 0;
	list <assignment>::iterator it;
	for (it = Comp.begin(); it != Comp.end(); it++) {
		if (it->getStatus() == late) {
			count++;
		}	
	}
	cout << count << endl;
}

string getFile(string FileName, list<assignment>& Assignments, list<assignment>& Assigned, list<assignment>& Completed) {
	bool checkFile = false;
	while (checkFile == false) {
		int choice;
		ifstream fin(FileName);
		if (!fin) {
			cout << "Error opening file. Make sure the file is in the same folder as the program.\n";
			cout << "Please choose from the following actions:\n"
				<< "1. Re-enter the file name and extension.\n"
				<< "2. Exit the program.\n";
			cin >> choice;
			switch (choice) {
			case 1: checkFile = false;
				cout << "Enter the name of the file you want to open. Please include file extension:\n ";
				cin >> FileName;
				break;
			case 2: return "Exiting"; break;
			}
		}
		else {
			assignment temp;
			checkFile = true;
			while (!fin.eof()) {
				fin >> temp;
				Assignments.push_back(temp);
				if (temp.getStatus() == assigned) {
					Assigned.push_back(temp);
				}
				else {
					Completed.push_back(temp);
				}
			}
		}
	}
	return FileName;
}

int main(){
	list<assignment> Assignments; // all assignments
	list<assignment> Assigned;
	list<assignment> Completed; // completed and late assignments

	assignment temp;

	string FileName;//used incase of diffrent file extensions .txt and .csv

	// determine file extesnion type and name to open with fin variable
	cout << "Enter the name of the file you want to open, please include file extension: " << endl;
	cin >> FileName;

	//bool goodToGo;
	string CorrectFileName = getFile(FileName, Assignments, Assigned, Completed);

	// initiate input/output variables
	//if (!goodToGo)//check that file exists
	//{
	//	cout << "Program will now exit." << endl;
	//	system("pause");
	//	return -1;
	//}


	// initial sort of all lists
	Assignments.sort();
	Assigned.sort();
	Completed.sort();
	
	
	bool menuBool = false; bool runAgain = true;
	int menuInput = 0;
	Date date;
	list<assignment>::iterator it;
	
	cout << "Welcome to the menu based assignment system!\n";
	
	while(runAgain){
		menuBool = false;
	
		while (!menuBool){
	
		cout << "\n"<< "What would you like to do?\n";
		cout << "1. Display assignments\n"
		<< "2. Add assignment to workload\n"
		<< "3. Edit assignment\n"
		<< "4. Log assignment completion\n"
		<< "5. Display number of late assignments\n"
		<< "6. Save    7. Exit\n\n";
		
		cin >> menuInput;
		if (cin.good()){
			menuBool=true;
			break;
		}
		else{
			cout << "Please limit input to integer coressponding to your choice\n\n";
			cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
		switch(menuInput){
			cin.clear();
			case 1 : 
				printAssignments(Assigned, Completed); break; // functional, TODO make it look pretty

			case 2 : // works
				if (addAssignment(Assignments, temp)){
					Assignments.push_back(temp);
					Assignments.sort();
					if (temp.getStatus() == assigned){
						Assigned.push_back(temp);
						Assigned.sort();
					}
					else{
						Completed.push_back(temp);
						Completed.sort();
					}
				}
				break;

			case 3: // TODO reorganize lists, erase edited assignment from all lists
				if (editAssignment(Assignments, it)){

					list<assignment>::iterator it2;
					for (it2 = Assigned.begin(); it2 != Assigned.end(); it2++){
						if (*it2 == *it){
							Assigned.erase(it2);
							break;
						}
					}

					for (it2 = Completed.begin(); it2 != Completed.end(); it2++){
						if (*it2 == *it){
							Completed.erase(it2);
							break;
						}
					}

					if (it->getStatus() == assigned){
						Assigned.push_back(*it);
						Assigned.sort();
					}
					else{
						Completed.push_back(*it);
						Completed.sort();
					}
				}
				break;

			case 4: 
				if (completeAssignment(Assignments, it)){
					list<assignment>::iterator it2;
					for (it2 = Assigned.begin(); it2 != Assigned.end(); it2++){
						if (*it2 == *it){
							Assigned.erase(it2);
							break;
						}
					}
					Completed.push_back(*it);
					Completed.sort();
				}
				break;
		
			case 5: 
				displayLate(Completed); break; // works
		
			case 6: 
				save(FileName, Assignments); break; //works
			
			case 7 : 
				"Goodbye!\n"; runAgain = false; break;
		}
	}
	
	system("pause");
	return 0;
}