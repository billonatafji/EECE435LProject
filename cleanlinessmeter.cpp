/**
* \file CleanlinessMeter.cpp
* \brief CleanlinessMeter class definition
*
*  this class creates a meter for the cleanliness of the tank.
*\author Bilal Natafgi
*\date 21-3-2018
*/

#include "cleanlinessmeter.h"
#include <Qt>
#include <QVBoxLayout>

CleanlinessMeter::CleanlinessMeter()
{

    this->ProgressBar = new QProgressBar();
    this->ProgressBar->setOrientation(Qt::Horizontal);
    this->ProgressBar->setRange(0,100);
    this->ProgressBar->setValue(0);
    this->ProgressBar->setFixedHeight(30);
    this->ProgressBar->setFixedWidth(200);

    this->setWidget(this->ProgressBar);
}

void CleanlinessMeter::UpdateValue(){

}
