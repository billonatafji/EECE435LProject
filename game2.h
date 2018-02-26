#ifndef GAME2_H
#define GAME2_H

#include <QDialog>
#include "scores.h"
#include "game.h"

namespace Ui {
class Game2;
}

class Game2 : public QDialog, public Game
{
    Q_OBJECT

public:
    explicit Game2(QWidget *parent = 0, User* user = new User());
    ~Game2();
    static QString name;


private slots:
    void on_backButton_clicked();

    void on_playButton_clicked();

private:
    Ui::Game2 *ui;
};

#endif // GAME2_H
