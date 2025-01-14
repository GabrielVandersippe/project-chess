#pragma once
#include <string>
using namespace std;

struct Pos {
	int x;
	int y;
	
	Pos(int x, int y) : x(x), y(y) {}
};

template <typename T>
inline Pos toPos(T s) { // Convertit d'un type de données autre en une pos
	return Pos(int(s[1] - 49), int(s[0]) - 65);
}