#pragma once

// Заголовочный файл с объявлением структуры данных

namespace itis {

  typedef int KEY_TYPE;

  typedef struct splay{

  	  KEY_TYPE key;
  	  struct splay* lchild;
	  struct splay* rchild;

  } splay;

  splay* New_Node(KEY_TYPE key);

  inline splay* Right_Rotate(splay* k2);

  inline splay* Left_Rotate(splay* k2);

  splay* Splay(int key, splay* root);//+

  splay* Insert(KEY_TYPE key, splay* root);//+

  splay* Remove(KEY_TYPE key, splay* root);//+

  splay* Find(KEY_TYPE key, splay* root);//+

  void InOrder(splay* root);

  //отсутствуют методы merge, split
}