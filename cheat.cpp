/**
* \file cheat.cpp
* \brief cheat class definition
*
*  TODO
*\author Bilal Natafgi
*\date 22-3-2018
*/
#include "cheat.h"
#include "ui_cheat.h"

cheat::cheat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cheat)
{
    ui->setupUi(this);
}

cheat::~cheat()
{
    delete ui;
}
