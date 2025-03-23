#include <iostream>
#include "linkedlist.h"
using namespace std;

//Constructor initializes the head of the linked list to NULL
LinkedList::LinkedList (){
    head = NULL;
}

//Insert a new term into the linked list
void LinkedList::insert(int coef, int expo){
    //Ignore terms with a coefficient of 0
    if (coef == 0){
        return;
    }
    
    //Create a new node for the term
    Node* newNode = new Node(coef, expo);
    
    //If the list is empty or the new term has a higher exponent than the head
    if(!head || expo > head->expo){
        newNode->next = head; //Point newNode to the current head
        head = newNode; //Update head to the new node
        return;
    }
    
    Node* current = head; //Create pointer to traverse the list
    Node* prev = NULL; //Create pointer to keep track of the previous node
    
    //Traverse the list to find the correct position for the new term
    while(current && current->expo >= expo){
        //If a term with the same exponent is found
        if (current->expo == expo){
            current->coef += coef; //Combine coefficients
            //If the combined coefficient is 0, then remove the term
            if (current->coef == 0){
                if(prev) {
                    prev->next = current->next; //Bypass the current node
                }
                else head = current->next; //Update head if removing the first node
                delete current; //Free memory of the removed node
            }
            delete newNode; //Free the new node
            return;
        }
        prev = current; //Move prev to the current node
        current = current->next; //Move to the next node
    }
    //Insert the new node in the correct position
    newNode->next = current;
    if(prev){
        prev->next = newNode; //Link previous node to the new node
    }
}

//Prints the polynomial in a readable format
void LinkedList::print(ostream& os) const{
    //If the list is empty, print 0
    if (!head){
        os << "0" << endl;
        return;
    }
    
    Node* current = head; //Create pointer to traverse the list
    bool firstTerm = true; //Flag to handle the formatting for the first term
    
    //Traverse the list and print each term
    while(current){
        //Manage the sign based on the first term
        if(!firstTerm && current->coef > 0){
            os << "+";
        }
        
        os << current->coef; //Print the coefficient
        if(current->expo > 0){
            os << "x^" << current->expo;
        }
        //Move to the next term
        current = current->next;
        //After the first term, this flag is set to false
        firstTerm = false;
    }
    os << endl;
}

//Overloaded equality operator to compare two linked lists
bool LinkedList::operator==(const LinkedList &other){
    //Pointer for this linked list
    Node* thisCurrent = this->head;
    //Pointer for the other linked list
    Node* otherCurrent = other.head;
    
    //Traverse both lists simultaneously
    while(thisCurrent && otherCurrent){
        //Compare coefficients and exponents
        if (thisCurrent->coef != otherCurrent->coef || thisCurrent->expo != otherCurrent->expo){
            return false;
        }
        //Move to the next term in this list
        thisCurrent = thisCurrent->next;
        //Move to the next term in the other list
        otherCurrent = otherCurrent->next;
    }
    
    //Both lists are equal if we reach the end of both simultaneously
    return thisCurrent == NULL && otherCurrent == NULL;
}

//Remove all nodes from the linked list and frees memory
void LinkedList::removeAll(){
    //Create pointer to traverse the list
    Node* current = head;
    while(current){
        Node* old = current; //Keep track of the current node
        current = current -> next; //Move to the next node
        delete old; //Free memory of the current node
    }
    head = NULL; //Set head to NULL after removal 
}

//Destructor to ensure all nodes are deleted when a LinkedList object is destroyed
LinkedList::~LinkedList(){
    removeAll(); //Call removeAll to clean up memory
}
