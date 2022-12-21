#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Pool = new Widget();
    MainWindow::setCentralWidget(Pool);
    setFixedSize(800, 450);

    setStyleSheet("background-color:green;");
    QMediaPlayer * s_player = new QMediaPlayer(this);
            s_player->setMedia(QUrl("back.mp3"));
            s_player->setVolume(10);
            s_player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Widget::Widget(QWidget *parent): QWidget(parent){

    ball[0].BallPoint.setX(455);
    ball[0].BallPoint.setY(225);

    ball[1].BallPoint.setX(175+30);
    ball[1].BallPoint.setY(225);

    ball[2].BallPoint.setX(143+30);
    ball[2].BallPoint.setY(209);

    ball[3].BallPoint.setX(143+30);
    ball[3].BallPoint.setY(241);



    for(int i = 0; i <=3; ++i){
        ball[i].BallVector[0] = 0.;
        ball[i].BallVector[1] = 0.;
    }

    drow_dots.x = 0;
    drow_dots.y = 0;

    dots.x = 0;
    dots.y = 0;

    connect( &q_timer, SIGNAL(timeout() ), SLOT(collision()) );
    q_timer.start(15);
    update();
}

void Widget::paintEvent(QPaintEvent *){
    QPainter img(this);
    QPen pen;
    img.setBrush(QColor(255,0,0));
    pen.setWidth(8);
    pen.setColor(QColor(150,125,0));
    img.setPen(pen);
    img.drawLine(50,50,750,50);
    img.drawLine(750,50,750,400);
    img.drawLine(750,400,50,400);
    img.drawLine(50,400,50,50);
    pen.setWidth(2);
    pen.setColor(QColor(255,255,255));
    img.setPen(pen);
    img.setBrush(QColor(255,255,255));
    img.drawEllipse(ball[0].BallPoint, 15, 15);
    pen.setColor(QColor(0,255,0));
    img.setPen(pen);
    img.setBrush(QColor(0,255,0));
    img.drawEllipse(ball[1].BallPoint, 15, 15);
    pen.setColor(QColor(0,0,255));
    img.setPen(pen);
    img.setBrush(QColor(0,0,255));
    img.drawEllipse(ball[2].BallPoint, 15, 15);
    pen.setColor(QColor(255,0,0));
    img.setPen(pen);
    img.setBrush(QColor(255,0,0));
    img.drawEllipse(ball[3].BallPoint, 15, 15);
    pen.setColor(QColor(0,0,0));
    img.setPen(pen);
    img.setBrush(QColor(0,0,0));
        //up
    img.drawLine(71,51,71,71);
    img.drawLine(71,71,51,71);

    img.drawLine(385,51,385,71);
    img.drawLine(385,71,405,71);
    img.drawLine(405,71,405,51);

    img.drawLine(729,51,729,71);
    img.drawLine(729,71,749,71);

        //down
    img.drawLine(51,379,71,379);
    img.drawLine(71,379,71,399);

    img.drawLine(385,399,385,379);
    img.drawLine(385,379,405,379);
    img.drawLine(405,379,405,399);

    img.drawLine(729,399,729,379);
    img.drawLine(729,379,749,379);



    if(check){
        QPen pen = img.pen();
        pen.setStyle(Qt::DashLine);
        img.setPen(pen);
        img.drawLine(ball[0].BallPoint.x(), ball[0].BallPoint.y(), drow_dots.x, drow_dots.y);
    }

}

void Widget::mousePressEvent(QMouseEvent *event){

    if (event->buttons()==Qt::LeftButton){
        dots.x = event->pos().x();
        dots.y = event->pos().y();
        checking();
        if(check){
            drow_dots.x = event->pos().x();
            drow_dots.y = event->pos().y();
        }

    }
}

void Widget::mouseMoveEvent(QMouseEvent *event){

    checking();

    if (check && event->buttons()==Qt::LeftButton){
        drow_dots.x = event->pos().x();
        drow_dots.y = event->pos().y();
    }

}

void Widget::mouseReleaseEvent(QMouseEvent *event){
    event->button();
    check = false;
    ball[0].BallVector[0] = (-drow_dots.x + ball[0].BallPoint.x())/7;
    ball[0].BallVector[1] = (-drow_dots.y + ball[0].BallPoint.y())/7;
    QMediaPlayer * m_player = new QMediaPlayer(this);
            m_player->setMedia(QUrl("smb_bump.wav"));
            m_player->setVolume(50);
            m_player->play();
}

int Widget::mod(int x, int y, int x0, int y0){
    int mod;
    mod = sqrt(pow((x-x0),2)+pow((y-y0),2));
    return mod;
}

