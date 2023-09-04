/***********************************************************************
 * File: ChessGui.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN
 * Update Date: 2023/05/16
 * Description: This program is for GUI of Chess Game
***********************************************************************/
#include "ChessGui.h"
#include "Player.h"
#include <iostream>
#include <cmath>
using namespace std;

// Intent:	Default constructor
// Pre:		None
// Post:	None
ChessGui::ChessGui()
{
	// set game window
	window.setFixedSize(900, 800);
	window.setWindowTitle("Chess");

	setMenu();
	window.show();
}

// Intent:	set menu of chess game
// Pre:		None
// Post:	None
void ChessGui::setMenu()
{
	// set background of game menu
	QPixmap backGroundTexture(".\\texture\\background.png");
	QLabel* backGround = new QLabel(&window);
	backGround->setPixmap(backGroundTexture);
	backGround->show();

	// set bgm
	QMediaPlayer* bgm = new QMediaPlayer(&window);
	bgm->setMedia(QUrl::fromLocalFile(QString(".\\sound\\bgm.mp3")));
	bgm->setVolume(50);
	bgm->play();

	// set button of start game
	QPushButton* startGame = new QPushButton("Start Game", &window);
	startGame->resize(320, 70);
	startGame->move(500, 495);
	startGame->setStyleSheet("background-color: #685849; color: #180d03; font-size: 45px; border: 1px solid #ececec;");
	startGame->show();

	// set comboBox of game mode
	QComboBox* gameMode = new QComboBox(&window);
	gameMode->resize(320, 70);
	gameMode->move(500, 575);
	gameMode->setStyleSheet("background-color: #685849; color: #180d03; font-size: 45px; border: 1px solid #ececec;");
	gameMode->addItem("     Normal");
	gameMode->addItem("  Time Limited");
	gameMode->show();

	// set SpinBox of game time limit
	QSpinBox* timeLimit = new QSpinBox(&window);
	timeLimit->setValue(10);
	timeLimit->resize(80, 70);
	timeLimit->move(420, 575);
	timeLimit->setStyleSheet("background-color: #685849; color: #180d03; font-size: 45px; border: 1px solid #ececec;");
	timeLimit->setRange(1, 30);
	timeLimit->setSingleStep(1);
	timeLimit->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	timeLimit->show();
	timeLimit->setVisible(false);

	// Intent:	Create different chess system according to the different options selected by the game mode
	// Pre:		if button of start game is clicked
	// Post:	None
	QObject::connect(startGame, &QPushButton::clicked, [&]() 
		{
			// create system
			this->gSystem = new ChessSystem(this);

			// if time limit mode choosen
			if (gameMode->currentIndex() == 1)
			{
				// set info
				this->gSystem->setMode(true);
				this->gSystem->getPlayer(WHITE).setTime(timeLimit->value() * 60);
				this->gSystem->getPlayer(BLACK).setTime(timeLimit->value() * 60);
			}

			// clear current widget and set to game playing gui
			clearWidget();
			setGame();
		});

	// Intent:	Change the objects displayed on the game menu
	// Pre:		if comboBox of index is changed 
	// Post:	None
	QObject::connect(gameMode, QOverload<int>::of(&QComboBox::currentIndexChanged), [&]()
		{
			if(gameMode->currentIndex() == 0)
				timeLimit->setVisible(false);
			else if(gameMode->currentIndex() == 1)
				timeLimit->setVisible(true);
		});
}

