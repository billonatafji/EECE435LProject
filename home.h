#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <user.h>
#include <QDateTime>
#include <scores.h>
#include "stdlib.h"
#include "history.h"
#include "gamemenu.h"
#include "game1.h"
#include "game2.h"

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0, User* user = new User());
    User* user;

    ~Home();

private slots:

    void on_historyButton_clicked();

    void on_game1Button_clicked();

    void on_game2Button_clicked();

    void on_backButton_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
