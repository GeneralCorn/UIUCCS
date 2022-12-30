#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <map>
#include <string>

#include "db_table.hpp"

class Database {
public:
  Database() = default;
  Database(const Database& rhs);
  Database& operator=(const Database& rhs);
  ~Database();

  void CreateTable(const std::string& table_name);
  void DropTable(const std::string& table_name);
  DbTable& GetTable(const std::string& table_name) {
    return *tables_[table_name];
  }
  friend std::ostream& operator<<(std::ostream& os, const Database& db);
  void ClearTable();

private:
  std::map<std::string, DbTable*> tables_;  // maps table name -> table
};

std::ostream& operator<<(std::ostream& os, const Database& db);

#endif