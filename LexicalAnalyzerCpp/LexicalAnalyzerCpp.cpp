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
void DisplayIntroduction();
void parse(const string& fileName);
vector<string> parseIdentifier(const string& input);
void printTokens(const vector<string>& tokens);

// Main function
int main()
{
    DisplayIntroduction();
    const string fileName("test.txt");
    parse(fileName);
    return 0;
}


// Function definitions

// Displays Introduction
void DisplayIntroduction() {
    cout << "Ticket: 29273\n";
    cout << "Class: CMPR Computer Organization\n";
    cout << "Instr: Joel Kirscher\n";
    cout << "Student: Guido Asbun\n\n";
    cout << "Lexical Analyzer\n";
    cout << "This program was developed using the Clion IDE version 2023.2 On The Fedora 39 OS\n";
    cout << "This program was tested and compiled using clang version 17.0.4 (Fedora 17.0.4-1.fc39)\n\n";
}

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

			vector<string> tokens = parseIdentifier(line);
            printTokens(tokens);
		}
		testFile.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
	}
}





vector<string> parseIdentifier(const string& input) {

    enum State { Normal, InComment, InLineComment, InString, InOperator };

    State currentState = Normal;

    vector<string> tokens;
    string token;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];
        char nextCh = (i + 1 < input.length()) ? input[i + 1] : '\0';

        switch (currentState) {
            case Normal:
                if (ch == '/' && nextCh == '*') {
                    currentState = InComment;
                    tokens.push_back("/*");
                    i++; // Skip the next character
                } else if (ch == '/' && nextCh == '/') {
                    currentState = InLineComment;
                    tokens.push_back("//");
                    i++;
                } else if (ch == '"') {
                    currentState = InString;
                    token += ch;
                } else if (SINGLE_OPERATORS.find(ch) != string::npos) {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                    token += ch;
                    if (DOUBLE_OPERATORS.find(string() + ch + nextCh) != string::npos) {
                        token += nextCh;
                        i++;
                    }
                    tokens.push_back(token);
                    token.clear();
                } else if (isspace(ch)) {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                } else {
                    token += ch;
                }
                break;

            case InComment:
                if (ch == '*' && nextCh == '/') {
                    currentState = Normal;
                    tokens.push_back("*/");
                    i++;
                }
                break;

            case InLineComment:
                if (ch == '\n') {
                    currentState = Normal;
                }
                break;

            case InString:
                token += ch;
                if (ch == '"') {
                    currentState = Normal;
                    tokens.push_back(token);
                    token.clear();
                }
                break;
            case InOperator:
                break;
        }
    }

    // Add the last token if any
    if (!token.empty()) {
        tokens.push_back(token);
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

/*
 * Results:
 *
Ticket: 29273
Class: CMPR Computer Organization
Instr: Joel Kirscher
Student: Guido Asbun

Lexical Analyzer
This program was developed using the Clion IDE version 2023.2 On The Fedora 39 OS
This program was tested and compiled using clang version 17.0.4 (Fedora 17.0.4-1.fc39)


*/







//vector<string> parseIdentifier(const string& input)
//{
//    // Initializes the states of the function
//    enum states { STATE_NOTHING, STATE_FIRST, STATE_SUCCEEDING, STATE_DONE};
//    states currentState(STATE_NOTHING);
//
//    // Initializes the size of the input string and the element number
//    const size_t inputSize(input.length());
//    size_t elementNum(0);
//
//    // Initializes the identifier and the tokens
//    string identifier;
//    vector <string> tokens;
//
//    // Initializes the letter position in the Constants string
//    int letterPosition(-1);
//    // Initialize if it is a comment or not
//    bool comment(false);
//    bool isLetterOrDigit;
//
//    // While statement that looks at every character in the input line.
//    while (elementNum < inputSize)
//    {
//        const char curChar(input[elementNum++]);
//        char nextChar = input[elementNum];
//        char nextNextChar = input[elementNum+1];
//        switch (currentState) {
//            case STATE_NOTHING:
//                break;
//            case STATE_FIRST:
//                break;
//            case STATE_SUCCEEDING:
//                break;
//            case STATE_DONE:
//                break;
//
//        }
//
////        switch (currentState) {
////            case STATE_NOTHING:
////                letterPosition = LETTERS_DIGITS.find(toupper(curChar));
////                if (letterPosition >= 0) {
////                    currentState = STATE_FIRST;
////                    identifier = curChar;
////                }
////                break;
////
////            case STATE_FIRST:
////                letterPosition = LETTERS_DIGITS.find(toupper(curChar));
////                if (letterPosition >= 0)
////                {
////                    currentState = STATE_SUCCEEDING;
////                    identifier += curChar;
////                }
////                else
////                {
////                    currentState = STATE_NOTHING;
////
////                    identifier = "";
////                }
////                break;
////
////            case STATE_SUCCEEDING:
////
////
////                break;
////
////            case STATE_DONE:
////
////                break;
////        }
//
//
//        switch (currentState)
//        {
//            // this test if the first character is something, if not it breaks and goes to the next character...
//            // if it is something it goes to the next state
//            case STATE_NOTHING:
//                if (curChar != ' ')
//                {
//                    currentState = STATE_FIRST;
//                    identifier = curChar; // this is a string that will be accumulated and put into the vector
//                }
//                break;
//
//                // This state first check to see if the character is a letter/digit or a special character
//                // if it is a letter/digit, it will assign it a flag -> true and go to the next state
//                // if it is a special character, it will assign it a flag -> false and go to the next state
//            case STATE_FIRST:
//                //test to see if it is a 1st character is special or not
//                letterPosition = LETTERS_DIGITS.find(toupper(curChar));
//                if (letterPosition >= 0)
//                {
//                    isLetterOrDigit = true;
//                    currentState = STATE_SUCCEEDING;
//                    if(!comment) identifier += curChar;
//
//                } else
//                {
//                    isLetterOrDigit = false;
//                    currentState = STATE_SUCCEEDING;
//                    if(!comment) identifier += curChar;
//                }
//
//                letterPosition = -1;
//                break;
//
//            case STATE_SUCCEEDING:
//                if (isLetterOrDigit)
//                {
//                    if (comment)
//                    {
//                        currentState = STATE_NOTHING;
//                        break;
//                    }
//                    letterPosition = LETTERS_DIGITS.find(toupper(curChar));
//                    if (letterPosition < 0)
//                    {
//                        currentState = STATE_NOTHING;
//                        cout << "identifier: " << identifier << endl;
//                        identifier = "";
//                    }
//                } else
//                {
//                    // run test to see if it is a line ending comment operator
//                    if (curChar == '/' && nextChar == '/') {
//                        currentState = STATE_DONE;
//                        break;
//                    }
//                    // run test to see if it is a block comment operator
//                    if (curChar == '/' && nextChar == '*') {
//                        comment = true;
//                        currentState = STATE_NOTHING;
//                        break;
//                    }
//                    // test to see of comment has ended
//                    if (curChar == '*' && nextChar == '/') {
//                        comment = false;
//                        currentState = STATE_NOTHING;
//                        break;
//                    }
//                    // test to see if inside a comment block
//                    if (comment)
//                    {
//                        currentState = STATE_NOTHING;
//                        break;
//                    }
//
//                }
//                break;
//            case STATE_DONE:
//                break;
//        }
//    }
//
//    return tokens;
//}