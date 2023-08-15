/********************************************
 ** Name: Hannah Baeq
 ** Date: 3/27/2023
 ** Email: hbaeq1@umbc.edu
 ** Section: 24
 ** File: Sequencer.cpp
 ** Description: This file contains the
         Sequencer class function definitions.
********************************************/
//including header file
#include "Sequencer.h"

// Name: Sequencer (constructor)
// Preconditions:  Populates m_fileName from passed information from call
//                 For example: ./proj3 proj3_data1.txt
// Postconditions: A sequencer created to populate DNA/mRNA strands
Sequencer::Sequencer(string fileName){
  //constructor setting the file name
  m_fileName = fileName;
}

// Name: Sequencer (destructor)
// Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
// Postconditions: All vectors are cleared of DNA and mRNA strands
//                 Indicates that the strands have been deallocated
Sequencer::~Sequencer(){
  //destructor
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    //deleting dna strands
    delete m_DNA.at(i);
  }
  cout << "Deleting DNA Strands" << endl;
  for (unsigned int i = 0; i < m_mRNA.size(); i++){
    //deleting mrna strands
    delete m_mRNA.at(i);
  }
  cout << "Deleting mRNA Strands" << endl;
}

// Name: StartSequencing
// Preconditions: m_fileName has been populated
// Postconditions: m_DNA has been populated (after ReadFile concludes)
void Sequencer::StartSequencing(){
  //calling read file
  ReadFile();
  //calling main menu and setting while loop for exit conditional
  int choice = MainMenu();
  while (choice != 5){
    choice = MainMenu();
  }
}

// Name: DisplayStrands
// Preconditions: At least one linked list is in mDNA (may have mRNA)
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands(){
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    //iterating through dna vector
    cout << endl << "DNA " << i+1 << endl;
    cout << "***" << m_DNA.at(i)->GetName() << "***" << endl;
    cout << *m_DNA.at(i);
    //can cout due to the friend operator
  }
  for (unsigned int i = 0; i < m_mRNA.size(); i++){
    //iterating through the mrna vector
    cout << endl << "mRNA " << i+1 << endl;
    cout << "***" << m_mRNA.at(i)->GetName() << "***" << endl;
    cout << *m_mRNA.at(i);
    //can cout due to the friend operator
  }
}

// Name: ReadFile
// Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in m_DNA
void Sequencer::ReadFile(){
  //input stream
  ifstream inputStream;
  inputStream.open(m_fileName);
  //opening file
  //initializing data
  string dataLine;
  string name;
  int counter = 0;
  if (inputStream.is_open()){
    cout << "Opened File" << endl;
    while (getline(inputStream, name, ',')){
      //getting data up until the first ',' to get the name
      //it will get line until there are no more names
      Strand *myStrand = new Strand(name);
      //initializing new strand
      getline(inputStream, dataLine, '\n');
      //getting data up until the new line
      for (int i = 0; i < int(dataLine.length()); i++){
        //for every character in the length
        if (dataLine[i] != ','){
          //if it's not a comma, insert it at the end
          myStrand->InsertEnd(dataLine[i]);
        }
        //no else statement since nothing happens
      }
      //adding the strand into the DNA vector
      m_DNA.push_back(myStrand);
      //counting to see how many strands were loaded
      counter++;
    }
    //closing input stream
    inputStream.close();
  }else{
    //dont really need this since the proj3.cpp does it
    cout << "File could not be opened." << endl;
  }
  //cout the amount of strands loaded
  cout << counter << " strands loaded." << endl;
}

// Name:  MainMenu
// Preconditions: m_DNA populated
// Postconditions: Indicates the user has quit the program
int Sequencer::MainMenu(){
  int userInput;
  cout << endl << "What would you like to do?:" << endl << "1. Display Strands" << endl << "2. Reverse Strand" << endl << "\
3. Transcribe DNA to mRNA" << endl << "4. Translate mRNA to Amino Acids" << endl << "5. Exit" << endl;
  cin >> userInput;
  //validation
  while (userInput > 5 || userInput < 1){
    cout << endl << "What would you like to do?:" << endl << "1. Display Strands" << endl << "2. Reverse Strand" << endl <<\
 "3. Transcribe DNA to mRNA" << endl << "4. Translate mRNA to Amino Acids" << endl <<"5. Exit" << endl;
    cin >> userInput;
  }
  //calling the different functions
  if (userInput == 5){
    //if 5, exit the program AND return 5
    cout << "Exiting program" << endl;
    return 5;
  }else if (userInput == 4){
    Translate();
  }else if (userInput == 3){
    Transcribe();
  }else if (userInput == 2){
    ReverseSequence();
  }else{
    DisplayStrands();
  }
  //returning 0 for every other choice
  return 0;
}

// Name: ChooseDNA
// Preconditions: Populated m_DNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseDNA(){
  //unsigned int to compare with .size()
  unsigned int index;
  cout << "Which strand to work with?" << endl << "Choose 1 - " << m_DNA.size() << endl;
  cin >> index;
  //validation
  while (index > m_DNA.size() || index < 1){
    cout << "Which strand to work with?" << endl << "Choose 1 - " << m_DNA.size() << endl;
    cin >> index;
  }
  //returning 'true' index
  return index - 1;
}

