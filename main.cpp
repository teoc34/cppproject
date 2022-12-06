//6.12.2022 - create table functions, the rest to be written soon

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
using namespace std;


class Table
{
	string* collumnName = nullptr;
	int noOfCollumns = 0;
	string* collumnType = nullptr;
	int* dimensionOfData = nullptr;
	int** dataInt = nullptr;
	string** dataText = nullptr;
	float** dataFloat = nullptr;
public:
	void setCollumnName(string name) {
		this->noOfCollumns += 1;
		this->collumnName[noOfCollumns] = name;
	}

	void setCollumnType(string type) {
		this->collumnType[noOfCollumns] = type;
	}

	void setdimensionOfData(int dimension) {
		this->dimensionOfData[noOfCollumns] = dimension;
	}

	string getCollumnName(int index) {
		if (index <= noOfCollumns)
			return this->collumnName[index];
	}

	string getTypeOfCollumnByIndex(int index) {
		if (index <= noOfCollumns)
			return this->collumnName[index];
	}

	string getTypeOfCollumByName(string name) {
		int pp = 0;
		for (int i = 1; i <= noOfCollumns; i++) {
			if (this->collumnName[i] == name) {
				return this->collumnType[i];
				pp = 1;
			}
		}
		if (pp == 0)
			return "No collumn with this name";
	}

	~Table() {
		if (this->collumnName != nullptr)
			delete[] this->collumnName;
		if (this->collumnType != nullptr)
			delete[] this->collumnType;
		if (this->dimensionOfData != nullptr)
			delete[] this->dimensionOfData;
		if (this->dataInt != nullptr)
			delete[] this->dataInt;
		if (this->dataText != nullptr)
			delete[] this->dataText;
		if (this->dataFloat != nullptr)
			delete[] this->dataFloat;
	}
	//the default value will be on the [0] of each data matrix
	Table(string* nameOfCollumn, string collumnType, int dimensionOfData, int defaultValue) {//the constructor for type int data of collumn

	}

	Table(string* nameOfCollumn, string collumnType, int dimensionOfData, float defaultValue) {//the constructor for type float data of collumn

	}

	Table(string* nameOfCollumn, string collumnType, int dimensionOfData, string defaultValue) {//the constructor for type text data of collumn

	}



};

char* readDynamicCommmand() {
	char* value;
	char buffer[1000];
	cout << endl << "Insert your command " << endl;
	fgets(buffer, sizeof(buffer), stdin);
	value = new char[strlen(buffer) + 1];
	strcpy(value, buffer);
	return value;
}
//this functions are made to edit the input of the user

//this function is from the first homework
//will edit the user's input so it can be used in the code
//this function will remove excessive spaces
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

char* toCapsLock(const char* text)
{
	char* result = new char[strlen(text) + 1];
	strcpy(result, text);
	int i = 0, n = strlen(text);
	while (i <= n) {
		if (text[i] >= 'a' && text[i] <= 'z')
			result[i] = text[i] - 32;
		else
			result[i] = text[i];
		i++;
	}
	return result;
}

bool paranthesisAccurateCreateTable(char* text) {
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

bool createTableCommand(char* text, char* name) {
	
	return true;//if input conditions are respected
	return false;//if the user wrote an inaccurate command
}

//this function will get the function
//from the user's command
char* commandToFunction(char* text) {
	//for create table function
	char* wrongcommandanswer = new char[3];
	strcpy(wrongcommandanswer, "-1");
	if (strstr(text, "(")) { //means the function is for creating a table, thus it has paranthesis
		char buffer[1000];
		int i = 0;
		while (text[i] != '(') {
			buffer[i] = text[i];
			i++;
		}
		buffer[i] = '\0';

		char* function = new char[i + 1];
		strcpy(function, buffer);

		char* newFunction = new char[i + 1];
		newFunction = removeSpaces(function);
		delete[] function;
		char* finalFunction = new char[i + 1];
		finalFunction = toCapsLock(newFunction);
		delete[] newFunction;
		//finalfunction has the following form: CREATETABLENAMEOFTABLE
		//we substract the command to keep the NAMEOFTABLE
		if (!(strstr(finalFunction, "CREATETABLE"))) {
			//if the user mispelled the comand
			return wrongcommandanswer;
		}
		else {
			finalFunction= finalFunction + 11;
			char* copyOfText = new char[strlen(text) + 1];
			strcpy(copyOfText, text);
			bool redlight = paranthesisAccurateCreateTable(strchr(copyOfText, '('));
			if (!redlight)
			{
				bool doubleLight=createTableCommand(strchr(copyOfText, '('), finalFunction);
				if (doubleLight)//if createTableCommand returns true - meaning there weren't any problems in creating the table - then we show the message for table creation
					return finalFunction;//finalFunction is the name of the table
				else return wrongcommandanswer;
			}
			else return wrongcommandanswer;
		}

	}
}

//this function will write on the screen
//the function requested by the user
void throwFunction(char* text) {
	while (commandToFunction(text) == "-1") {
		cout << endl << "Incorrect command. Please try again";
	}
	cout << endl << "Table " << commandToFunction(text) << " created.";
}
int main() {
	throwFunction(readDynamicCommmand());
	return 0;
}
