#include <iostream>
#include "Board.h"
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////
// Exemples d'impl�mentation des diff�rentes choses requises :
// 1. Templates : Fichier "VecMath.h", ligne 16
// 2. Classes d�riv�es : Fichier "Board.h", lignes 21 etc.
// 3. Erreurs : Pour �a on va impl�menter le fait que �a explose si on donne pas assez d'arguments au stringToPos.
// 4. H�ritage virtuel : cf lignes 21 etc.
// 5. STL : cout, cin & string utilis�s fr�quemment
//////////////////////////////////////////////////////////////////


int main() {
	Board board;
	bool game_ended = false; // TODO : � mettre � jour quand le roi est mang�
	int turn = 1; // Couleur du joueur

	cout << "Blanc (1) en minuscules; Noir (0) en majuscules \n" << endl;

	while (!game_ended) {
		cout << "Tour : " << turn << endl;
		board.show();

		string origin;
		string destination;

		bool correct_move = false;

		while (!correct_move) {
			cout << "\nChoisir quelle piece bouger : " << endl;
			cin >> origin;

			if (origin == "Menaces") {
				string input;
				bool good_input = false;

				while (!good_input) {
					cout << "\nQuelle piece ? " << endl;
					cin >> input;

					try {
						board.getPiece(stringToPos(input))->showMenaced(stringToPos(input));
						break;
					}
					catch (int) {
						cout << "Mauvaise entree !\n" << endl;
					}
				}
			}
			else {
				printf("x %i, y %i\n", stringToPos(origin).x, stringToPos(origin).y);
				cout << "Choisir ou la bouger : " << endl;
				cin >> destination;

				cout << board.freePath(stringToPos(origin), stringToPos(destination)) << endl;

				if (board.getPiece(stringToPos(origin)) && board.getPiece(stringToPos(origin))->color == turn) {
					board.moveTo(stringToPos(origin), stringToPos(destination), correct_move);
				}

				if (!correct_move) { cout << "Mouvement incorrect !" << endl; }
			}
		}
		

		turn = 1 - turn;
	}
}