#include <iostream>;
#include <string>;
#include <cmath>
using namespace std;

int main()
{
	long double side1, side2, side3;
	double cos, sin;
	string retr = "Yes";
	while(retr == "Yes")
	{
		cout << "The program finds 3 triangle vertices\n" << "Please eneter 3 sides of triagle\n";
		cout << "Enter the first side\n";
		while (!(cin >> side1) || (cin.peek() != '\n' || side1 <= 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have entered a not valid value\n" << "Enter a positive and integer value\n";
		}
		cout << "Enter the second side\n";
		while (!(cin >> side2) || (cin.peek() != '\n' || side2 <= 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have entered a not valid value\n" << "Enter a positive and integer value\n";
		}
		cout << "Enter the third side\n";
		while (!(cin >> side3) || (cin.peek() != '\n' || side3 <= 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "You have entered a not valid value\n" << "Enter a positive and integer value\n";
		}
		cos = (side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3);
		sin = sqrt(1 - (cos * cos));
		cout << ("0 0\n");
		cout << side1 << " 0\n";
		cout << side3 * cos << " " << side3 * sin << "\n";

	}
}