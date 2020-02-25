#include "widget.h"
#include <vector>
#include <QDebug>
using namespace std;

extern int boardSize;
extern int** board;//棋盘矩阵,1表示白棋，0表示没有棋，-1表示黑棋
//extern int** boardDebug;//棋盘矩阵,1表示白棋，0表示没有棋，-1表示黑棋
extern vector<dot> ComputerWin;
extern vector<dot> PlayerWin;
extern int scoreBuiler(int color,int direction,point current);

dot most_score(){
    dot max;
    int maxScore=0;
    if(ComputerWin.size()!=0){//如果我放有只叠加了一次的第二类致命点        
        for(dot current:ComputerWin){
            point currentPoint;
            currentPoint.x=current.x;
            currentPoint.y=current.y;
            int score=scoreBuiler(1,10,currentPoint);
            if(score>maxScore){
                maxScore=score;
                max=current;
            }
        }
    }
    if(PlayerWin.size()!=0){//如果我放没有只叠加了一次的第二类致命点，但是对方有只叠加了一次的第二类致命点
        for(dot current:PlayerWin){
            point currentPoint;
            currentPoint.x=current.x;
            currentPoint.y=current.y;
            int score=scoreBuiler(0,10,currentPoint);
            if(score>maxScore){
                maxScore=score;
                max=current;
            }
        }
    }
    if(PlayerWin.size()!=0 || ComputerWin.size()!=0){
        return max;
    }
    else{//双方都没有只叠加了一次的第二类致命点，全盘都打一次分，看看哪个点分最高
        maxScore=0;
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                if(board[i][j]==0){
                    point current;
                    current.x=i;
                    current.y=j;
                    int score=scoreBuiler(1,10,current)+scoreBuiler(0,10,current);
                    if(score>maxScore){
                        maxScore=score;
                        max.x=i;
                        max.y=j;
                    }
                }
            }
        }
        return max;
    }
    return dot();
}
int scoreBuiler(int color,int direction,point current){ //color表示是白色棋还是黑色棋，0位黑色，1位白色。direction表示第二种情况的方向，若为10表示没有方向，表示这个点既不是第一种情况也不是第二种情况。current是传进来打分的点
    int totalScore=0;
    if(color==1){//我方为白棋
        if(direction!=0){//垂直方向,每一种情况两个for循环，分别对应双向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置），用于判断是否有五个位置
            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && whileNumber==2){
                addScore=16;
            }
            if(whileNumber==0){
                addScore=8;
            }
            totalScore+=addScore;
        }
        if(direction!=1){//右上方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=2;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=1;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && whileNumber==2){
                addScore=16;
            }
            if(whileNumber==0){
                addScore=8;
            }
            totalScore+=addScore+2;
        }
        if(direction!=2){//水平方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=4;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=3;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=2;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=1;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=4;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=3;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=2;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=1;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && whileNumber==2){
                addScore=16;
            }
            if(whileNumber==0){
                addScore=8;
            }
            totalScore+=addScore;
        }
        if(direction!=3){//左上方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore+=8;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore+=6;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore+=4;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=2;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore+=2;
                        whileNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=1;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && whileNumber==2){
                addScore=16;
            }
            if(whileNumber==0){
                addScore=8;
            }
            totalScore+=addScore+2;
        }
    }

    if(color==0){//我方为黑棋
        if(direction!=0){//垂直方向,每一种情况两个for循环，分别对应双向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=2;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
                        addScore+=1;
                    }
                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && blackNumber==2){
                addScore=16;
            }
            if(blackNumber==0){
                addScore=8;
            }
            totalScore+=addScore;
        }
        if(direction!=1){//右上方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=2;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
                        addScore+=1;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && blackNumber==2){
                addScore=16;
            }
            if(blackNumber==0){
                addScore=8;
            }
            totalScore+=addScore+2;
        }
        if(direction!=2){//水平方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=4;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=3;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=2;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
                        addScore+=1;
                    }
                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=4;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=3;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=2;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
                        addScore+=1;
                    }
                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && blackNumber==2){
                addScore=16;
            }
            if(blackNumber==0){
                addScore=8;
            }
            totalScore+=addScore;
        }
        if(direction!=3){//左上方向
            int addScore=0;
            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=4;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=3;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=2;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
                        addScore+=1;
                    }
                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore+=8;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=4;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore-=8;
                        exception+=i;
                        break;
                    }
                }
                else if(i==2){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore+=6;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=3;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore-=6;
                        exception+=i;
                        break;
                    }
                }
                else if(i==3){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore+=4;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=2;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore-=4;
                        exception+=i;
                        break;
                    }
                }
                else if(i==4){
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
                        addScore+=2;
                        blackNumber++;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
                        addScore+=1;
                    }
                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
                        addScore-=2;
                        exception+=i;
                        break;
                    }
                }
            }
            if(exception==6 && blackNumber==2){
                addScore=16;
            }
            if(blackNumber==0){
                addScore=8;
            }
            totalScore+=addScore+2;
        }
    }
    return totalScore;
}
//int scoreBuiler(int color,int direction,point current){ //color表示是白色棋还是黑色棋，0位黑色，1位白色。direction表示第二种情况的方向，若为10表示没有方向，表示这个点既不是第一种情况也不是第二种情况。current是传进来打分的点
//    int totalScore=0;
//    if(color==1){//我方为白棋
//        if(direction!=0){//垂直方向,每一种情况两个for循环，分别对应双向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置），用于判断是否有五个位置
//            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
//                        addScore+=4;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && whileNumber==2){
//                addScore=6;
//            }
//            if(whileNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=1){//右上方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
//            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && whileNumber==2){
//                addScore=6;
//            }
//            if(whileNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=2){//水平方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
//            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
//                        addScore+=2;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
//                        addScore+=1;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
//                        addScore+=2;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
//                        addScore+=1;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && whileNumber==2){
//                addScore=6;
//            }
//            if(whileNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=3){//左上方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个黑子之间刚好有五个位置）
//            int whileNumber=0;//用来排除第二类的最后那三种特例的（两个黑子之间的五个位置里有两个白棋），用于判断是否有两个白棋
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
//                        addScore+=4;
//                        whileNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
//                        addScore+=2;
//                        whileNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && whileNumber==2){
//                addScore=6;
//            }
//            if(whileNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//    }

