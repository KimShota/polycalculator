//============================================================================
// Name         : Polynomial Calculator 
// Author       : Shota Matsumoto
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 18-09-2024 
// Description  : Polynomial Calculator in C++ using Singly Linked-List
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>

#include "linkedlist.h"
#include "polycalculator.h"
using namespace std;

//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display              : Display the Polynomials (Linked Lists)"<<endl
		<<"input                : Input Polynomial expressions from keyboard"<<endl
		<<"add                  : Add the Polynomials (Linked Lists)"<<endl
		<<"mul                  : Multiply the polynomials (Linked Lists)"<<endl
		<<"evaluate <ExpID,int> : Evaluate a polynomial for a specific value of x"<<endl
		<<"isequal              : Check if both poynoials are identical or not"<<endl
		<<"degree <ExpID>       : Returns the degree of a given polynomial."<<endl     
		<<"read <file_name>     : Load the data from <file> and add it into the Linked Lists"<<endl
		<<"write <file_name>    : Dump the contents of the resultant Linked list to a <file>"<<endl       
		<<"help                 : Display the list of available commands"<<endl
		<<"exit                 : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{
	//unittest(); 
	//return 0;
	PolyCalculator polycalc;

	listCommands();
	string user_input;
	string command;
	string parameter1;
	string parameter2;
	do
	{
		cout<<">";
		getline(cin,user_input);
		
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,',');
		getline(sstr,parameter2);


		
		if(command =="display") 		polycalc.display();
		else if(command == "input")     polycalc.input();
		else if(command == "add")		polycalc.add();
		else if(command == "mul")		polycalc.mul();
		else if(command == "evaluate")	polycalc.evaluate(stoi(parameter1),stoi(parameter2));
		else if(command == "isequal")   polycalc.isequal();
		else if(command == "degree")    cout<<"The degree of Exp"<<parameter1<<" is: "<<polycalc.degree(stoi(parameter1))<<endl;
		else if(command =="read")		polycalc.readData(parameter1),polycalc.display();
		else if(command == "write")		polycalc.writeData(parameter1);			
		else if(command == "help")		listCommands();
		else if(command == "exit" or command=="quit")			break;
		else 		cout<<"Invalid Command!!"<<endl;
	}while(true);

	return EXIT_SUCCESS;
}