// Intent:	set interface of main game
// Pre:		None
// Post:	None
void ChessGui::setGame()
{
	// set background of game
	QPixmap backGroundInGameTexture(".\\texture\\background2.png");
	QLabel* backGroundInGame = new QLabel(&window);
	backGroundInGame->setPixmap(backGroundInGameTexture);
	backGroundInGame->show();

	// set check field
	QPixmap checkTexture(".\\texture\\check.png");
	checkField = new QLabel(&window);
	checkField->resize(100, 100);
	checkField->setPixmap(checkTexture);
	checkField->setVisible(false);

	// set piece label
	auto tmpPlayer = gSystem->getPlayer(WHITE);
	for (auto it : tmpPlayer.getPieces())
		generatePieceLabel(it);

	tmpPlayer = gSystem->getPlayer(BLACK);
	for (auto it : tmpPlayer.getPieces())
		generatePieceLabel(it);

	// set button of resign
	QPixmap resignTexture(".\\texture\\resign.png");
	QIcon resignIcon(resignTexture);
	QPushButton *resignButton = new QPushButton(&window);
	resignButton->resize(90, 90);
	resignButton->move(805, 5);
	resignButton->setIcon(resignIcon);
	resignButton->setIconSize(QSize(90, 90));
	resignButton->show();

	// Intent:	According to which side's turn it is now, show other side wins and end game
	// Pre:		if button of resign is clicked
	// Post:	None
	QObject::connect(resignButton, &QPushButton::clicked, [&]()
		{
			// set diglog box
			QDialog* dialog = new QDialog(&window);
			dialog->setFixedSize(200, 150);

			// set message string
			QString message;
			if (gSystem->getTurn() == WHITE)
				message = "Black Win!";
			else
				message = "White Win!";

			// set label of message box
			QLabel* label = new QLabel(dialog);
			label->setText(message);
			QFont font("Arial", 15);
			label->setFont(font);
			label->move(20, 30);

			// set button of dialog close
			QPushButton* closeButton = new QPushButton("Close", dialog);
			closeButton->resize(60, 40);
			closeButton->move(70, 100);

			// Intent:	close dialog box
			// Pre:		if close button of dialog box is clicked
			// Post:	None
			QObject::connect(closeButton, &QPushButton::clicked, dialog, [&]()
				{
					dialog->close();
				});

			dialog->exec(); // show dialog box

			window.setEnabled(true);

			// reset game
			clearWidget();

			gSystem->reset();
			delete gSystem;

			setMenu();
		});

	// set undo button
	QPixmap undoTexture(".\\texture\\undo.png");
	QIcon undoIcon(undoTexture);
	QPushButton* undoButton = new QPushButton(&window);
	undoButton->resize(90, 90);
	undoButton->move(805, 105);
	undoButton->setIcon(undoIcon);
	undoButton->setIconSize(QSize(90, 90));
	undoButton->show();

	// Intent:	undo game
	// Pre:		if undo button pressed
	// Post:	None
	QObject::connect(undoButton, &QPushButton::clicked, [&]()
		{
			gSystem->undo();
		});

	// set redo button
	QPixmap redoTexture(".\\texture\\redo.png");
	QIcon redoIcon(redoTexture);
	QPushButton* redoButton = new QPushButton(&window);
	redoButton->resize(90, 90);
	redoButton->move(805, 205);
	redoButton->setIcon(redoIcon);
	redoButton->setIconSize(QSize(90, 90));
	redoButton->show();

	// Intent:	redo game
	// Pre:		if undo button pressed
	// Post:	None
	QObject::connect(redoButton, &QPushButton::clicked, [&]()
		{
			gSystem->redo();
		});

	// if game mode is time limted
	if (gSystem->getMode())
	{
		// set timer
		timerWhite = new QLabel(&window);
		timerBlack = new QLabel(&window);

		timerBlack->resize(90, 30);
		timerWhite->resize(90, 30);

		timerBlack->move(805, 315);
		timerWhite->move(805, 455);


		double timeInSec = gSystem->getPlayer(WHITE).getTime();
		double timeInMin = (double)((int)timeInSec / 60);
		timeInSec -= timeInMin * 60;
		timerWhite->setText(QString::number(timeInMin) + ":" + QString::number(timeInSec, 'f', 1));
		timerBlack->setText(QString::number(timeInMin) + ":" + QString::number(timeInSec, 'f', 1));

		timerWhite->show();
		timerBlack->show();

		QTimer* gTimer = new QTimer(&window);

		// run timer each 0.1s
		QObject::connect(gTimer, &QTimer::timeout, [&]() {
			if (gSystem->getTurn() == WHITE)
			{
				gSystem->getPlayer(WHITE).setTime(gSystem->getPlayer(WHITE).getTime() - 0.1f);
				double timeInSec = gSystem->getPlayer(WHITE).getTime();
				double timeInMin = (double)((int)timeInSec / 60);
				timeInSec -= timeInMin * 60;
				timerWhite->setText(QString::number(timeInMin) + ":" + QString::number(timeInSec, 'f', 1));
			}
			else
			{
				gSystem->getPlayer(BLACK).setTime(gSystem->getPlayer(BLACK).getTime() - 0.1f);
				double timeInSec = gSystem->getPlayer(BLACK).getTime();
				double timeInMin = (double)((int)timeInSec / 60);
				timeInSec -= timeInMin * 60;
				timerBlack->setText(QString::number(timeInMin) + ":" + QString::number(timeInSec, 'f', 1));
			}

			double temp = 0.001;

			if (fabs(gSystem->getPlayer(BLACK).getTime() - 55) < temp || fabs(gSystem->getPlayer(WHITE).getTime() - 55) < temp) {
				QDialog* dialog = new QDialog(&window);

				dialog->setFixedSize(200, 150);

				QString message;
				if(gSystem->getPlayer(BLACK).getTime() == 0)
					message = "Time's up\nWhite Win!";
				else
					message = "Time's up\nBlack Win!";

				QLabel* label = new QLabel(dialog);
				label->setText(message);
				QFont font("Arial", 15);
				label->setFont(font);
				label->move(20, 30);

				QPushButton* closeButton = new QPushButton("Close", dialog);

				closeButton->resize(60, 40);
				closeButton->move(70, 100);

				QObject::connect(closeButton, &QPushButton::clicked, dialog, [&]()
					{
						dialog->close();
					});

				dialog->exec();

				window.setEnabled(true);

				// reset game
				clearWidget();

				gSystem->reset();
				delete gSystem;

				setMenu();
			}
			});

		gTimer->setInterval(100);
		gTimer->start();
	}
}


