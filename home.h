#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <user.h>
#include <QTableWidget>
#include <QDateTime>
#include <scores.h>
#include "stdlib.h"
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
    void LoadScores(QString game);

    ~Home();

private slots:

    void on_newGame1Button_clicked();

    void on_resumeGame1Button_clicked();

    void on_newGameButton_2_clicked();

    void on_resumeGame2Button_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
