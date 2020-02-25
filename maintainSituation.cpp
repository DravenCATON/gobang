#include "widget.h"
extern int after_player(int x, int y);
extern int after_computer(int x,int y);

int maintainSituation(int turn,point current){//用来下了一步棋后调整状况的函数，0表示赢了，1表示没事
    int isWin=-1;
    if(turn == 0){//也就是这一步是玩家下的棋
         isWin=after_player(current.x,current.y);
    }else if(turn == 1){//也就是这一步是电脑下的棋
        isWin=after_computer(current.x,current.y);
    }
    return isWin;
}
