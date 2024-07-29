#include <fstream>

double** create_mat(std::ifstream& inp, const size_t row, const size_t col)
{
	double** matrix = new double* [row]; // создание двумерного динамического массива
	for (size_t r = 0; r < row; ++r)
	{
		matrix[r] = new double[col]; // инициализация элементов двумерного динамического массива
		for (size_t c = 0; c < col; ++c)
		{
			inp >> matrix[r][c]; // инициализация элементов одномерного динамического массива
		}
	}
	return matrix;
}

void swap_col(double** matrix, const size_t row, const size_t change_col1, const size_t change_col2)
{
	for (size_t r = 0; r < row; ++r)
	{
		std::swap(matrix[r][change_col1], matrix[r][change_col2]); // смена элементов,находящихся в заданных столбцах, местами
	}
}

void print_mat(std::ofstream& outp, double** matrix, const size_t row, const size_t col)
{
	for (size_t r = 0; r < row; ++r)
	{
		for (size_t c = 0; c < col; ++c)
		{
			outp << matrix[r][c] << " "; // запись ответа в файл
		}
	}
}

void delete_mat(double** matrix, const size_t row, const size_t col)
{
	for (size_t r = 0; r < row; ++r)
	{
		delete[] matrix[r]; // удаление одномерных динамических массивов
	}
	delete[] matrix; // удаление двумерного динамического массива
}

int main()
{
	std::ifstream inp("input.txt"); // открытие входного файла
	std::ofstream outp("output.txt");// открытие выходного файла
	size_t row, col; // объявление переменных, отвечающих за количество строк и столбцов в матрице
	inp >> row >> col; // инициализация переменных row и col
	double** matrix = create_mat(inp, row, col); // создание и заполнение матрицы
	size_t change_col1, change_col2; //объявление переменных, отвечающих за номера столбцов, которые нужно поменять местами 
	inp >> change_col1 >> change_col2; // инициализация переменных change_col1 и change_col2
	swap_col(matrix, row, change_col1, change_col2); // функция, меняющая заданные столбцы в матрице
	print_mat(outp, matrix, row, col); // функция для помещения ответа в файл
	delete_mat(matrix, row, col); // функция для удаления матрицы
	inp.close(); // закрытие входного файла
	outp.close(); //закрытие выходного файла
	return 0;
}