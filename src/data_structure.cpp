#include "data_structure.hpp"
#include <iostream>

namespace itis {

  SplayTree::SplayTree() {
    this->root = nullptr;
  }

  void Clear(Node *node) {
    if (node->left_child != nullptr || node->right_child != nullptr) {
      if (node->left_child != nullptr && node->right_child == nullptr) {
        Clear(node->left_child);
        delete node;
      } else if (node->left_child == nullptr && node->right_child != nullptr) {
        Clear(node->right_child);
        delete node;
      } else {
        Clear(node->left_child);
      }
    } else {
      delete node;
    }
  }

  SplayTree::SplayTree(Node *tree_root) {
    this->root = tree_root;
  }

  SplayTree::~SplayTree() {
    Node *curr = this->root;
    Clear(curr);
  }

  void SplayTree::zig(Node *node) {
    Node *parent_node = node->parent;

    if (parent_node->left_child == node) {
      Node *A = node->right_child;

      node->parent = nullptr;
      node->right_child = parent_node;

      parent_node->parent = node;
      parent_node->left_child = A;

      if (A != nullptr) {
        A->parent = parent_node;
      }
    } else {
      Node *A = node->left_child;

      node->parent = nullptr;
      node->left_child = parent_node;

      parent_node->parent = node;
      parent_node->right_child = A;

      if (A != nullptr) {
        A->parent = parent_node;
      }
    }
  }

  void SplayTree::zig_zig(Node *node) {
    Node *parent_node = node->parent;
    Node *grandparent_node = parent_node->parent;

    if (parent_node->left_child == node) {
      Node *A = node->right_child;
      Node *B = parent_node->right_child;

      node->parent = grandparent_node->parent;
      node->right_child = parent_node;

      parent_node->parent = node;
      parent_node->left_child = A;
      parent_node->right_child = grandparent_node;

      grandparent_node->parent = parent_node;
      grandparent_node->left_child = B;

      if (node->parent != nullptr) {
        if (node->parent->left_child == grandparent_node) {
          node->parent->left_child = node;
        } else {
          node->parent->right_child = node;
        }
      }
      if (A != nullptr) {
        A->parent = parent_node;
      }
      if (B != nullptr) {
        B->parent = grandparent_node;
      }
    } else {
      Node *A = parent_node->left_child;
      Node *B = node->left_child;

      node->parent = grandparent_node->parent;
      node->left_child = parent_node;

      parent_node->parent = node;
      parent_node->left_child = grandparent_node;
      parent_node->right_child = B;

      grandparent_node->parent = parent_node;
      grandparent_node->right_child = A;

      if (node->parent != nullptr) {
        if (node->parent->left_child == grandparent_node) {
          node->parent->left_child = node;
        } else {
          node->parent->right_child = node;
        }
      }

      if (A != nullptr) {
        A->parent = grandparent_node;
      }

      if (B != nullptr) {
        B->parent = parent_node;
      }
    }
  }

  void SplayTree::zig_zag(Node *x) {
    Node *parent_node = x->parent;
    Node *grandparent_node = parent_node->parent;

    if (parent_node->right_child == x) {
      Node *A = x->left_child;
      Node *B = x->right_child;

      x->parent = grandparent_node->parent;
      x->left_child = parent_node;
      x->right_child = grandparent_node;

      parent_node->parent = x;
      parent_node->right_child = A;

      grandparent_node->parent = x;
      grandparent_node->left_child = B;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }

      if (A != nullptr) {
        A->parent = parent_node;
      }

      if (B != nullptr) {
        B->parent = grandparent_node;
      }
    } else {
      Node *A = x->left_child;
      Node *B = x->right_child;

      x->parent = grandparent_node->parent;
      x->left_child = grandparent_node;
      x->right_child = parent_node;

      parent_node->parent = x;
      parent_node->left_child = B;

      grandparent_node->parent = x;
      grandparent_node->right_child = A;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }

      if (A != nullptr) {
        A->parent = grandparent_node;
      }

