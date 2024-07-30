#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

typedef tuple < double, double > val_t;
map<double, vector<val_t>> list;

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
	if (list.find(x) == list.end())
	{
		list[x] = vector<val_t>{};
	}
	vector<val_t>& ref_vec = list[x];
	for (int i = 0; i < a; ++i)
	{
		int n = i + 1;
		try
		{
			tie(an, sn) = ref_vec.at(i); 
			cout << "(Cached) " << "N = " << n << " An = " << an << " Sn = " << sn << endl;
		}
		catch (out_of_range& e)
		{
			an = presum(n) * pow(x, n + 1) / (n + 1);
			sn += 2 * an;
			ref_vec.push_back(make_tuple(an, sn));
			cout << "N = " << n << " An = " << an << " Sn = " << sn << endl;
		}
	}
}

void countAcc(double a, double x)
{
	long double an, sn = 0, en = 0;
	int n = 1;
	int i = 0;
	{
		if (list.find(x) == list.end())
		{
			list[x] = vector<val_t>{};
		}
		vector<val_t>& ref_vec = list[x];
		do
		{
			int n = i + 1;
			try
			{
				tie(an, sn) = ref_vec.at(i);
				en = abs(presum(n + 1) * pow(x, n + 2) / (n + 2) / sn);
				cout << "(Cached)" << "N = " << n << "An = " << an << " Sn = " << sn << endl;
			}
			catch (out_of_range& e)
			{
				an = presum(n) * pow(x, n + 1) / (n + 1);
				sn += 2 * an;
				en = abs(presum(n + 1) * pow(x, n + 2) / (n + 2) / sn);
				ref_vec.push_back(make_tuple(an, sn));
				cout << "N = " << n << " An = " << an << " Sn = " << sn << endl;
			}
			i++;
		} while (en > a);
	}
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
