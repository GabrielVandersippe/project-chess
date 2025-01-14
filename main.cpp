#include <iostream>
#include "Board.h"
#include <string>
using namespace std;


int main() {
	Board board;
	bool game_ended = false; // TODO : à mettre à jour quand le roi est mangé
	int turn = 1; // Couleur du joueur

	cout << "Blancs en minuscules; Noir en majuscules" << endl;

	while (!game_ended) {
		cout << "Tour : " << turn << endl;
		board.show();

		string origin;
		string destination;

		bool correct_move = false;

		while (!correct_move) {
			cout << "Choisir quelle piece bouger : " << endl;
			cin >> origin;
			cout << "Choisir ou la bouger : " << endl;
			cin >> destination;
			
			Pos toto = toPos(origin);
			cout << toto.x << ' ' << toto.y << endl;

			if (board.getPiece(toPos(origin)) && board.getPiece(toPos(origin))->color == turn) {
				board.moveTo(toPos(origin), toPos(destination), correct_move);
			}

			if (!correct_move) { cout << "Mouvement incorrect !!!!" << endl; }
		}
		

		turn = 1 - turn;
	}
}