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
		Move_result res;
		do {
			int col;
			std::cin >> col;
			res = b.insert_into_column(col, player);
			if(res == MOVE_OUT_OF_RANGE){
				std::cout << "Please enter a valid column number.\n";
			} else if(res == MOVE_COLUMN_FULL){
				std::cout << "Please select a non-full column.\n";
			} else if(res == MOVE_WIN){
				b.print();
				if(player == YELLOW){
					std::cout << "Yellow won!\n";
				} else {
					std::cout << "Red won!\n";
				}
				return 0;
			}
		}while(res != MOVE_OK);
		if(player == YELLOW){
			player = RED;
		} else {
			player = YELLOW;
		}
	}
	return 0;
}
