#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void ClearMem(int index, unsigned int size);

  // driver
  void Push(char ch) {
    if (head_ == nullptr) {
      head_ = tail_ = new Node(ch);
    } else {
      Node* temp = new Node(ch);
      tail_->next = temp;
      tail_ = temp;
    }
  }
  Node* Head() { return head_; }

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif
