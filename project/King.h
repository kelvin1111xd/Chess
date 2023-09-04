/***********************************************************************
 * File: King.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for King
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"

using namespace std;

class King :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    King() {};

    // Intent:	setting constructor, set king
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    King(Position pos_, bool color_) { this->pos = pos_; this->icon = KING; this->color = color_; };

    // Intent:	setting constructor, set king
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    King(int x, int y, bool color_) : King(Position{ x, y }, color_) {};
};

