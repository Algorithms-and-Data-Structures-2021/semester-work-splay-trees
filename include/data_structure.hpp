#pragma once
#include "node.hpp"
// Заголовочный файл с объявлением структуры данных

namespace itis {

  struct SplayTree {
   public:
    Node *way;

    static void zig(Node *vertex);
    static void zig_zig(Node *vertex);
    static void zig_zag(Node *vertex);
    void splay(Node *vertex);

    SplayTree();
    explicit SplayTree(Node *structure_way);
    Node *find(int index);
    void insert(int index);
    void remove(int index);
    void Clear(Node *index);
    ~SplayTree();
  };

}