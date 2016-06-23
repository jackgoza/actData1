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
<<<<<<< HEAD
// #include <Windows.h>
=======

>>>>>>> master
#undef max

using namespace std;

Date inputDate(){
	Date date;

	string temp;
	while (true){
		
		try {
			cin.ignore();
			getline(cin, temp);
			Date date(temp, US);
			if (date.valid_date(date.getYear(), date.getMonth(), date.getDay())){
				return date;
			}
			else{
				throw exception();
			}
		}
		catch (exception){
			cout << "Please enter a valid date(mm-dd-yyyy): ";
		}
	}
}

assignment addAssignment(list<assignment> AssignmentList){ // use this to make a new assignment
	assignment newAssn;			//*********** Made a huge mistake thinking the due dates were unique
	string temp;			// this function is fixed to check uniqueness of assigned dates
	char tempC;

	cout << "Assigned Date: (mm-dd-yyyy): ";

	newAssn.setAssignedDate(inputDate());
	
	list<assignment>::iterator it = AssignmentList.begin();

	do{
		if (it->getAssignedDate() == newAssn.getAssignedDate()){
			cout << "Assignment already exists, enter another date: ";
			newAssn.setAssignedDate(inputDate());
			it = AssignmentList.begin();
		}
		it++;
	} while (it != AssignmentList.end());

	cout << endl << "Description: ";
	getline(cin, temp);
	newAssn.setDescription(temp);

	do{
		cout << endl << "Due Date: ";
		newAssn.setDueDate(inputDate());
		if (newAssn.getDueDate() <= newAssn.getAssignedDate())
			cout << "Invalid Due Date";

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

void save(string File, list<assignment> List){ // overwrite file with new list
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
	//Don’t edit the assignment in these cases
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
	}
	cout << count << endl;
}

int main(){
<<<<<<< HEAD
	// SetConsoleTitle(TEXT("Assignment System, Proj1A, BY: J. Goza, J. Ford, S. Peery")); // set console title
=======
	//SetConsoleTitle(TEXT("Assignment System, Proj1A, BY: J. Goza, J. Ford, S. Peery")); // set console title
>>>>>>> master
	
	list<assignment> Assignments; // all assignments
	list<assignment> Assigned; 
	list<assignment> Completed; // completed and late assignments

	assignment temp;
	
	string FileName;//used incase of diffrent file extensions .txt and .csv
	
	// determine file extesnion type and name to open with fin variable
	cout << "Enter the name of the file you want to open, please include file extension: " << endl;
	cin >> FileName;
	
	/*TODO
	 make function fetfile() to call for lines 350-360. put in a while loop until correct file
	 has been found and loaded. give function a menu option for user to choose to try again or
	 exit
	 */
	
	// initiate input/output variables
	ifstream fin(FileName);
	if (!fin)//check that file exists
	{
		cout << "Error opening input file.\n " << "Program will now exit." << endl;
		system("pause");
		return -1;
	}


	while (fin.good()){ // initialize all lists with file input
		fin >> temp;
		Assignments.push_back(temp);
		if (temp.getStatus() == assigned){
			Assigned.push_back(temp);
		}
		else{
			Completed.push_back(temp);
		}
	}

	// initial sort of all lists
	Assignments.sort();
	Assigned.sort();
	Completed.sort();
	
	
	bool menuBool = false; bool runAgain = true;
	int menuInput = 0;
	
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
		case 1 : 
			printAssignments(Assigned, Completed); break; // functional, TODO make it look pretty

		case 2 : // works
			temp = addAssignment(Assignments);
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
			break;

		case 3: 
			editDue(Assigned); break; // TODO make all three edit cases one case 
										//(edit assignment: find assignment by **assigned** date: which part of assignment would you like to edit?)
		case 4: 
			editStatus(Assigned, Completed); break;
		
		case 5: 
			displayLate(Completed); break; // works
		
		case 6 :
			
		
		case 7 : 
			printAssignments(Assigned, Completed);// needs to output to txt file to update
		
		case 8 : 
			cout << "Goodbye!\n"; runAgain = false; break;
	}
	}
	
	
	system("pause");
	return 0;
}