#include <iostream>
#include "player.h"
#include "board.h"
#include "tile.h"
#include "rack.h"

using namespace std;

Board::Board()
{
	enum_sqType quarterBoard[7][7] = {
		{ TWS, N  , N  , DWS, N  , N  , N   },
		{ N  , DWS, N  , N  , N  , TLS, N   },
		{ N  , N  , DWS, N  , N  , N  , DLS },
		{ DLS, N  , N  , DWS, N  , N  , N   },
		{ N  , N  , N  , N  , DWS, N  , N   },
		{ N  , TLS, N  , N  , N  , TLS, N   },
		{ N  , N  , DLS, N  , N  , N  , DLS }
	};

	enum_sqType strip[7] = {TWS, N, N, DLS, N, N, N};

	sqStrings = {"   ", "DWS", "TWS", "DLS", "TLS"};

	// Top Left quarter
	for(int i = 0; i < NUM_ROWS/2; i++) {
		for(int j = 0; j < NUM_COLS/2; j++) {
			board[i][j] = new Square(quarterBoard[i][j], i, j);
		}
	}

	// Top Right quarter
	for(int i = 0; i < NUM_ROWS/2; i++) {
		for(int j = 0; j < NUM_COLS/2; j++) {
			int j2 = NUM_COLS - 1 - j;
			board[i][j2] = new Square(quarterBoard[i][j], i, j2);
		}
	}

	// Bottom Left quarter
	for(int i = 0; i < NUM_ROWS/2; i++) {
		for(int j = 0; j < NUM_COLS/2; j++) {
			int i2 = NUM_ROWS - 1 - i;
			board[i2][j] = new Square(quarterBoard[i][j], i2, j);
		}
	}

	// Bottom Right quarter
	for(int i = 0; i < NUM_ROWS/2; i++) {
		for(int j = 0; j < NUM_COLS/2; j++) {
			int i2 = NUM_ROWS - 1 - i;
			int j2 = NUM_COLS - 1 - j;
			board[i2][j2] = new Square(quarterBoard[i][j], i2, j2);
		}
	}

	// Vertical strips
	for(int j = 0; j < NUM_COLS/2; j++) {
		board[NUM_ROWS/2][j] = new Square(strip[j], j, NUM_ROWS/2);
	}

	for(int j = NUM_COLS - 1; j > NUM_COLS/2; j--) {
		board[NUM_ROWS/2][j] = new Square(strip[NUM_COLS - 1 - j], j, NUM_ROWS/2);
	}

	// Horizontal strips
	for(int j = 0; j < NUM_ROWS/2; j++) {
		board[j][NUM_COLS/2] = new Square(strip[j], NUM_COLS/2, j);
	}

	for(int j = NUM_ROWS - 1; j > NUM_ROWS/2; j--) {
		board[j][NUM_COLS/2] = new Square(strip[NUM_ROWS - 1 - j], NUM_COLS/2, j);
	}

	// Center
	board[7][7] = new Square(quarterBoard[1][1], 7, 7);

	// Set neighbours
	Square* currSquare = nullptr;
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			currSquare = board[i][j];
			if(j - 1 > -1) {
				currSquare->setLeft(board[i][j - 1]);
			}
			if(j + 1 < NUM_COLS) {
				currSquare->setRight(board[i][j + 1]);
			}
			if(i - 1 > -1) {
				currSquare->setAbove(board[i - 1][j]);
			}
			if(i + 1 < NUM_ROWS) {
				currSquare->setBelow(board[i + 1][j]);
			}
		}
	}
}

Board::~Board()
{
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			delete board[i][j];
		}
	}
}

