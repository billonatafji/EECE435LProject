/**
* \file signup.cpp
* \brief signup class definition
*
* the signup class
*\author Bilal natafgi
*\date 20-2-2018
*/
#include "signup.h"
#include "ui_signup.h"

/**
 * @brief SignUp::SignUp
 * @param parent
 *
 *constructor for the signup class.
 * it hides the validation error messages
 *
 */
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
///destructor
SignUp::~SignUp()
{
    delete ui;
}
/// excited when the cancel button is clicked
void SignUp::on_cancelButton_clicked()
{
    this->close();
}
/**
 * @brief SignUp::on_signUpButton_clicked
 *
 * this function is excited when the signup button is pressed.
 * it checks for errors in the form (ex: no username, not maching passwords...).
 * if everything is correct, it calls the adduser function in the user class, which also checks if the username is taken or not. if not, then the user is added.
 *
 */
void SignUp::on_signUpButton_clicked()
{
    bool canSubmit = true;

    if(ui->userNameEdit->text().isEmpty()){
        canSubmit = false;
        ui->userNameValidationLabel->setText("Your Username is Required.");
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
    /// if no errors in the form
    if(canSubmit){

        User user(ui->userNameEdit->text(),
                  ui->passwordEdit->text(),
                  ui->firstNameEdit->text(),
                  ui->lastNameEdit->text(),
                  ui->dateOfBirthEdit->text(),
                  ui->maleRadioButton->isChecked() ? ui->maleRadioButton->text() :ui->femaleRadioButton->text(),
                  QPixmap(profilePictureEdit).scaled(100,100).toImage());
        if(User::AddUser(user)){
            this->close();
        }
        else{
            ui->userNameValidationLabel->setText("The Username is Taken");
            ui->userNameValidationLabel->show();
        }

    }
    else{
        ui->formValidationLabel->show();
    }

}
/// this function is excited when a user presses the browse button.
/// it opens a file dialog for the user to choose a picture
/// the picture should have the exctention .png, .jpg, or .bmp
void SignUp::on_browseButton_clicked()
{
    this->profilePictureEdit = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->profilePictureLabel->setPixmap(QPixmap(profilePictureEdit).scaledToHeight(20));
}
