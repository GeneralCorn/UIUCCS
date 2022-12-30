#include "db.hpp"

#include <map>
#include <vector>

Database::Database(const Database& rhs) {
  if (!(rhs.tables_.empty())) {
    for (auto const& [ind, table] : rhs.tables_) {
      tables_[ind] = new DbTable(*table);
    }
  }
}

Database& Database::operator=(const Database& rhs) {
  if (&rhs == this /*|| rhs.tables_.empty()*/) return *this;
  for (auto& [ind, table] : tables_) {
    delete table;
  }
  tables_.clear();
  for (auto const& [ind, table] : rhs.tables_) {
    tables_[ind] = new DbTable(*table);
  }
  return *this;
}

// make sure this works
Database::~Database() {
  for (auto const& [id, val] : tables_) {
    delete val;
  }
  tables_.clear();
}

void Database::CreateTable(const std::string& table_name) {
  // auto itr = tables_.find(table_name);
  if (tables_.count(table_name) == 0) {
    tables_.insert(std::pair<std::string, DbTable*>(table_name, new DbTable()));
  }
}

void Database::DropTable(const std::string& table_name) {

  // auto itr = tables_.find(table_name);
	//
	// if (itr == table_.end()) {
	// 
	// }
	 
  if (tables_.count(table_name) <= 0) {
    throw std::invalid_argument("key not in map");
  }
  delete tables_[table_name];
  tables_.erase(table_name);
}
