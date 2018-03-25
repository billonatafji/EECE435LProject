#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class Error;
}

class Error : public QDialog
{
    Q_OBJECT

public:
    Error(QString msg, QWidget *parent = 0);
    ~Error();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Error *ui;
};

#endif // ERROR_H
