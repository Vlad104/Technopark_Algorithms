#pragma once

struct position {
	std::array<char, 9> chips;
	char zero_position; 	
	std::vecttor<position> Siblings() const {
		std::vector<position> sublings;
		if (zero_position >= 3) {
			const int new_zero_position = zero_position - 3;
			position down{chips, new_zero_position};
			std::swap(chips[zero_position], chips[new_zero_position]);
		}
	}
	bool operator==(const position& other) const {
		return chips == other.chips;	
		// zero position must be equal for equal chips
	}
	bool operator!=(const position& other) {return !operator==(other);};
	boll isFinish() const {
		return operator==(kFinishPosition);
	}
};

const position kFinishPosition{{1,2,3,4,5,6,7,8,0}, 8};