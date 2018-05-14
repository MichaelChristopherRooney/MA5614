#include "grid.h"

int main(void){
	Grid *g = new Grid();
	g->print();
	g->update(0);
	g->print();
	g->update(1);
	delete(g);
	return 0;
}
