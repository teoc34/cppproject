#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
using namespace std;


class Table
{
	string nameOfTable;
	string collumnName;
	string collumnType;
	int indexCollumn = 0;
	int dimensionOfData;
	int* dataInt = nullptr;
	int defaultValueInt = 0;
	string* dataText = nullptr;
	string defaultValueText;
	float* dataFloat = nullptr;
	float defaultValueFloat;
	bool ifFloat = 0, ifText = 0, ifInt = 0;
	//the ifInt, ifText, ifFloat variable show if the collumn of the table is type int, type float or type string


public:

	//-------------------------*Constructors*------------------------------------------------------------
	Table(string nameOfCollumn, string collumntype, int dimensionofdata, int defaultvalue) 
		: collumnName(nameOfCollumn), 
		collumnType(collumntype), 
		dimensionOfData(dimensionofdata), 
		defaultValueInt(defaultvalue){//the constructor for type int data of collumn
		this->ifInt = true;
		delete[] this->dataFloat;
		delete[] this->dataText;
	}

	Table(string nameOfCollumn, string collumntype, int dimensionofdata, float defaultvalue) 
		: collumnName(nameOfCollumn), 
		collumnType(collumntype), 
		dimensionOfData(dimensionofdata), 
		defaultValueFloat(defaultvalue) {//the constructor for type float data of collumn
		this->ifFloat = true;
		delete[] this->dataText;
		delete[] this->dataInt;
	}

	Table(string nameOfCollumn, string collumntype, int dimensionofdata, string defaultvalue) 
		: collumnName(nameOfCollumn), 
		collumnType(collumntype), 
		dimensionOfData(dimensionofdata), 
		defaultValueText(defaultvalue) {//the constructor for type text data of collumn
		this->ifText = true;
		delete[] this->dataFloat;
		delete[] this->dataInt;
	}


	//---------------------------*Setters and Getters*-----------------------------------------

	void setCollumnName(string name) {
		this->indexCollumn += 1;
		this->collumnName = name;
	}

	void setCollumnType(string type) {
		this->collumnType = type;
	}

	void setdimensionOfData(int dimension) {
		this->dimensionOfData = dimension;
	}

	string getCollumnNamebyIndex(int index) {
		if (this->indexCollumn == index)
			return this->collumnName;
		else return "0"; //"0" means the collumn is not the one the user is seeking, is the condition in a subsequent if - in the program
	}

	string getTypeOfCollumnByIndex(int index) {
		if (this->indexCollumn == index)
			return this->collumnType;
		else return "0";
	}

	string getTypeOfCollumByName(string name) {
			if (this->collumnName == name) {
				return this->collumnType;
			}
		return "0";
	}

	void setNameOfTable(string name) {
		this->nameOfTable = name;
	}

	//--------------------*Destructor*---------------------------

	~Table() {
		if (this->dataInt != nullptr)
			delete[] this->dataInt;
		if (this->dataText != nullptr)
			delete[] this->dataText;
		if (this->dataFloat != nullptr)
			delete[] this->dataFloat;
	}

};

//---------------------------------------*End of Class Definition*------------------------------------------------


//this function splits the command into words so it can be analyzed


int Split(const char* s, char delimiter, const char** words) { 
	// const char** words is the array that contains the words of the function
	int numWords = 0;
	const char* start = s;
	const char* end = s;
	while (*end != '\0') {
		if (*end == delimiter) {
			int length = end - start;
			char* word = new char[length + 1];
			strncpy(word, start, length);
			word[length] = '\0';
			words[numWords] = word;
			numWords++;
			start = end + 1;
		}
		end++;
	}
	if (start != end) {
		int length = end - start;
		char* word = new char[length + 1];
		strncpy(word, start, length);
		word[length] = '\0';
		words[numWords] = word;
		numWords++;
	}
	return numWords;
}

char* readDynamicCommmand() {
	char* value;
	char buffer[1000];
	cout << endl << "Insert your command " << endl;
	fgets(buffer, sizeof(buffer), stdin);
	value = new char[strlen(buffer) + 1];
	strcpy(value, buffer);
	return value;
}


//these functions are made to edit the input of the user

