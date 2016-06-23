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
	assignment();
	assignment(const assignment& other);
	const assignment& operator=(const assignment& rhs);

	Date getDueDate();
	string getDescription();
	Date getAssignedDate();
	Status getStatus();

	void setDueDate(Date date);
	void setDescription(string desc);
	void setAssignedDate(Date date);
	void setStatus(int stat);

	friend istream& operator>>(istream& in, assignment& current);
	friend ostream& operator<<(ostream& out, assignment& current);

	bool operator <(const assignment& rhs) const;
	bool operator >(const assignment& rhs) const;
	bool operator ==(const assignment& rhs) const;
	bool operator !=(const assignment& rhs) const;

};

#endif