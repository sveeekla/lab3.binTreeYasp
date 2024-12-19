module; 
//import NODE;

#include <iostream>
#include <fstream>
export module BinaryTree;
//export template<typename T>
//class NODE
//{
//public:
//	T* info;
//	NODE* left = nullptr, * right = nullptr;
//	NODE(T* info) :info(info) {}
//	~NODE()
//	{
//		info = left = right = nullptr;
//	}
//};
export template<typename T>
class BinaryTree
{
private:
	class NODE
	{
	public:
		T* info;
		NODE* left = nullptr, * right = nullptr;
		/*NODE(T* info) :info(info) {}*/
		NODE(const T& value) {
			info = new T(value); 
			left = nullptr;
			right = nullptr;
		}
		~NODE()
		{
			left = right = nullptr;
			info = NULL;
		}
	};
	NODE* root;
	void find_max_subtr(NODE*& r, NODE*& q);//вспомогашка для удаления 
	bool del_helper(NODE*& t, T data);
	void clear_helper(NODE*& t);
	void add_helper(NODE*& t, T data);// рекурсивно 
	int count_helper(NODE*& t);
	int height_tree_rec(NODE* node);
	void print(NODE* node,int level, std::ostream& stream = std::cout);
public:
	BinaryTree();
	void fill_from_file(std::ifstream& file);
	void print_to_console();
	void print_to_file(std::ofstream& file);
	bool find(T data);
	void add(T data);//обертка под рекурсию
	bool empty();
	void clear();
	bool del(T data);
	int count_nodes();
	int height();
	~BinaryTree();
};

template<typename T>
void BinaryTree<T>::find_max_subtr(NODE*& r, NODE*& q)
{
	if (r->right)
		find_max_subtr(r->right, q);
	else
	{
		*(q->info) = *(r->info);
		q = r;
		r = r->left;
	}
}
template<typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}
template<typename T>
void BinaryTree<T>::fill_from_file(std::ifstream& file)
{
	T x{};
	clear();
	while (file >> x)
		add(x);
}
template<typename T>
void BinaryTree<T>::print_to_console()
{
	if(root)
		print(root, 0);
}
template<typename T>
void BinaryTree<T>::print_to_file(std::ofstream& file)
{
	if (root)
		print(root, 0, file);
}
template<typename T>
void BinaryTree<T>::add_helper(NODE* &t, T data)
{
	if(!t)
	{
		t = new NODE(data);
	}
	else
		if (data < *(t->info))
			add_helper(t->left, data);
		else
			if (data > *(t->info))
				add_helper(t->right, data);
}

template<typename T>
int BinaryTree<T>::count_helper(NODE*& t)
{
	int result{};
	if (t)
		result = 1 + count_helper(t->left) + count_helper(t->right);
	return result;
}

template<typename T>
int BinaryTree<T>::height_tree_rec(NODE* node)
{
	if (node == nullptr) {
		return 0; // Высота пустого дерева равна 0
	}
	int leftHeight = height_tree_rec(node->left);
	int rightHeight = height_tree_rec(node->right);

	return std::max(leftHeight, rightHeight) + 1;
}

template<typename T>
void BinaryTree<T>::print(NODE* node,int level, std::ostream& stream)
{
	if (node)
	{
		print(node->right, level + 1, stream);
		if(&stream == &std::cout)
			for (int i = 1; i <= level; i++)
				stream << "   ";
		//std::cout.width(2);
		stream << *(node->info) << std::endl;
		print(node->left, level + 1, stream);
	}
}

template<typename T>
bool BinaryTree<T>::find(T data)
{
	NODE* t{ root };
	bool fl{ false };
	while (t && !fl)
	{
		if (data < *t->info)
			t = t->left;
		else
			if (data > *t->info)
				t = t->right;
			else
				fl = true;
	}
	return fl;
}

template<typename T>
void BinaryTree<T>::add(T data)
{
	add_helper(root, data);
}



template<typename T>
bool BinaryTree<T>::empty()
{
	return !root;
}

template<typename T>
void BinaryTree<T>::clear()
{
	if(root)
		clear_helper(root);
}

template<typename T>
void BinaryTree<T>::clear_helper(NODE* &t)
{
	if (t)
	{
		clear_helper(t->left);
		clear_helper(t->right);
		delete t;
		t = nullptr;
	}
}

template<typename T>
bool BinaryTree<T>::del(T data)
{
	if (root)
		return del_helper(root, data);
	else return false;
}

template<typename T>
int BinaryTree<T>::count_nodes()
{
	if (root)
		return count_helper(root);
	else return 0;
}

template<typename T>
int BinaryTree<T>::height()
{
	if (root)
		return height_tree_rec(root);
	else return 0;
}

template<typename T>
bool BinaryTree<T>::del_helper(NODE*& t, T data)
{
	bool result{false};
	if (t)
	{
		if (data < *(t->info))
			result = del_helper(t->left, data);
		else
			if (data > *(t->info))
				result = del_helper(t->right, data);
			else
			{
				result = true;
				NODE* q = t;
				if (!q->right)
					t = q->left;
				else
					if (!q->left)
						t = q->right;
					else
						find_max_subtr(q->left, q);
				delete q;
			}
	}
	return result;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	if (root)
		clear();
}
