#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <stdio.h>
#include <iostream>
#include <list>
#include "date.h"

using namespace std;

enum Status{ assigned = 1, completed = 2, late = 3 };

class assignment{
private:
	Date dueDate;
	string description;
	Date assignedDate;
	Status status;

public:
	//constructors
	assignment();
	//Pre: None
	//Post: assignment object created
	//Returns: none
	assignment(const assignment& other);
	//Pre:assignment object exists to copy
	//Post: assignment object cloned
	//Returns: none
	const assignment& operator=(const assignment& rhs);
	//Pre: two assignment object exist
	//Post: assignment equals rhs assignment
	//Returns: const assignment

	//getters
	Date getDueDate();
	//Pre: DueDate set
	//Post: none
	//Returns: Duedate
	string getDescription();
	//Pre: none
	//Post: none
	//Returns: description 
	Date getAssignedDate();
	//Pre: AssignedDate set
	//Post: none
	//Returns: AssignedDate
	Status getStatus();
	//Pre: Status set
	//Post: none
	//Returns: Status

	//setters
	void setDueDate(Date date);
	//Pre: none
	//Post: DueDate set
	//Returns: none
	void setDescription(string desc);
	//Pre: none
	//Post: Description set
	//Returns: none
	void setAssignedDate(Date date);
	//Pre: none
	//Post: AssignedDate set
	//Returns: none
	void setStatus(int stat);
	//Pre: none
	//Post: Status set
	//Returns: none

	// I/O operators
	friend istream& operator>>(istream& in, assignment& current);
	//Pre: istream opened
	//Post: assignment data read into object
	//Returns: istream
	friend ostream& operator<<(ostream& out, assignment& current);
	//Pre: ostream opened
	//Post: assignment object output to ostream
	//Returns: ostream

	// equality operators
	bool operator <(const assignment& rhs) const;
	//Pre: assignment rhs exists
	//Post: none
	//Returns: bool
	bool operator >(const assignment& rhs) const;
	//Pre: assignment rhs exists
	//Post: none
	//Returns: bool
	bool operator ==(const assignment& rhs) const;
	//Pre: assignment rhs exists
	//Post: none
	//Returns: bool
	bool operator !=(const assignment& rhs) const;
	//Pre: assignment rhs exists
	//Post: none
	//Returns: bool

};
#endif