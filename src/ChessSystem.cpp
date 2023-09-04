/***********************************************************************
 * File: ChessSystem.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for Chess System
***********************************************************************/
#include "ChessSystem.h"
#include "ChessGui.h"
#include "Player.h"
#include "Piece.h"
#include "Position.h"
#include <iostream>
using namespace std;

// Intent:	compare two positions whether is equal
// Pre:		two positions
// Post:	is two position equal 
bool operator==(const Position& lhs, const Position& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

// Intent:	compare two positions whether is not equal
// Pre:		two positions
// Post:	is two position not equal 
bool operator!=(const Position& lhs, const Position& rhs)
{
	return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

// Intent:	setting constructor, initial the white pieces and black pieces
// Pre:		ChessGui
// Post:	None
ChessSystem::ChessSystem(ChessGui* gui_)
{
	gui = gui_;
	white = new Player(this, WHITE); // initial all white pieces
	black = new Player(this, BLACK); // initial all black pieces
}

// Intent:	get king position
// Pre:		which color of king
// Post:	king position
Position ChessSystem::getKingPos(const bool& color)
{
	// find king
	Player* checkPlayer;
	if (color == WHITE)
		checkPlayer = white;
	else
		checkPlayer = black;
	Position kingPos;
	for (auto& it : checkPlayer->getPieces())
		if (it.getIcon() == KING)
			// get position
			kingPos = it.getPos();
	return kingPos;
}

// Intent:	get the position on the checkerboard whether exists white pieces or whether exists black pieces
// Pre:		const value WHITE or BLACK
// Post:	bool quadratic vector
vector<vector<bool>> ChessSystem::piecesExist(const bool& color)
{
	Player* tmpPlayer;

	// get white or black pieces
	if (color == WHITE)
		tmpPlayer = white;
	else
		tmpPlayer = black;

	vector<vector<bool>> exist(8);

	for (int i = 0; i < 8; i++) // initial bool quadratic vector
		for (int j = 0; j < 8; j++)
			exist[i].push_back(false);

	// get position of pieces and set correspond position of vector to true
	for (auto& it : tmpPlayer->getPieces())
		if (it.getPos().x != -1)
			exist[it.getPos().y][it.getPos().x] = true;

	return exist;
}

// Intent:	get positions of the piece movable
// Pre:		current position of piece
// Post:	position vector
vector<Position> ChessSystem::movablePos(const Position& currentPos)
{
	vector<Position> result;
	result = findPieceByPos(currentPos).validPos(); // get piece of current position movable position 

	return result;
}

// Intent:	renew log
// Pre:		None
// Post:	None
void ChessSystem::newLog()
{
	if (logIndex != log.size())
		log.erase(log.begin() + logIndex, log.end());
}

// Intent:	get domain of a player
// Pre:		which player of domain
// Post:	player's domain
vector<Position> ChessSystem::getDomain(const bool& color)
{
	// save result
	vector<Position> result;

	// get player
	Player* tmpPlayer;
	if (color == WHITE)
		tmpPlayer = white;
	else
		tmpPlayer = black;

	// run all the the piece
	for (auto& it : tmpPlayer->getPieces())
	{
		vector<Position> temp;

		if (it.getPos().x == -1)
			continue;

		// if piece is not pawn
		if (it.getIcon() != PAWN)
		{
			temp = it.validPos();
		}
		else // if piece is pawn
		{
			if (color == WHITE)
			{
				temp.push_back(Position{ it.getPos().x + 1, it.getPos().y - 1 });
				temp.push_back(Position{ it.getPos().x - 1, it.getPos().y - 1 });
			}
			else
			{
				temp.push_back(Position{ it.getPos().x + 1, it.getPos().y + 1 });
				temp.push_back(Position{ it.getPos().x - 1, it.getPos().y + 1 });
			}
		}

		for (auto pos : temp)
		{
			result.push_back(pos);
		}
	}
	return result;
}


// Intent:	get piece of position on the checkerboard 
// Pre:		position
// Post:	piece
Piece& ChessSystem::findPieceByPos(const Position& pos_)
{
	// find piece of position from white pieces
	for (auto& it : white->getPieces())
		if (it.getPos() == pos_)
			return it;

	// find piece of position from black pieces
	for (auto& it : black->getPieces())
		if (it.getPos() == pos_)
			return it;
}

// Intent:	move piece
// Pre:		piece, position of purpose
// Post:	None
void ChessSystem::movePiece(Piece& pieceToMove, const Position& purpose)
{
	// renew log
	newLog();

	// Get the pieces of the input piece color
	Player* tmpPlayer;

	if (pieceToMove.getColor() == WHITE)
		tmpPlayer = black;
	else
		tmpPlayer = white;

	// if piece is Pawn, and move two spaces at first
	if (pieceToMove.getColor() == WHITE && pieceToMove.getIcon() == PAWN)
	{
		if (pieceToMove.getPos().y == 6 && purpose.y == 4)
			white->setPassant(Position{ purpose.x , 5 }); // Set passant is the position behind the purpose position
	}
	else if (pieceToMove.getColor() == BLACK && pieceToMove.getIcon() == PAWN)
	{
		if (pieceToMove.getPos().y == 1 && purpose.y == 3)
			black->setPassant(Position{ purpose.x , 2 }); // Set passant is the position behind the purpose position
	}

	// if position of passant is valid and input piece move to the position
	if (tmpPlayer->getPassant().x != -1 && tmpPlayer->getPassant().y != -1)
	{
		if (tmpPlayer->getPassant().x == purpose.x && tmpPlayer->getPassant().y == purpose.y)
		{
			for (auto it = tmpPlayer->getPieces().begin(); it < tmpPlayer->getPieces().end(); it++)
				if (pieceToMove.getColor() == WHITE)
				{
					// If there is a enemy piece behind the position of passant, delete that enemy piece
					if (it->getPos().x == purpose.x && it->getPos().y == purpose.y + 1)
					{
						for (int i = 0; i < gui->getPiecesLabel().size(); i++)
							if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
								&& gui->getPiecesLabel()[i]->pos().y() == (purpose.y + 1) * 100)
							{
								// delete the enemy piece from labels of peice
								gui->getPiecesLabel()[i]->deleteLater();
								gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
							}
						
						// input log
						log.push_back(make_pair(make_pair(*it, 1), Position{-1, -1}));
						logIndex++;

						tmpPlayer->getPieces().erase(it); // delete the enemy piece from peices
					}
				}
				else
				{
					// If there is a enemy piece behind the position of passant, delete that enemy piece
					if (it->getPos().x == purpose.x && it->getPos().y == purpose.y - 1)
					{
						for (int i = 0; i < gui->getPiecesLabel().size(); i++)
							if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
								&& gui->getPiecesLabel()[i]->pos().y() == (purpose.y - 1) * 100)
							{
								// delete the enemy piece from labels of peice
								gui->getPiecesLabel()[i]->deleteLater();
								gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
							}

						// input log
						log.push_back(make_pair(make_pair(*it, 1), Position{ -1, -1 }));
						logIndex++;

						tmpPlayer->getPieces().erase(it); // delete the enemy piece from peices
					}
				}
		}
		tmpPlayer->setPassant(Position{ -1, -1 }); // set no position of passant
	}

	// if moving piece is king and move castling
	// white king side castling
	if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 6 && purpose.y == 7)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 700 && it->pos().y() == 700)
				it->move(QPoint(500, 700));

		// move piece
		for (auto& it : white->getPieces())
			if (it.getPos().x == 7 && it.getPos().y == 7)
			{
				// update log
				Piece it_ = it;
				log.push_back(make_pair(make_pair(it_, 2), Position{ 5, 7 }));
				logIndex++;

				it.setPos(Position{ 5, 7 });
			}
	}
	// white queen side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 2 && purpose.y == 7)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 0 && it->pos().y() == 700)
				it->move(QPoint(300, 700));

		// move piece
		for (auto& it : white->getPieces())
			if (it.getPos().x == 0 && it.getPos().y == 7)
			{
				// update log
				Piece it_ = it;
				log.push_back(make_pair(make_pair(it_, 2), Position{ 3, 7 }));
				logIndex++;

				it.setPos(Position{ 3, 7 });
			}
	}
	// black king side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 6 && purpose.y == 0)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 700 && it->pos().y() == 0)
				it->move(QPoint(500, 0));

		// move piece
		for (auto& it : black->getPieces())
			if (it.getPos().x == 7 && it.getPos().y == 0)
			{
				// update log
				Piece it_ = it;
				log.push_back(make_pair(make_pair(it_, 2), Position{ 5, 0 }));
				logIndex++;

				it.setPos(Position{ 5, 0 });
			}
	}
	// black queen side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 2 && purpose.y == 0)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 0 && it->pos().y() == 0)
				it->move(QPoint(300, 0));

		// move piece
		for (auto& it : black->getPieces())
			if (it.getPos().x == 0 && it.getPos().y == 0)
			{
				// update log
				Piece it_ = it;
				log.push_back(make_pair(make_pair(it_, 2), Position{ 3, 0 }));
				logIndex++;

				it.setPos(Position{ 3, 0 });
			}
	}

	// if postion of purpose have piece of enemy, delete the enemy piece
	for(auto it = tmpPlayer->getPieces().begin(); it < tmpPlayer->getPieces().end(); it++)
		if (it->getPos().x == purpose.x && it->getPos().y == purpose.y)
		{
			for (int i = 0; i < gui->getPiecesLabel().size(); i++)
				if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
					&& gui->getPiecesLabel()[i]->pos().y() == purpose.y * 100)
				{
					// delete the enemy piece from labels of peice
					gui->getPiecesLabel()[i]->deleteLater();
					gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
				}

			// update log
			log.push_back(make_pair(make_pair(*it, 1), Position{ -1, -1 }));
			logIndex++;

			// delete the enemy piece from peices
			tmpPlayer->getPieces().erase(it);
		}

	// if is that Pawn move to the last row, conduct the promoting event 
	if (pieceToMove.getIcon() == PAWN && ((pieceToMove.getColor() == WHITE && purpose.y == 0)
		|| (pieceToMove.getColor() == BLACK && purpose.y == 7)))
	{
		gui->promoting();
		Piece pCopy = pieceToMove;

		// update log
		log.push_back(make_pair(make_pair(pCopy, 3), Position{ -1, -1 }));
		logIndex++;
		pieceToMove.setIcon(promo);
	}

	// update log
	Piece pCopy = pieceToMove;
	log.push_back(make_pair(make_pair(pCopy, 0), purpose));
	logIndex++;

	// set position of piece to position of purpose
	pieceToMove.setPos(purpose);

	// set to moved
	pieceToMove.setMoved();

	// change turn
	if (gTurn) gTurn = false;
	else gTurn = true;
	
	// if check, uncheck
	if (checkOrNo)
	{
		checkOrNo = false;
		gui->uncheck();
	}

	// check if check or game over
	check();
	checkGameOver();
}

