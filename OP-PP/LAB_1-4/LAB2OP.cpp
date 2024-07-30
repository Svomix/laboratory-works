#include <iostream>
#include <cmath>
#include <string>
using namespace std;

double presum(int n)
{
	double sum = 0;
	for (double i = 1; i <= n; ++i)
	{
		sum += 1 / i;
	}
	return sum;
}

void countAs(int a, double x)
{
	long double an = 0, sn = 0, en;
	for (int n = 1; n <= a; ++n)
	{
		an = presum(n) * pow(x, n + 1) / (n + 1);
		sn += 2 * an;
		en = abs(presum(n + 1) * pow(x, n + 2) / (n + 2) / sn);
		cout << "N = " << n << ":An = " << an << " " << "Sn = " << sn << " " << "En = " << en << '\n';
	}
}

void countAcc(double a, double x)
{
	long double an, sn = 0, en = 0;
	int n = 1;
	do
	{
		an = presum(n) * pow(x, n + 1) / (n + 1);
		sn += 2 * an;
		en = abs(presum(n + 1) * pow(x, n + 2) / (n + 2) / sn);
		cout << "N = " << n << ":An = " << an << " " << "Sn = " << sn << " " << "En = " << en << '\n';
		++n;
	} while (en > a);
}

int main()
{ 
	double a, x;
	string retr = "Yes";
	while (retr == "Yes")
	{
		cout << "Enter the a (a > 0)\n";
		while (!(cin >> a) || cin.peek() != '\n' || a <= 0)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have not entered the number\n";
			cout << "Enter the a (a > 0)\n";
		}
		cout << "Enter the x (-1 <= x < 1)\n";
		while (!(cin >> x) || cin.peek() != '\n' || x >= 1 || x < -1)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have not entered the valid number\n";
			cout << "Enter a valid x\n";
		}
		if (a == int(a))
		{
			countAs(a, x);
		}
		else
		{
			countAcc(a, x);
		}
		cout << "Do you want to restart the program?\n" << "Print 'Yes' or 'No'\n";
		cin >> retr;
		while (retr != "Yes" && retr != "No")
		{
			cout << "You have not entered 'Yes' or 'No'\n" << "Print 'Yes' or 'No'\n";
			cin >> retr;
		}
	}
}
