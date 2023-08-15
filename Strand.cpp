/********************************************
 ** Name: Hannah Baeq
 ** Date: 3/27/2023
 ** Email: hbaeq1@umbc.edu
 ** Section: 24
 ** File: Strand.cpp
 ** Description: This file contains the
         Strand class function definitions.
********************************************/
#include "Strand.h"

// Name: Strand() - Default Constructor
// Preconditions: None
// Postconditions: Creates a new strand with a default name
Strand::Strand(){
  //giving default values
  m_name = "default";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: Strand(string) - Overloaded Constructor
// Preconditions: None
// Postconditions: Creates a new strand with passed name
Strand::Strand(string name){
  //overloaded constructor that sets m_name
  m_name = name;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: ~Strand() - Destructor
// Preconditions: There is an existing strand with at least one node
// Postconditions: Strand is deallocated (including all dynamically allocated nodes)
//                 to have no memory leaks!
Strand::~Strand(){
  //destructor
  Node *curr = m_head;
  //points at m_head
  while (curr != nullptr){
    //pushing everything one over
    m_head = curr;
    curr = curr->m_next;
    //deleting the "first"
    delete m_head;
  }
  //just to make sure hehe
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: InsertEnd
// Preconditions: Requires a strand
// Postconditions: Strand is larger.
void Strand::InsertEnd(char data){
  //inserting a node at the end
  //making a new node
  Node *temp = new Node();
  //setting the data
  temp->m_data = data;
  //if its an empty strand
  if (m_head == nullptr){
    //everything points to temp
    m_head = temp;
    m_tail = temp;
  }else{
    //the value of tail's m_next will now be temp
    m_tail->m_next = temp;
    //the last value is now temp, the new node
    m_tail = temp;
  }
  //size count increases
  m_size++;
}

// Name: GetName()
// Preconditions: Requires a strand
// Postconditions: Returns m_name;
string Strand::GetName(){return m_name;}

// Name: GetSize()
// Preconditions: Requires a strand
// Postconditions: Returns m_size;
int Strand::GetSize(){return m_size;}

// Name: ReverseSequence
// Preconditions: Reverses the strand
// Postconditions: Strand sequence is reversed in place; nothing returned
void Strand::ReverseSequence(){
  //creating three new nodes
  Node *curr = m_head;
  Node *temp = nullptr;
  Node *next;
  while (curr != nullptr){
    //next value of current (m_head for the first loop)
    next = curr->m_next;
    //next value of current is now temp
    curr->m_next = temp;
    //temp is now current
    temp = curr;
    //current is now next
    curr = next;
  }
  //setting tail and head
  next = m_head;
  m_head = m_tail;
  m_tail = next;
}

// Name: GetData
// Preconditions: Requires a DNA sequence
// Postconditions: Returns a single char from a node
char Strand::GetData(int nodeNum){
  //making a node
  Node *curr = m_head;
  //iterating to the integer value given
  for (int i = 0; i < nodeNum; i++){
    //moving one at a time to the m_next
    curr = curr->m_next;
  }
  //data is = that curr->m_data
  char data = curr->m_data;
  //returning the char type data.
  return data;
}

// Name: operator<<
// Preconditions: Requires a strand
// Postconditions: Returns an output stream (does not cout the output)
ostream&operator<<(ostream&output, Strand&myStrand){
  //new node = m_head
  Node *temp = myStrand.m_head;
  while (temp != nullptr){
    //output the data
    output << temp->m_data << "->";
    //move to the next node
    temp = temp->m_next;
  }
  //end!
  output << "END" << endl;
  //return the output
  return output;
}
