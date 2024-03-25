#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include<qpainter.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class snake;
}
QT_END_NAMESPACE

class snake : public QMainWindow
{
    Q_OBJECT

public:
    snake(QWidget *parent = nullptr);
    ~snake();
    void paintEvent(QPaintEvent *envent);
    void Initsnake();
    QRect CreateRect();
    void IsEat();
    void IsHit();

private slots:
    void snake_update();

private:
    Ui::snake *ui;
    QVector<QRect> vsnakeRect;
    QRect snakeHead;
    void keyPressEvent(QKeyEvent *key);
    QTimer *timer;
    bool blsOver;
    QString sDisplay;
    bool blsRun;
    int nDirection;
    QRect food;
    int nScore;
    QString scoreLabel;
    int speed;

};
#endif // SNAKE_H