void ChessSystem::movePieceWithoutLog(Piece& pieceToMove, const Position& purpose)
{
	// Get the pieces of the input piece color
	Player* tmpPlayer;

	if (pieceToMove.getColor() == WHITE)
		tmpPlayer = black;
	else
		tmpPlayer = white;

	// if piece is Pawn, and move two spaces at first
	if (pieceToMove.getColor() == WHITE && pieceToMove.getIcon() == PAWN)
	{
		if (pieceToMove.getPos().y == 6 && purpose.y == 4)
			white->setPassant(Position{ purpose.x , 5 }); // Set passant is the position behind the purpose position
	}
	else if (pieceToMove.getColor() == BLACK && pieceToMove.getIcon() == PAWN)
	{
		if (pieceToMove.getPos().y == 1 && purpose.y == 3)
			black->setPassant(Position{ purpose.x , 2 }); // Set passant is the position behind the purpose position
	}

	// if position of passant is valid and input piece move to the position
	if (tmpPlayer->getPassant().x != -1 && tmpPlayer->getPassant().y != -1)
	{
		if (tmpPlayer->getPassant().x == purpose.x && tmpPlayer->getPassant().y == purpose.y)
		{
			for (auto it = tmpPlayer->getPieces().begin(); it < tmpPlayer->getPieces().end(); it++)
				if (pieceToMove.getColor() == WHITE)
				{
					// If there is a enemy piece behind the position of passant, delete that enemy piece
					if (it->getPos().x == purpose.x && it->getPos().y == purpose.y + 1)
					{
						for (int i = 0; i < gui->getPiecesLabel().size(); i++)
							if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
								&& gui->getPiecesLabel()[i]->pos().y() == (purpose.y + 1) * 100)
							{
								// delete the enemy piece from labels of peice
								gui->getPiecesLabel()[i]->deleteLater();
								gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
							}
						tmpPlayer->getPieces().erase(it); // delete the enemy piece from peices
					}
				}
				else
				{
					// If there is a enemy piece behind the position of passant, delete that enemy piece
					if (it->getPos().x == purpose.x && it->getPos().y == purpose.y - 1)
					{
						for (int i = 0; i < gui->getPiecesLabel().size(); i++)
							if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
								&& gui->getPiecesLabel()[i]->pos().y() == (purpose.y - 1) * 100)
							{
								// delete the enemy piece from labels of peice
								gui->getPiecesLabel()[i]->deleteLater();
								gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
							}

						tmpPlayer->getPieces().erase(it); // delete the enemy piece from peices
					}
				}
		}
		tmpPlayer->setPassant(Position{ -1, -1 }); // set no position of passant
	}

	// if moving piece is king and move castling
	// white king side castling
	if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 6 && purpose.y == 7)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 700 && it->pos().y() == 700)
				it->move(QPoint(500, 700));

		// move piece
		for (auto& it : white->getPieces())
			if (it.getPos().x == 7 && it.getPos().y == 7)
			{
				it.setPos(Position{ 5, 7 });
			}
	}
	// white queen side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 2 && purpose.y == 7)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 0 && it->pos().y() == 700)
				it->move(QPoint(300, 700));

		// move piece
		for (auto& it : white->getPieces())
			if (it.getPos().x == 0 && it.getPos().y == 7)
			{
				it.setPos(Position{ 3, 7 });
			}
	}
	// black king side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 6 && purpose.y == 0)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 700 && it->pos().y() == 0)
				it->move(QPoint(500, 0));

		// move piece
		for (auto& it : black->getPieces())
			if (it.getPos().x == 7 && it.getPos().y == 0)
			{
				it.setPos(Position{ 5, 0 });
			}
	}
	// black queen side castling
	else if (pieceToMove.getIcon() == KING && !pieceToMove.getMoved() && purpose.x == 2 && purpose.y == 0)
	{
		// move label
		for (auto& it : gui->getPiecesLabel())
			if (it->pos().x() == 0 && it->pos().y() == 0)
				it->move(QPoint(300, 0));

		// move piece
		for (auto& it : black->getPieces())
			if (it.getPos().x == 0 && it.getPos().y == 0)
			{
				it.setPos(Position{ 3, 0 });
			}
	}

	// if postion of purpose have piece of enemy, delete the enemy piece
	for (auto it = tmpPlayer->getPieces().begin(); it < tmpPlayer->getPieces().end(); it++)
		if (it->getPos().x == purpose.x && it->getPos().y == purpose.y)
		{
			for (int i = 0; i < gui->getPiecesLabel().size(); i++)
				if (gui->getPiecesLabel()[i]->pos().x() == purpose.x * 100
					&& gui->getPiecesLabel()[i]->pos().y() == purpose.y * 100)
				{
					// delete the enemy piece from labels of peice
					gui->getPiecesLabel()[i]->deleteLater();
					gui->getPiecesLabel().erase(gui->getPiecesLabel().begin() + i);
				}
			// delete the enemy piece from peices
			tmpPlayer->getPieces().erase(it);
		}

	// if is that Pawn move to the last row, conduct the promoting event 
	if (pieceToMove.getIcon() == PAWN && ((pieceToMove.getColor() == WHITE && purpose.y == 0)
		|| (pieceToMove.getColor() == BLACK && purpose.y == 7)))
	{
		gui->promoting();
		Piece pCopy = pieceToMove;
	}

	// set position of piece to position of purpose
	pieceToMove.setPos(purpose);

	// set to moved
	pieceToMove.setMoved();

	// change turn
	if (gTurn) gTurn = false;
	else gTurn = true;

	// if check, uncheck
	if (checkOrNo)
	{
		checkOrNo = false;
		gui->uncheck();
	}
}

