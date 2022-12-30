#include "dna_strand.hpp"

#include <stdexcept>

// destructor
DNAstrand::~DNAstrand() {
  auto* curr = head_;
  while (curr != nullptr) {
    auto* temp = curr->next;
    delete curr;
    curr = temp;
  }
}
// helper
void DNAstrand::ClearMem(int index, unsigned int size) {
  auto* curr = head_;
  if (index == 0) {
    for (unsigned int i = size; i > 0; --i) {
      auto* temp = curr->next;
      delete curr;
      curr = temp;
    }
    head_ = curr;
  } else {
    Node* temp = nullptr;
    for (unsigned int i = index - 1; i > 0; --i) curr = curr->next;
    for (unsigned int i = 0; i < size; ++i) {
      temp = curr->next;
      curr->next = curr->next->next;
      delete temp;
    }
  }
}
/////main/////

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (&to_splice_in == this) return;
  if (pattern[0] == '\0' || pattern == nullptr || to_splice_in.head_ == nullptr)
    return;
  unsigned int psize = 0;  // size of pattern
  while (pattern[psize] != '\0') psize++;

  auto* curr = head_;
  int tracker = -1, foundidx = -1;
  while (curr != nullptr) {
    tracker++;
    bool charmatch = true;
    auto* tmp = curr;
    for (unsigned int i = 0; i < psize; ++i) {
      if (tmp->data != pattern[i]) charmatch = false;
      if (tmp->next != nullptr) tmp = tmp->next;
    }
    if (charmatch) foundidx = tracker;
    curr = curr->next;
  }
  // std::cout << "foundidx: " << foundidx << std::endl;
  if (foundidx == -1) {
    throw std::invalid_argument("pattern not found");
  }

  ClearMem(foundidx, psize);

  if (foundidx == 0) {
    to_splice_in.tail_->next = head_;
    head_ = to_splice_in.head_;
  } else {
    Node* curr = head_;
    for (int i = foundidx - 1; i > 0; --i) curr = curr->next;
    to_splice_in.tail_->next = curr->next;
    curr->next = to_splice_in.head_;
    tail_ = curr;
  }
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}
