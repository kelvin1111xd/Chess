/***********************************************************************
 * File: PieceLabel.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for event of moving piece
***********************************************************************/
#include "PieceLabel.h"
#include "Position.h"
#include "ChessGui.h"
#include "ChessSystem.h"
#include <vector>
#include<iostream>
using namespace std;

// Intent:	set position of piece to position of mouse  
// Pre:		mouse press on piece
// Post:	None
void PieceLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        Position currentPos{ (pos().x() + 50) / 100, (pos().y() + 50) / 100 }; // now position of piece on the checkerboard 
        lastPos = pos(); // now position of piece
        isPressed = true;

        // move center position of piece to now position of mouse 
        QPoint delta(50, 50);
        move(pos() + event->pos() - delta);

        // get valid position that can move to
        vector<Position> validPos = gSystem->movablePos(currentPos);
        gSystem->validPosInCheck(currentPos, validPos);

        // clear movable dots
        gui->clearMovablePlace();

        // set movale dots
        for (auto& it : validPos)
            gui->movablePlace(it);
    }
}
// Intent:	set position of piece to position of mouse 
// Pre:		mouse move
// Post:	None
void PieceLabel::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // move center position of piece to now position of mouse 
        QPoint delta(50, 50);
        move(pos() + event->pos() - delta);
    }
}

// Intent:	set the position of piece to new porsition or original position
// Pre:		mouse relese
// Post:	None
void PieceLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) 
    {
        isPressed = false;
        Position currentPos{ (pos().x() + 50) / 100, (pos().y() + 50) / 100 };  // now position of piece on the checkerboard 

        // movable position of piece on the checkerboard 
        vector<Position> validPos = gSystem->movablePos(Position{ (lastPos.x() + 50) / 100, (lastPos.y() + 50) / 100 });
        gSystem->validPosInCheck(Position{ (lastPos.x() + 50) / 100, (lastPos.y() + 50) / 100 }, validPos);

        // position of place whether is valid 
        bool isCurrentPosValid = false;

        for(const auto& it : validPos)
            if (it.x == currentPos.x && it.y == currentPos.y)
            {
                isCurrentPosValid = true;
                break;
            }

        if (isCurrentPosValid)
        {
            // set position to now position on the checkerboard 
            gSystem->movePiece(gSystem->findPieceByPos(Position{ lastPos.x() / 100, lastPos.y() / 100 }), currentPos);
            move(QPoint(currentPos.x * 100, currentPos.y * 100));
            lastPos = pos(); // set new position is original position

            if (gSystem->getPromo() != PAWN) // if the piece is promoted
            {
                QPixmap newTexture;

                // set the texture of piece to new texture 
                if (gSystem->getTurn() == BLACK)
                {
                    if (gSystem->getPromo() == QUEEN) newTexture.load(".\\texture\\white-queen.png");
                    if (gSystem->getPromo() == ROOK) newTexture.load(".\\texture\\white-rook.png");
                    if (gSystem->getPromo() == KNIGHT) newTexture.load(".\\texture\\white-knight.png");
                    if (gSystem->getPromo() == BISHOP) newTexture.load(".\\texture\\white-bishop.png");
                }
                else
                {
                    if (gSystem->getPromo() == QUEEN) newTexture.load(".\\texture\\black-queen.png");
                    if (gSystem->getPromo() == ROOK) newTexture.load(".\\texture\\black-rook.png");
                    if (gSystem->getPromo() == KNIGHT) newTexture.load(".\\texture\\black-knight.png");
                    if (gSystem->getPromo() == BISHOP) newTexture.load(".\\texture\\black-bishop.png");
                }

                gSystem->setPromo(PAWN); // set no piece promoting
                setPixmap(newTexture);
                update(); // updata label
            }
        }
        else
            move(lastPos); // move to original position

        // delete movable dots
        gui->clearMovablePlace();
    }
}

// Intent:	set label texture back to pawn
// Pre:	    which color of pawn
// Post:	None
void PieceLabel::backToPawn(bool color)
{
    // set to pawn
    QPixmap pawnTexture;

    if (color == WHITE)
        pawnTexture.load(".\\texture\\white-pawn.png");
    else
        pawnTexture.load(".\\texture\\black-pawn.png");
    setPixmap(pawnTexture);
    update();
}