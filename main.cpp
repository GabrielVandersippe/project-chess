#include <iostream>
#include "Board.h"
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////
// Exemples d'implementation d'elements importants :
// 1. Templates : Fichier "VecMath.h", ligne 24
// 2. Classes dérivées : Fichier "Board.h", lignes 18 etc.
// 3. Erreurs : Fichiers "main.cpp" et "VecMath.h" par exemple, pour des throw, try et catch.
// 4. Héritage virtuel : Fichier "Board.h", lignes 18 etc.
// 5. Utilisation de la STL : cout, cin & string utilisés fréquemment
// 6. Surcharge d'opérateurs : Fichier "VecMath.h"
//////////////////////////////////////////////////////////////////


int main() {
	Board board;
	bool game_ended = false;
	int turn = 1; // Couleur du joueur

	cout << "Blanc (1) en minuscules; Noir (0) en majuscules \n" << endl;

	cout << "POUR ACCEDER A L'AIDE, TAPER 'Help' AU DEBUT D'UN TOUR. \n" << endl;

	while (!game_ended) {
		cout << "Tour : " << turn << endl;
		board.show();

		string origin;
		string destination;

		bool correct_move = false;

		while (!correct_move) {
			cout << "\nEntrer une instruction : " << endl;
			cin >> origin;

			if (origin == "Help") {
				cout << endl;
				cout << " --- **** ---" << endl;
				cout << "| P - Pawn   |" << endl;
				cout << "| R - Rook   |" << endl;
				cout << "| P - Bishop |" << endl;
				cout << "| H - Horse  | (Knight mais K deja pris)" << endl;
				cout << "| Q - Queen  |" << endl;
				cout << "| K - King   |" << endl;
				cout << " --- **** ---" << endl;

				cout << "> Pour choisir une piece a deplacer, entrer sa position sous la forme 'A1'\n> Pour voir les cases menacees par une piece, taper 'Menaces'\n" << endl;
			}

			else if (origin == "Menaces") {
				string input;
				bool good_input = false;

				while (!good_input) {
					cout << "\nQuelle piece ? " << endl;
					cin >> input;

					try {
						board.getPiece(stringToPos(input))->showMenaced(stringToPos(input), board.getPiece(stringToPos(input))->color);
						break;
					}
					catch (int) { // Int -> erreur de getPiece
						cout << "Entree invalide ! Attention a bien rester dans la grille.\n" << endl;
					}
					catch (char) { // Char -> erreur de stringToPos
						cout << "Entree invalide ! Attention a mettre une entree de taille suffisante.\n" << endl;
					}
				}
			}
			else {
				try {
					cout << "Choisir ou bouger cette piece : " << endl;
					cin >> destination;

					if (board.getPiece(stringToPos(origin)) && board.getPiece(stringToPos(origin))->color == turn) {
						board.moveTo(stringToPos(origin), stringToPos(destination), correct_move);
					}

					if (!correct_move) { cout << "Mouvement incorrect !" << endl; }
				}
				catch (int) {
					cout << "Entree invalide ! Attention a bien rester dans la grille, ou a bien orthographier les commandes.\n" << endl;
				}
				catch (char) {
					cout << "Entree invalide ! Attention a mettre une entree de taille suffisante.\n" << endl;
				}
			}
		}
		
		game_ended = board.noMoreMoves(0) || board.noMoreMoves(1);

		turn = 1 - turn;
	}
}