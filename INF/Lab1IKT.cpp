#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "The program is calculate the Euler function\n";
	long long int n;
	string retr = "Yes";
	while (retr == "Yes")
	{
		cout << "Please enter positive and integer number to calculate the Euler function\n";
		while (!(cin >> n) || (cin.peek() != '\n') || (n <= 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have eneterd the wrong value\n" << "Please enter positive and integer number\n";
		}
		int result = n;
		for (int i = 2; i * i <= n; ++i)
			if (n % i == 0)
			{
				while (n % i == 0)
				{
					n /= i;
				}
				result -= result / i;
			}
		if (n > 1)
			result -= result / n;
		
		cout <<"The Euler function value is " << result;
		cout << "\nDo you want to restart the program\n" << "Print 'Yes' or 'No'\n";
		cin >> retr;
		while (retr != "Yes" && retr != "No")
		{
			cout << "You have not enered 'Yes' or 'No'\n" << "Print 'Yes' or 'No'\n";
			cin >> retr;
		}
	}
	cout << "The program is over";
}