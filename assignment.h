#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <stdio.h>
#include <iostream>
#include <list>
#include "date.h"

using namespace std;

enum Status{ assigned, completed, late };

class assignment{
private:
	Date dueDate;
	string description;
	Date assignedDate;
	Status status;

public:
	assignment();
	assignment(const assignment& other);
	const assignment& operator=(const assignment& rhs);

	Date getDueDate();
	string getDescription();
	Date getAssignedDate();
	Status getStatus();

	friend istream& operator>>(istream& in, assignment& current);
	friend ostream& operator<<(ostream& out, assignment& current);
};

#endif