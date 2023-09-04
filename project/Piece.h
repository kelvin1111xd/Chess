/***********************************************************************
 * File: Piece.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for positions of piece movable system main program header
***********************************************************************/
#pragma once
#include <vector>
#include "Position.h"
#include "Enum.h"
using namespace std;

class ChessSystem;

class Piece
{
protected:
	ChessSystem* gSystem;
	Position pos;
	char icon;
	bool color = WHITE;
	bool moved = false;

public:
	// Intent:	set ChessSystem
	// Pre:		ChessSystem
	// Post:	None
	void setSystem(ChessSystem* gSystem_) { gSystem = gSystem_; }

	// Intent:	get ChessSystem
	// Pre:		None
	// Post:	ChessSystem
	ChessSystem* getSystem() { return gSystem; }

	// Intent:	get position
	// Pre:		None
	// Post:	position
	const Position& getPos() { return pos; }

	// Intent:	set position
	// Pre:		position
	// Post:	None
	void setPos(Position pos_)
	{
		pos.x = pos_.x;
		pos.y = pos_.y;
	}

	// Intent:	get icon
	// Pre:		None
	// Post:	const value of icon
	const char getIcon() { return icon; }

	// Intent:	set icon
	// Pre:		const value of icon
	// Post:	None
	void setIcon(char icon_) { icon = icon_; }

	// Intent:	get chess color
	// Pre:		None
	// Post:	const value WHITE or BLACK
	const bool& getColor() { return color; }

	// Intent:	get piece moved or no
	// Pre:		None
	// Post:	moved
	const bool& getMoved() { return moved; }

	// Intent:	set moved piece if it's move
	// Pre:		None
	// Post:	None
	void setMoved() { moved = true; }

	// Intent:	get valid position where can move
	// Pre:		None
	// Post:	None
	vector<Position> validPos();
};

