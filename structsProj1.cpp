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

using namespace std;

int main(){

	ifstream in("assignment.txt");
	ofstream out("assignment2.txt");
	assignment temp;

	while (in.good()){
		in >> temp;
		out << temp;
	}

	in.close();
	out.close();
}