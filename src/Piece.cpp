/***********************************************************************
 * File: Piece.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for positions of piece movable system
***********************************************************************/
#include "Piece.h"
#include "ChessSystem.h"
#include "Player.h"
#include "Position.h"
#include "Enum.h"
#include <vector>
#include <iostream>
using namespace std;

// Intent:	get movable positions of the piece
// Pre:		None
// Post:	movable positions of the piece
vector<Position> Piece::validPos()
{
	// save movable positions of the piece
	vector<Position> tmpPos;

	// moving piece's color is valid in this turn
	if (gSystem->getTurn() == color)
	{
		// get where have pieces of on the checkerboard
		vector<vector<bool>> piecesExist = gSystem->piecesExist(color);
		vector<vector<bool>> enemyExist = gSystem->piecesExist(!color);


		if (icon == KING) // if is King
		{
			// move around
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					if (!(i == 0 && j == 0) && pos.x + i >= 0 && pos.x + i < 8 && pos.y + j >= 0 && pos.y + j < 8)
					{
						if (!piecesExist[pos.y + j][pos.x + i]) // if there have no same team of piece
							tmpPos.push_back(Position{ pos.x + i ,pos.y + j });
					}

			// if haven't move, check if can do castling
			if (!moved)
			{
				if (color == WHITE) // check white
				{
					// king side castling
					if (!piecesExist[7][5] && !piecesExist[7][6] && !gSystem->getCheckOrNo()) // moving place have no piece
					{
						// check there is not enemy domain
						Player ply = gSystem->getPlayer(WHITE);

						for(auto& it : ply.getPieces())
							if (it.icon == ROOK && !it.getMoved() && it.getPos().x == 7 && it.getPos().y == 7)
							{
								gSystem->setTurn(BLACK);
								vector<Position> domain = gSystem->getDomain(BLACK);
								gSystem->setTurn(WHITE);

								bool valid = true;
								for(auto& it : domain)
									if (it.y == 7 && (it.x == 5 || it.x == 6))
									{
										valid = false;
										break;
									}

								// if is valid
								if(valid)
									tmpPos.push_back(Position{ 6, 7 });
							}
					}

					// queen side castling
					if (!piecesExist[7][2] && !piecesExist[7][3] && !gSystem->getCheckOrNo()) // moving place have no piece
					{
						// check there is not enemy domain
						Player ply = gSystem->getPlayer(WHITE);

						for (auto& it : ply.getPieces())
							if (it.icon == ROOK && !it.getMoved() && it.getPos().x == 0 && it.getPos().y == 7)
							{
								gSystem->setTurn(BLACK);
								vector<Position> domain = gSystem->getDomain(BLACK);
								gSystem->setTurn(WHITE);

								bool valid = true;
								for (auto& it : domain)
									if (it.y == 7 && (it.x == 2 || it.x == 3))
									{
										valid = false;
										break;
									}

								// if is valid
								if (valid)
									tmpPos.push_back(Position{ 2, 7 });
							}
					}
				}
				else  // check black
				{
					if (!piecesExist[0][5] && !piecesExist[0][6] && !gSystem->getCheckOrNo()) // moving place have no piece
					{
						// check there is not enemy domain
						Player ply = gSystem->getPlayer(BLACK);

						for (auto& it : ply.getPieces())
							if (it.icon == ROOK && !it.getMoved() && it.getPos().x == 7 && it.getPos().y == 0)
							{
								gSystem->setTurn(WHITE);
								vector<Position> domain = gSystem->getDomain(WHITE);
								gSystem->setTurn(BLACK);

								bool valid = true;
								for (auto& it : domain)
									if (it.y == 0 && (it.x == 5 || it.x == 6))
									{
										valid = false;
										break;
									}

								// if is valid
								if (valid)
									tmpPos.push_back(Position{ 6, 0 });
							}
					}

					// queen side castling
					if (!piecesExist[0][2] && !piecesExist[0][3] && !gSystem->getCheckOrNo()) // moving place have no piece
					{
						// check there is not enemy domain
						Player ply = gSystem->getPlayer(BLACK);

						for (auto& it : ply.getPieces())
							if (it.icon == ROOK && !it.getMoved() && it.getPos().x == 0 && it.getPos().y == 0)
							{
								gSystem->setTurn(WHITE);
								vector<Position> domain = gSystem->getDomain(WHITE);
								gSystem->setTurn(BLACK);

								bool valid = true;
								for (auto& it : domain)
									if (it.y == 0 && (it.x == 2 || it.x == 3))
									{
										valid = false;
										break;
									}
								
								// if is valid
								if (valid)
									tmpPos.push_back(Position{ 2, 0 });
							}
					}
				}
			}
		}
		else if (icon == QUEEN) // if is queen
		{
			// set four direct movable
			bool direct[4] = { true, true, true, true };

			// set straight line of four directions
			for (int i = 1; i < 8; i++)
			{
				if (pos.x + i >= 0 && pos.x + i < 8 && direct[0])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y][pos.x + i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x + i ,pos.y });

						if (enemyExist[pos.y][pos.x + i])
							direct[0] = false;
					}
					else
						direct[0] = false;
				}

				if (pos.y - i >= 0 && pos.y - i < 8 && direct[1])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y - i][pos.x])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x ,pos.y - i });

						if (enemyExist[pos.y - i][pos.x])
							direct[1] = false;
					}
					else
						direct[1] = false;
				}

				if (pos.y + i >= 0 && pos.y + i < 8 && direct[2])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y + i][pos.x])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x ,pos.y + i });

						if (enemyExist[pos.y + i][pos.x])
							direct[2] = false;
					}
					else
						direct[2] = false;
				}

				if (pos.x - i >= 0 && pos.x - i < 8 && direct[3])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y][pos.x - i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x - i ,pos.y });

						if (enemyExist[pos.y][pos.x - i])
							direct[3] = false;
					}
					else
						direct[3] = false;
				}
			}
			// initial four directions
			for (int i = 0; i < 4; i++) direct[i] = true;

			// set diagonal line of four directions
			for (int i = 1; i < 8; i++)
			{
				if (pos.x + i >= 0 && pos.x + i < 8 && pos.y + i >= 0 && pos.y + i < 8 && direct[0])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y + i][pos.x + i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x + i ,pos.y + i });

						if (enemyExist[pos.y + i][pos.x + i])
							direct[0] = false;
					}
					else
						direct[0] = false;
				}

				if (pos.x + i >= 0 && pos.x + i < 8 && pos.y - i >= 0 && pos.y - i < 8 && direct[1])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y - i][pos.x + i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x + i ,pos.y - i });

						if (enemyExist[pos.y - i][pos.x + i])
							direct[1] = false;
					}
					else
						direct[1] = false;
				}

				if (pos.x - i >= 0 && pos.x - i < 8 && pos.y + i >= 0 && pos.y + i < 8 && direct[2])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y + i][pos.x - i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x - i ,pos.y + i });

						if (enemyExist[pos.y + i][pos.x - i])
							direct[2] = false;
					}
					else
						direct[2] = false;
				}

				if (pos.x - i >= 0 && pos.x - i < 8 && pos.y - i >= 0 && pos.y - i < 8 && direct[3])
				{
					// if the position no exist piece of our side
					if (!piecesExist[pos.y - i][pos.x - i])
					{
						// if encounter the piece of enemy, set the position after this direction cannot go
						tmpPos.push_back(Position{ pos.x - i ,pos.y - i });

						if (enemyExist[pos.y - i][pos.x - i])
							direct[3] = false;
					}
					else
						direct[3] = false;
				}
			}
		}
		else if (icon == BISHOP) // if is bishop
		{
			bool direct[4] = { true, true, true, true }; // set four sides movable

			// set diagonal line of four directions
			for (int i = 1; i < 8; i++)
			{
				if (pos.x + i >= 0 && pos.x + i < 8 && pos.y + i >= 0 && pos.y + i < 8 && direct[0])
				{
					if (!piecesExist[pos.y + i][pos.x + i]) // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x + i ,pos.y + i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y + i][pos.x + i])
							direct[0] = false;
					}
					else
						direct[0] = false;
				}
				if (pos.x + i >= 0 && pos.x + i < 8 && pos.y - i >= 0 && pos.y - i < 8 && direct[1])
				{
					if (!piecesExist[pos.y - i][pos.x + i]) // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x + i ,pos.y - i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y - i][pos.x + i])
							direct[1] = false;
					}
					else
						direct[1] = false;
				}
				if (pos.x - i >= 0 && pos.x - i < 8 && pos.y + i >= 0 && pos.y + i < 8 && direct[2])
				{
					if (!piecesExist[pos.y + i][pos.x - i]) // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x - i ,pos.y + i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y + i][pos.x - i])
							direct[2] = false;
					}
					else
						direct[2] = false;
				}
				if (pos.x - i >= 0 && pos.x - i < 8 && pos.y - i >= 0 && pos.y - i < 8 && direct[3])
				{
					if (!piecesExist[pos.y - i][pos.x - i])  // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x - i ,pos.y - i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y - i][pos.x - i])
							direct[3] = false;
					}
					else
						direct[3] = false;
				}
			}
		}
		else if (icon == ROOK)
		{
			bool direct[4] = { true ,true ,true ,true };  // set four sides movable

			// set straight line of four directions
			for (int i = 1; i < 8; i++)
			{
				if (pos.x + i >= 0 && pos.x + i < 8 && direct[0])
				{
					if (!piecesExist[pos.y][pos.x + i]) // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x + i ,pos.y });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y][pos.x + i])
							direct[0] = false;
					}
					else
						direct[0] = false;
				}
				if (pos.y - i >= 0 && pos.y - i < 8 && direct[1])
				{
					if (!piecesExist[pos.y - i][pos.x]) // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x ,pos.y - i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y - i][pos.x])
							direct[1] = false;
					}
					else
						direct[1] = false;
				}
				if (pos.y + i >= 0 && pos.y + i < 8 && direct[2])
				{
					if (!piecesExist[pos.y + i][pos.x])  // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x ,pos.y + i });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y + i][pos.x])
							direct[2] = false;
					}
					else
						direct[2] = false;
				}
				if (pos.x - i >= 0 && pos.x - i < 8 && direct[3])
				{
					if (!piecesExist[pos.y][pos.x - i])  // if the position no exist piece of our side
					{
						tmpPos.push_back(Position{ pos.x - i ,pos.y });

						// if encounter the piece of enemy, set the position after this direction cannot go
						if (enemyExist[pos.y][pos.x - i])
							direct[3] = false;
					}
					else
						direct[3] = false;
				}
			}
		}
		else if (icon == KNIGHT)
		{
			if (pos.x + 2 >= 0 && pos.x + 2 < 8 && pos.y + 1 >= 0 && pos.y + 1 < 8)
				if (!piecesExist[pos.y + 1][pos.x + 2])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x + 2 ,pos.y + 1 });

			if (pos.x + 1 >= 0 && pos.x + 1 < 8 && pos.y + 2 >= 0 && pos.y + 2 < 8)
				if (!piecesExist[pos.y + 2][pos.x + 1])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x + 1 ,pos.y + 2 });

			if (pos.x - 1 >= 0 && pos.x - 1 < 8 && pos.y + 2 >= 0 && pos.y + 2 < 8)
				if (!piecesExist[pos.y + 2][pos.x - 1])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x - 1 ,pos.y + 2 });

			if (pos.x - 2 >= 0 && pos.x - 2 < 8 && pos.y + 1 >= 0 && pos.y + 1 < 8)
				if (!piecesExist[pos.y + 1][pos.x - 2])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x - 2 ,pos.y + 1 });

			if (pos.x - 2 >= 0 && pos.x - 2 < 8 && pos.y - 1 >= 0 && pos.y - 1 < 8)
				if (!piecesExist[pos.y - 1][pos.x - 2])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x - 2 ,pos.y - 1 });

			if (pos.x + 1 >= 0 && pos.x + 1 < 8 && pos.y - 2 >= 0 && pos.y - 2 < 8)
				if (!piecesExist[pos.y - 2][pos.x + 1])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x + 1 ,pos.y - 2 });

			if (pos.x - 1 >= 0 && pos.x - 1 < 8 && pos.y - 2 >= 0 && pos.y - 2 < 8)
				if (!piecesExist[pos.y - 2][pos.x - 1])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x - 1 ,pos.y - 2 });

			if (pos.x + 2 >= 0 && pos.x + 2 < 8 && pos.y - 1 >= 0 && pos.y - 1 < 8)
				if (!piecesExist[pos.y - 1][pos.x + 2])  // if the position no exist piece of our side
					tmpPos.push_back(Position{ pos.x + 2 ,pos.y - 1 });
		}
		else if (icon == PAWN)
		{
			if (color == WHITE) // if is white pawn
			{
				if (pos.y - 1 >= 0 && pos.y - 1 < 8)
					if (!(piecesExist[pos.y - 1][pos.x] || enemyExist[pos.y - 1][pos.x])) // if the position no exist piece of enemy and our side
						tmpPos.push_back(Position{ pos.x ,pos.y - 1 });

				if (pos.y == 6 && !(piecesExist[pos.y - 1][pos.x] || enemyExist[pos.y - 1][pos.x]) // if white pawn in the starting point
					&& !(piecesExist[pos.y - 2][pos.x] || enemyExist[pos.y - 2][pos.x]))
					tmpPos.push_back(Position{ pos.x, pos.y - 2 });

				if (pos.y - 1 >= 0 && pos.y - 1 < 8 && pos.x - 1 >= 0 && pos.x - 1 < 8) // left front of pawn
					if(enemyExist[pos.y - 1][pos.x - 1]) // if exist piece of ememy
						tmpPos.push_back(Position{ pos.x - 1, pos.y - 1 });

				if (pos.y - 1 >= 0 && pos.y - 1 < 8 && pos.x + 1 >= 0 && pos.x + 1 < 8) // right front of pawn
					if (enemyExist[pos.y - 1][pos.x + 1])  // if exist piece of ememy
						tmpPos.push_back(Position{ pos.x + 1, pos.y - 1 });

				Player tmpPlayer = gSystem->getPlayer(!color);

				// if passant is exist
				if (tmpPlayer.getPassant().x != -1 && tmpPlayer.getPassant().y != -1)
				{
					if (tmpPlayer.getPassant().y == pos.y - 1 && (tmpPlayer.getPassant().x - 1 == pos.x
						|| tmpPlayer.getPassant().x + 1 == pos.x)) // if at right front or left front of our side pawn
						tmpPos.push_back(tmpPlayer.getPassant());
				}
			}
			else // if is black pawn
			{
				if (pos.y + 1 >= 0 && pos.y + 1 < 8)
					if (!(piecesExist[pos.y + 1][pos.x] || enemyExist[pos.y + 1][pos.x])) // if the position no exist piece of enemy and our side
						tmpPos.push_back(Position{ pos.x ,pos.y + 1 });

				if (pos.y == 1 && !(piecesExist[pos.y + 1][pos.x] || enemyExist[pos.y + 1][pos.x]) // if white pawn in the starting point
					&& !(piecesExist[pos.y + 2][pos.x] || enemyExist[pos.y + 2][pos.x])) 
					tmpPos.push_back(Position{ pos.x, pos.y + 2 });

				if (pos.y + 1 >= 0 && pos.y + 1 < 8 && pos.x - 1 >= 0 && pos.x - 1 < 8) // left behind of pawn
					if (enemyExist[pos.y + 1][pos.x - 1])
						tmpPos.push_back(Position{ pos.x - 1, pos.y + 1 });

				if (pos.y + 1 >= 0 && pos.y + 1 < 8 && pos.x + 1 >= 0 && pos.x + 1 < 8)  // right behind of pawn
					if (enemyExist[pos.y + 1][pos.x + 1])
						tmpPos.push_back(Position{ pos.x + 1, pos.y + 1 });

				Player tmpPlayer = gSystem->getPlayer(!color);

				// if passant is exist
				if (tmpPlayer.getPassant().x != -1 && tmpPlayer.getPassant().y != -1)
					if (tmpPlayer.getPassant().y == pos.y + 1 && (tmpPlayer.getPassant().x - 1 == pos.x
						|| tmpPlayer.getPassant().x + 1 == pos.x)) // if at right behind or left behind of our side pawn
						tmpPos.push_back(tmpPlayer.getPassant());
			}
		}
	}
	return tmpPos;
}