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

template <typename T>
struct CustomPos { // Permet de faire un vecteur 2 avec n'importe quel type.
	T x;
	T y;

	CustomPos(T x, T y) : x(x), y(y) {};
};

inline Pos stringToPos(string s) { // Convertit un string sous la fortme "A1" en une pos
	if (s.length() < 2) {
		throw 'a';
	}
	return Pos(int(s[1] - 49), int(s[0]) - 65);
}