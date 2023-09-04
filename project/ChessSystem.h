/***********************************************************************
 * File: ChessSystem.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Chess System main program header
***********************************************************************/
#pragma once
#include <vector>
#include <utility>
#include "Enum.h"
#include "Position.h"
#include "Player.h"
using namespace std;

class ChessGui;
class Piece;

class ChessSystem
{
private:
	ChessGui* gui;
	Player* white;
	Player* black;
	vector<pair<pair<Piece, int>, Position>> log;
	bool gMode = false;
	int logIndex = 0;
	int gState = MENU;
	bool gTurn = WHITE;
	char promo = PAWN;
	bool checkOrNo = false;

public:
	// Intent:	defult constructor
	// Pre:		None
	// Post:	None
	ChessSystem() : ChessSystem(nullptr) {};

	// Intent:	setting constructor, initial the white pieces and black pieces
	// Pre:		ChessGui
	// Post:	None	
	ChessSystem(ChessGui* gui_);

	// Intent:	get ChessGui
	// Pre:		None
	// Post:	gui of chess
	ChessGui* getGui() { return gui; }

	// Intent:	set gMode
	// Pre:		valid mode
	// Post:	None
	void setMode(bool mode_) { gMode = mode_; }

	// Intent:	get mode of game
	// Pre:		None
	// Post:	state of game
	const bool& getMode() { return gMode; }

	// Intent:	get state of game
	// Pre:		None
	// Post:	state of game
	const int& getState() { return gState; }

	// Intent:	set state of game
	// Pre:		state of game
	// Post:	None
	void setState(const int& state) { gState = state; }

	// Intent:	get turn of game
	// Pre:		None
	// Post:	turn of game
	bool getTurn() { return gTurn; }

	// Intent:	set turn of game
	// Pre:		turn of game
	// Post:	None
	void setTurn(const bool& turn_) { gTurn = turn_; }

	// Intent:	get pawn want piece of promoting
	// Pre:		None
	// Post:	piece of promoting
	const char& getPromo() { return promo; }

	// Intent:	set pawn want piece of promoting
	// Pre:		piece of promoting
	// Post:	None
	void setPromo(const char& promo_) { promo = promo_; }

	// Intent:	get the white pieces or the black pieces
	// Pre:		const value WHITE or BLACK
	// Post:	the white pieces or the black pieces
	Player& getPlayer(const bool& color)
	{
		if (color == WHITE)
			return *white;
		else
			return *black;
	}

	// Intent:	get check or no of game
	// Pre:		None
	// Post:	if check return true, else false;
	const bool& getCheckOrNo() { return checkOrNo; }

	// Intent:	get king position
	// Pre:		which color of king
	// Post:	king position
	Position getKingPos(const bool& color);

	// Intent:	get the position on the checkerboard whether exists white pieces or whether exists black pieces
	// Pre:		const value WHITE or BLACK
	// Post:	bool quadratic vector
	vector<vector<bool>> piecesExist(const bool& color);

	// Intent:	get positions of the piece movable
	// Pre:		current position of piece
	// Post:	position vector
	vector<Position> movablePos(const Position& currentPos);

	// Intent:	get domain of a player
	// Pre:		which player of domain
	// Post:	player's domain
	vector<Position> getDomain(const bool& color);

	// Intent:	get piece of position on the checkerboard 
	// Pre:		position
	// Post:	piece
	Piece& findPieceByPos(const Position& pos_);

	// Intent:	move piece
	// Pre:		piece, position of purpose
	// Post:	None
	void movePiece(Piece& pieceToMove, const Position& purpose);

	// Intent:	move piece without adding log
	// Pre:		piece, position of purpose
	// Post:	None
	void movePieceWithoutLog(Piece& pieceToMove, const Position& purpose);

	// Intent:	renew log
	// Pre:		None
	// Post:	None
	void newLog();

	// Intent:	check if check
	// Pre:		None
	// Post:	make check event if check is valid
	void check();

	// Intent:	check valid position that can move if actually valid that dont cause check
	// Pre:		piece which want to move, that valid position want to check
	// Post:	make valid position more valid
	void validPosInCheck(const Position& movingPiece, vector<Position>& validPos);

	// Intent:	check if game over
	// Pre:		None
	// Post:	make game over event
	void checkGameOver();

	// Intent:	reset game
	// Pre:		None
	// Post:	None
	void reset();

	// Intent:	do undo
	// Pre:		None
	// Post:	None
	void undo();

	// Intent:	do redo
	// Pre:		None
	// Post:	None
	void redo();
};

