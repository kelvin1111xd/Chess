/***********************************************************************
 * File: Rook.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Rook
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"
using namespace std;

class Rook :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    Rook() {};

    // Intent:	setting constructor, set rook
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    Rook(Position pos_, bool color_) { this->pos = pos_; this->icon = ROOK; this->color = color_; };

    // Intent:	setting constructor, set rock
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    Rook(int x, int y, bool color_) : Rook(Position{ x, y }, color_) {};
};

