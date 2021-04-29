#pragma once

namespace itis {
  struct Node {

    int number;
    Node *parent;
    Node *left;
    Node *right;

    explicit Node(int node_key) : number(node_key), parent(nullptr), left(nullptr), right(nullptr) {}
  };
}