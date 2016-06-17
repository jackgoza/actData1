
//
//  assignment.cpp
//  
//
//  Created by John Goza on 6/15/16.
//
//

#include <stdio.h>
#include "assignment.h"

assignment::assignment(){
	description = "";
}

assignment::assignment(assignment& other){
	dueDate = other.dueDate;
	description = other.description;
	assignedDate = other.assignedDate;
	status = other.status;
}

const assignment& assignment:: operator =(const assignment& rhs){
	dueDate = rhs.dueDate;
	description = rhs.description;
	assignedDate = rhs.assignedDate;
	status = rhs.status;
	return *this;
}

Date assignment::getDueDate(){
	return dueDate;
}

string assignment::getDescription(){
	return description;
}

Date assignment::getAssignedDate(){
	return assignedDate;
}
Status assignment::getStatus(){
	return status;
}

istream &operator>>(istream& in, assignment& current){
	char temp;

	in >> current.dueDate >> current.description >> current.assignedDate >> temp;

	switch (temp){
	case 'A':
	case'a': current.status = assigned; break;
	case'C':
	case'c': current.status = completed; break;
	case'L':
	case'l': current.status = late; break;
	}

	in.ignore(20, '\n');
	return in;
}

ostream& operator<<(ostream& out, assignment& current){
	out << current.dueDate << ", " << current.description << ", " << current.assignedDate << ", ";
	switch (current.status){
	case 0: out << "assigned"; break;
	case 1: out << "completed"; break;
	case 2: out << "late"; break;
	}

	return out << endl;
}