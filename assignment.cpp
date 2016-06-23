
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

assignment::assignment(const assignment& other){
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

void assignment::setDueDate(Date date){
	dueDate = date;
}
void assignment::setDescription(string desc){
	description = desc;
}
void assignment::setAssignedDate(Date date){
	assignedDate = date;
}
void assignment::setStatus(int stat){
	switch (stat){
	case 1: status = assigned; break;
	case 2: status = completed; break;
	case 3: status = late; break;
	}
}

istream &operator>>(istream& in, assignment& current){
	char temp;
	

	in >> current.dueDate;

	getline(in, current.description, ',');

	in >> current.assignedDate >> temp;

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
	case 1: out << "assigned"; break;
	case 2: out << "completed"; break;
	case 3: out << "late"; break;
	}

	return out;
}

bool assignment::operator <(const assignment& rhs) const{
	return dueDate < rhs.dueDate;
}

bool assignment::operator >(const assignment& rhs) const{
	return dueDate > rhs.dueDate;
}

bool assignment::operator ==(const assignment& rhs) const{
	return dueDate == rhs.dueDate;
}

bool assignment::operator !=(const assignment& rhs) const{
	return assignedDate != rhs.assignedDate;
}