#include "db_table.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    for (auto& [id, row_array] : rows_) {
      void** curr_row = new void*[2 * (size_t)row_col_capacity_];
      for (unsigned int j = 0; j < row_col_capacity_; ++j) {
        curr_row[j] = row_array[j];
      }
      delete[] row_array;
      rows_[id] = curr_row;
    }
    row_col_capacity_ = 2 * (size_t)row_col_capacity_;
  }
  col_descs_.push_back(col_desc);
  // initialize new column values
  unsigned int nextel = col_descs_.size() - 1;
  for (auto const& [id, row_array] : rows_) {
    if (col_desc.second == DataType::kInt) {
      auto* i = new int(0);
      row_array[nextel] = static_cast<void*>(i);
    } else if (col_desc.second == DataType::kDouble) {
      auto* d = new double(0.00);
      row_array[nextel] = static_cast<void*>(d);
    } else if (col_desc.second == DataType::kString) {
      auto* s = new std::string("");
      row_array[nextel] = static_cast<void*>(s);
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size()) {
    throw std::out_of_range("col_idx invalid");
  }
  if ((col_descs_.size() == 1) && !(rows_.empty())) {
    throw std::runtime_error(
        "any table with at least one row must have at least one column.");
  }

  for (unsigned int i = 0; i < rows_.size(); ++i) {
    if (col_descs_[col_idx].second == DataType::kInt) {
      delete static_cast<int*>(rows_[i][col_idx]);
    } else if (col_descs_[col_idx].second == DataType::kDouble) {
      delete static_cast<double*>(rows_[i][col_idx]);
    } else if (col_descs_[col_idx].second == DataType::kString) {
      delete static_cast<std::string*>(rows_[i][col_idx]);
    }
    for (unsigned int j = 0; j < col_descs_.size() - 1; ++j) {
      if (j >= col_idx) rows_[i][j] = rows_[i][j + 1];
    }
  }
  // for (unsigned int i = 0; i < rows_.size(); ++i) {}
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  // col_data is "parallel" to col_descs_
  if (!(col_data.size() == col_descs_.size())) {
    throw std::invalid_argument("initializer list not valid");
  }
  // next_unique_id_++;
  void** newrow = new void*[row_col_capacity_];
  unsigned int ind = 0;
  for (const std::string& str : col_data) {
    if (col_descs_[ind].second == DataType::kInt) {
      newrow[ind] = static_cast<void*>(new int(std::stoi(str)));
    } else if (col_descs_[ind].second == DataType::kDouble) {
      newrow[ind] = static_cast<void*>(new double(std::stod(str)));
    } else if (col_descs_[ind].second == DataType::kString) {
      newrow[ind] = static_cast<void*>(new std::string(str));
    }
    ind++;
  }
  rows_.insert(std::pair<unsigned int, void**>(next_unique_id_++, newrow));
  // rows_[next_unique_id_] = newrow;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.count(id) <= 0) {
    throw std::invalid_argument("invalid id!");
  }
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_[i].second == DataType::kString)
      delete (static_cast<std::string*>(rows_[id][i]));
    else if (col_descs_[i].second == DataType::kDouble)
      delete (static_cast<double*>(rows_[id][i]));
    else if (col_descs_[i].second == DataType::kInt)
      delete (static_cast<int*>(rows_[id][i]));
  }
  delete[] rows_[id];
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs) {
  ClearMap();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_.clear();
  col_descs_ = rhs.col_descs_;
  for (auto const& [id, row_array] : rhs.rows_) {
    rows_[id] = new void*[row_col_capacity_];
    for (unsigned int j = 0; j < col_descs_.size(); ++j) {
      if (col_descs_[j].second == DataType::kInt) {
        auto* value = new int(*(static_cast<int*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      } else if (col_descs_[j].second == DataType::kDouble) {
        auto* value = new double(*(static_cast<double*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      } else {
        auto* value =
            new std::string(*(static_cast<std::string*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      }
    }
  }
}

DbTable::~DbTable() { ClearMap(); }

void DbTable::ClearMap() {
  for (auto& [itr, row_array] : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_[i].second == DataType::kInt) {
        delete static_cast<int*>(row_array[i]);
      } else if (col_descs_[i].second == DataType::kDouble) {
        delete static_cast<double*>(row_array[i]);
      } else if (col_descs_[i].second == DataType::kString) {
        delete static_cast<std::string*>(row_array[i]);
      }
    }
    delete[] row_array;
  }
  rows_.clear();
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (&rhs == this) return *this;
  ClearMap();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_.clear();
  col_descs_ = rhs.col_descs_;

  for (auto const& [id, row_array] : rhs.rows_) {
    rows_[id] = new void*[row_col_capacity_];
    for (unsigned int j = 0; j < col_descs_.size(); ++j) {
      if (col_descs_[j].second == DataType::kInt) {
        auto* value = new int(*(static_cast<int*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      } else if (col_descs_[j].second == DataType::kDouble) {
        auto* value = new double(*(static_cast<double*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      } else {
        auto* value =
            new std::string(*(static_cast<std::string*>(row_array[j])));
        rows_[id][j] = static_cast<void*>(value);
      }
    }
  }
  return *this;
}

/*
Name(std::string), Home Airport(std::string), MQMs(int), MQDs(double)
Detroit Flyer, DTW, 25000, 3050.24
Austin Flyer, AUS, 65000, 8050.24
Houston Flyer, IAH, 3000, 515.17
NYC Flyer, LGA, 105000, 12551.3
*/

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  unsigned int size = table.col_descs_.size();
  for (unsigned int i = 0; i < size; ++i) {
    os << table.col_descs_[i].first;
    if (table.col_descs_[i].second == DataType::kString)
      os << "(std::string)";
    else if (table.col_descs_[i].second == DataType::kInt)
      os << "(int)";
    else if (table.col_descs_[i].second == DataType::kDouble)
      os << "(double)";
    if (i != size - 1) {
      os << ", ";
    }
  }
  os << std::endl;
  for (auto const& itr : table.rows_) {
    for (unsigned int j = 0; j < size; ++j) {
      if (table.col_descs_[j].second == DataType::kString) {
        os << *(static_cast<std::string*>(itr.second[j]));
      } else if (table.col_descs_[j].second == DataType::kDouble) {
        os << *(static_cast<double*>(itr.second[j]));
      } else if (table.col_descs_[j].second == DataType::kInt) {
        os << *(static_cast<int*>(itr.second[j]));
      }
      if (j != size - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}

/*
  for (unsigned int i = 0; i < table.rows_.size(); ++i) {
    for (unsigned int j = 0; j < table.col_descs_.size(); ++j) {
      if (table.col_descs_[j].second == DataType::kInt) {
        auto x = static_cast<int*>(table.rows_[i][j]);
        os << x;
      }
    }
    os << std::endl;
  }
  */
