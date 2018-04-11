#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class GameView;
}

class GameView : public QDialog
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = 0);

    QGraphicsScene* gameScene;

    void setScene(QGraphicsScene* gameScene);

    ~GameView();

private:
    Ui::GameView *ui;
};

#endif // GAMEVIEW_H
