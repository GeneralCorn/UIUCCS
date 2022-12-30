#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <queue>
#include <set>
#include <vector>

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream stu(people_fpath);
  std::ifstream rsp(relations_fpath);

  for (std::string uin; getline(stu, uin); uin = "") {
    idlist_.push_back(stoi(uin));
    graph_[stoi(uin)] = std::vector<std::pair<int, std::string>>();
  }
  for (std::string rel; getline(rsp, rel); rel = "") {
    std::vector<std::string> split = utilities::Split(rel, ',');
    graph_[stoi(split[0])].push_back({stoi(split[1]), split[2]});
    graph_[stoi(split[1])].push_back({stoi(split[0]), split[2]});
  }
}

size_t IlliniBook::CountGroups() const {
  std::map<int, bool> visited;
  for (auto [uin, x] : graph_) visited[uin] = false;
  unsigned int count = 0;
  for (auto [uin, x] : graph_) {
    if (visited[uin]) continue;
    count++;
    std::queue<int> q;
    q.push(uin);
    while (!q.empty()) {
      int temp = q.front();
      q.pop();
      for (const auto& i : graph_.at(temp)) {
        if (visited[i.first]) continue;
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::map<int, bool> visited;
  for (auto [uin, x] : graph_) visited[uin] = false;
  unsigned int count = 0;
  for (auto [uin, x] : graph_) {
    if (visited[uin]) continue;
    count++;
    std::queue<int> q;
    q.push(uin);
    while (!q.empty()) {
      int temp = q.front();
      q.pop();
      for (const auto& i : graph_.at(temp)) {
        if (visited[i.first] || i.second != relationship) continue;
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return count;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::map<int, bool> visited;
  for (auto [uin, x] : graph_) visited[uin] = false;
  unsigned int count = 0;
  for (auto [uin, x] : graph_) {
    if (visited[uin]) continue;
    count++;
    std::queue<int> q;
    q.push(uin);
    while (!q.empty()) {
      int temp = q.front();
      q.pop();
      for (const auto& i : graph_.at(temp)) {
        if (!visited[i.first] &&
            std::find(relationships.begin(), relationships.end(), i.second) !=
                relationships.end()) {
          q.push(i.first);
          visited[i.first] = true;
        }
      }
    }
  }
  return count;
}

int IlliniBook::BFS(int uin_1, int uin_2) const {
  std::queue<int> q;
  std::set<int> visited;
  int pathlength = 0;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {
    size_t s = q.size();
    for (size_t i = s; i > 0; --i) {
      int temp = q.front();
      q.pop();
      if (temp == uin_2) return pathlength;
      for (const auto& t : graph_.at(temp)) {
        if (visited.count(t.first) == 0) {
          q.push(t.first);
          visited.insert(t.first);
        }
      }
    }
    pathlength++;
  }
  return -1;
}

int IlliniBook::BFS(int uin_1,
                    int uin_2,
                    const std::string& relationship) const {
  std::queue<int> q;
  std::set<int> visited;
  int pathlength = 0;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {
    size_t s = q.size();
    for (size_t i = s; i > 0; --i) {
      int temp = q.front();
      q.pop();
      if (temp == uin_2) return pathlength;
      for (const auto& t : graph_.at(temp)) {
        if (visited.count(t.first) == 0 && t.second == relationship) {
          q.push(t.first);
          visited.insert(t.first);
        }
      }
    }
    pathlength++;
  }
  return -1;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  return BFS(uin_1, uin_2) != -1;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  return BFS(uin_1, uin_2, relationship) != -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  return BFS(uin_1, uin_2);
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  return BFS(uin_1, uin_2, relationship);
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::queue<int> q;
  std::set<int> visited;
  int pathlength = 0;
  q.push(uin);
  visited.insert(uin);
  while (!q.empty() && n > 0) {
    size_t s = q.size();
    for (size_t i = s; i > 0; --i) {
      int temp = q.front();
      q.pop();
      for (const auto& t : graph_.at(temp)) {
        if (visited.count(t.first) == 0) {
          q.push(t.first);
          visited.insert(t.first);
        }
      }
    }
    pathlength++;
    n--;
  }

  std::vector<int> steps;
  while (!q.empty()) {
    steps.push_back(q.front());
    q.pop();
  }
  return steps;
}