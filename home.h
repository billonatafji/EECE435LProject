#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <user.h>
#include <QTableWidget>
#include <QDateTime>
#include <scores.h>

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0, User* user = new User());
    User* user;
    void LoadScores();

    ~Home();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
