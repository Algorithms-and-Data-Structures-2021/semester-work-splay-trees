#pragma once

namespace itis {
  struct Node {
   public:
    int data;
    Node *parent;
    Node *left_child;
    Node *right_child;

    explicit Node(int node_key) : data(node_key), parent(nullptr), left_child(nullptr), right_child(nullptr) {
    }
  };
}  // namespace itis