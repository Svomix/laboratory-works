#include <iostream>
#include <string>
#include <stdint.h>
#include <iomanip>
using namespace std;

int main()
{
	int row, col;
	string retr = "Yes";
	cout << "The program calculates maximum and minimum of a matrix\n";
	while (retr == "Yes")
	{
		double max = DBL_MIN;
		double min = DBL_MAX;
		cout << "Enter a lenght of a row\n";
		while (!(cin >> row) || cin.peek() != '\n' || row <= 0)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have not entered a valid value\n";
			cout << "Enter a valid number\n";
		}
		cout << "Enter a lenght of a column\n";
		while (!(cin >> col) || cin.peek() != '\n' || col <= 0)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have not entered a valid value\n";
			cout << "Enter a valid number\n";
		}
		double** matrix = new double* [row];
		for (int i = 0; i < col; ++i)
		{
			matrix[i] = new double[col];
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				cout << "Enter the element[" << i << "]" << "[" << j << "]\n";
				while (!(cin >> matrix[i][j]) || cin.peek() != '\n')
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "You have not entered a valid value\n";
					cout << "Enter a valid number\n";
				}
			}
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (max < matrix[i][j])
				{
					max = matrix[i][j];
				}
				if (min > matrix[i][j])
				{
					min = matrix[i][j];
				}
			}
		}
		cout << "Maximum of the matrix is " << setprecision(10) << max << " " << "Minimum of the matrix is " << min << endl;
		for (int i = 0; i < row; ++i)
		{
			delete[] matrix[i];
		}
		cout << "Do you want to restart the program?\n" << "Print 'Yes' or 'No'\n";
		cin >> retr;
		while (retr != "Yes" && retr != "No")
		{
			cout << "You have not entered 'Yes' or 'No'\n";
			cout << "Print 'Yes' or 'No'\n";
			cin >> retr;
		}
	}
}