//this function is from the first homework
//removeSpaces will edit the user's input so it can be used in the code
//removeSpaces will remove excessive spaces
//USED ONLY for Drop table function
char* removeSpaces(const char* text) {
	char* result = new char[strlen(text) + 1];
	strcpy(result, text);
	int k = 0;
	while (result[k] == ' ') {
		result++;
	}
	char* newresult = new char[strlen(result) + 1];
	strcpy(newresult, result);

	int n = strlen(newresult);
	int i = 0;
	k = 0;
	while (i <= n) {
		if (result[i] != ' ') {
			newresult[k] = result[i];
			k++;
		}
		i++;
	}
	return newresult;
}


bool paranthesisAccurate(char* text) {
	//for number of paranthesis
	int rightParanthesis = 0; //the number of ")"
	int leftParanthesis = 0; // the number of "("
	int i = 0;
	while (text[i] != NULL) {
		if (text[i] == '(')
			leftParanthesis++;
		if (text[i] == ')')
			rightParanthesis++;
		i++;
	}
	if (leftParanthesis == rightParanthesis)
		return true;
	return false;
}

void createTable(char* words, int numWords,  Table& a){
	for (int i = 4; i <= numWords, i = i + 4) {
		for (int j = 0; j < 4; j++) {
			while (strchr(words[i+j], '(')!=nullptr)
				words[i] += 1;
			while (strchr(words[i + j], ')') != nullptr || strchr(words[i + j], ',') != nullptr)
			{
				char* newword = new char[strlen(words[i + j])];
				for (k = 0; k < strlen(words[i + j]) - 1; k++) {
					newword[k] = words[i + j][k];
				}
				newword[k] = '\n';
			}
			delete[] words[i + j];
			strcpy(words[i+j], newword);
			delete[]  newword;
	}
}

char* commandToFunctionCreateTable(char* text, Table& a) { //THIS CODE DOESN'T ACCEPT THE [IF NOT EXISTS] SECTION OF COMMAND 
	// we split the command into words
	const char* words;
	int numWords = Split(text, ' ', words); //words is passed through reference
	if (numWords < 7 || strcmp(words[0], "CREATE") || strcmp(words[1], "TABLE")) //meaning we don't have either the name or at least a correctly defined collumn
		return nullptr;
	if (!paranthesisAccurate) //the number of paranthesis is not right
		return nullptr;
	if ((numWords - 3) % 4 != 0) // the number of paranthesis is correct, but the description of each collumn is incorrect || the name contains spaces
		return nullptr;
	char* wordsofCollumns;
	int numWordsAfterCollumns = Split(strstr(text, "("), ' ', wordsofCollumns);
	if (numWordsAfterCollumns % 4 != 0) //if the last "if" was overrun (in the case of both the name of the table and the description of collumns were written incorrectly)
		return nullptr;
	
	//NOW we know the function was written correcly

	
	createTable(words, numWords, a);
	return words[2];
	
}


enum typeFunction { "CreateTable", "CreateIndex", "DropTable", "DropIndex", "DisplayIndex", "Insert", "Select", "Update"};
//this enum will be used to give the user an idea of how the function must look like. 
bool throwFunction(char* text, Table& a) {
	
	//we verify each possibility of function 
	
	if (strstr(text, "CREATE TABLE")) {
		if (commandToFunctionCreateTable(text, a) != nullptr)
		{
			cout << endl << "Table " << commandToFunctionCreateTable(text, a) << " created.";
			return 1;
		}
	}

	else if (strstr(text, "CREATE INDEX")) {
		return 1;
	}
	else if (strstr(text, "DROP TABLE")) {
		return 1;
	}
	else if (strstr(text, "DROP INDEX")) {
		return 1;
	}
	else if (strstr(text, "DISPLAY INDEX")) {
		return 1;
	}
	else if (strstr(text, "INSERT")) {
		return 1;
	}
	else if (strstr(text, "SELECT")) {
		return 1;
	}
	else if (strstr(text "UPDATE")) {
		return 1;
	}

	cout << endl << "Incorrect command. Please try again";
		return 0;
	}


int main() {
	Table* a;
	while (! throwFunction(readDynamicCommmand(), a)) {
		throwFunction(readDynamicCommmand(), a);
	}
	return 0;
}
