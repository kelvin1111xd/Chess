/***********************************************************************
 * File: Queen.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Queen
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"
using namespace std;

class Queen :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    Queen() {};

    // Intent:	setting constructor, set queen
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    Queen(Position pos_, bool color_) { this->pos = pos_; this->icon = QUEEN; this->color = color_; };

    // Intent:	setting constructor, set queen
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    Queen(int x, int y, bool color_) : Queen(Position{ x, y }, color_) {};
};

