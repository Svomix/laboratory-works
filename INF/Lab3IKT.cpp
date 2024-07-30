#include <iostream>
#include <string>
using namespace std;

int main()
{

	int size;
	double temp;
	bool flag = false;
	string retr = "Yes";
	while (retr == "Yes")
	{
		int count = 0;
		cout << "The programm finds the number of different numbers\n";
		cout << "Enter a size of an array. It must be an integer and positive value\n";

		while (!(cin >> size) || cin.peek() != '\n' || size <= 0)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have entered a wrong value\n";
			cout << "Enter a valid value\n";
		}

		double* arr = new double[size];
		cout << "Enter elements of an array\n";
		for (int i = 0; i < size; ++i)
		{
			while (!(cin >> temp) || cin.peek() != '\n')
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "You have entered a wrong value\n";
				cout << "Enter a valid value\n";
			}
			for (int j = 0; j <= i; ++j)
			{
				if (arr[j] == temp)
				{
					j = i + 1;
				}
				else if (j == i)
				{
					++count;
				}
			}

			arr[i] = temp;
		}
		cout << "The result is " << count << endl;
		cout << "Do you want to restart the programm\n";
		cout << "Print 'Yes' or 'No'\n";
		cin >> retr;
		while(retr != "Yes" && retr != "No")
		{
			cout << "You have not entered 'Yes' or 'No'\n";
			cout << "Print 'Yes' or 'No'\n";
			cin >> retr;
		}
	}
}