// Intent:	set label of piece and texture of piece
// Pre:		piece
// Post:	None
void ChessGui::generatePieceLabel(Piece& pieceToGenerate)
{
	// set all pieces Image
	QPixmap whitePawnTexture(".\\texture\\white-pawn.png");
	QPixmap whiteKnightTexture(".\\texture\\white-knight.png");
	QPixmap whiteBishopTexture(".\\texture\\white-bishop.png");
	QPixmap whiteRookTexture(".\\texture\\white-rook.png");
	QPixmap whiteQueenTexture(".\\texture\\white-queen.png");
	QPixmap whiteKingTexture(".\\texture\\white-king.png");
	QPixmap blackPawnTexture(".\\texture\\black-pawn.png");
	QPixmap blackKnightTexture(".\\texture\\black-knight.png");
	QPixmap blackBishopTexture(".\\texture\\black-bishop.png");
	QPixmap blackRookTexture(".\\texture\\black-rook.png");
	QPixmap blackQueenTexture(".\\texture\\black-queen.png");
	QPixmap blackKingTexture(".\\texture\\black-king.png");

	Position tmpPos = pieceToGenerate.getPos(); // get position of input piece

	// set piece label
	PieceLabel* tmpLabel = new PieceLabel(&window);
	piecesLabel.push_back(tmpLabel);
	piecesLabel.back()->move(tmpPos.x * 100, tmpPos.y * 100);

	// set texture of piece to label of piece
	if (pieceToGenerate.getColor() == WHITE)
	{
		if (pieceToGenerate.getIcon() == KING)
		{
			piecesLabel.back()->setPixmap(whiteKingTexture);
			piecesLabel.back()->setKing(WHITEKING);
		}
		else if (pieceToGenerate.getIcon() == QUEEN)	piecesLabel.back()->setPixmap(whiteQueenTexture);
		else if (pieceToGenerate.getIcon() == ROOK)		piecesLabel.back()->setPixmap(whiteRookTexture);
		else if (pieceToGenerate.getIcon() == KNIGHT)	piecesLabel.back()->setPixmap(whiteKnightTexture);
		else if (pieceToGenerate.getIcon() == BISHOP)	piecesLabel.back()->setPixmap(whiteBishopTexture);
		else if (pieceToGenerate.getIcon() == PAWN)		piecesLabel.back()->setPixmap(whitePawnTexture);
	}
	else
	{
		if (pieceToGenerate.getIcon() == KING)
		{
			piecesLabel.back()->setPixmap(blackKingTexture);
			piecesLabel.back()->setKing(BLACKKING);
		}
		else if (pieceToGenerate.getIcon() == QUEEN)	piecesLabel.back()->setPixmap(blackQueenTexture);
		else if (pieceToGenerate.getIcon() == ROOK)		piecesLabel.back()->setPixmap(blackRookTexture);
		else if (pieceToGenerate.getIcon() == KNIGHT)	piecesLabel.back()->setPixmap(blackKnightTexture);
		else if (pieceToGenerate.getIcon() == BISHOP)	piecesLabel.back()->setPixmap(blackBishopTexture);
		else if (pieceToGenerate.getIcon() == PAWN)		piecesLabel.back()->setPixmap(blackPawnTexture);
	}
	piecesLabel.back()->setGui(this); // set label of piece to chess gui
	piecesLabel.back()->setSystem(gSystem); // set label of piece to chess system
	piecesLabel.back()->show(); // show label of piece
}

