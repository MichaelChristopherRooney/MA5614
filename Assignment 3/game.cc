#include "board.h"

#include <iostream>
#include <unistd.h>

int main(void){
	Board b;
	Colour player = YELLOW;
	while(1){
		b.print();
		if(player == YELLOW){
			std::cout << "Yellow player select a column:\n";
		} else {
			std::cout << "Red player select a column:\n";
		}
		int col;
		std::cin >> col;
		// TODO: check error codes
		b.insert_into_column(col, player);
		Colour winner = b.check_win();
		if(winner != NONE){
			b.print();
			if(winner == YELLOW){
				std::cout << "Yellow won!\n";
			} else {
				std::cout << "Red won!\n";
			}
			std::cout << "Press enter to exit...\n";
			char c;
			std::cin >> c;
			return 0;
		}
		if(player == YELLOW){
			player = RED;
		} else {
			player = YELLOW;
		}
	}
	return 0;
}
