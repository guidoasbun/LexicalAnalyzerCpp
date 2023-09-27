// LexicalAnalyzerCpp.cpp : Defines the entry point for the application.
//

#include "LexicalAnalyzerCpp.h"
#include <fstream>
#include <string>

using namespace std;

int main()
{
	fstream testFile;
	testFile.open("test.txt", ios::in);
	if(testFile.is_open())
	{
		string line;
		while (getline(testFile,line))
		{
			if (line.empty()) continue;


			cout << line << endl;
		}
		testFile.close();
	}
	else
	{
		cout << "Error opening file";
	}


	return 0;
}
