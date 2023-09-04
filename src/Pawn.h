/***********************************************************************
 * File: Pawn.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Pawn
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"

using namespace std;

class Pawn :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    Pawn() {};

    // Intent:	setting constructor, set pawn
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    Pawn(Position pos_, bool color_) { this->pos = pos_; this->icon = PAWN; this->color = color_; };

    // Intent:	setting constructor, set pawn
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    Pawn(int x, int y, bool color_) : Pawn(Position{ x, y }, color_) {};
};

