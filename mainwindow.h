#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <vector>
#include <QStylePainter>
#include <QPoint>
#include <QRect>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>
#include <cmath>
#include <QString>

struct Ball{
  QPoint BallPoint;
  double BallVector[2];
};

struct Dots{
    int x,y;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
   Widget(QWidget *parent = nullptr);

private slots:
    void collision();

private:
    Ball ball[16];
    QTimer q_timer;
    Dots dots, drow_dots;
    bool check = false;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void checking();
    int mod(int x, int y, int x0, int y0);
};










QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Widget *Pool;
};
#endif // MAINWINDOW_H
