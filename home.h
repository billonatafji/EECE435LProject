#ifndef HOME_H
#define HOME_H

#include <QDialog>

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0, QString username = QString(""));
    ~Home();

private:
    Ui::Home *ui;
};

#endif // HOME_H
