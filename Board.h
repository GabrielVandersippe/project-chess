#pragma once
#include "VecMath.h"
#include <iostream>
using namespace std;

enum PieceSymbols { p = 'p', P = 'P', k = 'k', K = 'K', q = 'q', Q = 'Q', r = 'r', R = 'R', h = 'h', H = 'H', b = 'b', B = 'B' };

struct Piece {
	char symbol;
	int color; //1 for white, 0 for black
	bool has_moved;

	Piece(char s,int c) : symbol(s), color(c), has_moved(false) {};

	virtual void showMenaced(Pos pos,int color) { printf("placeholder never printed"); }
};

struct Pawn : public Piece {
	Pawn(int color) : Piece(char(int('P') + 32 * color), color) {};

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('P') + 32 * color) << ' ';
				}
				else if ((i == pos.y + (2 * color - 1)) && (abs(pos.x - j) == 1)) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct Rook : public Piece {
	Rook(int color) : Piece(char(int('R') + 32 * color), color) {};

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('R') + 32 * color) << ' ';
				}
				else if ((i == pos.y) || (j == pos.x)) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct King : public Piece {
	King(int color) : Piece(char(int('K') + 32 * color), color) {};

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('K') + 32 * color) << ' ';
				}
				else if ((abs(i - pos.y) <= 1) && (abs(j - pos.x) <= 1) && (((i == pos.y) || (j == pos.x)) || abs(i - pos.y) == abs(j - pos.x))) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct Queen : public Piece {
	Queen(int color) : Piece(char(int('Q') + 32 * color), color) {};

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('Q') + 32 * color) << ' ';
				}
				else if (((i == pos.y) || (j == pos.x)) || abs(i - pos.y) == abs(j - pos.x)) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct Knight : public Piece {
	Knight(int color) : Piece(char(int('H') + 32 * color), color) {}; // H pour Horse

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('R') + 32 * color) << ' ';
				}
				else if ((abs(pos.y - i) == 1 && abs(pos.x - j == 2)) || (abs(pos.y - i) == 2 && abs(pos.x - j == 1))) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct Bishop : public Piece {
	Bishop(int color) : Piece(char(int('B') + 32 * color), color) {};

	void showMenaced(Pos pos, int color) {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (Pos(j, i) == pos) {
					cout << char(int('B') + 32 * color) << ' ';
				}
				else if (abs(i - pos.y) == abs(j-pos.x)) {
					cout << "X ";
				}
				else {
					cout << ". ";
				}
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

struct Board {
	Piece* cases[8][8];

	void moveTo(Pos origin, Pos destination, bool &correct_move);

	bool usualMoveChecks(Pos origin, Pos destination);

	bool isMenaced(Pos pos, Piece* myself);

	bool freePath(Pos origin, Pos destination);

	bool noMoreMoves(int color); //Regarde si le roi de la couleur donnée peut encore bouger.

	Piece* getPiece(Pos pos) { 
		if (0<=pos.x && 8>pos.x && 0 <= pos.y && 8 > pos.y) return cases[pos.x][pos.y]; 
		else throw 1; // On throw 1 si jamais le getPiece est appelé en dehors de ses limites
	};
	void setPiece(Pos pos, Piece* p) { cases[pos.x][pos.y] = p; }

	Pos blackKingPos = Pos(4,7);
	Pos whiteKingPos = Pos(4,0);

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
		}

		Rook* white_rook1 = new Rook(1);
		Rook* white_rook2 = new Rook(1);
		Rook* black_rook1 = new Rook(0);
		Rook* black_rook2 = new Rook(0);

		cases[0][0] = white_rook1;
		cases[7][0] = white_rook2;
		cases[0][7] = black_rook1;
		cases[7][7] = black_rook2;


		Knight* white_knight1 = new Knight(1);
		Knight* white_knight2 = new Knight(1);
		Knight* black_knight1 = new Knight(0);
		Knight* black_knight2 = new Knight(0);

		cases[1][0] = white_knight1;
		cases[6][0] = white_knight2;
		cases[1][7] = black_knight1;
		cases[6][7] = black_knight2;


		Bishop* white_bishop1 = new Bishop(1);
		Bishop* white_bishop2 = new Bishop(1);
		Bishop* black_bishop1 = new Bishop(0);
		Bishop* black_bishop2 = new Bishop(0);

		cases[2][0] = white_bishop1;
		cases[5][0] = white_bishop2;
		cases[2][7] = black_bishop1;
		cases[5][7] = black_bishop2;


		Queen* white_queen = new Queen(1);
		Queen* black_queen = new Queen(0);

		cases[3][0] = white_queen;
		cases[3][7] = black_queen;
		

		King* white_king = new King(1);
		King* black_king = new King(0);

		cases[4][0] = white_king;
		cases[4][7] = black_king;
	}

	void show() {
		for (int i = 0; i < 8; i++) {
			cout << char(i + 65) << " | ";
			for (int j = 0; j < 8; j++) {
				if (cases[j][i]) {
					cout << cases[j][i]->symbol << ' ';
				}
				else { cout << ". "; }
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

inline bool Board::freePath(Pos origin, Pos destination) {
	bool is_free = true;

	if (origin.x == destination.x) {
		int y = min(destination.y, origin.y);
		for (int i = 1; i < abs(destination.y - origin.y); i++) {
			is_free = is_free && !getPiece(Pos(origin.x, y + i));
		}
	}
	else if (origin.y == destination.y)
	{
		int x = min(origin.x, destination.x);
		for (int i = 1; i < abs(destination.x - origin.x); i++) {
			is_free = is_free && !getPiece(Pos(x + i, origin.y));
		}
	}
	else
	{
		int x = min(origin.x, destination.x);
		int y = min(destination.y, origin.y);
		for (int i = 1; i < abs(destination.x - origin.x); i++) {
			is_free = is_free && !getPiece(Pos(x + i, y + i));
		}
	}
	return is_free;
}

inline bool Board::noMoreMoves(int color) {
	bool canMove = false;

	Pos pos = (color == 1) ? whiteKingPos : blackKingPos;
	for (int i = -1; i < 1; i++) {
		for (int j = -1; j < 1; j++) {
			if ((pos.x + i < 8) && (pos.x >= 0) && (pos.y + j < 8) && (pos.y + j >= 0) && (!getPiece(pos + Pos(i,j)) || getPiece(pos + Pos(i, j))-> color == 1 - color)) {
				canMove = canMove && isMenaced(pos, getPiece(pos));
			}
		}
	}
	return canMove;
}

inline bool Board::isMenaced(Pos pos, Piece* myself) {
	bool menaced = false;
	
	int color = myself->color;

	Piece* p = nullptr;
	int i = 1;
	// Boucle qui cherche la première pièce dans une direction
	while ((!p || (p == myself)) && (pos.x + i < 8)) {
		p = cases[pos.x + i][pos.y];
		i += 1;
	}
	menaced = p 
		&& (
			(p->symbol == char(int('Q') + 32 * (1-color)))
			|| (p->symbol == char(int('R') + 32 * (1 - color)))
			|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
			);

	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.x - i >= 0)) {
		p = cases[pos.x - i][pos.y];
		i += 1;
	}
	menaced = menaced ||
		(p
		&& (
			(p->symbol == char(int('Q') + 32 * (1 - color)))
			|| (p->symbol == char(int('R') + 32 * (1 - color)))
			|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
			));
	
	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.y + i < 8)) {
		p = cases[pos.x][pos.y + i];
		i += 1;
	}
	menaced = menaced ||
		(p
		&& (
			(p->symbol == char(int('Q') + 32 * (1-color)))
			|| (p->symbol == char(int('R') + 32 * (1 - color)))
			|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
			));

	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.y - i >= 0)) {
		p = cases[pos.x][pos.y - i];
		i += 1;
	}
	menaced = menaced ||
		(p
		&& (
			(p->symbol == char(int('Q') + 32 * (1 - color)))
			|| (p->symbol == char(int('R') + 32 * (1 - color)))
			|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
			));
	
	//Check cases diagonales :
	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.x + i < 8) && (pos.y - i >= 0)) {
		p = cases[pos.x + i][pos.y - i];
		i += 1;
	}
	menaced = menaced ||
		(p
			&& (
				(p->symbol == char(int('Q') + 32 * (1 - color)))
				|| (p->symbol == char(int('B') + 32 * (1 - color)))
				|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
				|| ((p->symbol == char(int('P') + 32 * (1 - color))) && (i == 2) && (color == 0)) //Menaced by a pawn here only if the piece moving is black
				));
	
	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.x - i >= 0) && (pos.y + i < 8)) {
		p = cases[pos.x - i][pos.y + i];
		i += 1;
	}
	menaced = menaced ||
		(p
			&& (
				(p->symbol == char(int('Q') + 32 * (1 - color)))
				|| (p->symbol == char(int('B') + 32 * (1 - color)))
				|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
				|| ((p->symbol == char(int('P') + 32 * (1 - color))) && (i == 2) && (color == 1)) //Same but white
				));
	
	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.x - i >= 0) && (pos.y - i >= 0)) {
		p = cases[pos.x - i][pos.y - i];
		i += 1;
	}
	menaced = menaced ||
		(p
			&& (
				(p->symbol == char(int('Q') + 32 * (1 - color)))
				|| (p->symbol == char(int('B') + 32 * (1 - color)))
				|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
				|| ((p->symbol == char(int('P') + 32 * (1 - color))) && (i == 2) && (color == 0)) // Black
				));

	p = nullptr;
	i = 1;
	while ((!p || (p == myself)) && (pos.x + i < 8) && (pos.y + i < 8)) {
		p = cases[pos.x + i][pos.y + i];
		i += 1;
	}
	menaced = menaced ||
		(p
			&& (
				(p->symbol == char(int('Q') + 32 * (1 - color)))
				|| (p->symbol == char(int('B') + 32 * (1 - color)))
				|| ((p->symbol == char(int('K') + 32 * (1 - color))) && (i == 2))
				|| ((p->symbol == char(int('P') + 32 * (1 - color))) && (i == 2) && (color == 1)) // White
				));
	
	int knightMoves[8][2] = { {2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2} };

	for (int i = 0; i < 8; i++) {
		try {
			p = getPiece(pos + toPos<int*>(knightMoves[i]));
			menaced = menaced || (p && p->symbol == char(int('H') + 32 * (1 - color)));
		}
		catch (int) {}
	}

	return menaced;
}

