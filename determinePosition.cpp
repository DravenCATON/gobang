#include "widget.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<QDebug>
using namespace std;
extern point scoreBuiler();
extern vector<dot> ComputerWin;
extern vector<dot> PlayerWin;
extern bool cmp(dot dot1, dot dot2);
extern void find_sec(int x, int y,int tag);
extern dot find_point(vector<dot>ComputerWin, vector<dot>HumanWin);
extern void playerWin();
extern void computerWin();
#define HumanWin PlayerWin


point determinePosition() {
    dot bestDot = find_point(ComputerWin, PlayerWin);
    point bestPoint;
    bestPoint.x = bestDot.x;
    bestPoint.y = bestDot.y;
    return bestPoint;
}

extern dot most_score();//晓鸣的打分函数

void player_to_computer(int i, int j) {
    if(find_if(ComputerWin.begin(),ComputerWin.end(),findd(i,j))!=ComputerWin.end()){
        ComputerWin.erase(find_if(ComputerWin.begin(), ComputerWin.end(), findd(i, j)));
    }
    find_sec(i, j, 1);
}

//电脑对玩家
void computer_to_player(int i, int j) {
    if(find_if(PlayerWin.begin(),PlayerWin.end(),findd(i,j))!=PlayerWin.end()){
        PlayerWin.erase(find_if(PlayerWin.begin(), PlayerWin.end(), findd(i, j)));
    }
    find_sec(i, j, -1);
}

