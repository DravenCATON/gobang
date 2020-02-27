#include "widget.h"
#include "ui_widget.h"
#include "messageDialog.h"
#include <QPalette>
#include <QMovie>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPixmap>
#include <QSize>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QStack>
#include <vector>
using namespace std;

//全局变量
int turn=0;//0表示给player下棋（用黑色），1表示给computer下棋（用白色）
int boardSize=16;
int** board=new int*[boardSize];//棋盘矩阵,1表示白棋，0表示没有棋，-1表示黑棋
extern int maintainSituation(int turn,point current);
extern point determinePosition();
extern int scoreBuiler(int color,int direction,point current);
//extern int scoreBuilerDebug(int color,int direction,point current);
//调试的全局变量
//int** boardDebug=new int*[boardSize];//用于调试的棋盘矩阵,1表示白棋，0表示没有棋，-1表示黑棋
int turnDebug=0;//0表示给player下棋（用黑色），1表示给computer下棋（用白色）,2表示打分

//电脑以及玩家的致命点的vector
vector<dot> ComputerWin;
vector<dot> PlayerWin;



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //初始化参数
    ui->setupUi(this);
    mDialog=new messageDialog();
    for (int i = 0; i < boardSize; i++) {
       board[i]=new int[boardSize];
       for(int j=0;j<boardSize;j++){
           board[i][j]=0;
       }
    }

    //为对话框设置功能
    mDialog->installEventFilter(this);

    //设置默认页面
    ui->stackedWidget->setCurrentIndex(0);

    //背景变成白色
    QPalette palette=this->palette();
    palette.setColor(QPalette::Window,QColor(255,255,255));
    this->setPalette(palette);

    //加图标
    this->setWindowIcon(QIcon(QString(":/batman.png")));

    //增加gif
    QMovie *movie=new QMovie(QString(":/hhh.gif"));
    movie->setScaledSize(QSize(640,300));
    ui->gifLabel->setMovie(movie);
    movie->start();

    //设置按钮样式
    ui->pushButton->setStyleSheet("background-color:white; border:0.5px solid black; border-radius:3px; padding:3px;");
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);//阴影
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setBlurRadius(10);
    ui->pushButton->setGraphicsEffect(shadowEffect);
    ui->pushButton->installEventFilter(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    //返回按钮的功能设置
    connect(ui->returnButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        ComputerWin.clear();
        PlayerWin.clear();
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
    });


    //为棋盘安装监听过滤
    ui->widget_5->installEventFilter(this);


    //重来的按钮的功能
    connect(ui->againButton,&QPushButton::clicked,[=](){
        ComputerWin.clear();
        PlayerWin.clear();
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
        ui->widget_5->update();
    });

    //电脑先手的按钮作用

    connect(ui->comFirstButton,&QPushButton::clicked,[=](){
        ComputerWin.clear();
        PlayerWin.clear();
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
        board[7][7]=1;
        point first;
        first.x=7;
        first.y=7;
        maintainSituation(turn,first);
        ui->widget_5->update();
    });


    //调试页面
    //设置debug按钮的功能
    connect(ui->debugButton,&QPushButton::clicked,[=](){
        ComputerWin.clear();
        PlayerWin.clear();
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
        ui->widget_5->update();
        ui->stackedWidget->setCurrentIndex(2);
    });

    //设置调试页面返回按钮的功能
    connect(ui->returnlButton2,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
        ComputerWin.clear();
        PlayerWin.clear();
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
    });

    //为调试的棋盘安装监听过滤
    ui->widget_7->installEventFilter(this);

    //黑棋按钮的作用
    connect(ui->blackButton,&QPushButton::clicked,[=](){
        turnDebug=0;
    });

    //白棋按钮的作用
    connect(ui->whiteButton,&QPushButton::clicked,[=](){
        turnDebug=1;
    });

    //打分按钮的作用
    connect(ui->scoreButton,&QPushButton::clicked,[=](){
        turnDebug=2;
    });

    //调试的重来   
    connect(ui->againButton2,&QPushButton::clicked,[=](){
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                board[i][j]=0;
            }
        }
        ComputerWin.clear();
        PlayerWin.clear();
        ui->widget_7->update();
    });

}


