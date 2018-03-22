#include "cleanlinessmeter.h"
#include <Qt>
#include <QVBoxLayout>
CleanlinessMeter::CleanlinessMeter()
{
    //QVBoxLayout* formLayout = new QVBoxLayout();

    this->ProgressBar = new QProgressBar();
    this->ProgressBar->setOrientation(Qt::Horizontal);
    this->ProgressBar->setRange(0,100);
    this->ProgressBar->setValue(0);
    this->ProgressBar->setFixedHeight(30);
    this->ProgressBar->setFixedWidth(300);

    this->setWidget(this->ProgressBar);

//    this->ProgressBar->setGeometry(30,30,30,300);
//    formLayout->addWidget(this->ProgressBar);

//    this->setLayout(this->ProgressBar->layout());
}

void CleanlinessMeter::UpdateValue(){

}
