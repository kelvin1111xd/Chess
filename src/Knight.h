/***********************************************************************
 * File: Knight.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Knight
***********************************************************************/
#pragma once
#include <vector>
#include "Piece.h"

using namespace std;

class Knight :
    public Piece
{
public:
    // Intent:	defult constructor
    // Pre:		None
    // Post:	None
    Knight() {};

    // Intent:	setting constructor, set knight
    // Pre:		position of piece, const value WHITE or BLACK
    // Post:	None
    Knight(Position pos_, bool color_) { this->pos = pos_; this->icon = KNIGHT; this->color = color_; };

    // Intent:	setting constructor, set knight
    // Pre:		x coordinate and y coordinate of piece, const value WHITE or BLACK
    // Post:	None
    Knight(int x, int y, bool color_) : Knight(Position{ x, y }, color_) {};
};

