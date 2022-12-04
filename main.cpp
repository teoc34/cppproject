#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
enum OrderType { Coffee, Water, Sweets, Juice}
class CoffeeShop
{
    
public:
    string CoffeeShopLocation="Calea Victoriei";
    string *Departments="Marketing";
    string *Employees="Andrei";
    int Orders=0;
    int Order_Item=1;
    OrderType type=Coffee;
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

//this function will get the function
//from the user's command
char* commandToFunction(char* text) {
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
	return finalFunction;
}

//this function will write on the screen
//the function requested by the user
void throwFunction(char* text) {
	cout << endl << commandToFunction(text);
}
int main() {
	throwFunction(readDynamicCommmand());
	return 0;
}
