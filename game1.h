#ifndef GAME1_H
#define GAME1_H

#include <QDialog>
#include "game.h"

namespace Ui {
class Game1;
}

class Game1 : public QDialog, public Game
{
    Q_OBJECT

public:
    explicit Game1(QWidget *parent = 0, User* user = new User());
    ~Game1();
    static QString name;


private slots:
    void on_backButton_clicked();

    void on_playButton_clicked();

private:
    Ui::Game1 *ui;
};

#endif // GAME1_H
