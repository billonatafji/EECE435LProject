#include "signup.h"
#include "ui_signup.h"
#include "home.h"
#include <QFileDialog>
#include <QRegExp>


SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->formValidationLabel->hide();
    ui->userNameValidationLabel->hide();
    ui->firstNameValidationLabel->hide();
    ui->lastNameValidationLabel->hide();
    ui->passwordValidationLabel->hide();
    ui->confirmPasswordValidationLabel->hide();
    ui->profilePictureValidationLabel->hide();
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_cancelButton_clicked()
{
    this->close();
}

void SignUp::on_signUpButton_clicked()
{
    bool canSubmit = true;

    if(ui->userNameEdit->text().isEmpty()){
        canSubmit = false;
        ui->userNameValidationLabel->show();
    }else{
        ui->userNameValidationLabel->hide();
    }

    if(ui->firstNameEdit->text().isEmpty()){
        canSubmit = false;
        ui->firstNameValidationLabel->show();
    }else{
        ui->firstNameValidationLabel->hide();
    }

    if(ui->lastNameEdit->text().isEmpty()){
        canSubmit = false;
        ui->lastNameValidationLabel->show();
    }else{
        ui->lastNameValidationLabel->hide();
    }

    if(QRegExp("^((?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,})$").indexIn(ui->passwordEdit->text())<0){
        ui->passwordValidationLabel->show();
        canSubmit = false;
    }else{
        ui->passwordValidationLabel->hide();
    }

    if(ui->confirmPasswordEdit->text() != ui->passwordEdit->text() || ui->confirmPasswordEdit->text().isEmpty()){
        canSubmit = false;
        ui->confirmPasswordValidationLabel->show();
    }else{
        ui->confirmPasswordValidationLabel->hide();
    }

    if(ui->profilePictureLabel->pixmap() == NULL){
        canSubmit = false;
        ui->profilePictureValidationLabel->show();
    }else{
        ui->profilePictureValidationLabel->hide();
    }

    if(canSubmit){
        this->close();
        Home home(NULL,QString("test"));
        home.exec();
    }
    else{
        ui->formValidationLabel->show();
    }

}

void SignUp::on_browseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug(filePath.toLatin1());
    ui->profilePictureLabel->setPixmap(QPixmap(filePath).scaled(20,20));

}
