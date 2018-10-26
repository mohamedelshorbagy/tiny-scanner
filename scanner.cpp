#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/** Functions
 * 
 */

void getToken(string);
bool isDigit(char);
bool isLetter(char);
bool isSpace(char);
bool isSymbol(char);

enum STATES
{
	START,
	INCOMMENT,
	INNUM,
	INID,
	INASSIGN,
	DONE
};
STATES state = START;

string RESERVED_WORDS[] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};

int main()
{
	ifstream file;
	string line, code;
	file.open("code.txt");
	while (!file.eof())
	{
		getline(file, line);
		code += line;
	}

	// Listen for the output in the screen and write it into the file required
	freopen("output.txt", "w", stdout);
	getToken(code);
	fclose(stdout);

	return 0;
}

/**
 * @function { getToken }
 * @param { String } l
 * @desc: parse the code in its input string (the content of the file) and cout the proper output for every text
 * @return { Void }
 * 
 */
void getToken(string l)
{
	string mytoken;
	bool res_flag = 0;
	int i = 0;
	while (state != DONE)
	{
		switch (state)
		{
		case START:
			if (isSpace(l[i]))
			{
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			else if (isDigit(l[i]))
			{
				state = INNUM;
			}
			else if (isLetter(l[i]))
			{
				state = INID;
			}
			else if (l[i] == ':')
			{
				state = INASSIGN;
			}
			else if (l[i] == '{')
			{
				i++;
				state = INCOMMENT;
			}
			else if (isSymbol(l[i]))
			{
				switch (l[i])
				{
				case ';':
					cout << l[i] << endl;
					break;
				default:
					cout << l[i] << " ";
					break;
				}
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			else
				state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT)
			{
				while (l[i] != '}')
				{
					i++;
				}
				i++;
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			break;

		case INNUM:
			while (isDigit(l[i]))
			{
				mytoken += l[i];
				i++;
			}
			cout << "number"
				 << " ";
			mytoken = "";
			if (i == l.length())
				state = DONE;
			else
				state = START;
			break;

		case INID:
			while (isLetter(l[i]))
			{
				mytoken += l[i];
				i++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (RESERVED_WORDS[i] == mytoken)
					res_flag = 1;
			}
			if (res_flag)
				cout << endl
					 << mytoken << " ";
			else
				cout << "identifier"
					 << " ";
			mytoken = "";
			res_flag = 0;
			if (i == l.length())
				state = DONE;
			else
				state = START;
			break;

		case INASSIGN:
			if (l[i] == ':')
			{
				i += 2;
				cout << ":="
					 << " ";
				state = START;
			}
			else
			{
				if (i == l.length())
					state = DONE;
				else
					state = START;
			}
			break;
		case DONE:
			break;
		}
	}
}
/**
 * @function { isDigit }
 * @desc: return true or false depends on the char type (digit or not)
 * @param { char } d
 * @return {boolean} [true, false]  
 * 
 */
bool isDigit(char d) { return (d >= '0' && d <= '9'); }

/**
 * @function { isLetter }
 * @desc: return true or false depends on the char type (letter or not)
 * @param { char } l
 * @return {boolean} [true, false]  
 * 
 */
bool isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }

/**
 * @function { isSpace }
 * @desc: return true or false depends on the char type (space or not)
 * @param { char } s
 * @return {boolean} [true, false]  
 * 
 */
bool isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }
/**
 * @function { isSymbol }
 * @desc: return true or false depends on the char type (symbol or not)
 * @param { char } c
 * @return {boolean} [true, false]  
 * 
 */
bool isSymbol(char c) { return (c == '+' || '-' || '*' || '/' || '=' || '<' || '(' || ')' || ';'); }