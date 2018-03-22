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