// Intent:	check if check
// Pre:		None
// Post:	make check event if check is valid
void ChessSystem::check()
{
	// get domain
	gTurn = !gTurn;
	vector<Position> domain = getDomain(gTurn);
	gTurn = !gTurn;

	// if king in enemy domain, check
	Position kingPos = getKingPos(gTurn);
	for(auto& it : domain)
		if (kingPos == it)
		{
			checkOrNo = true;

			gui->check(kingPos);

			break;
		}
}

// Intent:	check valid position that can move if actually valid that dont cause check
// Pre:		piece which want to move, that valid position want to check
// Post:	make valid position more valid
void ChessSystem::validPosInCheck(const Position& movingPiecePos, vector<Position>& validPos)
{
	// save result
	vector<Position> result;

	// check each valid position
	for (auto it : validPos)
	{
		// get player
		Player* movingPlayer;
		Player* enemyPlayer;

		if (gTurn == WHITE)
		{
			movingPlayer = white;
			enemyPlayer = black;
		}
		else
		{
			movingPlayer = black;
			enemyPlayer = white;
		}

		// simulate when moving piece to the valid position
		// eat when there a enemy piece
		Piece* tmpPiece = nullptr;
		for (auto& piece : enemyPlayer->getPieces())
			if (piece.getPos().x == it.x && piece.getPos().y == it.y)
			{
				tmpPiece = &piece;
				break;
			}
		if (tmpPiece != nullptr) tmpPiece->setPos(Position{ -1, -1 });
		
		// move piece
		Piece* movingPiece;
		for(auto& piece : movingPlayer->getPieces())
			if (piece.getPos().x == movingPiecePos.x && piece.getPos().y == movingPiecePos.y)
			{
				movingPiece = &piece;
				break;
			}
		movingPiece->setPos(it);

		// get king position
		Position kingPos;
		for (auto& piece : movingPlayer->getPieces())
			if (piece.getIcon() == KING)
				kingPos = piece.getPos();
		
		// get domain
		gTurn = !gTurn;
		vector<Position> domain = getDomain(gTurn);
		gTurn = !gTurn;

		// if king in enemy domain, is a invalid position
		bool isValid = true;
		for(auto& pos : domain)
			if (pos.x == kingPos.x && pos.y == kingPos.y)
			{
				isValid = false;
				break;
			}

		// if is valid, take it
		if (isValid) result.push_back(it);

		// back to before simulate
		if(tmpPiece != nullptr) tmpPiece->setPos(it);
		movingPiece->setPos(movingPiecePos);
	}

	// set the new valid position
	validPos = result;
}

