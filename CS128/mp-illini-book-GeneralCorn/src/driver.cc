#include <iostream>
#include <string>
#include <vector>

#include "illini_book.hpp"

int main() {
  auto* ib = new IlliniBook("./example/persons.csv", "./example/relations.csv");
  std::cout << "CountGroups(): " << ib->CountGroups() << std::endl;
  std::cout << "CountGroups(\"128\"): " << ib->CountGroups("128") << std::endl;
  std::cout << "CountGroups(\"124\"): " << ib->CountGroups("124") << std::endl;
  std::cout << "CountGroups(\"173\"): " << ib->CountGroups("173") << std::endl;
  std::cout << "CountGroups(2): "
            << ib->CountGroups(std::vector<std::string>{"128", "173"})
            << std::endl;
  std::cout << "CountGroups(3): "
            << ib->CountGroups(std::vector<std::string>{"128", "124", "173"})
            << std::endl;

  std::cout << "AreRelated(1, 2): " << ib->AreRelated(1, 2) << std::endl;
  std::cout << "AreRelated(3, 2): " << ib->AreRelated(3, 2) << std::endl;
  std::cout << "AreRelated(1, 9): " << ib->AreRelated(1, 9) << std::endl;

  std::cout << "AreRelated(1, 2, \"128\"): " << ib->AreRelated(1, 2, "128")
            << std::endl;
  std::cout << "AreRelated(1, 2, \"124\"): " << ib->AreRelated(1, 2, "124")
            << std::endl;
  std::cout << "AreRelated(1, 6, \"128\"): " << ib->AreRelated(1, 6, "128")
            << std::endl;
  std::cout << "AreRelated(1, 6, \"124\"): " << ib->AreRelated(1, 6, "124")
            << std::endl;
  std::cout << "AreRelated(1, 2): " << ib->AreRelated(1, 2) << std::endl;
  std::cout << "AreRelated(3, 2): " << ib->AreRelated(3, 2) << std::endl;
  std::cout << "AreRelated(1, 9): " << ib->AreRelated(1, 9) << std::endl;

  std::cout << "GetRelated(1, 2): " << ib->GetRelated(1, 2) << std::endl;
  std::cout << "GetRelated(3, 2): " << ib->GetRelated(3, 2) << std::endl;
  std::cout << "GetRelated(1, 9): " << ib->GetRelated(1, 9) << std::endl;
  std::cout << "GetRelated(1, 2, \"128\"): " << ib->GetRelated(1, 2, "128")
            << std::endl;
  std::cout << "GetRelated(1, 2, \"124\"): " << ib->GetRelated(1, 2, "124")
            << std::endl;
  std::cout << "GetRelated(1, 6, \"128\"): " << ib->GetRelated(1, 6, "128")
            << std::endl;
  std::cout << "GetRelated(1, 6, \"124\"): " << ib->GetRelated(1, 6, "124")
            << std::endl;

  std::cout << "{ ";
  for (const auto& i : ib->GetSteps(1, 1)) {
    std::cout << i << ", ";
  }
  std::cout << " }" << std::endl;

  std::cout << "{ ";
  for (const auto& i : ib->GetSteps(1, 2)) {
    std::cout << i << ", ";
  }
  std::cout << " }" << std::endl;

  std::cout << "{ ";
  for (const auto& i : ib->GetSteps(1, 3)) {
    std::cout << i << ", ";
  }
  std::cout << " }" << std::endl;

  std::cout << "{ ";
  for (const auto& i : ib->GetSteps(9, 1)) {
    std::cout << i << ", ";
  }
  std::cout << " }" << std::endl;

  return 0;
}
