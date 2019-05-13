#include "Input.h"
#include "ConsoleFunctions.h"
#include <sstream>
#include <limits>
#include <regex>

using namespace std;

/**
* Check if there is any other character than an escape line in the end of the input
*
* @param	&in		Input string stream that you want to check the end
*
* @return	bool	Boolean value correspondent to if there is something different to '\n' in the end
*/
bool afterNumber(istringstream & in)
{
	int numbers = 0;
	char ch;
	if (in.get(ch))
	{
		return true;
	}
	return false;
}

unsigned int intInput(string question)
{
	int option;
	bool valid = false;

	string prov;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!valid)
	{
		getlineZ(cin, prov);
		istringstream iss(prov);
		while (!(iss >> option))
		{
			if (iss.eof())
			{
				iss.clear();
				cin.clear();
			}
			if (iss.fail())
			{
				iss.clear();
				cin.clear();
			}

			clrscr(currentPos);
			getlineZ(cin, prov);
			iss.str(prov);
		}
		if (!afterNumber(iss) && option >= 0)
		{
			valid = true;
		}
		else
		{
			cin.clear();
		}
		if (!valid)
		{
			clrscr(currentPos);
		}
	}

	return static_cast<unsigned int>(option);
}

int menuInput(string question, int inferiorLimit, int superiorLimit)
{
	string option;
	bool ValidInput = false;
	int option_number;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getlineZ(cin, option);


		if (cin.eof())
		{
			cin.clear();
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}
		if (option.empty())
		{
			ErrorFlag = true;
		}
		else
		{
			if (option.length() > 0) {
				for (size_t i = 0; i < option.length(); i++)
				{
					if (!isdigit((unsigned char)option.at(i)))
					{
						ErrorFlag = true;
						break;
					}
				}
			}
			if (!ErrorFlag)
				option_number = stoi(option);

			if (!ErrorFlag && !(option_number >= inferiorLimit && option_number <= superiorLimit))
			{
				ErrorFlag = true;
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{

			clrscr(currentPos);
		}

	}

	return option_number;
}