#include <fstream>

struct tree_node
{
	long long int val;
	tree_node* right;
	tree_node* left;
	tree_node(long long int v) : val(v), right(nullptr), left(nullptr) {};
};

class search_tree
{
private:
	void push(const int, tree_node*& cur_node); // функция для добавления узла в дерево
	void postord(tree_node*, std::ofstream&); // обратный обход
	void delete_tree(tree_node*&); //рекурсивное удаление дерева
	void remove_even(tree_node*); //рекурсивное удаление всех четных элементов
	void remove_node(tree_node*&); //удаление узла
	tree_node* node = nullptr;
public:
	void read_tree(std::ifstream&); // функция для чтения из файла
	void print(std::ofstream&); // функция для сохранение в файл
	void remove_evens(); // функция для удаления четных элементов
	void clear(); // функция для удаления дерева
};

void search_tree::read_tree(std::ifstream& inp)
{
	long long int v;
	while (inp >> v) push(v, node); // пока идет чтение из файла
}

void search_tree::push(const int v, tree_node*& cur_node) // текущей указатель на узел передается по ссылке для корректного добавления узлов
{
	if (!cur_node) // если спустились до еще несуществующего узла
	{
		cur_node = new tree_node(v); // создать узел
		return;
	}
	if (v > cur_node->val) // если текущее число больше корневого элемента записываем вправо
		push(v, cur_node->right); // переходим к правому поддереву
	else
		push(v, cur_node->left); // переходим к левому поддереву
}

void search_tree::clear()
{
	delete_tree(node); // вызов рекурсивной функции
}

void search_tree::delete_tree(tree_node*& node) // указатель на узел передается по ссылке, чтобы после выполнения функции корень стал nullptr
{
	if (!node) return;
	delete_tree(node->left);
	delete_tree(node->right);
	delete node;
	node = nullptr;
}

void search_tree::print(std::ofstream& outf)
{
	postord(node, outf); // вызов функции обхода дерева
}

void search_tree::postord(tree_node* cur_node, std::ofstream& outf) // обратный обход дерева
{
	if (!cur_node) return;
	postord(cur_node->left, outf); // обойти левое поддерево
	postord(cur_node->right, outf);// обойти правое поддерево
	outf << cur_node->val << ' '; // вывести элемент
}

void search_tree::remove_evens()
{
	if (!node) return;
	if (!(node->val & 1)) // если корень дерева четный
	{
		remove_node(node); // удаляем корень
		remove_evens(); // вызываем рекурсивно, чтобы исключить случай когда на место удаленного корня опять встанет четный элемент
	}
	else
		remove_even(node); // функция удаления всех четных элементов
}

void search_tree::remove_even(tree_node* node)
{
	if (!node) return;
	if (node->left && !(node->left->val & 1)) // если узел существует и четный
	{
		remove_node(node->left); // удаляем четный элемент
		remove_even(node); // вызываем рекурсивно, чтобы на его место опять не встал четный
		return;
	}
	if (node->right && !(node->right->val & 1)) // если узел существует и четный
	{
		remove_node(node->right); // удаляем четный элемент
		remove_even(node); // вызываем рекурсивно, чтобы на его место опять не встал четный
		return;
	}
	remove_even(node->left); // удаление четных из левого поддерева
	remove_even(node->right); // удаление четных из правого поддерева
}

void search_tree::remove_node(tree_node*& node) // удаляя узел, ставим на его место левого сына, а првавую ветвь удаляемого элемент переносим к самому правому элементу левого сына
{
	tree_node* temp = node;
	if (node->left && node->right) // если у корня есть оба потомка
	{
		tree_node* right_branch = node->left;
		while (right_branch->right) // пока не дошли до самого правого элемента левого сына
			right_branch = right_branch->right; // двигаемся вправо
		right_branch->right = node->right; // перенос правого поддерева удаляемого элемента к самому правому элементу левого сына
		node = node->left;
	}
	else if (node->right) // если нет левого элемента на место удаляемого встает правый сын
		node = node->right;
	else // если нет правого элемента на место удаляемого встает левый сын
		node = node->left;
	delete temp; // удаление четного элемента
}

int main()
{
	std::ifstream inp("input.txt"); // открытие входного файла
	std::ofstream outf("output.txt"); // открытие выходного файла
	search_tree t;
	t.read_tree(inp); // заполнение дерева поиска из файла
	t.remove_evens(); // удалние четных элементов
	t.print(outf); // сохранение результат в файл
	t.clear(); // удаление дерева
	inp.close(); // закрытие входного файла
	outf.close(); // закрытие выходного файла
}