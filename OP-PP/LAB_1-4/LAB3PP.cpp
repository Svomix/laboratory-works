#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
//*
// Подключение библиотек для:
// 1) Ввода вывода данных
// 2) Использования вектора
// 3) Использования srand
// 4) Использование таймера
// 5) Использование строк
// 6) Использование степеней
//*
using namespace std;

int verificate(int num) // Функция для проверки валидности данных о размере вектора
{
	while (!(cin >> num) || cin.peek() != '\n' || num < 2)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "You have entered a not valid value\n";
		cout << "Enter a size of a vector (size is an integer number and >= 2)\n";
	}
	return num;
}

string verificate(string retr) // Функция для проверки валидности данных о размере вектора
{
	while (retr != "Yes" && retr != "No") // Запрос на перезапуск программы
	{
		cout << "You have not entered 'Yes' or 'No'\n";
		cout << "Print 'Yes' or 'No'\n";
		cin >> retr;
	}
	return retr;
}

int verificate_for_numbers(int num) // Функция для проверки валидности данных о размере вектора
{
	while (!(cin >> num) || cin.peek() != '\n')
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "You have entered a not valid value\n";
		cout << "Enter an integer value\n";
	}
	return num;
}


void filling_arr_auto(int size, vector<int>& arr) //  Функция для заполнение вектора случайными числами
{
	random_device dev;
	mt19937 engine(dev());
	uniform_int_distribution<int> distrit(-1000000, 1000000);
	for (int i = 0; i < size; ++i)
	{
		arr[i] = distrit(engine); // Генерация случайных положительных и отрицательных чисел
	}
}

void filling_arr_keyboard(int size, vector<int>& arr) //  Функция для заполнение вектора случайными числами
{
	cout << "Enter " << size << " numbers for filling the array\n";
	int temp = 1;
	for (size_t i = 0; i < size; ++i)
	{
		cout << "Enter " << i + 1 << " number:\n";
		temp = verificate_for_numbers(temp);
		arr[i] = temp;
	}
}

void filling_arr_auto_notuniq(int size, vector<int>& arr) //  Функция для заполнение вектора случайными числами
{
	random_device dev;
	mt19937 engine(dev());
	uniform_int_distribution<int> distrit(-10000000, 10000000);
	for (int i = 0; i < size; ++i)
	{
		arr[i] = distrit(engine) % 4; // Генерация случайных положительных и отрицательных чисел
	}
}

void shell_sort(int size, vector<int>& arr) // Функция сортиовки Шелла
{
	for (int s = size / 2; s > 0; s /= 2) // Установка интервала
	{
		for (int i = s; i < size; ++i)
		{
			for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s)
			{
				int temp = arr[j];
				arr[j] = arr[j + s];
				arr[j + s] = temp;
			}
		}
	}
}

void print_vec(int size, vector<int>& arr) // Функция для вывода вектора
{
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main()
{
	cout << "The program realizes Shell sorting\n";
	int choice2, size = 0;
	string choice1;
	string retr = "Yes"; // Установка флага для работы программы 

	while (retr == "Yes")
	{
		cout << "Enter a size of a vector (size is an integer number and >= 2)\n";
		size = verificate(size); // Вызов функции для проверки валидности данных
		vector <int> arr(size);
		vector <int> arrcopy;
		cout << "Do you want to fill array by yourself\n";
		cout << "Print 'Yes' or 'No'\n";
		cin >> choice1;

		while (choice1 != "Yes" && choice1 != "No") // Запрос на перезапуск программы
		{
			cout << "You have not entered 'Yes' or 'No'\n";
			cout << "Print 'Yes' or 'No'\n";
			cin >> choice1;
		}

		if (choice1 == "Yes")
		{
			filling_arr_keyboard(size,arr);
		}
		else
		{
			cout << "Do you want to fill array of absolute random numbers or random little uniqe numbers\n";
			cout << "Print 1-absolue random numbers, 2-random little uniqe numbers\n";
			cin >> choice2;

			while (choice2 != 1 && choice2 != 2)
			{
				cout << "You have not enetred 1 or 2\n";
				cout << "Print 1-absolue random numbers, 2-random little uniqe numbers\n";
				cin >> choice2;
			}

			if (choice2 == 1)
			{
				filling_arr_auto(size, arr); // Вызов функции для заполнения 
			}
			else
			{
				filling_arr_auto_notuniq(size, arr);
			}
		}

		int size1;
		copy(arr.begin(), arr.end(), back_inserter(arrcopy));

		if (size > 20) // Если количество элементов вектора больше 20,то печатаь надо 20, а сортировать все
		{
			size1 = 20;

			cout << "Unsorted vector:\n";
			print_vec(size1, arr);

			auto start = chrono::steady_clock::now();
			shell_sort(size, arr);
			auto end = chrono::steady_clock::now();
			cout << "Sorted vector with Shell sorting:\n";
			print_vec(size1, arr);

			auto time1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			cout << "Time of Shell sorting is " << time1 << endl;
			auto start1 = chrono::steady_clock::now();
			sort(arrcopy.begin(), arrcopy.end());
			auto end1 = chrono::steady_clock::now();
			cout << "Sorted vector with standard methods:\n";
			print_vec(size1, arrcopy);
			auto time2 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();

			cout << "Time of standart sorting is " << time2 << endl;
			cout << "Shell sorting / standart sorting is " << (double)time1 / (double)time2 << endl;
		}
		else // Иначе сортируем и выводим всё
		{
			cout << "Unsorted vector:\n";
			print_vec(size, arr);
			auto start = chrono::high_resolution_clock::now();
			shell_sort(size, arr);
			auto end = chrono::high_resolution_clock::now();
			cout << "Sorted vector with Shell sorting:\n";
			print_vec(size, arr);

			auto time1 = (end - start).count();
			cout << "Time of Shell sorting is " << time1 << endl;
			auto start1 = chrono::high_resolution_clock::now();
			sort(arrcopy.begin(), arrcopy.end());
			auto end1 = chrono::high_resolution_clock::now();
			cout << "Sorted vector with standard methods:\n";
			print_vec(size, arrcopy);

			auto time2 = (end1 - start1).count();
			cout << "Time of standart sorting is " << time2 << endl;
			cout << "Shell sorting / standart sorting is " << (double)time1 / (double)time2 << endl;
		}

		cout << "Do you want to restart the program?\n";
		cout << "Print 'Yes' or 'No'\n";
		cin >> retr;
		verificate(retr);
	}
	cout << "The program is over\n"; // Сообщение о завершении программы
}