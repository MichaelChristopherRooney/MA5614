#include "grid.h"

int main(void){
	Grid *g = new Grid();
	g->print();
	g->update();
	g->print();
	g->update();
	g->print();
	delete(g);
	return 0;
}
