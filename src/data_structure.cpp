#include "data_structure.hpp"
#include <iostream>

namespace itis {

  SplayTree::SplayTree() : way(nullptr) {}
  SplayTree::SplayTree(Node *tree_root) : way(tree_root) {}

  // Диструктор. В нём дерево удаляется путём удаления начального узла
  SplayTree::~SplayTree() {
    Node *curr = this->way;
    Clear(curr);
  }

  void SplayTree::splay(Node *x) {
    while (x->parent != nullptr) {
      Node *parent_node = x->parent;
      Node *grandparent_node = parent_node->parent;
      if (grandparent_node == nullptr) {
        zig(x);
      } else if (grandparent_node->left == parent_node && parent_node->left == x) {
        zig_zig(x);
      } else if (grandparent_node->right == parent_node && parent_node->right == x) {
        zig_zig(x);
      } else {
        zig_zag(x);
      }
    }
    this->way = x;
  }

  void SplayTree::zig(Node *vertex) {
    Node *parent = vertex->parent;

    if (parent->left == vertex) {

      Node *turn = vertex->right;
      vertex->parent = nullptr;
      vertex->right = parent;
      parent->parent = vertex;
      parent->left = turn;
      if (turn != nullptr)
        turn->parent = parent;

    } else {

      Node *vertexA = vertex->left;
      vertex->parent = nullptr;
      vertex->left = parent;
      parent->parent = vertex;
      parent->right = vertexA;

      if (vertexA != nullptr) {
        vertexA->parent = parent;
      }
    }
  }

  void SplayTree::zig_zig(Node *vertex) {
    Node *parent = vertex->parent;
    Node *grandparent = parent->parent;

    if (parent->left == vertex) {
      Node *vertexA = vertex->right;
      Node *vertexB = parent->right;
      vertex->parent = grandparent->parent;
      vertex->right = parent;
      parent->parent = vertex;
      parent->left = vertexA;
      parent->right = grandparent;
      grandparent->parent = parent;
      grandparent->left = vertexB;

      if (vertex->parent != nullptr) {
        if (vertex->parent->left == grandparent) {
          vertex->parent->left = vertex;
        } else {
          vertex->parent->right = vertex;
        }
      }
      if (vertexA != nullptr) {
        vertexA->parent = parent;
      }
      if (vertexB != nullptr) {
        vertexB->parent = grandparent;
      }

    } else {
      Node *vertexA = parent->left;
      Node *vertexB = vertex->left;
      vertex->parent = grandparent->parent;
      vertex->left = parent;
      parent->parent = vertex;
      parent->left = grandparent;
      parent->right = vertexB;
      grandparent->parent = parent;
      grandparent->right = vertexA;

      if (vertex->parent != nullptr) {
        if (vertex->parent->left == grandparent) {
          vertex->parent->left = vertex;
        } else {
          vertex->parent->right = vertex;
        }
      }
      if (vertexA != nullptr) {
        vertexA->parent = grandparent;
      }
      if (vertexB != nullptr) {
        vertexB->parent = parent;
      }
    }
  }

  void SplayTree::zig_zag(Node *vertex) {
    Node *parent = vertex->parent;
    Node *grandparent = parent->parent;

    if (parent->right == vertex) {
      Node *vertexA = vertex->left;
      Node *vertexB = vertex->right;

      vertex->parent = grandparent->parent;
      vertex->left = parent;
      vertex->right = grandparent;

      parent->parent = vertex;
      parent->right = vertexA;

      grandparent->parent = vertex;
      grandparent->left = vertexA;

      if (vertex->parent != nullptr) {
        if (vertex->parent->left == grandparent) {
          vertex->parent->left = vertex;
        } else {
          vertex->parent->right = vertex;
        }
      }

      if (vertexA != nullptr) {
        vertexA->parent = parent;
      }

      if (vertexB != nullptr) {
        vertexB->parent = grandparent;
      }

    } else {
      Node *vertexA = vertex->left;
      Node *vertexB = vertex->right;

      vertex->parent = grandparent->parent;
      vertex->left = grandparent;
      vertex->right = parent;

      parent->parent = vertex;
      parent->left = vertexB;

      grandparent->parent = vertex;
      grandparent->right = vertexA;

      if (vertex->parent != nullptr) {
        if (vertex->parent->left == grandparent) {
          vertex->parent->left = vertex;
        } else {
          vertex->parent->right = vertex;
        }
      }

      if (vertexA != nullptr) {
        vertexA->parent = grandparent;
      }

      if (vertexB != nullptr) {
        vertexA->parent = parent;
      }
    }
  }

