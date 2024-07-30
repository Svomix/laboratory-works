#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
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

void filling_arr(int size, vector<int>& arr) //  Функция для заполнение вектора случайными числами
{
	srand(time(NULL));
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() * pow((-1), rand()); // Генерация случайных положительных и отрицательных чисел
	}
}



void shell_sort(int size, vector<int>& arr) // Функция сортиовки Шелла
{
	for (int s = size / 2; s > 0; s /= 2) // Установка интервала
	{
		for (int i = s; i < size / 2; ++i)
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
	int size = 0;
	string retr = "Yes"; // Установка флага для работы программы 
	while (retr == "Yes") 
	{
		cout << "Enter a size of a vector (size is an integer number and >= 2)\n";
		size = verificate(size); // Вызов функции для проверки валидности данных
		vector <int> arr(size); // Создание вектора
		filling_arr(size,arr); // Вызов функции для заполнения 
		int size1;
		if (size > 20) // Если количество элементов вектора больше 20,то печатаь надо 20, а сортировать все
		{
			size1 = 20;
			cout << "Unsorted vector:\n";
			print_vec(size1, arr);
			shell_sort(size, arr);
			cout << "Sorted vector:\n";
			print_vec(size1, arr);
		} 
		else // Иначе сортируем и выводим всё
		{
			cout << "Unsorted vector:\n";
			print_vec(size, arr);
			shell_sort(size, arr);
			cout << "Sorted vector:\n";
			print_vec(size, arr);
		}
		cout << "Do you want to restart the program?\n";
		cout << "Print 'Yes' or 'No'\n";
		cin >> retr;
		while (retr != "Yes" && retr != "No") // Запрос на перезапуск программы
		{
			cout << "You have not entered 'Yes' or 'No\n'";
			cout << "Print 'Yes' or 'No'\n";
			cin >> retr;
		}
	}
	cout << "The program is over\n"; // Сообщение о завершении программы
}