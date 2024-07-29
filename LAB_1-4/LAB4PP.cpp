#include<fstream> 
#include<iostream>
#include<string>

int main()
{
	std::cout << "The program counts the number of occurrences of a character in a string";
	int retr = 1;
	do
	{
		std::ifstream F("input.txt");
		std::string str, temp;
		char sym;
		std::getline(F, temp);
		std::getline(F, str);
		sym = temp[0];
		F.close();
		std::ofstream O("output.txt", std::ios::app);
		int res = 0;
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (sym == str[i])
			{
				++res;
			}
		}
		str.clear();
		O << "The number of occurrences " << sym << " in the string is " << res << std::endl;
		O.close();
		std::cout << "\nThe result has been written to the file\n";
		std::cout << "Do you want to change input and restart the program?\n";
		std::cout << "Print '1' or '2'\n";
		std::cout << "1-Yes 2-No\n";
		std::cin >> retr;

		while (retr != 1 && retr != 2)
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "You have not entered '1' or '2'\n";
			std::cout << "Print '1' or '2'\n";
			std::cin >> retr;
		}

	} while (retr == 1);
	std::cout << "The program is over";
}