// Intent:	menu of pawn promoting choose
// Pre:		None
// Post:	None
void ChessGui::promoting()
{
	window.setEnabled(false);

	// set dialog box
	QDialog* dialog = new QDialog(&window);
	dialog->setFixedSize(150, 450);

	QButtonGroup* radioGroup = new QButtonGroup(dialog); // radioButton Group

	// create radioButtons
	QRadioButton* radioButton1 = new QRadioButton(dialog);
	QRadioButton* radioButton2 = new QRadioButton(dialog);
	QRadioButton* radioButton3 = new QRadioButton(dialog);
	QRadioButton* radioButton4 = new QRadioButton(dialog);

	// add radioButtons to radioButton Group
	radioGroup->addButton(radioButton1, 1);
	radioGroup->addButton(radioButton2, 2);
	radioGroup->addButton(radioButton3, 3);
	radioGroup->addButton(radioButton4, 4);

	// set size of radioButtons
	radioButton1->resize(20, 20);
	radioButton2->resize(20, 20);
	radioButton3->resize(20, 20);
	radioButton4->resize(20, 20);

	// set position of radioButtons
	radioButton1->move(20, 40);
	radioButton2->move(20, 140);
	radioButton3->move(20, 240);
	radioButton4->move(20, 340);

	// create labels
	QLabel* label1 = new QLabel(dialog);
	QLabel* label2 = new QLabel(dialog);
	QLabel* label3 = new QLabel(dialog);
	QLabel* label4 = new QLabel(dialog);

	// set size of labels
	label1->resize(100, 100);
	label2->resize(100, 100);
	label3->resize(100, 100);
	label4->resize(100, 100);

	// set position of labels
	label1->move(50, 0);
	label2->move(50, 100);
	label3->move(50, 200);
	label4->move(50, 300);

	// create textures
	QPixmap QueenTexture;
	QPixmap RookTexture;
	QPixmap KnightTexture;
	QPixmap BishopTexture;

	// set Images of piece to textures
	if (gSystem->getTurn() == WHITE)
	{
		QueenTexture.load(".\\texture\\white-queen.png");
		RookTexture.load(".\\texture\\white-rook.png");
		KnightTexture.load(".\\texture\\white-knight.png");
		BishopTexture.load(".\\texture\\white-bishop.png");
	}
	else
	{
		QueenTexture.load(".\\texture\\black-queen.png");
		RookTexture.load(".\\texture\\black-rook.png");
		KnightTexture.load(".\\texture\\black-knight.png");
		BishopTexture.load(".\\texture\\black-bishop.png");
	}

	// set textures to labels 
	label1->setPixmap(QueenTexture);
	label2->setPixmap(RookTexture);
	label3->setPixmap(KnightTexture);
	label4->setPixmap(BishopTexture);

	// show labels
	label1->show();
	label2->show();
	label3->show();
	label4->show();

	// set button of choose
	QPushButton* closeButton = new QPushButton("choose", dialog);
	closeButton->resize(60, 40);
	closeButton->move(45, 410);

	// Intent:	change pawn to chosen piece
	// Pre:		if button of choose is clicked
	// Post:	None
	QObject::connect(closeButton, &QPushButton::clicked, dialog, [&]()
		{
			if (radioGroup->checkedId() == 1)
				gSystem->setPromo(QUEEN);  // promote to Queen
			else if (radioGroup->checkedId() == 2)
				gSystem->setPromo(ROOK);   // promote to Rook
			else if (radioGroup->checkedId() == 3)
				gSystem->setPromo(KNIGHT); // promote to Knight
			else if (radioGroup->checkedId() == 4)
				gSystem->setPromo(BISHOP); // promote to Bishop

			dialog->close();
		});

	dialog->exec(); // show dialog box

	window.setEnabled(true);
}

