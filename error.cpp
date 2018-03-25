#include "error.h"
#include "ui_error.h"

Error::Error(QString msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Error)
{
    ui->setupUi(this);

    ui->label->setText(msg);
}

Error::~Error()
{
    delete ui;
}

void Error::on_pushButton_clicked()
{
    this->close();
}