//    if(color==0){//我方为黑棋
//        if(direction!=0){//垂直方向,每一种情况两个for循环，分别对应双向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
//            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i<boardSize && current.y+i>=0 && board[current.x][current.y+i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i<boardSize && current.y-i>=0 && board[current.x][current.y-i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && blackNumber==2){
//                addScore=6;
//            }
//            if(blackNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=1){//右上方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
//            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y+i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y-i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && blackNumber==2){
//                addScore=6;
//            }
//            if(blackNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=2){//水平方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
//            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
//                        addScore+=2;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==0){
//                        addScore+=1;
//                    }
//                    if(current.x+i<boardSize && current.x+i>=0 && board[current.x+i][current.y]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
//                        addScore+=2;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==0){
//                        addScore+=1;
//                    }
//                    if(current.x-i<boardSize && current.x-i>=0 && board[current.x-i][current.y]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && blackNumber==2){
//                addScore=6;
//            }
//            if(blackNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//        if(direction!=3){//左上方向
//            int addScore=0;
//            int exception=0;//用来排除第二类的最后那三种特例的（两个白子之间刚好有五个位置）
//            int blackNumber=0;//用来排除第二类的最后那三种特例的（两个白子之间的五个位置里有两个黑棋），用于判断是否有两个黑子
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y+i< boardSize && current.y+i>=0 && current.x-i< boardSize && current.x-i>=0 && board[current.x-i][current.y+i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            for(int i=1;i<=4;i++){
//                if(i==1){
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
//                        addScore+=4;
//                        blackNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
//                        addScore+=2;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
//                        addScore-=4;
//                        exception+=i;
//                        break;
//                    }
//                }
//                else{
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==-1){
//                        addScore+=2;
//                        blackNumber++;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==0){
//                        addScore+=1;
//                    }
//                    if(current.y-i< boardSize && current.y-i>=0 && current.x+i< boardSize && current.x+i>=0 && board[current.x+i][current.y-i]==1){
//                        addScore-=2;
//                        exception+=i;
//                        break;
//                    }
//                }
//            }
//            if(exception==6 && blackNumber==2){
//                addScore=6;
//            }
//            if(blackNumber==0){
//                totalScore-=6;
//            }
//            totalScore+=addScore;
//        }
//    }
//    return totalScore;
//}
