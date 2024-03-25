#include "snake.h"
#include "./ui_snake.h"
#include<qrect.h>
#include<qtimer.h>
#include<QKeyEvent>
#include <QRandomGenerator>
snake::snake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::snake),blsRun(false),speed(400)
{
    ui->setupUi(this);
    this->setGeometry(QRect(600,300,290,310));
}

snake::~snake()
{
    delete ui;
}
void snake::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!blsRun)
    {
        Initsnake();
    }

    //background
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(15,15,260,260);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(20,20,250,250);
    painter.drawPixmap(20,20,250,250,QPixmap(":/images/img/back.jpg"));
/*
    painter.setPen(Qt::blue);
    for(int i=2;i<=27;i++)
    {
        painter.drawLine(20,i*10,270,i*10);
        painter.drawLine(i*10,20,i*10,270);
    }
*/
    QFont font1("Courier",24);
    painter.setFont(font1);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawText(40,150,sDisplay);

    QFont font2("Courier",15);
    painter.setFont(font2);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawText(140,300,scoreLabel);
    painter.drawText(230,300,QString::number(nScore));

    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    //painter.drawRect(food);
    painter.drawPixmap(food,QPixmap(":/images/img/apple.jpg"));
    painter.drawRects(&vsnakeRect[0],vsnakeRect.size());//n个
    if(blsOver)
        timer->stop();
}
void snake::Initsnake()
{
    nDirection=2;
    blsRun=true;
    blsOver=false;
    scoreLabel="score:";
    nScore=0;

    food=CreateRect();

    vsnakeRect.resize(5);

    for(int i=0;i<vsnakeRect.size();i++)
    {
        QRect rect(100,70+10*i,10,10);
        vsnakeRect[vsnakeRect.size()-1-i]=rect;
    }
    snakeHead=vsnakeRect.first();

    timer=new QTimer(this);
    timer->start(speed);
    connect(timer,SIGNAL(timeout()),SLOT(snake_update()));

}

void snake::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *key=(QKeyEvent*)event;
    switch (key->key())
    {
    case Qt::Key_Up:nDirection=1;
        break;
    case Qt::Key_Down:nDirection=2;
        break;
    case Qt::Key_Left:nDirection=3;
        break;
    case Qt::Key_Right:nDirection=4;
        break;
    default:;

    }
}

void snake::snake_update()
{
    sDisplay="";
    snakeHead=vsnakeRect.first();
    IsEat();
    IsHit();
    for(int j=0;j<vsnakeRect.size()-1;j++)
    {
        vsnakeRect[vsnakeRect.size()-1-j]=vsnakeRect[vsnakeRect.size()-2-j];
    }


    switch(nDirection)
    {
    case 1:
        snakeHead.setTop(snakeHead.top()-10);
        snakeHead.setBottom(snakeHead.bottom()-10);
        break;
    case 2:
        snakeHead.setTop(snakeHead.top()+10);
        snakeHead.setBottom(snakeHead.bottom()+10);
        break;
    case 3:
        snakeHead.setLeft(snakeHead.left()-10);
        snakeHead.setRight(snakeHead.right()-10);
        break;
    case 4:
        snakeHead.setLeft(snakeHead.left()+10);
        snakeHead.setRight(snakeHead.right()+10);
    default:;
    }
    vsnakeRect[0]=snakeHead;
    if(snakeHead.left()<20||snakeHead.right()>270||snakeHead.top()<20||snakeHead.bottom()>270)
    {
        sDisplay="Game Over";
        blsOver=true;
    }
    update();

}

QRect snake::CreateRect()
{
    int x,y;
    x=QRandomGenerator::global()->bounded(0,1000)%25;
    y=QRandomGenerator::global()->bounded(0,1000)%25;
    QRect rect(20+x*10,20+y*10,10,10);
    return rect;
}

void snake::IsEat()
{
    if(snakeHead==food)
    {
        snakeHead=food;
        vsnakeRect.push_back(vsnakeRect.last());
        food=CreateRect();
        nScore+=10;
        if(speed>50)
        {
            speed-=10;
            timer->stop();
            timer->start(speed);
        }
    }
}

void snake::IsHit()
{
    for(int i=1;i<vsnakeRect.size();i++)
    {
        if(snakeHead==vsnakeRect[i])
        {
            sDisplay="Game Over";
            blsOver=true;
            update();
        }
    }
}