      if (B != nullptr) {
        B->parent = parent_node;
      }
    }
  }

  void SplayTree::splay(Node *x) {
    while (x->parent != nullptr) {
      Node *parent_node = x->parent;
      Node *grandparent_node = parent_node->parent;
      if (grandparent_node == nullptr) {
        zig(x);
      }
      else if (grandparent_node->left_child == parent_node && parent_node->left_child == x) {
        zig_zig(x);
      }
      else if (grandparent_node->right_child == parent_node && parent_node->right_child == x) {
        zig_zig(x);
      }
      else {
        zig_zag(x);
      }
    }
    this->root = x;
  }

  Node *tree_max_key(Node *root) {
    Node *curr = root;
    while (curr->right_child != nullptr) {
      curr = curr->right_child;
    }
    return curr;
  }

  Node *tree_min_key(Node *subRoot) {
    Node *curr = subRoot;
    while (curr->left_child != nullptr) {
      curr = curr->left_child;
    }
    return curr;
  }

  void SplayTree::remove(int x) {
    Node *del = find(x);
    if (del == nullptr) {
      return;
    }
    Node *L = del->left_child;
    if (L == nullptr) {
      root = del->right_child;
      root->parent = nullptr;
      delete del;
      return;
    }
    while (L->right_child != nullptr) {
      L = L->right_child;
    }
    if (del->right_child != nullptr) {
      L->right_child = del->right_child;
      del->right_child->parent = L;
    }
    root = del->left_child;
    root->parent = nullptr;
    delete del;
  }

  void SplayTree::insert(int x) {
    if (root == nullptr) {
      root = new Node(x);
      return;
    }
    Node *curr = this->root;
    while (curr != nullptr) {
      if (x < curr->data) {
        if (curr->left_child == nullptr) {
          Node *new_node = new Node(x);
          curr->left_child = new_node;
          new_node->parent = curr;
          splay(new_node);
          this->root = new_node;
          return;
        } else {
          curr = curr->left_child;
        }
      } else if (x >= curr->data) {
        if (curr->right_child == nullptr) {
          Node *new_node = new Node(x);
          curr->right_child = new_node;
          new_node->parent = curr;
          splay(new_node);
          this->root = new_node;
          return;
        } else {
          curr = curr->right_child;
        }
      } else {
        splay(curr);
        return;
      }
    }
  }

  Node *SplayTree::find(int x) {
    Node *ret = nullptr;
    Node *curr = this->root;
    Node *prev = nullptr;
    while (curr != nullptr) {
      prev = curr;
      if (x < curr->data) {
        curr = curr->left_child;
      } else if (x > curr->data) {
        curr = curr->right_child;
      } else {
        ret = curr;
        break;
      }
    }
    if (ret != nullptr) {
      splay(ret);
    } else if (prev != nullptr) {
      splay(prev);
    }
    return ret;
  }

  Node *SplayTree::merge(SplayTree *s, SplayTree *t) {
    Node *x = tree_max_key(s->root);
    splay(x);
    x->right_child = t->root;
    t->root->parent = x;
    return x;
  }

  void SplayTree::split(Node *x) {
    splay(x);
    Node *s = nullptr;
    Node *t = nullptr;
    if (x->right_child) {
      t = x->right_child;
      t->parent = nullptr;
    } else {
      t = nullptr;
    }
    s = x;
    s->right_child = nullptr;
    x = nullptr;
  }

  void SplayTree::prettyPrint(Node *node) {
    if (node->left_child != nullptr && node->right_child != nullptr) {
      std::cout << node->data << ": " << node->left_child->data << ", " << node->right_child->data << std::endl;
    } else if (node->left_child != nullptr) {
      std::cout << node->data << ": " << node->left_child->data << std::endl;
    } else if (node->right_child != nullptr) {
      std::cout << node->data << ": " << node->right_child->data << std::endl;
    } else {
      std::cout << node->data << ": There are not any child" << std::endl;
    }
    if (node->left_child != nullptr && node->right_child != nullptr) {
      prettyPrint(node->left_child);
      prettyPrint(node->right_child);
    } else if (node->left_child != nullptr) {
      prettyPrint(node->left_child);
    } else if (node->right_child != nullptr) {
      prettyPrint(node->right_child);
    }
  }

}  // namespace itis