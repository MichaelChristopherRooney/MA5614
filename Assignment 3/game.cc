#include "board.h"

int main(void){
	Board b;
	b.print();
	b.insert_into_column(0, YELLOW);
	b.print();
	b.insert_into_column(0, RED);
	b.print();
	b.insert_into_column(0, YELLOW);
	b.print();
	b.insert_into_column(0, RED);
	b.print();
	return 0;
}
