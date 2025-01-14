#pragma once
#include "VecMath.h"
#include <iostream>
using namespace std;

enum PieceSymbols {p = ('p' | 'P'), k = ('k' | 'K'), q = ('q' | 'Q'), r = ('r' | 'R'), h = ('h' | 'H'), b = ('b' | 'B')};

struct Piece {
	char symbol;
	int color; //1 for white, 0 for black
	bool has_moved;

	Piece(char s,int c) : symbol(s), color(c), has_moved(false) {};

	//virtual void moveTo(Pos destination) = 0;
};

struct Pawn : public Piece {
	Pawn(int color) : Piece(char(int('P') + 32 * color), color) {};
	bool first_turn = true;
};

struct Rook : public Piece {
	Rook(int color) : Piece(char(int('R') + 32 * color), color) {};
};

struct King : public Piece {
	King(int color) : Piece(char(int('K') + 32 * color), color) {};
};

struct Queen : public Piece {
	Queen(int color) : Piece(char(int('Q') + 32 * color), color) {};
};

struct Knight : public Piece {
	Knight(int color) : Piece(char(int('H') + 32 * color), color) {}; // H pour Horse
};

struct Bishop : public Piece {
	Bishop(int color) : Piece(char(int('B') + 32 * color), color) {};
};

struct Board {
	Piece* cases[8][8];

	void moveTo(Pos origin, Pos destination, bool &correct_move);
	bool usualMoveChecks(Pos origin, Pos destination);

	Piece* getPiece(Pos pos) { return cases[pos.x][pos.y]; };
	void setPiece(Pos pos, Piece* p) { cases[pos.x][pos.y] = p; }

	Board() {

		for (int i = 0; i < 8; i++) {
			Pawn* white_pawn = new Pawn(1);
			Pawn* black_pawn = new Pawn(0);

			cases[i][1] = white_pawn;
			cases[i][6] = black_pawn;

			cases[i][2] = nullptr;
			cases[i][3] = nullptr;
			cases[i][4] = nullptr;
			cases[i][5] = nullptr;

			// TODO : other pieces
			cases[i][0] = nullptr;
			cases[i][7] = nullptr;
		}
	}

	void show() {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (cases[j][i]) {
					cout << cases[j][i]->symbol << ' ';
				}
				else { cout << "# "; }
			}
			cout << " | " << endl;
		}
		cout << "    ";
		for (int i = 0; i < 8; i++) {
			cout << i + 1 << ' ';
		}
		cout << endl;
	}
};

inline bool Board::usualMoveChecks(Pos origin, Pos destination) {
	return ((destination.x >= 0)
		&& (destination.x < 8)
		&& (destination.y >= 0)
		&& (destination.y < 8)
		&& (getPiece(origin))
		&& (!getPiece(destination) || (getPiece(destination)->color != getPiece(origin)->color))); //Vrai pour tous, sauf pion.
}

inline void Board::moveTo(Pos origin, Pos destination, bool &correct_move){

	Piece* piece = getPiece(origin);

	switch (piece->symbol) {
		case PieceSymbols::p : // TODO : En passant
			if (usualMoveChecks(origin, destination)
				&& ((!getPiece(destination)) // Cas 1 : on va tout droit : il n'y a pas de pièces devant.
					&& (destination.x == origin.x)  // On ne change pas de ligne
					&& ((destination.y - origin.y == 2 * piece->color - 1) // On ne bouge que d'une case dans le bon sens
						|| ((destination.y - origin.y == 4 * piece->color - 2) && !piece->has_moved))) // Ou bien au premier coup on peut aller plus loin.
					|| (getPiece(destination) // Cas 2 : on mange en diagonale
						&& (abs(destination.x - origin.x) == 1)
						&& (destination.y - origin.y == 2 * piece->color - 1)
						&& (getPiece(destination)->color != getPiece(origin)->color))) 
			{
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}
			break;
	}

}