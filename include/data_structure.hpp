#pragma once
#include "node.hpp"
// Заголовочный файл с объявлением структуры данных

namespace itis {

  struct SplayTree {
   public:
    Node *root;

    static void zig(Node *x);
    static void zig_zig(Node *x);
    static void zig_zag(Node *x);
    void splay(Node *x);

    SplayTree();
    explicit SplayTree(Node *x);
    Node *find(int x);
    void insert(int x);
    void remove(int x);
    void Clear(Node *x);
    void split(Node *x);
    void prettyPrint(Node *x);
    ~SplayTree() ;
  };

}  // namespace itis