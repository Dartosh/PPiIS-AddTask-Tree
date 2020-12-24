#include <iostream>
#include "list.h"
#include "bin_tree.h"

using namespace std;

int main()
{
	tree<int> A;
	A.add_node(1, 2);
	A.add_node(1, 3);
	A.add_node(2, 5);

	node<int>* B = A.find_node(1);

	A.del_node(B);

	return 0;
}