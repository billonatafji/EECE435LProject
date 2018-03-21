#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "game.h"
#include "game1.h"
#include "game2.h"

namespace Ui {
class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = 0, User* user = new User());
    User* user;
    ~History();

private slots:
    void on_backButton_clicked();

private:
    Ui::History *ui;
};

#endif // HISTORY_H
