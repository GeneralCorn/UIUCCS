#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  // /////////////////////////////////////
  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  // /////////////////////////////////////

  first->Join(0, second);
  first->SetAt(0, 'd');
  first->PushBack('g');
  std::cout << first->ToString() << std::endl;  // hii!@

  // std::cout << first->Size() << std::endl; // 5

  // std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  // std::cout << first_clone->ToString() << std::endl; // hii!@
  // std::cout << first_clone->Size() << std::endl; // 5

  return 0;
}
