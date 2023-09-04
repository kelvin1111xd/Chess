/***********************************************************************
 * File: Player.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for initial pieces
***********************************************************************/
#include "Player.h"

// Intent:	setting constructor, initial pieces
// Pre:		ChessSystem, const value WHITE or BLACK
// Post:	None
Player::Player(ChessSystem* gSystem_, const bool& color_)
{
	gSystem = gSystem_;
	color = color_;
	int y = 0;

	if (color == WHITE) y = 7; // if color is white, y = 7 

	// set color and position of pieces on the checkerboard
	pieces.push_back(King(4, y, color));
	pieces.push_back(Queen(3, y, color));
	pieces.push_back(Bishop(2, y, color));
	pieces.push_back(Bishop(5, y, color));
	pieces.push_back(Knight(1, y, color));
	pieces.push_back(Knight(6, y, color));
	pieces.push_back(Rook(0, y, color));
	pieces.push_back(Rook(7, y, color));

	for (int i = 0; i < 8; i++)
		if (color == WHITE)
			pieces.push_back(Pawn(i, 6, color));
		else
			pieces.push_back(Pawn(i, 1, color));

	for (auto& it : pieces) // set pieces to this ChessSystem
		it.setSystem(gSystem);
}