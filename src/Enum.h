/***********************************************************************
 * File: Enum.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for put all Enums
***********************************************************************/
#pragma once
enum COLOR
{
	WHITE = true,
	BLACK = false
};

enum State
{
	MENU = 0,
	PLAYING = 1,
	GAMEOVER = 2
};

enum Mode
{
	NORMAL = 0,
	TIMELIMITED = 1
};

enum PieceType
{
	EMPTYSQUARE = ' ',
	KING = 'K',
	QUEEN = 'Q',
	KNIGHT = 'N',
	ROOK = 'R',
	BISHOP = 'B',
	PAWN = 'P',
};

enum KingColor
{
	NOTKING = 0,
	WHITEKING = 1,
	BLACKKING = 2
};