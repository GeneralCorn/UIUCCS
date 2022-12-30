#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>

class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList() { ClearMem(); }
  void InsertInOrder(const T& data);
  void Reverse();

  /// HELPER///
  void InsertAscending(const T& data);
  void InsertDescending(const T& data);
  void ClearMem();

  /// FRIEND///
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return;
  }
  // deep copy constructor
  head_ = new Node<T>(source.head_->data);
  auto *tcurr = head_, *scurr = source.head_;
  // head_ = source.head_;
  // tcurr = tcurr->next;
  while (scurr->next != source.head_) {
    scurr = scurr->next;
    tcurr->next = new Node<T>(scurr->data);
    tcurr = tcurr->next;
  }
  tail_ = tcurr;
  tail_->next = head_;
  node_order_ = source.node_order_;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (&source == this) return *this;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return *this;
  }
  ClearMem();
  // deep copy constructor
  head_ = new Node<T>(source.head_->data);
  auto *tcurr = head_, *scurr = source.head_;
  while (scurr->next != source.head_) {
    scurr = scurr->next;
    tcurr->next = new Node<T>(scurr->data);
    tcurr = tcurr->next;
  }
  tail_ = tcurr;
  tail_->next = head_;
  node_order_ = source.node_order_;
  return *this;
}

template <typename T>
void CircularLinkedList<T>::ClearMem() {
  // delete from start
  if (head_ != nullptr) {
    // wrap around, tail_ = head_
    auto* curr = head_;
    while (curr->next != head_) {
      auto* newnode = curr->next;
      delete curr;
      curr = newnode;
    }
    delete curr;
    head_ = tail_ = nullptr;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertAscending(const T& data) {
  T hd = head_->data;
  T td = tail_->data;
  /*head_ smallest, tail_->prev largest*/
  if (data <= hd) {
    auto* newnode = new Node<T>(data, head_);  // second constructor
    head_ = newnode;
    tail_->next = head_;
  } else if (data >= td) {
    auto* newnode = new Node<T>(data, head_);  // same
    tail_->next = newnode;
    tail_ = tail_->next;
    // tail_->next = head_; redundant from overloaded constructor
  } else {
    auto* curr = head_;
    // for (auto* curr = head_; data < curr->next-> data; curr = curr->next)
    while (curr->next->data <= data) curr = curr->next;
    auto* newnode = new Node<T>(data, curr->next);
    curr->next = newnode;
  }
}
template <typename T>
// essentially flipped from above
void CircularLinkedList<T>::InsertDescending(const T& data) {
  T hd = head_->data;
  T td = tail_->data;
  /*head_ largest, tail->prev smallest*/
  if (data >= hd) {
    auto* newnode = new Node<T>(data, head_);
    head_ = newnode;
    tail_->next = head_;
  } else if (data <= td) {
    auto* newnode = new Node<T>(data, head_);
    tail_->next = newnode;
    tail_ = tail_->next;
  } else {
    auto* curr = head_;
    while (curr->next->data >= data) curr = curr->next;
    auto* newnode = new Node<T>(data, curr->next);
    curr->next = newnode;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    auto* newnode = new Node<T>(data);
    tail_ = head_ = newnode;
    tail_->next = head_;
    // head_->next = head_;
  } else {
    switch (node_order_) {
    case (Order::kASC):
      InsertAscending(data);
      break;
    case (Order::kDESC):
      InsertDescending(data);
      break;
    default:
      break;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  switch (node_order_) {
  case (Order::kASC):
    node_order_ = Order::kDESC;
    break;
  case (Order::kDESC):
    node_order_ = Order::kASC;
    break;
  default:
    break;
  }
  if (head_ == nullptr) {
    return;
  }

  auto* curr = head_;
  Node<T>* next = nullptr;
  Node<T>* prev = nullptr;

  do {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  } while (curr != head_);

  head_->next = prev;
  head_ = prev;
  tail_ = curr;
  tail_->next = head_;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif