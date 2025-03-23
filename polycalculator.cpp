#include <iostream>
#include<cmath>
#include <string>
#include "polycalculator.h"
using namespace std;

//Input method to read the polynomial expressions from user
void PolyCalculator::input(){
    //Declare variables as string to store the polynomial expressions entered by user
    string exp1, exp2;
    
    //Take the first polynomial expression from the user
    cout << "Enter first Polynomial expression: ";
    getline(cin, exp1); //Read the entire line of input for the first polynomial
    parse(exp1, list1); //Call the parse method to convert the string expression into a linked list representation
    
    //Take the second polynomial expression from the user
    cout << "Enter second Polynomial expression: ";
    getline(cin, exp2); //Read the entire line of input for the second polynomial
    parse(exp2, list2); //Call the parse method to convert the string expression into a linked list representation
}

//Display method to print the two polynomial expressions
void PolyCalculator::display(ostream& os){
    //Print the first polynomial expression
    os << "Exp1: ";
    list1.print(cout); // Call the print function of list1 to display the first expression
    os << endl;
    
    //Print the second polynomial expression
    os << "Exp2: ";
    list2.print(cout); //Call the print function of list2 to display the second expression
    os << endl;
    
    //Check if the third polynomial exists
    if (list3.head != NULL)
    {
        os << "Exp3: ";
        list3.print(cout); //Call the print function of list3 to display the result expression
        os<<endl;
    }
}

// Add method to add two polynomials and store the result in list3
void PolyCalculator::add(){
    Node* curr1 = list1.head; //Pointer to traverse the first polynomial list
    Node* curr2 = list2.head; //Pointer to traverse the second polynomial list
    
    //Clear any previous result stored in list3 before actually preforming addition
    list3.removeAll();
    
    //Traverse both lists and add corresponding terms with the same exponents
    while (curr1 != NULL && curr2 != NULL){
        if (curr1->expo == curr2->expo){ //If exponents match
            // Add the coefficients and insert the term into the result list
            list3.insert(curr1->coef + curr2->coef, curr1->expo);
            curr1 = curr1->next; // Move to the next term in list1
            curr2 = curr2->next; // Move to the next term in list2
        } else if(curr1->expo > curr2->expo){ //If the list1 has a higher exponent
            //Insert the term from list1 to the result list
            list3.insert(curr1->coef, curr1->expo);
            curr1 = curr1->next; //Move to the next term in list1
        } else{ //If list2 has a higher exponent
            //Insert the term from list2 into the result list
            list3.insert(curr2->coef, curr2->expo);
            curr2 = curr2->next; //Move to the next term in list2
        }
    }
    
    //Add any remaining terms from list1 if list2 is exhausted
    while (curr1 != NULL){
        list3.insert(curr1->coef, curr1->expo);
        curr1 = curr1->next;
    }
    
    //Add any remaining terms from list2 if list1 is exhausted
    while(curr2 != NULL){
        list3.insert(curr2->coef, curr2->expo);
        curr2 = curr2->next;
    }
}

//Multiply method to mutiply two polynomials and store the result in list3
void PolyCalculator::mul(){
    Node* curr1 = list1.head; //Pointer to traverse the first polynomial list
    
    //Clear any previous result stored in list3 before actually preforming multiplication
    list3.removeAll();
    
    // Nested loop: For each term in list1, multiply it by every term in list2
    while(curr1 != NULL){
        Node* curr2 = list2.head; // Pointer to traverse the second polynomial list
        
        while (curr2 != NULL){
            // Multiply the coefficients of the current terms from list1 and list2
            int newCoef = curr1->coef * curr2->coef;
            // Add the exponents of the current terms since it's a product of powers
            int newExpo = curr1->expo + curr2->expo;
            //Insert the new term, product of coefficients and sum of exponents, into the list 3
            list3.insert(newCoef, newExpo);
            //Move to the next term in list2
            curr2 = curr2->next;
        }
        //Move to the next term in list1
        curr1 = curr1->next;
    }
}

//Evaluate method to calculate the value of a polynomial for a given x
void PolyCalculator::evaluate(int expID, int x){
    //Create a pointer to store the chosen polynomial linked list
    LinkedList* polyexp;
    
    //Determine which polynomial to evaluate based on expID
    if (expID == 1){
        polyexp = &list1; //Choose the first polynomial
    } else if (expID == 2){
        polyexp = &list2; //Choose the second polynomial
    } else if (expID == 3 && list3.head != NULL){
        polyexp = &list3;
    } else{
        //Print an error message if the expID provided is invalid
        cout << "expID is invalid" << endl;
        return;
    }
    
    //Display the chosen polynomial expression
    cout << "P(x) = ";
    polyexp->print(cout); //Print the selected polynomial
    cout << endl;
    
    //Traverse the linked list to compute the sum of terms for the given value of x
    Node* curr = polyexp->head;
    int sum = 0; //Initialize sum to 0
    while (curr != NULL){
        //Use the formula to evaluate each term
        int termValue = curr->coef * pow(x, curr->expo);
        sum += termValue; //Add the value of the current term to the sum
        //Move to the next term in the polynomial
        curr = curr->next;
    }
    
    //Display the result of evaluating the polynomial at x
    cout << "p(" << x << ") = " << sum << endl;
}

