#pragma once
#include <string>
using namespace std;

template <typename T>
struct Pos {
	T x;
	T y;
	
	Pos(T x, T y) : x(x), y(y) {}

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

template <typename T1, typename T2> // Transforme un ensemble à deux éléments quelconque en une position
inline Pos<T1> toPos(T2 t) {
	return Pos<T1>(t[0], t[1]); 
}

inline Pos<int> stringToPos(string s) { // Convertit un string sous la fortme "A1" en une pos
	if (s.length() < 2) {
		throw 'a';
	}
	return Pos<int>(int(s[1] - 49), int(s[0]) - 65);
}