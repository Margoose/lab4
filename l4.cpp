#include "stdafx.h"
#include <iostream>
#include "Tree.h"

void main()
{
	int n(5), leaf(2), i(1), j(0), data(0), number(0);
	int a[] = {0,1,1,1,3,4,4,5,5,5};
	int b[] = {0,1,3,4,5,9};
	tree *t = new tree(data);
	data++;
	while (i <= n)
	{
		leaf = b[i];
		std::cout<<"\nLeaf(Level_"<<i<<"): ";
		//std::cin>>leaf;
		std::cout<<leaf<<"\n";
		while (j < leaf)
		{
			number = a[j+1];
			std::cout<<"\nNumber(Level_"<<i<<"): ";
			//std::cin>>number;
			std::cout<<number<<"\nData(Level_"<<i<<"): ";
			//std::cin>>data;
			std::cout<<data;
 			t->add(i, number, data);
			j++;
			data++;
		}
		std::cout<<"\n";
		j = 0;
		i++;
	}
	t->print();
	std::cout<<"\nWays to (10): "<<t->find(10)<<std::endl;
	delete t;
	system("pause");
}

// В непустом дереве Т найти длину пути (число ветвей) от корня до ближайшей вершины с элементом Е. Если элемент Е не входит в Т, то за ответ принять "-1". Дерево ЛЮБОЕ, не бинарное.