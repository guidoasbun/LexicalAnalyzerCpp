// LexicalAnalyzerCpp.cpp : Defines the entry point for the application.
//

#include "LexicalAnalyzerCpp.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string CAP_LETTERS = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string DIGITS = "0123456789";
const string LETTERS_DIGITS = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const string SINGLE_OPERATORS = "{}[]#()?.+-*/%^&|~!=<>";
const string DOUBLE_OPERATORS = "## <: ";

// Function prototypes
void parse(const string& fileName);
vector<string> parseIdentifier(const string& input);
void printTokens(const vector<string>& tokens);

// Function definitions
void parse(const string& fileName)
{
	fstream testFile;
	testFile.open(fileName, ios::in);

	if(testFile.is_open())
	{
		string line;
		while(getline(testFile, line))
		{
			if(line.empty()) continue;

			parseIdentifier(line);
		}
		testFile.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
	}

}

vector<string> parseIdentifier(const string& input)
{
	vector <string> tokens;

	

	return tokens;
}

void printTokens(const vector<string>& tokens)
{
		for(auto &token : tokens)
		{
			cout << token << endl;
	}
}



int main()
{
	const string fileName("test.txt");
	parse(fileName);


	return 0;
}
