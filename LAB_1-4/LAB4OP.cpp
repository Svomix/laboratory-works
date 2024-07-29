#include <fstream>
int main()
{
	int c = 0;
	std::ifstream F;
	std::ofstream O;
	F.open("input.txt");
	O.open("output.txt");
	char sym,temp;
	F.get(sym);
	while (F.get(temp))
	{
		if (temp == sym)
			++c;
	}
	O << c;
	F.close();
	O.close();
}