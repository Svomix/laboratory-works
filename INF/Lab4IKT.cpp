#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	cout << "The programm finds the number of the sentences\n";
	fstream F;
	char sym, sym1 = '*';
	int c = 0;
	string name;
	cin >> name;
	F.open(name);
	if (F.is_open())
	{
		while (F.get(sym))
		{
			if (sym1 == '.' && sym == '.' || sym1 == '.' && sym == '!' || sym1 == '.' && sym == '?')
			{
					--c;
			}
			if (sym == '.' || sym == '!' || sym == '?')
			{
				++c;
			}
			sym1 = sym;
		}
	}
	else
	{
		cout << "Unable to open file";
	}
	F.close();
	cout << "The result is " << c << endl;
}