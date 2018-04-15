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

#include "game1.h"

Description::Description(QWidget *parent, QString game) :
    QDialog(parent),
    ui(new Ui::Description)
{
    ui->setupUi(this);
    this->Game = game;

    ui->descriptionLabel->setText(QString("<h1>Description of %1</h1>").arg(this->Game));
    if(this->Game == Game1::name)
       { ui->textBrowser->setText(QString("<p style=\"text-align: center;\"><em>in this game, your main objetive is to stay clean the tank from all bacteria, while staying away from the bacteria that harms you.</em></p>\
                                    <p style=\"text-align: center;\">you will find a cleanness bar on the left of the screen, and an immunity level meter on the right.</p>\
                                   <p style=\"text-align: center;\">the cleanness bar indicates the cleanness of the tank,<strong> and you win the game when it reaches 100%.</strong></p>\
                                   <p style=\"text-align: center;\">your immunity level increases when you collide with a healthy item ( fruits, sports, vegitables...), and decreases when you collide with unhealty items ( cigarettes, junk food...)</p>\
                                   <p style=\"text-align: center;\">you should clean the tank before the timer ends or <strong>you lose the game</strong>.</p>\
                                   <p style=\"text-align: center;\"><strong>harder levels unlock</strong> when you get higher scores.</p>\
                                   <p style=\"text-align: center;\">harder levels have new difficulties that will <strong>reveal themselves.</strong></p>"));
        }
    else
    {
        ui->textBrowser->setText(QString("<p style=\"text-align: center;\"><strong><em>in this game, your main objetive is to feed the baby healthy items, and protect him from the unhealthy ones.</em></strong></p>\
        <p style=\"text-align: center;\">you will find a health bar on the right of the screen, and an weapon level meter on the left.</p>\
        <p style=\"text-align: center;\">the health bar indicates the health of the baby,<strong> and you win the game when it reaches 100%.</strong></p>\
        <p style=\"text-align: center;\"><strong>you have 3 types of weapons: laser, bomb, and a hook.</strong></p>\
        <p style=\"text-align: center;\">your weapon level increases when you grab&nbsp; healthy item with the hook ( fruits, sports, vegitables...), and decreases when you grab unhealty items ( cigarettes, junk food...)</p>\
        <p style=\"text-align: center;\"><span style=\"text-decoration: underline;\"><strong>the weapon strength controls its speed and range.</strong></span></p>\
        <p style=\"text-align: center;\">your timer and score will also increase when you grab a healthy item, and decreases when you grab an unhealthy one.</p>\
        <p style=\"text-align: center;\">unhealthy items can be <strong>zapped with the laser.</strong></p>\
        <p style=\"text-align: center;\">zapping unhealthy items increases your score, while zapping healthy ones decreases it.</p>\
        <p style=\"text-align: center;\">when you reach a score threashold, a bomb is available for you.<strong> use it wisely</strong></p>\
        <p style=\"text-align: center;\">you should fill the health of the baby before the timer ends or <strong>you lose the game</strong>.</p>\
        <p style=\"text-align: center;\"><strong>harder levels unlock</strong> when you get higher scores.</p>\
        <p style=\"text-align: center;\">the movement is controlled with the left and right arrows on the keyboard.</p>\
        <p style=\"text-align: center;\">firing weapons is done with the (x) key.</p>\
        <p style=\"text-align: center;\">switching betwean weapons is done with the (z) key.</p>"));
    }
}

Description::~Description()
{
    delete ui;
}

void Description::on_backButton_clicked()
{
    this->close();
}
