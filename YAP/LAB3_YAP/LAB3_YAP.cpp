#include<fstream>

struct node
{
	long double v;
	node* next;
	node(long double val = 0, node* nx = nullptr) :v(val), next(nx) {};
};

class cycle_list
{
private:
	node* head;
public:
	cycle_list(node* h = nullptr) { head = h; }; // конструктор
	void read_file(std::ifstream&);
	void print_list(std::ofstream&);
	void push_back(const long double);
	long long get_size();
	friend void swap(cycle_list& l, node* first, node* second);
	friend node** make_arr(const cycle_list& l, const long long total);
	friend void rebuild_cyclelist(cycle_list& l, node** arr, const long long n);
	friend void selection_sort(cycle_list& l);
	~cycle_list() // деструктор
	{
		if (head) {
			node* cur = head;
			while (cur->next != head) {
				node* tmp = cur->next;
				delete cur;
				cur = tmp;
			}
			delete cur;
		}
	}
};

void cycle_list::push_back(const long double v)
{
	if (head) // если список существует
	{
		node* cur = head;
		while (cur->next != head) // пока не дошли до конца
			cur = cur->next;
		cur->next = new node(v, head); // создание нового элемента
	}
	else // если добавление первого элемента
	{
		head = new node(v); // создать голову
		head->next = head;
	}
}

void cycle_list::read_file(std::ifstream& inp) // метод для чтения списка из файла
{
	long double v;
	while (inp >> v)
	{
		this->push_back(v); // добавление в конец
	}
}

void cycle_list::print_list(std::ofstream& outf) // метод для вывода списка в файл
{
	if (head) // если список существует
	{
		node* cur = head;
		do
		{
			outf << cur->v << ' '; // вывод через пробел
			cur = cur->next;
		} while (cur != head);
	}
}

long long cycle_list::get_size() // метод для получения размера
{
	long long int total = 0;
	if (head) // если список существует
	{
		node* cur = head;
		do
		{
			++total; // увеличение счетчика
			cur = cur->next;
		} while (cur != head); // пока не дошли до конца
	}
	return total;
}

void swap(cycle_list& l, node* first, node* second) // обмен данными как обмен указателями на соответствующие элементы списка
{
	if ((!first || !second) || (first == second)) // если какой то из элементов nullptr или это один и тот же элемент
		return; // обмен не требуется
	node* cur = l.head;
	node* pfirst = nullptr, * psecond = nullptr, * temp; // переменные для хранение элементов, которые предсшествуют изменяемым
	if (first->next->next == first) // если всего два элемента
	{
		l.head = second; // достаточно изменить голову списка, так как менять поле next не требуется
		return;
	}
	if (first->next == second) // если смена соседних элементов
	{
		while (cur->next != first)
			cur = cur->next;
		pfirst = cur; // элемент, предшествующий первому
		first->next = second->next;// изменение поле next у первого элемента
		second->next = first; // изменение поле next у второго элемента
		pfirst->next = second; // изменение поле next у предшествующего первому элемента
		return;
	}
	else if (second->next == first) // если смена соседних элементов
	{
		while (cur->next != second)
			cur = cur->next;
		psecond = cur; // элемент, предшествующий первому
		second->next = first->next; // изменение поле next у первого элемента
		first->next = second; // изменение поле next у второго элемента
		psecond->next = first; // изменение поле next у предшествующего первому элемента
		return;
	}
	do
	{
		if (cur->next == first) // поиск элемента, который предшествует первому
			pfirst = cur;
		if (cur->next == second) //поиск элемента, который предшествует второму
			psecond = cur;
		cur = cur->next;
	} while (cur != l.head && (pfirst == nullptr || psecond == nullptr)); // пока не дошли до конца списка или оба элемента не найдены
	if (pfirst && psecond) // если оба элементы найдены
	{
		pfirst->next = second; // изменение поле next у предшествующего первому элемента
		psecond->next = first; // изменение поле next у предшествующего второму элемента
		temp = second->next; // элемент, идущий после второго элемента сохраняется во временную переменную
		second->next = first->next; // изменение поле next у второго элемента 
		first->next = temp; // изменение поле next у первого элемента
	}
	if (first == l.head) // если меняли голову
		l.head = second; // присвоить голове новое значение
	else if (second == l.head)// если меняли голову
		l.head = first; // присвоить голове новое значение
}

