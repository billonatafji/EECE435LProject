#include "history.h"
#include "ui_history.h"

History::History(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    this->user = user;

    QStringList scores = Scores::GetUserScores(this->user->Username,Game1::name);
    qSort(scores.begin(),scores.end(), qGreater<QString>());

    ui->game1ScoresList->clear();
    ui->game1ScoresList->addItems(scores);
    ui->game1HighestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore(Game1::name)));

    scores = Scores::GetUserScores(this->user->Username,Game2::name);
    qSort(scores.begin(),scores.end(), qGreater<QString>());

    ui->game2ScoresList->clear();
    ui->game2ScoresList->addItems(scores);
    ui->game2HighestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore(Game2::name)));
}

History::~History()
{
    delete ui;
}

void History::on_backButton_clicked()
{
    this->close();
}