// Intent:	check if game over
// Pre:		None
// Post:	make game over event
void ChessSystem::checkGameOver()
{
	// get player
	Player* moveNowPlayer;
	if (gTurn == WHITE)
		moveNowPlayer = white;
	else
		moveNowPlayer = black;

	// find valid position that can move to
	bool valid = false;
	for (auto it : moveNowPlayer->getPieces())
	{
		vector<Position> temp = it.validPos();
		validPosInCheck(it.getPos(), temp);

		if (temp.size() > 0)
		{
			valid = true;
			break;
		}
	}

	// if there have no valid position, gameover
	if (!valid)
	{
		if (checkOrNo) // if in check, a player win
		{
			gui->gameOver(gTurn);
		}
		else // if no, draw
		{
			gui->draw();
		}
	}
	
}

// Intent:	reset game
// Pre:		None
// Post:	None
void ChessSystem::reset()
{
	delete white;
	delete black;
}

// Intent:	do undo
// Pre:		None
// Post:	None
void ChessSystem::undo()
{
	// when log can do undo
	if (logIndex > 0)
	{
		// undo move
		gTurn = !gTurn;

		// get player
		Player* tmpPlayer;
		Player* tmpEnemyPlayer;
		if (log[logIndex - 1].first.first.getColor() == WHITE)
		{
			tmpPlayer = white;
			tmpEnemyPlayer = black;
		}
		else
		{
			tmpPlayer = black;
			tmpEnemyPlayer = white;

		}

		// when the move is normal move
		if (log[logIndex - 1].first.second == 0)
		{
			for (auto& it : tmpPlayer->getPieces())
			{
				if (it.getPos() == log[logIndex - 1].second)
				{
					// move label
					for (auto& it_ : gui->getPiecesLabel())
						if (it_->pos().x() == log[logIndex - 1].second.x * 100 && it_->pos().y() == log[logIndex - 1].second.y * 100)
							it_->move(QPoint(log[logIndex - 1].first.first.getPos().x * 100, log[logIndex - 1].first.first.getPos().y * 100));
					
					// move piece
					it = log[logIndex - 1].first.first;
				}
			}
			logIndex--;

			// if eated, regenerate the piece
			if (log[logIndex - 1].first.second == 1)
			{
				tmpEnemyPlayer->getPieces().push_back(log[logIndex - 1].first.first);
				gui->generatePieceLabel(log[logIndex - 1].first.first);
				logIndex--;
			}

			// if castling, move back the rook
			if (log[logIndex - 1].first.second == 2)
			{
				for (auto& it : tmpPlayer->getPieces())
				{
					if (it.getPos() == log[logIndex - 1].second)
					{
						// move label
						for (auto& it_ : gui->getPiecesLabel())
							if (it_->pos().x() == log[logIndex - 1].second.x * 100 && it_->pos().y() == log[logIndex - 1].second.y * 100)
								it_->move(QPoint(log[logIndex - 1].first.first.getPos().x * 100, log[logIndex - 1].first.first.getPos().y * 100));
						
						// move piece
						it = log[logIndex - 1].first.first;
					}
				}
				logIndex--;
			}
		}
		// if the move is promoting
		else if (log[logIndex - 1].first.second == 3)
		{
			for (auto& it : tmpPlayer->getPieces())
			{
				if (it.getPos() == log[logIndex - 1].second)
				{
					for (auto& it_ : gui->getPiecesLabel())
						if (it_->pos().x() == log[logIndex - 1].second.x * 100 && it_->pos().y() == log[logIndex - 1].second.y * 100)
						{
							// move back
							it_->backToPawn(log[logIndex - 1].first.first.getColor());
							it_->move(QPoint(log[logIndex - 1].first.first.getPos().x * 100, log[logIndex - 1].first.first.getPos().y * 100));
						}
					
					// set back icon
					it.setIcon(PAWN);
					it = log[logIndex - 1].first.first;
				}
			}
		}
	}
}

