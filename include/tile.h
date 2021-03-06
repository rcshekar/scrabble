#ifndef TILE_H
#define TILE_H
#include <string>

class Bag;
class Rack;
class Square;

enum enum_location {BAG, RACK, BOARD};

class Tile {
private:
	Square* tSquare;
	char letter;
	int points;
	Bag* tBag;
	Rack* tRack;
	enum_location presentLoc;

public:
	Tile(char l, int p, enum_location p_loc);
	Tile(Tile& source);
	~Tile() {}

	char getLetter();
	std::string getLetterStr();
	int getPoints();
	int getLoc();
	Rack* getRack();
	Bag* getBag();
	Square* getSquare();

	void setLoc(int loc);
	void setBag(Bag* b);
	void setRack(Rack* r);
	void setSquare(Square* s);
	void show();

};

#endif
