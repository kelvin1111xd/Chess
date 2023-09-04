/***********************************************************************
 * File: Bishop.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Bishop
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"

using namespace std;

class Bishop :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    Bishop() {};

    // Intent:	setting constructor, set bishop
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    Bishop(Position pos_, bool color_) { this->pos = pos_; this->icon = BISHOP; this->color = color_; };

    // Intent:	setting constructor, set bishop
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    Bishop(int x, int y, bool color_) : Bishop(Position{ x, y }, color_) {};
};

