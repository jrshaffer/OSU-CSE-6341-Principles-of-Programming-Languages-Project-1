#include <string>
#include <vector>
#include "Token.h"

using namespace std;

// reads file input
void readFile(string & input);

// structures output of tokens and ouputs the tokens
void output(vector<Token>& tokens);

// gets each token from the input file
Token getNextToken(string input, int & index);