node** make_arr(const cycle_list& l, const long long total) // создание массива указателей на элементы списка
{
	node** arr = new node * [total];
	node* cur = l.head;
	long long int i = 0; // начальный индекс массива
	do
	{
		arr[i] = cur;
		cur = cur->next;
		++i;
	} while (cur != l.head); // пока не дошли до конца
	return arr;
}

void heapify(node** arr, const long long int n, const long long int i) // преобразование в кучу
{
	long long int larg_ind = i; // потенциальный корень
	long long int left = 2 * i + 1; // левый элемент
	long long int right = 2 * i + 2; // правый элемент
	if (left < n && arr[left]->v > arr[larg_ind]->v) // если левый элемент больше корня
		larg_ind = left;
	if (right < n && arr[right]->v > arr[larg_ind]->v) // если правый элемент больше корня
		larg_ind = right;
	if (larg_ind != i) // если больший элемент не корень
	{
		std::swap(arr[i], arr[larg_ind]); // смена местами указаетелей на соответствующие элементы списка(меняем местами потенциальный корень и настоящий)
		heapify(arr, n, larg_ind); // рекурсия для получившегося массива
	}
}

void rebuild_cyclelist(cycle_list& l, node** arr, const long long n) // построение списка по массиву
{
	l.head = arr[0];
	node* cur = l.head;
	long long int i = 1; // начинаем с 1 т.к 0 уже присвоен голове
	do
	{
		cur->next = arr[i];
		cur = cur->next; // продвижение по списку
		++i; // увеличение индекса
	} while (i != n);
	cur->next = l.head;
}

void heap_sort(cycle_list& l, const long long int n) // сортировка кучей
{
	node** list_arr = make_arr(l, n); // создание массива из указателей на элементы списка
	for (long long i = n / 2 - 1; i >= 0; --i) // создание кучи
		heapify(list_arr, n, i);
	for (long long i = n - 1; i >= 0; --i)
	{
		std::swap(list_arr[0], list_arr[i]); // смена местами указаетелей на соответствующие элементы списка(перемещаем корень в конец)
		heapify(list_arr, i, 0); // создание кучи из оставшегося массива
	}
	rebuild_cyclelist(l, list_arr, n); // перестройка списка 
	delete[] list_arr;
}

void selection_sort(cycle_list& l) // сортировка выбором
{
	if (l.head) // если список существует
	{
		node* pi = l.head, * pj = pi->next, * nx, * min;
		do
		{
			nx = pi->next; // элемент который следует за сортируемым
			min = pi; // минимальный элемент
			pj = pi->next;
			do
			{
				if (min->v > pj->v) // если текущий минимум больше очередного значения
					min = pj; // минимум обновляется
				pj = pj->next; // переход к следующему элементу
			} while (pj != l.head); // пока не дошли до конца
			if (min->v != pi->v) // если текущей элемент оказался не минимальным
				swap(l, pi, min); // поменять его с минимальным
			pi = nx; // переходим к следующему элементу
		} while (pi->next != l.head); // пока не дошли до конца
	}
}

int main()
{
	std::ifstream inp("input.txt"); // открытие входного файла
	std::ofstream ofs("output.txt"); // открытие выходного файла
	bool choice; // переменная, отвечающая за выбор сортировки
	inp >> choice;
	cycle_list l; // создание списка
	l.read_file(inp); // заполнение списка из файла
	long long elem_num = l.get_size(); // количество элементов в списке
	if (choice)
		heap_sort(l, elem_num); // сортировка кучей
	else
		selection_sort(l); // сортировка выбором
	ofs << elem_num << ' '; // вывод количества элементов в файл
	l.print_list(ofs); // вывод отсортированного массива
	inp.close(); // закрытие входного файла
	ofs.close(); // закрытие выходного файла
	return 0;
}