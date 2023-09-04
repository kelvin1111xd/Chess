/***********************************************************************
 * File: ChessGui.h
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for GUI of Chess Game main program header
***********************************************************************/
#pragma once

#include <QApplication>
#include <QtWidgets>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSpinBox>
#include <QPixmap>
#include <QDialog>
#include <QString>
#include <QFont>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <vector>
#include "Position.h"
#include "Enum.h"
#include "PieceLabel.h"
#include "ChessSystem.h"
#include <QIcon>
#include "main.h"
using namespace std;

class Piece;

class ChessGui
{
private:
	QWidget window;
	ChessSystem* gSystem;
	vector<PieceLabel*> piecesLabel;
	vector<QLabel*> dot;
	QLabel* checkField;
	QLabel* timerWhite;
	QLabel* timerBlack;

public:
	ChessGui();

	// Intent:	return Pieceslabel vector
	// Pre:		None
	// Post:	vector of PiecesLabel
	vector<PieceLabel*>& getPiecesLabel() { return piecesLabel; };

	// Intent:	set menu of chess game
	// Pre:		None
	// Post:	None
	void setMenu();

	// Intent:	set interface of main game
	// Pre:		None
	// Post:	None
	void setGame();

	// Intent:	delete all objects on window
	// Pre:		None
	// Post:	None
	void clearWidget();

	// Intent:	menu of pawn promoting choose
	// Pre:		None
	// Post:	set system promo
	void promoting();

	// Intent:	set label of piece and texture of piece
	// Pre:		piece
	// Post:	None
	void generatePieceLabel(Piece& pieceToGenerate);

	// Intent:	delete dots of movable
	// Pre:		None
	// Post:	None
	void clearMovablePlace();

	// Intent:	set dot of movable
	// Pre:		movable position
	// Post:	None
	void movablePlace(Position movablePos);

	// Intent:	check if check
	// Pre:		valid king posiotion
	// Post:	make check event if check is valid
	void check(Position kingPos);

	// Intent:	check if uncheck
	// Pre:		None
	// Post:	uncheck when check over
	void uncheck();

	// Intent:	show game over event
	// Pre:		color of who win
	// Post:	show victory message and end program
	void gameOver(const bool& color_);

	// Intent:	show draw event
	// Pre:		None
	// Post:	show draw message and end program
	void draw();
};
