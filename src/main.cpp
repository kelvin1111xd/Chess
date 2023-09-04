/***********************************************************************
 * File: main.cpp
 * Author: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN 
 * Create Date: 2023/05/16
 * Editor: Kelvin Tan Chen Hao, JHENG YUAN CHEN, YU JIE YUAN 
 * Update Date: 2023/05/16
 * Description: This program is for game of Chess main program
***********************************************************************/
#include "main.h"

// run as Chess.exe : play game by GUI
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChessGui gui; // create chessGui
	return a.exec();
}