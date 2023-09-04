/********************************************************************************
** Form generated from reading UI file 'ChessGui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSGUI_H
#define UI_CHESSGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessGuiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChessGuiClass)
    {
        if (ChessGuiClass->objectName().isEmpty())
            ChessGuiClass->setObjectName(QString::fromUtf8("ChessGuiClass"));
        ChessGuiClass->resize(600, 400);
        menuBar = new QMenuBar(ChessGuiClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ChessGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChessGuiClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChessGuiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChessGuiClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ChessGuiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChessGuiClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChessGuiClass->setStatusBar(statusBar);

        retranslateUi(ChessGuiClass);

        QMetaObject::connectSlotsByName(ChessGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChessGuiClass)
    {
        ChessGuiClass->setWindowTitle(QCoreApplication::translate("ChessGuiClass", "ChessGui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessGuiClass: public Ui_ChessGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSGUI_H