  /* Метод find. В нём производится поиск элемента по индексу.
       - Если не существует такого индекса, то возвращает null. Если же нет, то поиск продолжаетя до тех пор,
         пока не найдётся данный элемент по номеру */
  Node *SplayTree::find(int index) {
    Node *returning = nullptr;
    Node *current = this->way;
    Node *previous = nullptr;
    while (current != nullptr) {
      previous = current;
      if (index < current->number) {
        current = current->left;
      } else if (index > current->number) {
        current = current->right;
      } else {
        returning = current;
        break;
      }
    }
    if (returning != nullptr) {
      splay(returning);
    } else if (previous != nullptr) {
      splay(previous);
    }
    return returning;
  }

  /* Метод insert. Действует по следующему алгоритму:
       1) Если у дерева нет корня, корнем становится узел с этим числом
       2) В противном случае сначала ищется место в дереве по правилу "Родитель больше нового узла, а потомок - меньше" */
  void SplayTree::insert(int index) {
    if (way == nullptr) {
      way = new Node(index);
      return;
    }
    Node *current = this->way;
    while (current != nullptr) {
      if (index < current->number) {
        if (current->left == nullptr) {
          Node *new_node = new Node(index);
          current->left = new_node;
          new_node->parent = current;
          splay(new_node);
          this->way = new_node;
          return;
        } else {
          current = current->left;
        }
      } else if (index >= current->number) {
        if (current->right == nullptr) {
          Node *new_node = new Node(index);
          current->right = new_node;
          new_node->parent = current;
          splay(new_node);
          this->way = new_node;
          return;
        } else {
          current = current->right;
        }
      } else {
        splay(current);
        return;
      }
    }
  }

  /* Метод remove. Действует по следующему алгоритму:
       1) Если не существует узла по индексу, то алгоритм прекращает работу
       2) Если узел существует, то алгоритм делает так, что потомки удаляемого узла становятся потомками родителей удаляемого узла */
  void SplayTree::remove(int index) {
    Node *deleting_node = find(index);
    if (deleting_node != nullptr) {
      Node *vertexL = deleting_node->left;
      if (vertexL == nullptr) {
        way = deleting_node->right;
        way->parent = nullptr;
        delete deleting_node;
        return;
      }
      while (vertexL->right != nullptr) {
        vertexL = vertexL->right;
      }
      if (deleting_node->right != nullptr) {
        vertexL->right = deleting_node->right;
        deleting_node->right->parent = vertexL;
      }
      way = deleting_node->left;
      way->parent = nullptr;
      delete deleting_node;
    }
  }

  /* В методе Clear происходит следующее:
         1) Берётся узел о индексу
         2) Осуществляется проверка: если у этого узла нет дочерних узлов, то он удаляется без дополнительных операций
            В противном случае запускается рекурсия по удалению сначала ребёнка слева (если есть), а потом справа (если есть) */
  void SplayTree::Clear(Node *index) {
    if (index->left != nullptr || index->right != nullptr) {
      if (index->left != nullptr && index->right == nullptr) {
        Clear(index->left);
        delete index;
      } else {
        Clear(index->left);
      }
      if (index->left == nullptr && index->right != nullptr) {
        Clear(index->right);
        delete index;
      }
    } else {
      delete index;
    }
  }

}  // namespace itis