#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>
#include "game.h"
#include "game1.h"
#include "game2.h"
#include "description.h"

namespace Ui {
class Gamemenu;
}

class Gamemenu : public QDialog
{
    Q_OBJECT

public:
    explicit Gamemenu(QWidget *parent = 0, QString game = "", User* user = new User());

    QString Game;
    User* user;

    ~Gamemenu();

private slots:

    void on_descriptionButton_clicked();

    void on_resumeGameButton_clicked();

    void on_newGameButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Gamemenu *ui;
};

#endif // GAMEMENU_H