void Board::show()
{
	string toPrint;
	Square* currSquare;


	cout << "                                   "; // 35 spaces
	for(int k = 0; k < NUM_COLS; k++) {
		BOLD_BROWN("+-----");
	}

	BOLD_BROWN("+");
	cout << "\n";

	for(int i = 0; i < NUM_ROWS; i++) {
		if(i < 10) {
			BOLD_WHITE("                                 " + to_string(i) + " ");
		}
		else {
			BOLD_WHITE("                                " + to_string(i) + " ");
		}

		BOLD_BROWN("| ");
		for(int j = 0; j < NUM_COLS; j++) {
			toPrint = "   ";
			currSquare = board[i][j];
			if(currSquare->isEmpty()) {
				if(i == 7 && j == 7) {
					BOLD_PINK("");
				}
				else {
					toPrint = sqStrings[currSquare->getType()];
					switch(currSquare->getType()) {
					case 0:
						cout << toPrint;
						break;
					case 1:
						BOLD_PINK(toPrint);
						break;
					case 2:
						BOLD_ORANGE(toPrint);
						break;
					case 3:
						BOLD_CYAN(toPrint);
						break;
					case 4:
						BOLD_BLUE(toPrint);
						break;
					}
				}
			}
			else {
				toPrint = " " + currSquare->getTile()->getLetterStr() + " ";
				BOLD_WHITE(toPrint);
			}
			BOLD_BROWN(" | ");
		}
		cout << "\n";
		cout << "                                   ";
		for(int k = 0; k < NUM_COLS; k++) {
			BOLD_BROWN("+-----");
		}

		BOLD_BROWN("+");
		cout << "\n";
	}

	BOLD_WHITE("                                      0   ");
	for(int k = 1; k < NUM_COLS; k++)
		if(k < 10) {
			BOLD_WHITE("  " + to_string(k) + "   ");
		}
		else {
			BOLD_WHITE(" " + to_string(k) + "   ");
		}
	cout << "\n\n";
}

void Board::showDebug()
{
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			cout << "(" << i << "," << j << ")" << "-";
			board[i][j]->show();
			cout << "   ";
		}
		cout << "\n";
	}
	cout << "\n";
}

bool Board::placeTile(Tile* t, int r, int c)
{
	if(r < 0 || r > NUM_ROWS - 1) {
		throw string("Invalid row number\n");
	}
	else if (c < 0 || c > NUM_COLS - 1) {
		throw string("Invalid column number\n");
	}
	else {
		Square* curr = board[r][c];
		if(curr->isEmpty()) {
			curr->setTile(t);
			t->setSquare(curr);
			t->setLoc(2);
			return true;
		}
		else {
			return false;
		}
	}
}

void Board::placeTileStr(Rack* rack, vector<Tile*> tilesInStr, int r, int c, char dir)
{
	auto it = tilesInStr.begin();
	int currRow = r;
	int currCol = c;
	vector<Tile*> placed;
	try {
		while(it != tilesInStr.end()) {
			if(dir == 'h') {
				if(placeTile(*it, currRow, currCol++)) {
					placed.push_back(*it);
					it++;
				}
			}
			else if(dir == 'v') {
				if(placeTile(*it, currRow++, currCol)) {
					placed.push_back(*it);
					it++;
				}
			}
		}
	}
	catch(string err) {
		int currRow = r;
		int currCol = c;
		if(dir == 'h') {
			for(int i = 0; i < placed.size(); i++) {
				rack->addTile(retrieve(currRow, currCol++));
			}
		}
		else if(dir == 'v') {
			for(int i = 0; i < placed.size(); i++) {
				rack->addTile(retrieve(currRow++, currCol));
			}
		}
		for(int i = placed.size(); i < tilesInStr.size(); i ++) {
			rack->addTile(tilesInStr[i]);
		}
		throw(err + " Because some of the tiles won't fit on the board\n");
	}
}

Tile* Board::retrieve(int r, int c)
{
	Tile* t = nullptr;
	if(!board[r][c]->isEmpty()) {
		t = board[r][c]->getTile();
		board[r][c]->setTile(nullptr);
	}
	return t;
}

Square* Board::getSquare(int r, int c)
{
	if(r > -1 && r < NUM_ROWS && c > -1 && c < NUM_COLS) {
		return board[r][c];
	}
	else {
		return nullptr;
	}
}
