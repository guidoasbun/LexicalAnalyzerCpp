// CodeCppStarterCodeToParse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
/*
 *
 * The main focus of this demo code is to show states as we do parsing
 * AND
 * to show how to find a character or a word in a string without coding a for loop
 * we can use the find member function of the string class to help us.
 * AND
 * to improve testing time, note that we can just hit ENTER
 * and the default string is used for the demo.  This saves time pasting or typing data into the program.
 *
 *
 * Correct or perhaps better coding style is to use 'enum' for the state defines.
 *
 * Possible improvments:
 * 1) we could create a single string that has the alphabet, underscore and DIGITS in it to
 *    simplify the code.  We would not need to search both the alpha and DIGITS strings.
 * 2) Two of the states are doing the exact same thing.   We should eleminate one state, etc.
 * 3) some cleanup of the code is possible.
 *
 *
 */
using namespace std;
// Parsing constant data:
const string CAP_LETTERS("_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const string DIGITS("0123456789");
const string LETTERS_AND_DIGITS("_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

// Function Definitions
void demoParse();
string  setupParse();
vector<string> parseIdentifiers(string userInput);



void demoParse()
{
    cout << "Input a line of data. or zero characters and we will use a default string of data : ";
    string userInput;
    getline(cin, userInput);
    string defaultInput = " int main () { int myCount = My123;  int j = 123;  double tempature; return tempature  ";
    string parseStr = (userInput.length() == 0) ? defaultInput : userInput;

    //parseStr contains the data
    vector<string> results = parseIdentifiers(parseStr);

    //Prints out results which are in a vector
    for (int j = 0; j < results.size(); j++)
    {
        string oneIdent = results[j];
        /*string reserved = "int double short long class enum for do while return";
        int posInReserved = reserved.find(oneIdent);
        if  ( posInReserved < 0 )*/
        cout << oneIdent << endl;
    }
}

int mainExample()
{
    cout << "Code Cpp Starter Code To Parse!\n";
    demoParse();
    return 0;
}


vector<string> parseIdentifiers(string userInput)
{
    enum states { STATE_NOTHING, STATE_FIRST, STATE_SUCCEEDING, STATE_DONE };
    states stateCurrent = STATE_NOTHING;

    int inElementNum;
    char curChar;

    string identifier = "";
    inElementNum = 0;

    vector<string> results;

    int posLetter = -1;
    int posDigit = -1;

    while (inElementNum < userInput.length())
    {
        curChar = userInput[inElementNum++];

        switch (stateCurrent)
        {
        case STATE_NOTHING:
            // look for just a letter
            posLetter = CAP_LETTERS.find(toupper(curChar));
            if (posLetter >= 0)
            {
                stateCurrent = STATE_FIRST;
                identifier = curChar;
            }
            break;
        case STATE_FIRST:
            posLetter = LETTERS_AND_DIGITS.find(toupper(curChar));
            if (posLetter >= 0)
            {
                stateCurrent = STATE_SUCCEEDING;
                identifier = identifier + curChar;
            }
            else
            {
                stateCurrent = STATE_NOTHING; // we will start all over looking for the next identifier
                // but save off the identifier we have found
                results.push_back(identifier);
                identifier = "";
            }
            break;
        case STATE_SUCCEEDING:
            posDigit = -1;
            posLetter = CAP_LETTERS.find(toupper(curChar));
            if (posLetter < 0)
            {
                posDigit = DIGITS.find(curChar);
            }
            if (posLetter >= 0 || posDigit >= 0)
            {
                stateCurrent = STATE_SUCCEEDING;
                identifier = identifier + curChar;
            }
            if (posLetter < 0 && posDigit < 0)
            {
                stateCurrent = STATE_NOTHING; // we will start all over looking for the next identifier
                // but save off the identifier we have found
                results.push_back(identifier);
                identifier = "";
            }
            break;
        case STATE_DONE:
            break;
        }
    }
    return results;
}
