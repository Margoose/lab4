#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <vector>
#include <cstdlib>

class tree
{
	int size, maxlevel;
	struct derevo;
	derevo *root;
	derevo *leaf(derevo *);
	derevo *findlevel(int, int *, derevo *);
	derevo *m_print(int &, derevo *, int &);
	derevo *_find(const int &, int &, derevo *d);
public:
	tree(int);
	~tree();
	void add(int, int, int);
	void print();
	int find(const int &);
};

struct tree::derevo
{
	int data;
	int level;
	derevo *parent;
	std::vector<derevo *> child;
};

tree::tree(int data)
{
	root = new derevo;
	root->data = data;
	root->level = 0;
	root->parent = nullptr;
}

tree::~tree()
{
	derevo *n;
	while (!root->child.empty())
	{
		n = leaf(root);
		n->parent->child.pop_back();
		delete n;
	}
	delete root;
}

tree::derevo *tree::findlevel(int level, int *number, derevo *node)
{
	if (node->level == level - 1)
		return node;
	else
	{
		if (node->child.empty())
			return nullptr;

		for (auto it = node->child.begin(); it != node->child.end(); ++it)
		{
			derevo *buff = findlevel(level, number, *it);
			if (buff != nullptr)
			{
				if ((*it)->level == level - 1)
					(*number)--;
				if (*number == 0)
					return buff;
			}
		}	
	}
}

void tree::add(int level, int number, int data)
{
	int num(number);
	derevo *d = findlevel(level, &num, root);
	if (!d)
	{
		std::cout<<"\n\nWrong number!\n";
		system("pause");
		exit(1);
	}
	derevo *n = new derevo;
	n->data = data;
	n->level = level;
	n->parent = d;
	d->child.push_back(n);
	if (level>maxlevel) maxlevel = level;
}

tree::derevo *tree::leaf(derevo *d)
{
	if (d->child.empty())
		return d;
	else
	{
		for (auto it = d->child.rbegin(); it != d->child.rend(); ++it)
		{
			derevo *buff = leaf(*it);
			if (buff != nullptr)
				return buff;
		}
	}
}

int tree::find(const int &k)
{
	int l = maxlevel + 1;
	auto n = _find(k, l, root);
	if (l > maxlevel) return -1;
	return l;
}

tree::derevo *tree::_find(const int &k, int &l, derevo *d)
{
	if (d->data == k && l>d->level) l = d->level;
	if (d->child.empty() && d == leaf (root)) return d;

	if (d->child.empty())
		return nullptr;

	for (auto it = d->child.begin(); it != d->child.end(); ++it)
		derevo *buff = _find(k, l, *it);
}

tree::derevo *tree::m_print(int &k, derevo *d, int &j)
{
	if (d->level == k)
	{
		std::cout<<d->data<<"|";
		if (k !=0 && *--d->parent->child.end() == d) std::cout<<"|";
		j++;
		return d;
	}
	else
	{
		if (d->child.empty())
			return nullptr;

		std::cout<<"|";
		for (auto it = d->child.begin(); it != d->child.end(); ++it)
			derevo *buff = m_print(k, *it, j);
	}
}

void tree::print()
{
	derevo *buff;
	int k(0), j(1);
	while (k <= maxlevel)
	{
		std::cout<<std::setw(30-2*j)<<"";
		buff = m_print(k, root, j);
		std::cout<<"\n";
		k++;
	}
}
#endif