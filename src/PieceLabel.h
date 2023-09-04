/***********************************************************************
 * File: PieceLabel.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for event of moving piece main program header
***********************************************************************/
#pragma once
#include <QtWidgets>
#include <QEvent>
#include <QtCore/QPoint>
#include <QLabel>
#include <vector>
#include "Enum.h"
using namespace std;

class ChessGui;
class ChessSystem;

class PieceLabel :
    public QLabel
{
private:
    ChessGui *gui = nullptr;
    ChessSystem* gSystem = nullptr;
    QPoint lastPos;
    bool isPressed = false;
    int isKing = NOTKING;

public:
    // Intent:	Default constructor
    // Pre:		None
    // Post:	None
    PieceLabel() {}

    // Intent:	setting constructor
    // Pre:		QWidget
    // Post:	None
    PieceLabel(QWidget* parent = 0) : QLabel(parent) {}

    // Intent:	set ChessGui to this
    // Pre:	    ChessGui
    // Post:	None
    void setGui(ChessGui* gui_) { gui = gui_; }

    // Intent:	set ChessSystem to this
    // Pre:	    ChessSystem
    // Post:	None
    void setSystem(ChessSystem* gSystem_) { gSystem = gSystem_; }

    // Intent:	set if this piece label is a king
    // Pre:	    king's color
    // Post:	None
    void setKing(const int& kingColor) { isKing = kingColor; }

    // Intent:	get true if this piece label is a king
    // Pre:	    None
    // Post:	if is king return true, else false
    const int& getKing() { return isKing; }

    // Intent:	set label texture back to pawn
    // Pre:	    which color of pawn
    // Post:	None
    void backToPawn(bool color);

protected:
    // Intent:	set position of piece to position of mouse  
        // Pre:		mouse press on piece
        // Post:	None
    void mousePressEvent(QMouseEvent* event);

    // Intent:	set position of piece to position of mouse 
    // Pre:		mouse move
    // Post:	None
    void mouseMoveEvent(QMouseEvent* event);

    // Intent:	set the position of piece to new porsition or original position
    // Pre:		mouse relese
    // Post:	None
    void mouseReleaseEvent(QMouseEvent* event);
};

