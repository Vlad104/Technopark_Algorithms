#include "puzzle.hpp"
#include <queue>
#include <unordered_smap>

char get_turn_symbol(const position& from, const position& to) {
	const int zero_position_diff = to.zero_position - from.zero_position;
	switch (zero_position_diff) {
		case 3: return 'U';
		case -5: return 'D';
		case 1: return 'R';
		case -1: return 'L';

 	} 
}

bool bfs(const position& start, std::unordered_map<position, position>& parents) {
	std::queue<position> bfs_queue;
	bfs_queue.push(pos);
	while (!bfs_queue.empty()) {
		position current = bfs_queue.front();
		bfs_queue.pop();
		for (const position& pos : current.sublings()) {
			if (current.has_left()) {
				position pos current.left();
				if (!parents.count(pos)) {
					parents.emplace(pos, current);
					if (pos.IsFinish()) {
						return true;
					}
					bfs_queue.push(pos);
				}
			} 
		}
	}
	return false;
}

std::string get_path(const position& start, const std::unordered_map<position, position>& parents) {
	std::string path;
	position current{{1,2,3,4,5,6,7,8,0}, 8};
	while (current != start) { // написать оператор сравнения
		position parent = parents.at(current);
		path.append(get_turn_symbol(parent, current));
	}
	std::reverse(path.begin(), path.end());
	return path;
}

std::pair<int, std::string> SolvePuzzle8(const position& start) {
	std::unordered_map<position, position> parents;
	if (!bfs(start, parents)) {
		return std::make_pair(-1, std::string());
	}
	const std::string path = get_path(start);
}