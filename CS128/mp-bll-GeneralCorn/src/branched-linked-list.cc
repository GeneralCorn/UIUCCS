#include "branched-linked-list.hpp"

// yichenliu

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  Node* curr = head_;
  auto* newcurr = to_copy.head_;
  while (newcurr != nullptr) {
    // two conditions
    if (newcurr->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*(newcurr->next_bll_));
    }
    if (newcurr->next_node_ != nullptr) {
      curr->next_node_ = new Node((newcurr->next_node_->data_));
    }
    curr = curr->next_node_;
    newcurr = newcurr->next_node_;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (&rhs == this) return *this;
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
  } else {
    head_ = new Node(rhs.head_->data_);
    Node* curr = head_;
    auto* newcurr = rhs.head_;
    while (newcurr != nullptr) {
      // two conditions
      if (newcurr->next_bll_ != nullptr) {
        curr->next_bll_ = new BLL(*(newcurr->next_bll_));
      }
      if (newcurr->next_node_ != nullptr) {
        curr->next_node_ = new Node((newcurr->next_node_->data_));
      }
      curr = curr->next_node_;
      newcurr = newcurr->next_node_;
    }
  }
  return *this;
}

BLL::~BLL() {
  Clear(head_);  // aka ROOT of BLL
  head_ = nullptr;
}

// self
void BLL::Clear(Node* toclear) {
  if (toclear == nullptr) {
    return;
  }
  if (toclear->next_bll_ != nullptr) {
    delete toclear->next_bll_;
  }
  Clear(toclear->next_node_);
  delete toclear;
}

size_t BLL::Size() const {
  size_t count = 0;
  auto* curr = head_;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr) {
      count += curr->next_bll_->Size();
      count++;
    } else
      count++;
    curr = curr->next_node_;
  }
  return count;
}

Node* BLL::PushBack(char dat) {
  // disregard ->next_bll_
  Node* newnode = new Node(dat);
  if (head_ == nullptr) {
    head_ = newnode;
  } else {
    auto* curr = head_;
    while (curr->next_node_ != nullptr) {
      curr = curr->next_node_;
    }
    curr->next_node_ = newnode;
  }
  return newnode;
}

char BLL::GetAt(size_t idx) const {
  if (idx < 0 || idx >= Size()) throw std::invalid_argument("invalid idx");
  Node* curr = head_;
  for (size_t i = idx; i > 0; i--) {
    if (curr->next_bll_ != nullptr) {
      curr = curr->next_bll_->head_;
    } else {
      curr = curr->next_node_;
    }
  }
  return curr->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx >= Size()) throw std::invalid_argument("invalid idx");
  Node* curr = head_;
  for (size_t i = idx; i > 0; i--) {
    if (curr->next_bll_ != nullptr) {
      curr = curr->next_bll_->head_;
    } else {
      curr = curr->next_node_;
    }
  }
  curr->data_ = dat;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) return true;
  Node *turtle = head_, *hare = GetNext(head_);
  while (turtle != nullptr && hare != nullptr && GetNext(turtle) != nullptr &&
         GetNext(hare) != nullptr) {
    if (turtle == hare) return false;
    turtle = GetNext(turtle);
    hare = GetNext(GetNext(hare));
  }
  return true;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= Size()) throw std::invalid_argument("invalid idx");
  // list == nullptr doesn't matter
  auto* curr = head_;
  for (size_t i = idx; i > 0; i--) {
    if (curr->next_bll_ != nullptr) {
      curr = curr->next_bll_->head_;
    } else {
      curr = curr->next_node_;
    }
  }
  if (curr->next_bll_ == nullptr) {
    curr->next_bll_ = list;
  } else {
    throw std::invalid_argument("existing bll");
  }
  if (!IsBLLAcyclic()) {
    curr->next_node_ = nullptr;
    throw std::runtime_error("will be cyclic");
  }
}

std::string BLL::ToString() const {
  std::string tostring;
  auto* curr = head_;
  while (curr != nullptr) {
    tostring += curr->data_;
    if (curr->next_bll_ != nullptr) {
      tostring += curr->next_bll_->ToString();
    }
    curr = curr->next_node_;
  }
  return tostring;
}
