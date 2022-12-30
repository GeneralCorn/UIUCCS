#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

  // random

  BLL* Nextbll(Node* curr) const {
    if (curr->next_bll_ != nullptr) {
      return curr->next_bll_;
    }
    return nullptr;
  }
  Node* Nextnode(Node* curr) const {
    if (curr->next_node_ != nullptr && curr->next_bll_ == nullptr) {
      return curr->next_node_;
    }
    return nullptr;
  }

  Node* GetNext(Node* curr) const {
    if (curr->next_bll_ != nullptr) {
      return curr->next_bll_->head_;
    } else if (curr->next_node_ != nullptr) {
      return curr->next_node_;
    }
    return nullptr;
  }

  // self
  // override
  void Clear(Node* toclear);

private:
  Node* head_;
  bool IsBLLAcyclic() const;
};

#endif