//Degree method to return the highest exponent of a polynomial
int PolyCalculator::degree(int expID){
    //Create a pointer to the selected polynomial
    LinkedList* polyexp;
    
    //Determine which polynomial to find the degree of
    if(expID == 1){
        polyexp = &list1;
    } else if(expID == 2){
        polyexp = &list2;
    } else if (expID == 3 && list3.head != NULL){
        polyexp = &list3;
    }else {
        //Print an error message if the expID provided is invalid
        cout << "expID is invalid" << endl;
        return -1;
    }
    
    //If the polynomial is empty, print an error message
    if (polyexp->head == NULL){
        cout << "Poly empty!" << endl;
        return -1;
    }
    
    //Return the exponent of the head node since the list is stored
    return polyexp->head->expo;
}

//Check if two polynomials are identical or not
void PolyCalculator::isequal(){
    //Compare the two polynomials
    if (list1 == list2){
        cout << "Both polynomials are identical." << endl;
    }
    else{
        cout << "Two polynomials are not idential." << endl;
    }
}

//Read polynomial expressionsn from a file
void PolyCalculator::readData(std::string path){
    //Open the file for reading
    ifstream infile(path);
    if(!infile){
        //If the file cannot be found print an error message
        cerr << "File cannot be opened" << endl;
        exit(-1);
    }
    
    string line;
    string expr;
    
    //Clear previous polynomial data from list1 and list2
    list1.removeAll();
    list2.removeAll();
    
    //Read the first polynomial expression from the file
    if(getline(infile, expr)){
        //If parsing fails, then print an error message
        if (!parse(expr, list1)){
            cerr << "Error: Invalid polynomial expression in file" << endl;
        }
    }
    
    //Read the second polynomial expression from the file
    if (getline(infile, expr)){
        //If parsing fails, then print an error message
        if (!parse(expr, list2)){
            cerr << "Error: Invalid polynomial expression in file" << endl;
        }
    }
    
    //Close the file
    infile.close();
}

//Write polynomial expressions and results to a file
void PolyCalculator::writeData(std::string path){
    //Open the file for writing
    ofstream outfile(path);
    //If the file cannot be opened, then print an error message
    if(!outfile){
        cout << "File cannot be opened" << endl;
        exit (-1);
    }
    
    //Write the first polynomial expression to the file
    outfile << "Exp1 = ";
    list1.print(outfile); //Print the first polynomial to the file
    
    //Write the second polynomial expression to the file
    outfile << "Exp2 = ";
    list2.print(outfile); //Print the second polynomial to the file
    
    //Perform addition first and write the result to the file
    add();
    outfile << "Exp1 + Exp2 = ";
    list3.print(outfile); //Print the result of the addition to the file
    
    //Perform multiplication first and then print the result to the file
    mul();
    outfile << "Exp1 * Exp2 = ";
    list3.print(outfile); //Print the result of the multiplication to the file
    
    //Close the file
    outfile.close();
    
}

bool PolyCalculator::parse(std::string expr,LinkedList& list){
    int coef = 0; // Initialize integer variable to store the coefficient
    int expo = 0; // Initialize integer variable to store the exponent
    char sign = '+'; // Initialize character variable to track the sign of the term
    bool readingCoef = true; // Flag to indicate if we are reading a coefficient

    // Remove spaces from the expression for easier parsing
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    for (size_t i = 0; i < expr.length(); ++i) {
        char currentChar = expr[i];

        // Check for '+' or '-' sign
        if (currentChar == '+' || currentChar == '-') {
            // If reading a coefficient, finalize the previous term
            if (!readingCoef) {
                // Insert the term into the linked list
                list.insert(coef * (sign == '+' ? 1 : -1), expo);
                coef = 0; // Reset coefficient
                expo = 0; // Reset exponent
            }
            sign = currentChar; // Update sign
            readingCoef = true; // Start reading the next coefficient
            continue;
        }

        // Read coefficient
        if (isdigit(currentChar)) {
            if (readingCoef) {
                coef = coef * 10 + (currentChar - '0'); // Build the coefficient
            } else {
                // In case we encounter a digit after an exponent
                // We can ignore it or handle it based on your specific requirement
                return false; // Invalid input format
            }
        } else if (currentChar == 'x' || currentChar == 'X') {
            // 'x' indicates that we are expecting an exponent
            readingCoef = false; // Finished reading coefficient
            if (i + 1 < expr.length() && expr[i + 1] == '^') {
                // Read exponent if it's defined
                i += 2; // Skip '^'
                while (i < expr.length() && isdigit(expr[i])) {
                    expo = expo * 10 + (expr[i] - '0'); // Build the exponent
                    ++i;
                }
                --i; // Adjust for the outer loop increment
            } else {
                // If no exponent is specified, it defaults to 1
                expo = 1;
            }
        } else {
            // Invalid character encountered
            return false; // Invalid input format
        }
    }

    // Insert the last term into the linked list
    if (!readingCoef) {
        list.insert(coef * (sign == '+' ? 1 : -1), expo);
    }

    return true; // Return true
}
