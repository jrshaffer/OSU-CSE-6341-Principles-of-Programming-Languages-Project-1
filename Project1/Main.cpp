// Joseph Shaffer
// Shaffer.567
// CSE 6341 Autumn 2017

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include "Token.h"
#include "Helper.h"

using namespace std;


// main class
int main(int argc, char *argv[]) {
	string input; // represents file's input
	vector<Token> tokens; // vector of tokens
	int index(0); // index for reading file 
	readFile(input);
	Token token = getNextToken(input, index);
	tokens.push_back(token); // adds first token to vector
	// Stops adding tokens to vector if at End of file
	while (token.getType() != "EOF") {
		if (token.getType() == "ERROR") {
			cout << token.getType() << ": Invalid token: " << token.getValue() << endl;
			exit(0);
		}
		token = getNextToken(input, index);
		tokens.push_back(token);
	}
	output(tokens);	// outputs token
	 
	return 0;
}





			
	
