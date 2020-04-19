#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "bag.h"
#include "tile.h"
#include "utils.h"

using namespace std;

enum_location loc = BAG;

Bag::Bag()
{
	Tile* curTile = nullptr;
	/* Add a's */
	for(int i = 0; i < 9; i++){
		curTile = new Tile('a', 1, loc);
		bag.push_back(curTile);
	}

	/* Add b's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('b', 3, loc);
		bag.push_back(curTile);
	}

	/* Add c's */	
	for(int i = 0; i < 2; i++){
		curTile = new Tile('c', 3, loc);
		bag.push_back(curTile);
	}

	/* Add d's */
	for(int i = 0; i < 4; i++){
		curTile = new Tile('d', 2, loc);
		bag.push_back(curTile);
	}

	/* Add e's */
	for(int i = 0; i < 12; i++){
		curTile = new Tile('e', 1, loc);
		bag.push_back(curTile);
	}

	/* Add f's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('f', 4, loc);
		bag.push_back(curTile);
	}

	/* Add g's */
	for(int i = 0; i < 3; i++){
		curTile = new Tile('g', 2, loc);
		bag.push_back(curTile);
	}

	/* Add h's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('h', 4, loc);
		bag.push_back(curTile);
	}

	/* Add i's */
	for(int i = 0; i < 9; i++){
		curTile = new Tile('i', 1, loc);
		bag.push_back(curTile);
	}

	/* Add j */
	curTile = new Tile('j', 8, loc);
	bag.push_back(curTile);

	/* Add k */
	curTile = new Tile('k', 5, loc);
	bag.push_back(curTile);

	/* Add l's */
	for(int i = 0; i < 4; i++){
		curTile = new Tile('l', 1, loc);
		bag.push_back(curTile);
	}

	/* Add m's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('m', 3, loc);
		bag.push_back(curTile);
	}

	/* Add n's */
	for(int i = 0; i < 6; i++){
		curTile = new Tile('n', 1, loc);
		bag.push_back(curTile);
	}

	/* Add o's */
	for(int i = 0; i < 8; i++){
		curTile = new Tile('o', 1, loc);
		bag.push_back(curTile);
	}

	/* Add p's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('p', 3, loc);
		bag.push_back(curTile);
	}

	/* Add q */
	curTile = new Tile('q', 10, loc);
	bag.push_back(curTile);

	/* Add r's */
	for(int i = 0; i < 6; i++){
		curTile = new Tile('r', 1, loc);
		bag.push_back(curTile);
	}

	/* Add s's */
	for(int i = 0; i < 4; i++){
		curTile = new Tile('s', 1, loc);
		bag.push_back(curTile);
	}

	/* Add t's */
	for(int i = 0; i < 6; i++){
		curTile = new Tile('t', 1, loc);
		bag.push_back(curTile);
	}

	/* Add u's */
	for(int i = 0; i < 4; i++){
		curTile = new Tile('u', 3, loc);
		bag.push_back(curTile);
	}

	/* Add v's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('v', 4, loc);
		bag.push_back(curTile);
	}

	/* Add w's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('w', 4, loc);
		bag.push_back(curTile);
	}
	/* Add x */
	curTile = new Tile('x', 8, loc);
	bag.push_back(curTile);

	/* Add y's */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('y', 4, loc);
		bag.push_back(curTile);
	}

	/* Add z */
	curTile = new Tile('z', 10, loc);
	bag.push_back(curTile);

	/* Add ?'s */
	for(int i = 0; i < 2; i++){
		curTile = new Tile('?', 0, loc);
		bag.push_back(curTile);
	}
}

Bag::~Bag()
{
	for(Tile* t : bag)
		delete t;

	bag.clear();
}

void Bag::show()
{
	for(Tile* i : bag)
		cout << i->getLetter();
	cout << endl;
}

void Bag::shuffle()
{
	int j;
	Tile* temp = nullptr;
	srand(time(NULL));

	for(int i = 0; i < bag.size(); i++){
		j = rand() % bag.size();
		temp = bag[i];
		bag[i] = bag[j];
		bag[j] = temp;
	}

}

vector<Tile*> Bag::draw(int count)
{
	vector<Tile*> drawn;
	int prev_size = bag.size();
	
	shuffle();

	for(int i = 0; i < count && i < prev_size; i++){
		drawn.push_back(bag.back());
		bag.pop_back();
	}
	return drawn;
}