// Name: ChooseMRNA
// Preconditions: Populated m_mRNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseMRNA(){
  //unsigned int to compare with .size()
  unsigned int index;
  cout << "Which strand to work with?" << endl << "Choose 1 - " << m_mRNA.size() << endl;
  cin >> index;
  //validation
  while (index > m_mRNA.size() || index < 1){
    cout << "Which strand to work with?" << endl << "Choose 1 - " << m_mRNA.size() << endl;
    cin >> index;
  }
  //returning 'true' index
  return index - 1;
}

// Name: ReverseSequence
// Preconditions: Populated m_DNA or m_mRNA
// Postconditions: Reverses a specific strand replacing in place
void Sequencer::ReverseSequence(){
  //initializing variables
  int strandChoice;
  int strandIndex;
  string coutStrand;
  //asking the type of strand
  cout << "Which type of strand to reverse?" << endl << "1. DNA" << endl << "2. mRNA" << endl;
  cin >> strandChoice;
  //validation for strand type
  while (strandChoice > 2 || strandChoice < 1){
    cout << "Which type of strand to reverse?" << endl << "1. DNA" << endl << "2. mRNA" << endl;
    cin >> strandChoice;
  }
  //if DNA
  if (strandChoice == 1){
    //to make ouput easier
    coutStrand = "DNA";
    //choosing the dna strand
    strandIndex = ChooseDNA();
    //reversing sequence
    m_DNA.at(strandIndex)->ReverseSequence();
  }else{
    //making sure that mrna exists
    if (m_mRNA.size() < 1){
      cout << "No mRNA to translate; transcribe first" << endl;
      return;
    }else{
      coutStrand = "mRNA";
      //making cout easier
      strandIndex = ChooseMRNA();
      //choosing mrna strand
      m_mRNA.at(strandIndex)->ReverseSequence();
      //calling reverse sequence on the mrna strand
    }
  }
  //output statement for the user.
  cout << "Done reversing " << coutStrand << " " << strandIndex+1 << "'s strand." << endl;
}

// Name: Transcribe
// Preconditions: Populated m_DNA
// Postconditions: Transcribes each strand of m_DNA to m_mRNA
void Sequencer::Transcribe(){
  //initializing variables
  int counter = 0;
  char character;
  char newCharacter;
  //unsigned int to compare with .size()
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    //new strand for mrna
    Strand *myStrand = new Strand(m_DNA.at(i)->GetName());
    for (int j = 0; j < m_DNA.at(i)->GetSize(); j++){
      //getting data
      character = m_DNA.at(i)->GetData(j);
      //comparing data
      if (character == 'A'){
        newCharacter = 'U';
      }else if (character == 'T'){
        newCharacter = 'A';
      }else if (character == 'C'){
        newCharacter = 'G';
      }else{
        newCharacter = 'C';
      }
      //inserting the new character into the mrna strand
      myStrand->InsertEnd(newCharacter);
    }
    //adding the strand into the mrna vector
    m_mRNA.push_back(myStrand);
    //counting
    counter++;
  }
  //output for the user
  cout << counter << " strands of DNA successfully transcribed into new mRNA strands" << endl;
}

// Name: Translate
// Preconditions: Populated m_mRNA
// Postconditions: Translates a specific strand of mRNA to amino acids
void Sequencer::Translate(){
  //making sure that mrna strands exist
  if (m_mRNA.size() == 0){
    cout << "No mRNA to translate; transcribe first" << endl;
  }else{
    //initializing variables and choosing the mrna strand
    int strandNum = ChooseMRNA();
    string emptyString;
    //getting name
    cout << endl << "***" << m_mRNA.at(strandNum)->GetName() << "***" << endl;
    for (int i = 0; i < m_mRNA.at(strandNum)->GetSize(); i++){
      //getting size
      //adding 1 since the indez starts at 0
      int threes = i + 1;
      if (threes % 3 == 0){
        //mod 3 means that there are three characters added up
        //adding the last character
        emptyString += m_mRNA.at(strandNum)->GetData(i);
        //calling convert function
        string aminoAcid = Convert(emptyString);
        cout << emptyString << "->" << aminoAcid << endl;
        //emptying the string for the next set
        emptyString = "";
      }else{
        //adds the first two characters
        emptyString += m_mRNA.at(strandNum)->GetData(i);
      }
    }
    //output statement for the user
    cout << "Done translating mRNA " << strandNum+1 << "'s strand." << endl;
  }
}

// Name: Convert (Provided)
// Preconditions: Passed exactly three U, A, G, or C
// Postconditions: Returns the string name of each amino acid
string Sequencer::Convert(const string trinucleotide){
  //a ton of comparing!!
  //given to us by professor
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
          (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
          (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
          (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
          (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
          (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
          (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
          (trinucleotide=="UCA")||(trinucleotide=="UCG")||
          (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
          (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

