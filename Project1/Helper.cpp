#include "Token.h"
#include "Helper.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;


// adds each line of file to input string
void readFile(string & input) {
	string buffer;
	while (getline(cin, buffer)) {
		input += buffer;
	}
}

// determines number of each atom, sum for numeric atoms and outputs aspects of each type of token
void output(vector<Token>& tokens) {
	int open(0), close(0), numeric(0), literal(0), numSum(0);
	string numericAtoms(""), literalAtoms("");
	Token token;
	// checks by token type
	for (unsigned i = 0; i < tokens.size(); i++) {
		token = tokens[i];
		if (token.getType() == "Open") {
			open++;
		} else if (token.getType() == "Close") {
			close++;
		} else if (token.getType() == "Atom") {
			if (token.getAtom() == "Literal") {
				literal++;
				literalAtoms += ", " + token.getValue();
			} else if (token.getAtom() == "Numeric") {
				numeric++;
				numericAtoms += ", " + token.getValue();
				stringstream value(token.getValue());
				int i;
				value >> i;
				numSum += i;
			}
		} 
	}
	
	cout << "LITERAL ATOMS: " << literal << literalAtoms << endl;
	cout << "NUMERIC ATOMS: " << numeric << ", " << numSum << endl;
	cout << "OPEN PARENTHESES: " << open << endl;
	cout << "CLOSING PARENTHESES: " << close << endl;
}

// Gets and determines the type of token 
Token getNextToken(string input, int& index) {
	Token token;
	try {
		// for EOF tokens
		if (input.length() == (unsigned) index) {
			token.setType("EOF");
			token.setValue("\0");
			return token;
		// Moves past spaces
		} else if (input[index] == 32) {
			return getNextToken(input, ++index);
		// For open parentheses
		} else if (input[index] == '(') {
			index++;
			token.setType("Open");
			token.setValue("(");
			return token;
		// For closed parentheses
		} else if (input[index] == ')') {
			index++;
			token.setType("Close");
			token.setValue(")");
			return token;
		// for Literal Atoms if first char is capital letter
		} else if (input[index] >= 'A' && input[index]<= 'Z') {
			string s = string(1, input[index]);
			int t = index;
			// stores any following letters or capitals
			while ((input[++t] >= 'A' && input[t] <= 'Z') || (input[t] >= '0' && input[t] <= '9')) {
				s += input[t];
			}
			index = t;
			token.setType("Atom");
			token.setAtom("Literal");
			token.setValue(s);
			return token;
		// for numerical atoms if first char is number
		} else if (input[index] >= '0' && input[index] <= '9') {
			string s = string(1, input[index]);
			int t = index;
			// adds following numbers and captial letters
			while ((input[++t] >= 'A' && input[t] <= 'Z') || (input[t] >= '0' && input[t] <= '9')) {
				s += input[t];
			} 
			index = t;
			char c;
			// creates error token if letter follows after number
			for (unsigned i = 0; i < s.length(); i++) {
				c = s[i];
				if (c >= 'A' && c <= 'Z') {
					token.setType("ERROR");
					token.setValue(s);
					return token;
				}
			}
			token.setType("Atom");
			token.setAtom("Numeric");
			token.setValue(s);
			return token;
		}
	}
	catch (exception& e) {
 		cout << "An exception was caught with message '" << e.what() << "'" << endl;
	}
	token.setType("EOF");
	return token;
}
