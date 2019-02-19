#ifndef C_CPP_STRING_H
#define C_CPP_STRING_H

#include <iostream>

using namespace std;

const int MAX_C_STRING_SIZE = 256;

char* toCString(int number) {
	char* cString = new char[MAX_C_STRING_SIZE];
	int pos = 0;
	do {
		cString[pos++] = number % 10 + '0';
		number /= 10;
	} while (number);
	for (int i = 0; i < pos / 2; i++) {
		swap(cString[i], cString[pos - 1 - i]);
	}
	cString[pos] = '\0';
	
	return cString;
 }
 
 char* toCString(string cPPString) {
 	char* cString = new char[MAX_C_STRING_SIZE];
 	for (int i = 0; i < cPPString.size(); i++) {
 		cString[i] = cPPString[i];
	}
	cString[cPPString.size()] = '\0';
	 
	return cString; 
}

char* toCString(char c) {
	char* cString = new char[2];
	cString[0] = c;
	cString[1] = '\0';
	
	return cString;
}

char* concatCString(char* s1, char* s2) {
	char* s = new char[MAX_C_STRING_SIZE];
	int pos = 0;
	for (int i = 0; s1[i] != '\0'; i++) {
		s[pos++] = s1[i];
	}
	for (int i = 0; s2[i] != '\0'; i++) {
		s[pos++] = s2[i];
	}
	s[pos] = '\0';
	
	return s;
}

#endif // C_CPP_STRING_H
