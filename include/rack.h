#ifndef RACK_H
#define RACK_H
#include <array>
#include <vector>

class Tile;

class Rack {
private:
	std::array<Tile*, 7> rack;

public:
	Rack();
	~Rack() {};

	Tile* getTile(char ch);
	std::vector<Tile*> getTileStrVec(std::string tileStr);

	void fill(std::vector<Tile*> t);
	void addTile(Tile* t);
	bool isEmpty();
	void show();
};

#endif
