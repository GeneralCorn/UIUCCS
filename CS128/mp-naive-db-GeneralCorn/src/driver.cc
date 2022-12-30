#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  // write informal tests here

  DbTable* x = new DbTable();
  x->AddColumn({"name", DataType::kString});
  x->AddColumn({"gpa", DataType::kInt});
  x->AddColumn({"score", DataType::kDouble});
  x->AddRow(std::initializer_list<std::string>({"mark", "3", "4.5"}));
  x->DeleteRowById(0);

  std::ofstream os("test.txt");
  auto* y = new Database();
  y->CreateTable("table1");
  y->GetTable("table1") = *x;
  delete x;
  auto* s = new Database();
  *s = *y;
}
