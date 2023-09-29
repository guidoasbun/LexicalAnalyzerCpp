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
const string DOUBLE_OPERATORS = "## <:";

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
	enum states { STATE_NOTHING, STATE_FIRST, STATE_SUCCEEDING, STATE_DONE, STATE_COMMENT };
	states currentState = STATE_NOTHING;

	const size_t inputSize(input.length());
	size_t elementNum(0);

    string identifier = "";
	vector <string> tokens;

    int letterPosition(-1);

	while (elementNum < inputSize)
	{
		const char curChar(input[elementNum++]);
        // next char = input[elementNum]
        // 3rd char =  input[elementNum+1]

		switch (currentState)
		{
		    case STATE_NOTHING:
                if (curChar != ' ')
                {
                    currentState = STATE_FIRST;
                    identifier = curChar;
                }
			    break;

            case STATE_FIRST:
                //test to see if it is a word or number
                letterPosition = LETTERS_DIGITS.find(toupper(curChar));


            case STATE_DONE:
                break;


		}
	}


	
	

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