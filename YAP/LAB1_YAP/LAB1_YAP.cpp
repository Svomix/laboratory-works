#include <fstream>

double* append(double* arr, size_t& size, size_t& capacity, double elem) // функция для добавления нового элемента в массив
{

	if (size == capacity) // если текущий размер массива равен 'запасу' выделенной памяти производится выделение новой памяти
	{
		capacity = size * 2; // увеличение размера 'запаса' вдвое
		double* new_arr = new double[capacity];
		for (size_t i = 0; i < size; ++i) // копирование старых элементов
		{
			new_arr[i] = arr[i];
		}
		new_arr[size] = elem; // добавление текущего элемента
		++size; // увеличение размера массива
		delete[] arr; // удаление старой памяти
		return new_arr;
	}
	else // если 'запаса' уже хватает, то добавляем элемент в конец
	{
		arr[size] = elem;
		++size;
		return arr;
	}
}

int diff_pos_neg(double* arr, size_t size) // функция для обработки массива
{
	int res = 0; // начальное значение разности устанавливается на 0
	for (size_t i = 0; i < size; arr[i] >= 0 ? res += (arr[i] != 0) : res--, ++i); 	// идет проход по всем элементам массива, если очередное значение >= 0, то счетчик увеличивается на 1, если число не равно нулю, иначе уменьшается на 1.
	return res;
}

int main()
{
	size_t size = 0, capacity = 1; // начальные размеры массива - 0 и 'запаса' - 1
	std::ifstream inpfile("input.txt"); // открытие входного файла 
	std::ofstream outfile("output.txt"); // открытие выходного файла
	double* arr = new double[capacity]; // выделение памяти для массива
	double curr; // текущий элемент
	while (inpfile >> curr)
	{
		arr = append(arr, size, capacity, curr); // добавление элемента в массив
	}
	int res = diff_pos_neg(arr, size); // вычисление разности между количеством положительных и отрицательных элементов
	outfile << res; // запись ответа в файл
	inpfile.close(); // закрытие входного файла 
	outfile.close(); // закрытие выходного файла
	delete[] arr; // удаление памяти выделенной для хранения массива
	return 0;
}