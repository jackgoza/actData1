//
//  stuctsProj1.cpp
//  dataone
//
//  Created by John Goza on 6/16/16.
//  Copyright © 2016 JohnGoza. All rights reserved.
//

#include <stdio.h>
#include "assignment.h"
#include <fstream>
#include <list>
#include <iterator>

using namespace std;

int main(){
	list<assignment> Assignments;
	list<assignment> Assigned;
	list<assignment> Completed;

	assignment temp;

	ifstream in("assignment.txt");

	while (in.good()){
		in >> temp;
		Assignments.push_back(temp);
	}

	list <assignment>::iterator it = Assignments.begin();

	for (it; it != Assignments.end(); it++){
		cout << *it;
	}

	system("pause");
}