inline void Board::moveTo(Pos origin, Pos destination, bool &correct_move){

	Piece* piece = getPiece(origin);

	switch (piece->symbol) {
		case PieceSymbols::P :
		case PieceSymbols::p : // TODO : En passant
			if (usualMoveChecks(origin, destination)
				&& ((
					// Cas 1 : on va tout droit : il n'y a pas de pièces devant.
					!getPiece(destination)
					&& (destination.x == origin.x)  // On ne change pas de ligne
					&& (
						// On ne bouge que d'une case dans le bon sens
						(destination.y - origin.y == 2 * piece->color - 1)
						// Ou bien au premier coup on peut aller plus loin.
						|| ((destination.y - origin.y == 4 * piece->color - 2) && !piece->has_moved && freePath(origin, destination))
						)
					) 
					
					// Cas 2 : on mange en diagonale
				|| (
					getPiece(destination) 
					&& (abs(destination.x - origin.x) == 1)
					&& (destination.y - origin.y == 2 * piece->color - 1)
					&& (getPiece(destination)->color != piece->color)
				))
			)
				 
			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}
			break;

		case PieceSymbols::R :
		case PieceSymbols::r :

			if (usualMoveChecks(origin, destination)
				&& (origin.x == destination.x || origin.y == destination.y) // En ligne
				&& freePath(origin,destination) // Rien sur le chemin
				&& origin != destination // On reste pas statique
			)

			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}

			break;

		case PieceSymbols::B:
		case PieceSymbols::b:

			if (usualMoveChecks(origin, destination)
				&& (abs(origin.x-destination.x) == abs(origin.y-destination.y)) // En diagonale
				&& freePath(origin, destination) // Rien sur le chemin
				&& origin != destination // On reste pas statique
				)

			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}

			break;

		case PieceSymbols::Q:
		case PieceSymbols::q:

			if (usualMoveChecks(origin, destination)
				&& ((abs(origin.x - destination.x) == abs(origin.y - destination.y))
					|| (origin.x == destination.x || origin.y == destination.y)) // En diagonale ou en ligne
				&& freePath(origin, destination) // Rien sur le chemin
				&& origin != destination // On reste pas statique
				)

			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}

			break;

		case PieceSymbols::K: // TODO : Ne pas pouvoir bouger si une case est menacée.
		case PieceSymbols::k:

			if (usualMoveChecks(origin, destination)
				&& ((abs(origin.x - destination.x) <= 1) && (abs(origin.y - destination.y) <= 1))
				&& freePath(origin, destination) // Rien sur le chemin
				&& origin != destination // On reste pas statique
				&& !isMenaced(destination, piece) // L'arrivée n'est pas menacée.
				)

			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
				if (piece->color == 1) whiteKingPos = destination; else blackKingPos = destination;
			}

			break;

		case PieceSymbols::H:
		case PieceSymbols::h:

			if (usualMoveChecks(origin, destination)
				&& (
					(abs(origin.x - destination.x) == 1  && abs(destination.y - origin.y) == 2)
					|| (abs(origin.y - destination.y) == 1 && abs(destination.x - origin.x) == 2)
					)
				&& origin != destination // On reste pas statique
				)

			{
				piece->has_moved = true;
				correct_move = true; // On ne met à jour le booléen correct_move SSI le mouvement est valide.
				if (getPiece(destination)) { delete getPiece(destination); }
				setPiece(destination, piece);
				setPiece(origin, nullptr);
			}

			break;

	}

}