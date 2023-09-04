/***********************************************************************
 * File: Player.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for initial pieces main program header
***********************************************************************/
#pragma once
#include <vector>
#include "Enum.h"
#include "Position.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Pawn.h"

class ChessSystem;

class Player
{
private:
	ChessSystem* gSystem;
	bool color;
	vector<Piece> pieces;
	Position enPassant{ -1, -1 };
	double time = 600;

public:
	// Intent:	defult constructor
	// Pre:		None
	// Post:	None
	Player() : Player(nullptr, WHITE) {};

	// Intent:	setting constructor, initial pieces
	// Pre:		ChessSystem, const value WHITE or BLACK
	// Post:	None
	Player(ChessSystem* gSystem_, const bool& color_);

	// Intent:	get vector of pieces
	// Pre:		None
	// Post:	vector of pieces
	vector<Piece>& getPieces() { return pieces; }

	// Intent:	set timer
	// Pre:		time limit
	// Post:	None
	void setTime(double time_) { time = time_; };

	// Intent:	get timer time
	// Pre:		None
	// Post:	time
	double& getTime() { return time; }

	// Intent:	set position that passant can move
	// Pre:		position
	// Post:	None
	void setPassant(const Position& pos_) { enPassant.x = pos_.x; enPassant.y = pos_.y; }

	// Intent:	get position that passant can move
	// Pre:		None
	// Post:	position
	Position& getPassant() { return enPassant; }
};

