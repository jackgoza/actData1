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

Date inputDate(){
	Date date;

	string temp;
	while (true){
		
		try {
			getline(cin, temp);
			Date date(temp);
			if (date.valid_date(date.getDay(), date.getMonth(), date.getYear())){
				return date;
			}
			else{
				throw exception();
			}
		}
		catch (exception){
			cout << "Please enter a valid date(dd-mm-yyyy): ";
		}
	}
}

assignment getAssn(){
	assignment newAssn;
	string temp;
	char tempC;

	cout << "Due Date: (dd-mm-yyyy); ";
	newAssn.setDueDate(inputDate());

	cout << endl << "Description: ";
	getline(cin, temp);
	newAssn.setDescription(temp);

	do{
		cout << endl << "Assigned Date: ";
		newAssn.setAssignedDate(inputDate());
		if (newAssn.getDueDate() <= newAssn.getAssignedDate())
			cout << "Invalid Assigned Date";

	} while (newAssn.getDueDate() <= newAssn.getAssignedDate());
		
	do{
		cout << endl << "Status: " << endl << "1. assigned\n2, completed\n3. late\n";
		cin >> tempC;
		getline(cin, temp);
	}while (temp != "" || (int)tempC < 49 || int(tempC > 51));
	newAssn.setStatus((int)tempC - 48);

	return newAssn;
}

void addAssn(list<assignment> List){
	string Assnstr, Duestr, Decstr;

	cout << "Enter assignment date in form 00/00/0000 : \n";
	cin >> Assnstr;
	cout << "\nEnter assignment due date in form 00/00/0000 : \n";
	cin >> Duestr;
	cout << "\nEnter assignment description:\n";
	cin >> Decstr;
	
	Date tempAssn(Assnstr);
	Date tempDue(Duestr);
	
	if (tempDue <= tempAssn){
		cout << "Due date is less than or equal to assigned date";
		return;
	}
	
	assignment Assn;
	Assn.setAssignedDate(tempAssn);
	Assn.setDueDate(tempDue);
	Assn.setDescription(Decstr);
	
	list <assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++){
		if (*it == Assn){
			cout << "Assignment already exists";
			return;
		}
	}
	List.push_back(Assn);
} // This is redundant

void sort(list<assignment> L1, list<assignment> L2, list<assignment> L3){
	L1.sort();
	L2.sort();
	L3.sort();
}

void markComplete(list<assignment> Assn, list<assignment> Comp, Date assnDate){
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++){
		if(it->getDueDate() == assnDate){
			assignment Temp = *it;
			it = Assn.erase(it);
			Comp.push_back(Temp);
			return;
		}
	}
	cout << "Assignment not found.\n";
	return;
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

void save(string File, list<assignment> List){
	ofstream out(File);
	list<assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++)
		out << *it << endl;
	out.close();
}

void editDue(list<assignment> Assn)//edit due date
{// first find the assignment with the given due date.
	//more than one assigment may share same due date
	//Don’t edit the assignment in these cases :
	//The assignment with the given assigned list doesn’t exists in the assigned list.
	//The given assigned or due dates are invalid.
	
	assignment Temp;
	int year, month, day;
	Date AssnDate, oldDueDate, newDueDate, tempDate;
	bool valid = false;
	//input AssnDate
	while (valid==false) {
		cout << "Enter assignment date for editing:\n" << endl;
		cout << "Year: " << endl;
		cin >> year;
		cout << "\n" << "Month: " << endl;
		cin >> month;
		cout << "\n" << "Day: " << endl;
		cin >> day;
		valid = tempDate.valid_date(year, month, day);
		AssnDate = tempDate;
	}
	//input oldDueDate
	while (valid == false) {
		cout << "Enter old due date for assignment:\n" << endl;
		cout << "Year: " << endl;
		cin >> year;
		cout << "\n" << "Month: " << endl;
		cin >> month;
		cout << "\n" << "Day: " << endl;
		cin >> day;
		valid = tempDate.valid_date(year, month, day);
		oldDueDate = tempDate;
	}
	//input newDueDate
	while (valid == false) {
		cout << "Enter new due date for assignment:\n" << endl;
		cout << "Year: " << endl;
		cin >> year;
		cout << "\n" << "Month: " << endl;
		cin >> month;
		cout << "\n" << "Day: " << endl;
		cin >> day;
		valid = tempDate.valid_date(year, month, day);
		newDueDate = tempDate;
	}
	
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++) {
		if (it->getAssignedDate() == AssnDate) {
			if (it->getDueDate() == oldDueDate){
				Temp = *it;
				Temp.setDueDate(newDueDate);
				//sort list
				//update txt file
				return;
			}
		}
		cout << "Assignment not found.\n";
		return;
	}
}

