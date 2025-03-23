//============================================================================
// Name         : Polynomial Calculator 
// Author       : Shota Matsumoto
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 18-09-2024 
// Description  : Polynomial Calculator in C++ using Singly Linked-List
//============================================================================

#ifndef POLYCALCULATOR_H
#define POLYCALCULATOR_H
#include<fstream>
#include<string>
#include "linkedlist.h"
//=======================================
class PolyCalculator
{
	private:
		LinkedList list1;
		LinkedList list2;
		LinkedList list3;
	public:
		void input(); //take input the values of polynomial expressions
		void display(ostream &os=std::cout); //display both polynomials (list1 and list2)
		void add(); //add both polynomials (list1 and list2) and save the result in list3
		void mul(); //multiply both polynomials (list1 and list2) and save the result in list3
		void evaluate(int expID, int x); //evalutes both polynomials for a given value of x
		int degree(int expID);	//returns the degree of a polynomial
		void isequal(); //checks if both polynomials are identical or not
		void readData(std::string path); //read a file and load the data into the linked lists (list1 and list2)
		void writeData(std::string path); //write the polynomial expressions and the results of addition,subtraction and multiplication to a file
		bool parse(std::string expr,LinkedList& list);	//parse a string (expr) and saves the results in a linkedlist (list). This method returns true if expression is true false otherwise
};

#endif 
