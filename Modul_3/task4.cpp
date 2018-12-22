#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <limits>

const int resolution = 16;
const int inf = std::numeric_limits<int>::max();

struct position {
  std::array<int, resolution> chips;
  int zero_position;

  bool is_finish() const;
  std::vector<position> sublings() const;

  bool operator==(const position& other) const { return chips == other.chips;};
  bool operator!=(const position& other) const { return !operator==(other);}
};

const position kFinishPosition{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 15};

namespace std {
  template<> struct hash<position> {
    unsigned int operator()(const position& pos) const {
      unsigned int hash = 0;
      for (auto chip: pos.chips) {
        hash = hash * 37 + chip;
      }
      return hash;
    }
  };
}

bool position::is_finish() const {
  return operator==(kFinishPosition);
}

std::vector<position> position::sublings() const {
  std::vector<position> siblings;
  if (zero_position >= 4) {
    const int new_zero_position = zero_position - 4;
    position down{chips, new_zero_position};
    std::swap(down.chips[zero_position], down.chips[new_zero_position]);
    siblings.emplace_back(down);
  }
  if (zero_position <= 12) {
    const int new_zero_position = zero_position + 4;
    position up{chips, new_zero_position};
    std::swap(up.chips[zero_position], up.chips[new_zero_position]);
    siblings.emplace_back(up);
  }
  if (zero_position % 4 != 0) {
    const int new_zero_position = zero_position - 1;
    position right{chips, new_zero_position};
    std::swap(right.chips[zero_position], right.chips[new_zero_position]);
    siblings.emplace_back(right);
  }
  if (zero_position % 4 != 3) {
    const int new_zero_position = zero_position + 1;
    position left{chips, new_zero_position};
    std::swap(left.chips[zero_position], left.chips[new_zero_position]);
    siblings.emplace_back(left);
  }
  return siblings;
}

char get_command(const position& from, const position& to) {
  const int zero_position_diff = to.zero_position - from.zero_position;
  switch (zero_position_diff) {
    case 4: 
      return 'U';
    case -4: 
      return 'D';
    case 1: 
      return 'L';
    case -1: 
      return 'R';
    default:
      return '\0'; 
  }
}

bool bfs(const position& start, std::unordered_map<position, position>& parents) {
  std::queue<position> bfs_queue;
  bfs_queue.push(start);
  while (!bfs_queue.empty()) {
    position current = bfs_queue.front(); 
    bfs_queue.pop();
    for (const position& pos: current.sublings()) {
      if (parents.find(pos) == parents.end()) {
        parents.emplace(pos, current);
        if (pos.is_finish()) {
          return true;
        }
        bfs_queue.push(pos);
      }
    }
  }
  return false;
}

/*
int Dijkstra(const position& from, std::unordered_map<position, position>& parents) {

    std::vector<int> min_paths(16, inf);
    min_paths[from] = 0;


    std::set<std::pait<position, position>> q;
    q.emplace(make_pair());

    while(!q.empty()) {
        auto vertex = *q.begin();
        q.erase(q.begin());
        
        std::vector<ListGraph::Vertice> vertices;
        graph.GetNextVertices(vertex.value, vertices);
        
        for (ListGraph::Vertice v : vertices) {

            if (min_paths[v.value] > min_paths[vertex.value] + v.path) {            
                q.erase(ListGraph::Vertice(v.value, min_paths[v.value]));
                min_paths[v.value] = min_paths[vertex.value] + v.path;
                q.emplace(ListGraph::Vertice(v.value, min_paths[v.value]));
            }
        }
    }
    if (min_paths[to] == inf) {
        return -1;
    }
    return min_paths[to];
}
*/
/*
void AStar(const position& start, std::unordered_map<position, position>& parents) {
    std::vector<int> d(9, inf);

    std::priority_queue<position> q;
    q.push(start);
    while (!q.empty()) {
        auto u = q.top();
        q.pop();
        auto E = q.sublings();
        for (auto v : E) {
            if (d[v] == inf) {
                q.push(v);
            }
            if (d[v] > d[u] + w)
        }
    }

}
*/


std::string get_path(const position& start, const std::unordered_map<position, position>& parents) {
  std::string path;
  position current = kFinishPosition;
  while (current != start) {
    position parent = parents.at(current);
    path.push_back(get_command(parent, current));
    current = parent;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::pair<int, std::string> solve(const position& start) {
  std::unordered_map<position, position> parents;
  if (!bfs(start, parents)) {
    return std::make_pair(-1, std::string());
  }
  const std::string path = get_path(start, parents);
  return std::make_pair(path.size(), path);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::array<int, resolution> input;
  int start_pos = 0;

  for (int i = 0; i < resolution; i++) {
    int x = 0;
    std::cin >> x;
    input[i] = x;
    if (x == 0) {
      start_pos = i;
    }
  }

  position start{input, start_pos};
  const auto solution = solve(start);
  std::cout << solution.first << std::endl << solution.second << std::endl;
  return 0;
}