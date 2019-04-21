/************************************************************************
* thedjnK's Sentrius Programmer                                         *
* Copyright (C) 2018, thedjnK                                           *
*                                                                       *
* File: main.cpp                                                        *
* Version: 0.01a                                                        *
* Last Updated: 14/11/2018                                              *
*                                                                       *
* Parts of code used in this application come from Laird's UwTerminalX, *
* licensed under the GPLv3 from https://github.com/LairdCP/UwTerminalX  *
*                                                                       *
* License terms are as follows:                                         *
*                                                                       *
* This program is free software: you can redistribute it and/or         *
* modify it under the terms of the GNU General Public License as        *
* published by the Free Software Foundation, version 3.                 *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program.  If not, see http://www.gnu.org/licenses/    *
*                                                                       *
************************************************************************/

//Includes
#include "mainwindow.h"
#include <QApplication>

//Main program entry
int main(int argc, char *argv[])
{
    //Run Qt application
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