void editDescription(list<assignment> Assn)//edit description of assignment
{// first find the assignment with the given due date.
	//more than one assigment may share same due date
	//Don’t edit the assignment in these cases :
	//The assignment with the given assigned list doesn’t exists in the assigned list.
	//The given assigned date is invalid.
	assignment Temp;
	Date AssnDate;
	string newDescription;
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++) {
		if (it->getAssignedDate() == AssnDate) {
			Temp.setDescription(newDescription);
			//update txt file
			return;
		}
		cout << "Assignment not found.\n";
		return;
	}
}

void editStatus(list<assignment> Assn, list<assignment> Comp)//edit status: late, complete
{// first find the assignment with the given due date.
	//more than one assigment may share same due date
	//Don’t edit the assignment in these cases :
	//The assignment with the given assigned list doesn’t exists in the assigned list.
	//The given assigned or due dates are invalid.
	//error handeling for other that acceptable status
	assignment Temp;
	Date AssnDate;
	int newStatus;
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++) {
		if (it->getAssignedDate() == AssnDate) {
			cout << "Select status change:\n" << endl;
			cout << "1 = completed\n" << "2 = late\n" << endl;
			cin >> newStatus;
			newStatus += 1;
			assignment Temp = *it;
			Temp.setStatus(newStatus);
			if (newStatus == 2) {
				//remove from assigned
				it = Assn.erase(it);
				//move to completed
				Comp.push_back(Temp);
				//resort completed list
				return;
			}
			//update txt file
			return;
		}
		cout << "Assignment not found.\n";
		return;
	}
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
		cout << count << endl;
		return;
	}
}

string getFile(string FileName) {
	bool checkFile = false;
	while (checkFile == false) {
		int choice;
		ifstream fin(FileName);
		cout << "Enter the name of the file you want to open. Please include file extension:\n ";
		cin >> FileName;
		if (!fin) {
			cout << "Error opening file. Make sure the file is in the same folder as the program.\n";
			cout << "Please choose from the following actions:\n"
				<< "1. Re-enter the file name and extension.\n"
				<< "2. Exit the program.\n";
			cin >> choice;
			switch (choice) {
			case 1: checkFile = false; break;
			case 2: return -1; break;
			}
		}
		else {
			checkFile = true;
			while (fin.good()) {
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
return FileName
}

int main(){
	//SetConsoleTitle(TEXT("Assignment System, Proj1A, BY: J. Goza, J. Ford, S. Peery")); // set console title
	
	list<assignment> Assignments;
	list<assignment> Assigned;
	list<assignment> Completed;

	assignment temp;
	
	string FileName;//used incase of diffrent file extensions .txt and .csv
	
	cout << "Welcome to the menu based assignment system!\n";

	// determine file extesnion type and name to open with fin variable
	cout << "Enter the name of the file you want to open, please include file extension: " << endl;
	cin >> FileName;
	getFile(FileName);
	
	bool menuBool = false; bool runAgain = true;
	int menuInput = 0;
		
	while(runAgain){
		menuBool = false;
	
		while (!menuBool){
	
		cout << "\n"<< "What would you like to do?\n";
		cout << "1. Display assignments\n"
		<< "2. Add assignment to workload\n"
		<< "3. Edit due date for assignment\n"
		<< "4. Edit assignment description\n"
		<< "5. Log assignment completion\n"
		<< "6. Display number of late assignments\n"
		<< "7. Save    8. Exit\n\n";
		
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
		case 1 : printAssignments(Assigned, Completed); break;
		case 2 : addAssn(Assigned); break;
		case 3: editDue(Assigned); break;
		case 4: editDescription(Assigned); break;
		case 5: editStatus (Assigned, Completed); break;
		case 6 : displayLate(Completed); break;
		case 7 : printAssignments(Assigned, Completed);// needs to output to txt file to update
		case 8 : cout << "Goodbye!\n"; runAgain = false; break;
	}
	}
	
	
	system("pause");
	return 0;
}
