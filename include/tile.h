#ifndef TILE_H
#define TILE_H

class Bag;
class Rack;

enum enum_location {BAG , RACK, BOARD};

class Tile {
	private:
		// square*, bag*, rack*
		char letter;
		int points;
		Bag* myBag;
		Rack* myRack;
		enum_location presentLoc;

	public:
		Tile(char l, int p, enum_location p_loc);
		Tile(Tile& source);
		~Tile(){}

		char getLetter();
		int getPoints();
		int getLoc();
		void setBag(Bag* b);
		void setRack(Rack* r);
		void show();

};

#endif
