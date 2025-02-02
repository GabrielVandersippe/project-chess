#pragma once
#include <string>
using namespace std;

struct Pos {
	int x;
	int y;
	
	Pos(int x, int y) : x(x), y(y) {}

	bool operator!= (const Pos& pos) {
		return (pos.x != x) || (pos.y != y);
	}

	bool operator== (const Pos & pos) {
		return (pos.x == x) && (pos.y == y);
	}

	Pos operator+ (const Pos& pos) {
		return Pos(pos.x + x, pos.y + y);
	}
};

template <typename T> // Transforme un ensemble à deux éléments quelconque en une position
inline Pos toPos(T t) {
	return Pos(t[0], t[1]); 
}

inline Pos stringToPos(string s) { // Convertit un string sous la fortme "A1" en une pos
	return Pos(int(s[1] - 49), int(s[0]) - 65);
}