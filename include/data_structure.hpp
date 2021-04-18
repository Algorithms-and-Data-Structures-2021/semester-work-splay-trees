#pragma once
#include "node.hpp"
// Заголовочный файл с объявлением структуры данных

namespace itis {

  struct SplayTree {
   public:
    Node *root;

    static void zig(Node *node);
    static void zig_zig(Node *node);
    static void zig_zag(Node *node);
    void splay(Node *x);

    SplayTree();
    explicit SplayTree(Node *node);
    Node *find(int index);
    void insert(int index);
    void remove(int index);
    void split(Node *node);
    Node *merge(SplayTree *s, SplayTree *t);
    void prettyPrint(Node *node);
    ~SplayTree();
  };

}  // namespace itis