void Widget::checking(){
    int m, x, y;
    x = ball[0].BallPoint.x();
    y = ball[0].BallPoint.y();
    m = mod(dots.x, dots.y, x, y);
    if (m <= 15){
        check = true;
    }else check = false;
}

void Widget::collision(){
    for(int i = 0; i <= 3; ++i){

        if (ball[i].BallPoint.x()<=81&&ball[i].BallPoint.y()<=81&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();
        }

        if (ball[i].BallPoint.x()<=81&&ball[i].BallPoint.y()>=355&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();
        }

        if (ball[i].BallPoint.x()>=725&&ball[i].BallPoint.y()<=81&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();

        }

        if (ball[i].BallPoint.x()>=725&&ball[i].BallPoint.y()>=355&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();
        }

        if (ball[i].BallPoint.x()>=380&&ball[i].BallPoint.x()<=410&&ball[i].BallPoint.y()<=85&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();
        }

        if (ball[i].BallPoint.x()>=380&&ball[i].BallPoint.x()<=410&&ball[i].BallPoint.y()>=355&&ball[i].BallPoint.x()<900)
        {
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            ball[i].BallPoint.setX(1000);ball[i].BallPoint.setY(1000);
            QMediaPlayer * m_player = new QMediaPlayer(this);
                    m_player->setMedia(QUrl("vsego-horoshego.mp3"));
                    m_player->setVolume(50);
                    m_player->play();
        }

        ball[i].BallVector[0] = ball[i].BallVector[0]*0.98;
        ball[i].BallVector[1] = ball[i].BallVector[1]*0.98;

        if(((ball[i].BallVector[0] <= 1.3) && (ball[i].BallVector[0] >=0 )) || ((ball[i].BallVector[0] >= -1.3) && (ball[i].BallVector[0] <= 0)))
            ball[i].BallVector[0] = 0;
        if(((ball[i].BallVector[1] <= 1.3) && (ball[i].BallVector[1] >=0 )) || ((ball[i].BallVector[1] >= -1.3) && (ball[i].BallVector[1] <= 0)))
            ball[i].BallVector[1] = 0;

        double x_ball, y_ball;
        x_ball = ball[i].BallPoint.x() + ball[i].BallVector[0];
        y_ball = ball[i].BallPoint.y() + ball[i].BallVector[1];

        ball[i].BallPoint.setX(x_ball);
        ball[i].BallPoint.setY(y_ball);

        if(ball[i].BallPoint.x() <= 65)
            if(ball[i].BallVector[0] < 0)
            {ball[i].BallVector[0] = -ball[i].BallVector[0];
                QMediaPlayer * m_player = new QMediaPlayer(this);
                        m_player->setMedia(QUrl("smb_fireball.wav"));
                        m_player->setVolume(50);
                        m_player->play();}

        if(ball[i].BallPoint.y() <= 65)
            if(ball[i].BallVector[1] < 0)
            {ball[0].BallVector[1] = -ball[i].BallVector[1];QMediaPlayer * m_player = new QMediaPlayer(this);
                m_player->setMedia(QUrl("smb_fireball.wav"));
                m_player->setVolume(50);
                m_player->play();}


        if(ball[i].BallPoint.x() >= 735)
            if(ball[i].BallVector[0] > 0)
            {ball[i].BallVector[0] = -ball[i].BallVector[0];QMediaPlayer * m_player = new QMediaPlayer(this);
                m_player->setMedia(QUrl("smb_fireball.wav"));
                m_player->setVolume(50);
                m_player->play();}


        if(ball[i].BallPoint.y() >= 385)
            if(ball[i].BallVector[1] > 0)
            {ball[i].BallVector[1] = -ball[i].BallVector[1];QMediaPlayer * m_player = new QMediaPlayer(this);
                m_player->setMedia(QUrl("smb_fireball.wav"));
                m_player->setVolume(50);
                m_player->play();}


        for(int n = i + 1; n < 4; ++n){
            int m = mod(ball[i].BallPoint.x(),ball[i].BallPoint.y(),ball[n].BallPoint.x(),ball[n].BallPoint.y());

            if(m <= 30){
                double bi0, bi1, bn0, bn1;
                bi0 = ball[i].BallVector[0];
                bi1 = ball[i].BallVector[1];
                bn0 = ball[n].BallVector[0];
                bn1 = ball[n].BallVector[1];
                ball[i].BallVector[0] = -bi0/2 + bn0/2;
                ball[i].BallVector[1] = -bi1/2 + bn1/2;
                ball[n].BallVector[0] = -bn0/2 + bi0;
                ball[n].BallVector[1] = -bn1/2 + bi1;


            }
        }



    }
    update();
}
