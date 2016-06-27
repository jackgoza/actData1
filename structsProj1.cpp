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

#undef max // this is used to a compile problem in VS2015

using namespace std;

// decleration and defined functions for main

// input date funciton will take user input and use date.h
// to validate input for an actual date. this is a bool function
// that will return true of false (true for good input, false for
// incorrect input. it makes no changes to lists or file
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

//boolean function that checks for valid info before adding an assignment to a list
//since the assigned date is unique, it validates that the date doesnt exist prior
//to adding it to a list. it will check and validate all info and then based on the 
//status that will be assigned, this is done by menu option. this function does make
//changes to the list however it does not update the input/ouput file
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

	do{// check to see if date is duplicate
		if (it->getAssignedDate() == newAssn.getAssignedDate()){
			cout << "Assignment already exists, no assignment added";
			return false;
		}
		it++;
	} while (it != AssignmentList.end());

	do{// if here, date not duplicate and its ok to add with all info
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

//this function prints out both the assigned and completed lists
//it prints out to the user, broken up into two parts: assigned and
//completed. both lists are printed in descending order and will reflect
//any changes made that the user has done to the point of printing
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

//this function is a boolean that validates the information provided by the user
//it checks the date is valid and then checks to see if the date exists in the list.
//if it exists, it then looks at the status to see if it is already completed,
//if it isnt, then it allows for a change to be made. if it passes all validation
//it calls the setstatus function to make chages. this function does not itself
//chage anyinformation of the file or lists, it only validates true or false if 
//the change is allowed
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

//this function opens the input file and updates it with the 
//assignments list. once copleted it closes the file
void save(string File, list<assignment> List){ 
	ofstream out(File);                        
	list<assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++){
		out << *it;
		if (*it != List.back()){
			out << endl;
		}
	}
	out.close();
}

//this is a bool funciton that allows the user to duedate, description and status
//it calls the input date function to check the validity of the date being searched,
//which must be search for by assigned date(its the only unique date). once the assigned date is
//found, the user gets a menu to choose what to edit. the function checks any new date entered
//for validity as well as checking to ensure duedate is not before an assigned date
//this function does not change the input/output file, it only makes changes to the list
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

// On demand, count the number of late assignments.
// late status should only be in the list of assigned
// this function will iterate throught the completed list and search for the status of late
//it then keeps count of the number found and outputs the info to the screen for the user
//this function does not save the info nor make changes to the input/output file
void displayLate(list<assignment> Comp)
{
	int count = 0;
	list <assignment>::iterator it;
	for (it = Comp.begin(); it != Comp.end(); it++) {
		if (it->getStatus() == late) {
			count++;
		}	
	}
	cout << count << endl;
}

//takes in string for filename, checks it is a valid file and opens it. while reading in file it puts the info
//into three lists, the main list assignnments which is used to save all changes to be writen back to the 
//valid file, the assinged list and completed list. as the data is added into the assignments list, they are checked
//for status and also added to the appropriate list. while doing all this, each list is put into descending order
//to make adding and edditing the list more efficent. it has a menu option so the user can try again if they miss
//type the filename or to just plain quit the program. after the correct filename has been typed and checked
//the function returns it to the main file so that the save function has the correct file to udate
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

// main program
int main(){
	list<assignment> Assignments; // all assignments
	list<assignment> Assigned;
	list<assignment> Completed; // completed and late assignments

	assignment temp;

	string FileName;//used incase of diffrent file extensions .txt and .csv

	cout << "Welcome to the menu based assignment system!\n";
  
	// determine file extesnion type and name to open with fin variable
	cout << "Enter the name of the file you want to open, please include file extension: " << endl;
	cin >> FileName;

	//call getfile function with return of correct filename string
	string CorrectFileName = getFile(FileName, Assignments, Assigned, Completed);


	// initial sort of all lists
	Assignments.sort();
	Assigned.sort();
	Completed.sort();
	
	// set bool for main program loop
	bool menuBool = false; bool runAgain = true;

	// set up main variables and itterator
	int menuInput = 0;
	Date date;
	list<assignment>::iterator it;
	
	//main loop
	while(runAgain){
		menuBool = false;
	
		//menu loop for selection 
		while (!menuBool){
	
		cout << "\n"<< "What would you like to do?\n";
		cout << "1. Display assignments\n"
		<< "2. Add assignment to workload\n"
		<< "3. Edit assignment\n"
		<< "4. Log assignment completion\n"
		<< "5. Display number of late assignments\n"
		<< "6. Save    7. Exit\n\n";
		
		cin >> menuInput;

		//check for valid input and break out of loop
		if (cin.good()){
			menuBool=true;
			break;
		}
		//non-valid input will restart menu selection loop
		else{
			cout << "Please limit input to integer coressponding to your choice\n\n";
			cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//clear anything remaining before starting loop over
		}
	}
		// switch case for menu selection
		switch(menuInput){
			cin.clear();
			case 1 : 
				printAssignments(Assigned, Completed); break; //prints both assigned and completed list

			case 2 : // allows addition of assignments(assigned || completed)
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
				save(FileName, Assignments);//update file with changes
				break;

			case 3:
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
				save(FileName, Assignments);//update file with changes
				break;

			case 4: // edit assigned to show completion
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
				save(FileName, Assignments);//update file with changes
				break;
		
			case 5: // displays count to user of number of completed late assignments
				displayLate(Completed); break; 
		
			case 6: // opens input file to edit changes and additions in desecding order
				save(FileName, Assignments); break; 
			
			case 7 : //exits the program
				"Goodbye!\n"; runAgain = false; break;
		}
	}
	//system("pause");//used during testing
	return 0;
}