// Intent:	delete all objects on window
// Pre:		None
// Post:	None
void ChessGui::clearWidget()
{
	piecesLabel.clear(); // delete label of pieces

	for (QObject* child : window.children()) // delete all objects on window
		child->deleteLater();
}

// Intent:	delete dots of movable
// Pre:		None
// Post:	None
void ChessGui::clearMovablePlace()
{
	for (auto& it : dot) // delete all dot
		it->deleteLater();
	dot.clear();
}

// Intent:	set dot of movable
// Pre:		movable position
// Post:	None
void ChessGui::movablePlace(Position movablePos)
{
	// set label of movable dot
	QLabel* tmpLabel = new QLabel(&window);
	QPixmap movable(".\\texture\\moveable.png");
	tmpLabel->move(QPoint(movablePos.x * 100, movablePos.y * 100));
	tmpLabel->resize(100, 100);
	tmpLabel->setPixmap(movable);
	tmpLabel->show(); // show movable dot
	dot.push_back(tmpLabel); // add to vector
}

// Intent:	check if check
// Pre:		valid king posiotion
// Post:	make check event if check is valid
void ChessGui::check(Position kingPos)
{
	checkField->move(QPoint(kingPos.x * 100, kingPos.y * 100));
	checkField->setVisible(true);
}

// Intent:	check if uncheck
// Pre:		None
// Post:	uncheck when check over
void ChessGui::uncheck()
{
	checkField->setVisible(false);
}

// Intent:	show game over event
// Pre:		color of who win
// Post:	show victory message and end program
void ChessGui::gameOver(const bool& color_)
{
	// show message
	QDialog* dialog = new QDialog(&window);

	dialog->setFixedSize(200, 150);

	QString message;
	if (color_ == WHITE)
		message = "Checkmate,\nBlack Win!";
	else
		message = "Checkmate,\nWhite Win!";

	QLabel* label = new QLabel(dialog);
	label->setText(message);
	QFont font("Arial", 15);
	label->setFont(font);
	label->move(20, 30);

	// close button
	QPushButton* closeButton = new QPushButton("Close", dialog);

	closeButton->resize(60, 40);
	closeButton->move(70, 100);

	QObject::connect(closeButton, &QPushButton::clicked, dialog, [&]()
		{
			dialog->close();
		});

	dialog->exec();

	window.setEnabled(true);

	// reset game
	clearWidget();

	gSystem->reset();
	delete gSystem;

	setMenu();
}

// Intent:	show draw event
// Pre:		None
// Post:	show draw message and end program
void ChessGui::draw()
{
	// show message
	QDialog* dialog = new QDialog(&window);

	dialog->setFixedSize(200, 150);

	QString message = "Draw";

	QLabel* label = new QLabel(dialog);
	label->setText(message);
	QFont font("Arial", 15);
	label->setFont(font);
	label->move(20, 30);

	// close button
	QPushButton* closeButton = new QPushButton("Close", dialog);

	closeButton->resize(60, 40);
	closeButton->move(70, 100);

	QObject::connect(closeButton, &QPushButton::clicked, dialog, [&]()
		{
			dialog->close();
		});

	dialog->exec();

	window.setEnabled(true);

	// reset game
	clearWidget();

	gSystem->reset();
	delete gSystem;

	setMenu();
}