#ifndef CLEANLINESSMETER_H
#define CLEANLINESSMETER_H

#include <QObject>
#include <QProgressBar>
#include <QWidget>
#include <QGraphicsProxyWidget>

class CleanlinessMeter : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit CleanlinessMeter();

    QProgressBar *ProgressBar;
    void UpdateValue();

signals:

public slots:
};

#endif // CLEANLINESSMETER_H