int after_player(int x, int y) {//0表示赢了，1表示没事
    if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(x, y)) == PlayerWin.end()) {
        find_sec(x, y, -1);//找出这一步对他自己是否可以形成致命点 
        player_to_computer(x,y);
    }
    //就是说原来中没有这个点
    else{
        vector<dot>::iterator it=find_if(PlayerWin.begin(),PlayerWin.end(),findd(x,y));
        if (it->total_score > 100) {
            return 0;
        }//对方胜利
        else {
            PlayerWin.erase(it);//删除已下的点
            find_sec(x, y, -1);//更新玩家致命点
            player_to_computer(x,y);//更新电脑
        }
    }
    return 1;
}
//电脑下棋后的影响
int after_computer(int x,int y){//0表示赢了，1表示没事
    if(find_if(ComputerWin.begin(),ComputerWin.end(),findd(x,y))==ComputerWin.end()){
        //是打分后下的点
        find_sec(x, y, 1);//更新电脑的致命点
        computer_to_player(x,y);//更新玩家致命点
    }
    else{
        vector<dot>::iterator it=find_if(ComputerWin.begin(),ComputerWin.end(),findd(x,y));
        if(it->total_score>100){
            ComputerWin.erase(ComputerWin.begin());
            return 0;
        }
        else{
            ComputerWin.erase(it);
            find_sec(x, y, 1);//更新电脑的致命点
            computer_to_player(x,y);//更新玩家致命点
        }
    }
    return 1;
}
dot find_point(vector<dot>ComputerWin, vector<dot>HumanWin) {
    if (ComputerWin.size() != 0 && ComputerWin.front().total_score > 110) {
        dot temp = ComputerWin.front();
        return temp;
    }
    else {
        if (HumanWin.size() != 0 && PlayerWin.front().total_score > 110) {
            dot temp = PlayerWin.front();
            return temp;
            //computer_stepP1_change();
        }
        else {
            if (ComputerWin.size() != 0 && ComputerWin.front().total_score > 100) {
                dot temp = ComputerWin.front();
                return temp;
            }//我方必胜点和致命点1的，这步将形成必胜点，可以宣布我们赢了
            else {
                if (HumanWin.size() != 0 && PlayerWin.front().total_score > 100) {
                    dot temp = PlayerWin.front();
                    return temp;
                    //computer_stepP1_change();
                }//对方必胜点和致命点1，此步用于破坏对方当前最需要下的一步**注意他和第一步的区别
                else {
                    if (ComputerWin.size() != 0 && ComputerWin.front().total_score > 1) {//此时要形成致命点1
                        /*下面是电脑下了之后对玩家的影响*/
                        dot temp = ComputerWin.front();//如果进行到现在，说明剩下的是等级不高的致命点2**因为若是等级高的在第一个if已经解决
                        return temp;
                        //computer_stepC2_change();
                    }//我方致命点2
                    else {
                        if (HumanWin.size() != 0 && HumanWin.front().total_score > 1) {
                            dot temp = HumanWin.front();
                            return temp;
                            //computer_stepP2_change();
                        }//对方致命点2
                        else return most_score();//打分函数
                    }
                }
            }
        }
    }
}
//void computer_stepP2_change() {
//    dot temp = HumanWin.front();
//    HumanWin.erase(HumanWin.begin());
//    //周围的致命1或致命点2进行更新*2
//    if (temp.score[0] != 0) {
//        int i = 1;
//        while (temp.y + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {
//            if (checkboard[temp.x][temp.y + i] == -1)i++;
//            if (checkboard[temp.x][temp.y + i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y + i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y + i))).score[0] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y + i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y - i >= 0 && checkboard[temp.x][temp.y - i] != -1) {
//            if (checkboard[temp.x][temp.y - i] == -1)i++;
//            if (checkboard[temp.x][temp.y - i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y - i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y - i))).score[0] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x, temp.y - i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[1] != 0) {
//        int i = 1;
//        while (temp.y + i <= 14 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y + i] != -1) {
//            if (checkboard[temp.x + i][temp.y + i] == -1)i++;
//            if (checkboard[temp.x + i][temp.y + i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y + i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y + i))).score[1] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y + i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y - i >= 0 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y - i] != -1) {
//            if (checkboard[temp.x - i][temp.y - i] == -1)i++;
//            if (checkboard[temp.x - i][temp.y - i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y - i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y - i))).score[1] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y - i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[2] != 0) {
//        int i = 1;
//        while (temp.x + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {
//            if (checkboard[temp.x + i][temp.y] == -1)i++;
//            if (checkboard[temp.x + i][temp.y] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y))).score[2] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.x - i >= 0 && checkboard[temp.x - i][temp.y] != -1) {
//            if (checkboard[temp.x - i][temp.y] == -1)i++;
//            if (checkboard[temp.x - i][temp.y] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y))).score[2] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[3] != 0) {
//        int i = 1;
//        while (temp.y - i >= 0 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y - i] != -1) {
//            if (checkboard[temp.x + i][temp.y - i] == -1)i++;
//            if (checkboard[temp.x + i][temp.y - i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y - i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y - i))).score[3] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x + i, temp.y - i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y + i <= 14 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y + i] != -1) {
//            if (checkboard[temp.x - i][temp.y + i] == -1)i++;
//            if (checkboard[temp.x - i][temp.y + i] == 0) {
//                if (find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y + i)) == HumanWin.end()) break;
//                else {
//                    if ((*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y + i))).score[3] == 0)break;
//                    else {
//                        (*find_if(HumanWin.begin(), HumanWin.end(), findd(temp.x - i, temp.y + i))).total_score = +100;
//                        push_heap(HumanWin.begin(), HumanWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    find_sec(temp.x, temp.y, 1);
//    find_sec(temp.x, temp.y, -1);
//}
////是电脑走了对手的致命点2后的影响
//void computer_stepC2_change() {
//    dot temp = ComputerWin.front();//如果进行到现在，说明剩下的是等级不高的致命点2**因为若是等级高的在第一个if已经解决
//    ComputerWin.erase(ComputerWin.begin());
//    //周围的致命1或致命点2进行更新*2
//    if (temp.score[0] != 0) {
//        int i = 1;
//        while (temp.y + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {//遇到黑子或边界则终止
//            if (checkboard[temp.x][temp.y + i] == 1)i++;//我方棋子忽略
//            if (checkboard[temp.x][temp.y + i] == 0) {//若是白子则进行判断
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y + i)) == ComputerWin.end()) break;//在原来中找不到则说明改空格不是致命点2的点，忽略且break
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y + i))).score[0] == 0)break;//方向不同，也break
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y + i))).total_score = +100;//方向相同，提升该点级别
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);//调整堆
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y - i >= 0 && checkboard[temp.x][temp.y - i] != -1) {//同一个方向上的不同走向
//            if (checkboard[temp.x][temp.y - i] == 1)i++;//下面的和前面一样
//            if (checkboard[temp.x][temp.y - i] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y - i)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y - i))).score[0] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x, temp.y - i))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[1] != 0) {
//        int i = 1;
//        while (temp.y + i <= 14 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y + i] != -1) {
//            if (checkboard[temp.x + i][temp.y + i] == 1)i++;
//            if (checkboard[temp.x + i][temp.y + i] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y + i)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y + i))).score[1] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y + i))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y - i >= 0 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y - i] != -1) {
//            if (checkboard[temp.x - i][temp.y - i] == 1)i++;
//            if (checkboard[temp.x - i][temp.y - i] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y - i)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y - i))).score[1] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y - i))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[2] != 0) {
//        int i = 1;
//        while (temp.x + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {
//            if (checkboard[temp.x + i][temp.y] == 1)i++;
//            if (checkboard[temp.x + i][temp.y] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y))).score[2] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.x - i >= 0 && checkboard[temp.x - i][temp.y] != -1) {
//            if (checkboard[temp.x - i][temp.y] == 1)i++;
//            if (checkboard[temp.x - i][temp.y] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y))).score[2] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    if (temp.score[3] != 0) {
//        int i = 1;
//        while (temp.y - i >= 0 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y - i] != -1) {
//            if (checkboard[temp.x + i][temp.y - i] == 1)i++;
//            if (checkboard[temp.x + i][temp.y - i] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y - i)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y - i))).score[3] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x + i, temp.y - i))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//        i = 1;
//        while (temp.y + i <= 14 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y + i] != -1) {
//            if (checkboard[temp.x - i][temp.y + i] == 1)i++;
//            if (checkboard[temp.x - i][temp.y + i] == 0) {
//                if (find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y + i)) == ComputerWin.end()) break;
//                else {
//                    if ((*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y + i))).score[3] == 0)break;
//                    else {
//                        (*find_if(ComputerWin.begin(), ComputerWin.end(), findd(temp.x - i, temp.y + i))).total_score = +100;
//                        push_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
//                        break;
//                    }
//                }
//            }
//        }
//    }
//    find_sec(temp.x, temp.y, 1);//寻找二级致命点
//    PlayerWin.erase(find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y)));
//    find_sec(temp.x, temp.y, -1);
//}
////是电脑走了自己致命点2后的影响
//void computer_stepP1_change() {
//    dot temp = HumanWin.front();
//    PlayerWin.erase(find(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y)));//有修改
//    find_sec(temp.x, temp.y, -1);
//    find_sec(temp.x, temp.y, 1);
//    cout << "你的诡计已经失败了垃圾" << endl;
//}
////电脑走了对手的致命点1后的影响
//void computer_stepC_change(int i, int j) {

//}
////电脑走了打分点

//    //else {//对方下棋时
//    //if (PlayerWin.size() != 0 && PlayerWin.front().total_score > 100) {
//    //    dot temp = PlayerWin.front();
//    //    PlayerWin.erase(PlayerWin.begin());
//    //    cout << " 我下五子棋就像cxk" << endl;
//    //    return temp;
//    //}//我方必胜点和致命点1的，这步将形成必胜点，可以宣布我们赢了
//    //if (ComputerWin.size() != 0 && ComputerWin.front().total_score > 100) {
//    //    dot temp = ComputerWin.front();
//    //    ComputerWin.erase(ComputerWin.begin());
//    //    cout << "我的诡计已经失败了垃圾" << endl;
//    //    return temp;
//    //}//对方必胜点和致命点1，此步用于破坏对方当前最需要下的一步**注意他和第一步的区别
//    //if (PlayerWin.size() != 0) {//此时要形成致命点1
//    //    dot temp = PlayerWin.front();//如果进行到现在，说明剩下的是等级不高的致命点2**因为若是等级高的在第一个if已经解决
//    //    PlayerWin.erase(PlayerWin.begin());
//    //    //周围的致命1或致命点2进行更新*2

//    //    /*下面是电脑下了之后对玩家的影响*/
//    //    player_to_computer(temp.x, temp.y);
//    //    return temp;
//    //}//我方致命点2
//    //if (ComputerWin.size() != 0) {
//    //    dot temp = ComputerWin.front();
//    //    ComputerWin.erase(ComputerWin.begin());
//    //    //周围的致命1或致命点2进行更新*2
//    //    if (temp.score[0] != 0) {
//    //        int i = 1;
//    //        while (temp.y + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {//遇到黑子或边界则终止
//    //            if (checkboard[temp.x][temp.y + i] == -1)i++;//我方棋子忽略
//    //            if (checkboard[temp.x][temp.y + i] == 0) {//若是白子则进行判断
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y + i)) == PlayerWin.end()) break;//在原来中找不到则说明改空格不是致命点2的点，忽略且break
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y + i))).score[0] == 0)break;//方向不同，也break
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y + i))).total_score = +100;//方向相同，提升该点级别
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);//调整堆
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //        i = 1;
//    //        while (temp.y - i >= 0 && checkboard[temp.x][temp.y - i] != -1) {//同一个方向上的不同走向
//    //            if (checkboard[temp.x][temp.y - i] == -1)i++;//下面的和前面一样
//    //            if (checkboard[temp.x][temp.y - i] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y - i)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y - i))).score[0] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x, temp.y - i))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//    //    if (temp.score[1] != 0) {
//    //        int i = 1;
//    //        while (temp.y + i <= 14 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y + i] != -1) {
//    //            if (checkboard[temp.x + i][temp.y + i] == -1)i++;
//    //            if (checkboard[temp.x + i][temp.y + i] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y + i)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y + i))).score[1] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y + i))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //        i = 1;
//    //        while (temp.y - i >= 0 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y - i] != -1) {
//    //            if (checkboard[temp.x - i][temp.y - i] == -1)i++;
//    //            if (checkboard[temp.x - i][temp.y - i] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y - i)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y - i))).score[1] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y - i))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//    //    if (temp.score[2] != 0) {
//    //        int i = 1;
//    //        while (temp.x + i <= 14 && checkboard[temp.x][temp.y + i] != -1) {
//    //            if (checkboard[temp.x + i][temp.y] == -1)i++;
//    //            if (checkboard[temp.x + i][temp.y] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y))).score[2] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //        i = 1;
//    //        while (temp.x - i >= 0 && checkboard[temp.x - i][temp.y] != -1) {
//    //            if (checkboard[temp.x - i][temp.y] == -1)i++;
//    //            if (checkboard[temp.x - i][temp.y] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y))).score[2] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//    //    if (temp.score[3] != 0) {
//    //        int i = 1;
//    //        while (temp.y - i >= 0 && temp.x + i <= 14 && checkboard[temp.x + i][temp.y - i] != -1) {
//    //            if (checkboard[temp.x + i][temp.y - i] == -1)i++;
//    //            if (checkboard[temp.x + i][temp.y - i] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y - i)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y - i))).score[3] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x + i, temp.y - i))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //        i = 1;
//    //        while (temp.y + i <= 14 && temp.x - i >= 0 && checkboard[temp.x - i][temp.y + i] != -1) {
//    //            if (checkboard[temp.x - i][temp.y + i] == -1)i++;
//    //            if (checkboard[temp.x - i][temp.y + i] == 0) {
//    //                if (find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y + i)) == PlayerWin.end()) break;
//    //                else {
//    //                    if ((*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y + i))).score[3] == 0)break;
//    //                    else {
//    //                        (*find_if(PlayerWin.begin(), PlayerWin.end(), findd(temp.x - i, temp.y + i))).total_score = +100;
//    //                        push_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
//    //                        break;
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//    //    find_sec(temp.x, temp.y, -1);
//    //    player_to_computer(temp.x,temp.y);
//    //    return temp;
//    //}//对方致命点2
//    //return most_score();//打分函数
//}
//}

