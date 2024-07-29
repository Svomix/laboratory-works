#include <fstream>

int main()
{
	std::ifstream inpfile("input.txt");
	std::ofstream outfile("output.txt");
	int a, b;
	inpfile >> a >> b;
	outfile << a + b;
	inpfile.close();
	outfile.close();
}