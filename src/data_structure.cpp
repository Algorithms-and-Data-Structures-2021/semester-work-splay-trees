#include "data_structure.hpp"
#include <iostream>
#include <cstdlib>

// файл с определениями

namespace itis {

/* Right_Rotate(Y поворачивается вправо):
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
*/
inline splay* Right_Rotate(splay* k2)
{
	splay* k1 = k2->lchild;
	k2->lchild = k1->rchild;
	k1->rchild = k2;
	return k1;
}

/* Left_Rotate(Y поворачивается влево):
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 */
inline splay* Left_Rotate(splay* k2)
{
	splay* k1 = k2->rchild;
	k2->rchild = k1->lchild;
	k1->lchild = k2;
	return k1;
}

splay* Splay(int key, splay* root)
{
	if(root == nullptr) {
		return NULL;
}
	splay header;
	header.lchild = header.rchild = NULL;
	splay* LeftTreeMax = &header;
	splay* RightTreeMin = &header;

	while(true)
	{
		if(key < root->key)
		{
			if(root->lchild == nullptr) {
				break;
}
			if(key < root->lchild->key)
			{
				root = Right_Rotate(root);
				if(root->lchild == nullptr) {
					break;
}
			}

			RightTreeMin->lchild = root;
			RightTreeMin = RightTreeMin->lchild;
			root = root->lchild;
			RightTreeMin->lchild = NULL;
		}
		else if(key > root->key)
		{
			if(root->rchild == nullptr) {
				break;
}
			if(key > root->rchild->key)
			{
				root = Left_Rotate(root);
				if(root->rchild == nullptr) {
					break;
}
			}

			LeftTreeMax->rchild = root;
			LeftTreeMax = LeftTreeMax->rchild;
			root = root->rchild;
			LeftTreeMax->rchild = NULL;
		}
		else {
			break;
}
	}
	LeftTreeMax->rchild = root->lchild;
	RightTreeMin->lchild = root->rchild;
	root->lchild = header.rchild;
	root->rchild = header.lchild;

	return root;
}

splay* New_Node(KEY_TYPE key)
{
	auto* p_node = new splay;
  p_node->key = key;
	p_node->lchild = p_node->rchild = NULL;
	return p_node;
}

splay* Insert(KEY_TYPE key, splay* root)
{
  static splay* p_node;
  p_node = NULL;
  if(p_node == nullptr) {
		p_node = New_Node(key);
	} else {
		p_node->key = key;
}
	if(root == nullptr)
	{
		root = p_node;
		p_node = NULL;
		return root;
	}
	root = Splay(key, root);
	if(key < root->key)
	{
		p_node->lchild = root->lchild;
		p_node->rchild = root;
		root->lchild = NULL;
		root = p_node;
	}
	else if(key > root->key)
	{
		p_node->rchild = root->rchild;
		p_node->lchild = root;
		root->rchild = NULL;
		root = p_node;
	}
	else {
		return root;
}
	p_node = NULL;
	return root;
}


splay* Remove(KEY_TYPE key, splay* root)
{
	splay* temp;
	if(root == nullptr) {
		return NULL;
}
	root = Splay(key, root);
	if(key != root->key) {
		return root;
	}
  if (root->lchild != nullptr) {
    temp = root;
    root = Splay(key, root->lchild);
    root->rchild = temp->rchild;
  } else {
    temp = root;
    root = root->rchild;
  }
  free(temp);
  return root;

}

splay* Find(KEY_TYPE key, splay* root) {
	return Splay(key, root);
}

void InOrder(splay* root) {
	if(root != nullptr)
	{
		InOrder(root->lchild);
		std::cout<< "key: " <<root->key;
		if(root->lchild != nullptr) {
			std::cout<< " | left child: "<< root->lchild->key;
}
		if(root->rchild != nullptr) {
			std::cout << " | right child: " << root->rchild->key;
}
		std::cout<< "\n";
		InOrder(root->rchild);
	}
}

}  // namespace itis