// Intent:	do redo
// Pre:		None
// Post:	None
void ChessSystem::redo()
{
	// if log can do redo
	if (logIndex < log.size())
	{
		if (logIndex < log.size())
		{
			// if eated
			if (log[logIndex].first.second == 1)
			{
				logIndex++;
			}

			// if castling
			if (log[logIndex].first.second == 2)
			{

				logIndex++;
			}
		}

		// get player
		Player* tmpPlayer;
		Player* tmpEnemyPlayer;
		if (log[logIndex].first.first.getColor() == WHITE)
		{
			tmpPlayer = white;
			tmpEnemyPlayer = black;
		}
		else
		{
			tmpPlayer = black;
			tmpEnemyPlayer = white;

		}

		// if move is a normal move
		if (log[logIndex].first.second == 0)
		{
			for (auto& it : tmpPlayer->getPieces())
			{
				if (it.getPos() == log[logIndex].first.first.getPos())
				{
					// save position
					Position temp = log[logIndex].first.first.getPos();

					// move piece
					movePieceWithoutLog(it, log[logIndex].second);

					for (auto& it_ : gui->getPiecesLabel())
						if (it_->pos().x() == temp.x * 100 && it_->pos().y() == temp.y * 100)
							// move label
						{
							it_->move(QPoint(log[logIndex].second.x * 100, log[logIndex].second.y * 100));
						}
				}
			}
			logIndex++;
		}
	}
}