bool Widget::eventFilter(QObject *watched, QEvent *event){
    //用事件过滤器为按钮们添加鼠标进入出去的颜色变化样式
    if(watched==ui->pushButton){
        QPushButton* pushbutton=static_cast<QPushButton*>(watched);
        if(event->type()==QEvent::Enter){
            pushbutton->setStyleSheet("background-color:black; color:white; border:0.5px solid black; border-radius:3px; padding:3px;");
            return true;
        }
        if(event->type()==QEvent::Leave){
            pushbutton->setStyleSheet("background-color:white; color:black; border:0.5px solid black; border-radius:3px; padding:3px;");
            return true;
        }
    }

    //做关于棋盘的各种事件
    if(watched==ui->widget_5){
        QWidget* widget=static_cast<QWidget*>(watched);
        //绘制棋盘
        if(event->type()==QEvent::Paint){
            QPainter painter(ui->widget_5);
            painter.setRenderHint(QPainter::Antialiasing);
            QPixmap pixmap(":/board.png");
            pixmap=pixmap.scaled(420,420);
            painter.drawPixmap(60,20,pixmap);
            QPixmap whitePixmap(":/white.png");
            whitePixmap=whitePixmap.scaled(28,28);
            QPixmap blackPixmap(":/black.png");
            blackPixmap=blackPixmap.scaled(28,28);
            for(int i=0;i<boardSize;i++){
                for(int j=0;j<boardSize;j++){
                    if(board[i][j]==1){//1表示白棋，0表示没有棋，-1表示黑棋
                        painter.drawPixmap(i*28+60-14,j*28+20-14,28,28,whitePixmap);
                    }
                    else if(board[i][j]==-1){
                        painter.drawPixmap(i*28+60-14,j*28+20-14,28,28,blackPixmap);
                    }
                }
            }
        }

        //棋盘点击事件
        if(event->type()==QEvent::MouseButtonRelease){
            if(turn==0){//玩家下棋
                QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
                int x=mouseEvent->x();
                int y=mouseEvent->y();
                if(x>=60&&x<=60+420&&y>=20&&y<=20+420){
                    int xRelateToBoard=x-60;
                    int yRelateToBoard=y-20;

                    int xSteps=xRelateToBoard/28;
                    int xRemainder=xRelateToBoard%28;
                    if(xRemainder>14){
                        xSteps++;
                    }

                    int ySteps=yRelateToBoard/28;
                    int yRemainder=yRelateToBoard%28;
                    if(yRemainder>14){
                        ySteps++;
                    }
                    if(board[xSteps][ySteps]==0){
                        board[xSteps][ySteps]=-1;
                        widget->update();
                        point current;
                        current.x=xSteps;
                        current.y=ySteps;
                        if(!maintainSituation(turn,current)){
                            playerWin();
                            return true;
                        }
                        turn=1;
                        point comPoint = determinePosition();
                        board[comPoint.x][comPoint.y]=1;
                        if(!maintainSituation(turn,comPoint)){
                            computerWin();
                            turn=0;
                            return true;
                        }
                        turn=0;
                    }
                }
            }
        }
    }

    if(watched==mDialog){
        if(event->type()==QEvent::Close){
            ComputerWin.clear();
            PlayerWin.clear();
            for(int i=0;i<boardSize;i++){
                for(int j=0;j<boardSize;j++){
                    board[i][j]=0;
                }
            }
            return true;
        }
    }

        //做关于调试棋盘的各种事件
        if(watched==ui->widget_7){
            QWidget* widget=static_cast<QWidget*>(watched);
            //绘制棋盘
            if(event->type()==QEvent::Paint){
                QPainter painter(ui->widget_7);
                painter.setRenderHint(QPainter::Antialiasing);
                QPixmap pixmap(":/board.png");
                pixmap=pixmap.scaled(420,420);
                painter.drawPixmap(60,20,pixmap);
                QPixmap whitePixmap(":/white.png");
                whitePixmap=whitePixmap.scaled(28,28);
                QPixmap blackPixmap(":/black.png");
                blackPixmap=blackPixmap.scaled(28,28);
                for(int i=0;i<boardSize;i++){
                    for(int j=0;j<boardSize;j++){
                        if(board[i][j]==1){//1表示白棋，0表示没有棋，-1表示黑棋
                            painter.drawPixmap(i*28+60-14,j*28+20-14,28,28,whitePixmap);
                        }
                        else if(board[i][j]==-1){
                            painter.drawPixmap(i*28+60-14,j*28+20-14,28,28,blackPixmap);
                        }
                    }
                }

            }

            //棋盘点击事件
            if(event->type()==QEvent::MouseButtonRelease){
                QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
                int x=mouseEvent->x();
                int y=mouseEvent->y();
                if(x>=60&&x<=60+420&&y>=20&&y<=20+420){
                    int xRelateToBoard=x-60;
                    int yRelateToBoard=y-20;

                    int xSteps=xRelateToBoard/28;
                    int xRemainder=xRelateToBoard%28;
                    if(xRemainder>14){
                        xSteps++;
                    }

                    int ySteps=yRelateToBoard/28;
                    int yRemainder=yRelateToBoard%28;
                    if(yRemainder>14){
                        ySteps++;
                    }
                    if(turnDebug==0){//黑棋
                        if(board[xSteps][ySteps]==0){
                            board[xSteps][ySteps]=-1;
                            point current;
                            current.x=xSteps;
                            current.y=ySteps;
                            maintainSituation(turnDebug,current);
                            qDebug()<<PlayerWin.size();
                            for(dot var:PlayerWin){
                                QString hh=QString("点(%1,%2)在vector中，分值为%3").arg(var.x).arg(var.y).arg(var.total_score);
                                qDebug()<<hh;
                            }
                        }
                    }
                    else if(turnDebug==1){//白棋
                        if(board[xSteps][ySteps]==0){
                            board[xSteps][ySteps]=1;
                            point current;
                            current.x=xSteps;
                            current.y=ySteps;
                            maintainSituation(turnDebug,current);
                            qDebug()<<ComputerWin.size();
                            for(dot var:ComputerWin){
                                qDebug()<<QString("点(%1,%2)在vector中，分值为%3").arg(var.x).arg(var.y).arg(var.total_score);
                            }
                        }
                    }
                    else if(turnDebug==2){//打分
                        point current;
                        current.x=xSteps;
                        current.y=ySteps;
                        qDebug()<<scoreBuiler(0,10,current);
                    }
                    for(dot current:PlayerWin){
                        qDebug()<<current.x<<","<<current.y;
                    }
                    widget->update();
                }
            }
        }
        return QWidget::eventFilter(watched,event);
}

void Widget::playerWin(){
    mDialog->setLabelText("你赢了");
    mDialog->show();

}
void Widget::computerWin(){
    mDialog->setLabelText("你输了");
    mDialog->show();
}

Widget::~Widget()
{
    delete ui;
}

