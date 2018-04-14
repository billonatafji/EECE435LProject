/**
* \file description.cpp
* \brief Description class definition
*
*
*\author Bilal Natafgi
*\date 21-3-2018
*/
#include "description.h"
#include "ui_description.h"

Description::Description(QWidget *parent, QString game) :
    QDialog(parent),
    ui(new Ui::Description)
{
    ui->setupUi(this);
    this->Game = game;

    ui->descriptionLabel->setText(QString("<h1>Description of %1</h1>").arg(this->Game));
}

Description::~Description()
{
    delete ui;
}

void Description::on_backButton_clicked()
{
    this->close();
}
