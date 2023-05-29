/**
Copyright 2023 darrpama@student.21-school.ru

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#ifndef CPP2_S21_CONTAINERS_S21_TREE_H
#define CPP2_S21_CONTAINERS_S21_TREE_H

#include <cstddef>

namespace s21 {
// Структура узла дерева
template <class T1, class T2>
class Node {
  T1 key_;
  T2 data_;
  Node<T1, T2> *left_;
  Node<T1, T2> *right_;

  Node(const T1 key = T1{}, const T2 data = T2{}, Node<T1, T2> *left_ = nullptr,
       Node<T1, T2> *right_ = nullptr)
      : key_{key}, data_{data}, left_{left_}, right_{right_} {}
};

// Структура дерева
template <class T1, class T2>
class BSTree {
  // private attributes
 private:
  Node<T1, T2> *root = nullptr;

  // public methods
 public:
  // Добавление пары (key, value) в дерево
  void insert(T1 key, T2 data);
  // Исключение из дерева значения по ключу
  void remove(T1 key);
  // Получение значения по ключу key
  // T2 find(T1 key);
  // private methods
 private:
  void insert(Node<T1, T2> *&n, T1 key, T2 data);
  // Node<T1, T2> *find(T1 key, Node<T1, T2> *root);
  Node<T1, T2> *successor(Node<T1, T2> *n);
  void remove(Node<T1, T2> *&n, T1 key);
};

// private
template <class T1, class T2>
void BSTree<T1, T2>::insert(Node<T1, T2> *&node, T1 key, T2 data) {
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node<T1, T2>(key, data);
    } else {
      insert(node->left_, key, data);
    }
  } else if (key >= node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new Node<T1, T2>(key, data);
    } else {
      insert(node->left_, key, data);
    }
  }
}

// public
template <class T1, class T2>
void BSTree<T1, T2>::insert(T1 key, T2 data) {
  insert(root, key, data);
}

// private
template <class T1, class T2>
Node<T1, T2> *BSTree<T1, T2>::successor(Node<T1, T2> *n) {
  Node<T1, T2> *r = n->right;
  while (r->left != nullptr) r = r->left;
  return r;
}

// private
template <class T1, class T2>
void BSTree<T1, T2>::remove(Node<T1, T2> *&n, T1 key) {
  if (n == nullptr) {
    return;
  }
  if (key == n->key_) {
    if (n->left_ == nullptr || n->right_ == nullptr) {
      Node<T1, T2> *child = (n->left != nullptr ? n->left_ : n->right_);
      delete n;
      n = child;
    } else {
      Node<T1, T2> *success = successor(n);
      n->key = success->key_;
      n->data = success->data_;
      remove(n->right_, success->key_);
    }
    return;
  }
  if (key < n->key_) {
    remove(n->left_, key);
  } else {
    remove(n->right_, key);
  }
}

// public
template <class T1, class T2>
void BSTree<T1, T2>::remove(T1 key) {
  remove(root, key);
}

// // private
// template <class T1, class T2>
// Node<T1, T2> *BSTree<T1, T2>::find(T1 key, Node<T1, T2> *n) {
//   if (n == nullptr || key == n->key_) {
//     return n;
//   }
//   if (key < n->key_) {
//     return find(n->left_, key);
//   } else {
//     return find(n->right_, key);
//   }
// }
//
// // public
// template <class T1, class T2>
// T2 BSTree<T1, T2>::find(T1 key) {
//   Node<T1, T2> *n = find(key, root);
//   if (n != nullptr) {
//     return n->getData();
//   } else {
//     return T2{};
//   }
// }
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
