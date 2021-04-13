#include <iostream>

#include "data_structure.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	itis::splay *root = NULL;
	itis::KEY_TYPE vector[] = {9,8,7,6,5,4,3,2,1,0};
//	int vector[] = {15};
	const int length = sizeof(vector)/sizeof(int);
	int i;
	for(i = 0; i< length;i++)
		root = Insert(vector[i], root);

	std::cout<<"\nInOrder: \n";
	InOrder(root);

	itis::KEY_TYPE input;
	char type;

	while(1)
	{
		std::cout<<"\nplease input type(S(s)/D(d)/I(i)) and key of the node you want to do with the tree(in a (type key) tuple): ";
		std::cin>>type>>input;
		switch(type)
		{
			case 'S':
			case 's':
				root = Find(input, root);
				std::cout<<"\nAfter Search "<<input<<std::endl;
				InOrder(root);
				break;
            case 'D':
			case 'd':
				root = Remove(input, root);
				std::cout<<"\nAfter Delete: "<<input<<std::endl;
				InOrder(root);
				break;
			case 'I':
			case 'i':
				root = Insert(input, root);
				std::cout<<"\nAfter Insert: "<<input<<std::endl;
				InOrder(root);
				break;
			default:
				std::cout<<"\nInvalid type! type could only be s/S, i/I, d/D.\n";
		}
	}

}