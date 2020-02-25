#define checkboard board
#include<iostream>
#include<vector>
#include "widget.h"
#include<QDebug>
extern int** board;
using namespace std;
extern vector<dot> ComputerWin;
extern vector<dot> PlayerWin;



bool cmp(dot dot1, dot dot2) {
    return dot1.total_score < dot2.total_score;
}//比较函数

//struct arrage{
//	int flag;//判断是否是合适位置
//	//int tochange;//判断是否输入
//	int x;
//	int y;
//};
//bool is_killing(arrage* data, int dec);//浩贤的函数
//int* find_sec(int x, int y) {
//	arrage data[6] = { 0 };
//	int i_up = 0;
//	while (checkborad[x][y + i_up] != -1 && (y + i_up) >= 0 && (y + i_up) <= 14 && i_up <= 5) {
//		i_up++;//找出范围-向上
//	}
//	int i_down = 0;
//	while (checkborad[x][y - i_down] != -1 && (y - i_down) >= 0 && (y - i_down) <= 14 && i_down <= 5) {
//		i_down++;//找出范围-向上
//	}
//	if (i_up + i_down >= 5) {//保证整个范围有六个
//		while (i_up + i_down >= 5) {
//			int temp = i_up+y;
//			for (int i = 0; i <6; i++,temp--) {
//				data[i].flag = checkborad[x][temp];
//				data[i].x = x;
//				data[i].y = temp;
//			}
//			is_killing(data,0);
//			i_up--;
//		}
//	}
//	int i_left = 0;
//	while (checkborad[x+i_left][y] != -1 && (x + i_left) >= 0 && (x + i_left) <= 14 && i_left <= 5) {
//		i_left++;//找出范围-向右
//	}
//	int i_right = 0;
//	while (checkborad[x-i_right][y] != -1 && (x - i_right) >= 0 && (x - i_right) <= 14 && i_right <= 5) {
//		i_right++;//找出范围-向左
//	}
//	if (i_left + i_right >= 5) {
//		while (i_left + i_right >= 5) {
//			int temp = i_left+x;
//			for (int i = 0; i < 6; i++, temp--) {
//				data[i].flag = checkborad[temp][y];
//				data[i].x = temp;
//				data[i].y = y;
//			}
//			is_killing(data,1);
//			i_left--;
//		}
//	}
//	int i_left_1 = 0; int i_up_1 = 0;
//	while (checkborad[x - i_left_1][y + i_up_1] != -1 && (x - i_left_1) >= 0 && (x - i_left_1) <= 14 && (y + i_up_1) >= 0 && (y + i_up_1 <= 14) && i_left_1 <= 5 && i_up_1 <= 5) {
//		i_left_1++; i_up_1++;
//	}
//	int i_right_1 = 0; int i_down_1 = 0;
//	while (checkborad[x + i_right_1][y - i_down_1] != -1 && (x + i_right_1) >= 0 && (x + i_right_1) <= 14 && (y - i_down_1) >= 0 && (y - i_down_1 <= 14) && i_right_1 <= 5 && i_down_1 <= 5) {
//		i_right_1++; i_down_1++;
//	}
//	if (i_left_1 + i_right_1 >= 5&&i_up_1+i_down_1>=5) {
//		while (i_left_1 + i_right_1 >= 5 && i_up_1 + i_down_1 >= 5) {
//			int temp_x = x-i_left_1; int temp_y = i_up_1 + y;
//			for (int i = 0; i < 6; i++, temp_x--,temp_y--) {
//				data[i].flag = checkborad[temp_x][temp_y];
//				data[i].x = temp_x;
//				data[i].y = temp_y;
//			}
//			is_killing(data,2);
//			i_left_1--; i_down_1--;
//		}
//	}
//	int i_left_1 = 0; int i_up_1 = 0;
//	while (checkborad[x - i_left_1][y - i_up_1] != -1 && (x - i_left_1) >= 0 && (x - i_left_1) <= 14 && (y - i_up_1) >= 0 && (y - i_up_1 <= 14) && i_left_1 <= 5 && i_up_1 <= 5) {
//		i_left_1++; i_up_1++;
//	}
//	int i_right_1 = 0; int i_down_1 = 0;
//	while (checkborad[x + i_right_1][y + i_down_1] != -1 && (x + i_right_1) >= 0 && (x + i_right_1) <= 14 && (y + i_down_1) >= 0 && (y + i_down_1 <= 14) && i_right_1 <= 5 && i_down_1 <= 5) {
//		i_right_1++; i_down_1++;
//	}
//	if (i_left_1 + i_right_1 >= 5 && i_up_1 + i_down_1 >= 5) {
//		while (i_left_1 + i_right_1 >= 5 && i_up_1 + i_down_1 >= 5) {
//			int temp_x = x-i_left_1; int temp_y = y-i_up_1;
//			for (int i = 0; i < 6; i++, temp_x--, temp_y--) {
//				data[i].flag = checkborad[temp_x][temp_y];
//			 	data[i].x = temp_x;
//				data[i].y = temp_y;
//			}
//			is_killing(data,3);
//			i_left_1--; i_down_1--;
//		}
//	}
//}
//插入电脑的
void insert1_cpt(int i, int j, int direction) {//插入制胜点1
    vector<dot>::iterator it = find_if(ComputerWin.begin(), ComputerWin.end(), findd(i, j));
    if (it == ComputerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 101;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        ComputerWin.push_back(*data);
    }
    else {
        it->total_score += 101 - it->score[direction];
        it->score[direction] = 101;
    }
    make_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
}
void insert1_cpt2(int i, int j, int direction) {//插入制胜点1
    vector<dot>::iterator it = find_if(ComputerWin.begin(), ComputerWin.end(), findd(i, j));
    if (it == ComputerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 111;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        ComputerWin.push_back(*data);
    }
    else {
        it->total_score += 111 - it->score[direction];
        it->score[direction] = 111;
    }
    make_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
}
void insert2_cpt(int i, int j, int direction) {//插入制胜点2
    vector<dot>::iterator it = find_if(ComputerWin.begin(), ComputerWin.end(), findd(i, j));
    if (it == ComputerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 1;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        ComputerWin.push_back(*data);
    }
    else {
        it->total_score += 1 - it->score[direction];
        it->score[direction] = 1;
    }
    make_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
}
void insert2_cpt2(int i, int j, int direction) {//插入制胜点2
    vector<dot>::iterator it = find_if(ComputerWin.begin(), ComputerWin.end(), findd(i, j));
    if (it == ComputerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 2;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        ComputerWin.push_back(*data);
    }
    else {
        it->total_score += 2 - it->score[direction];
        it->score[direction] = 2;
    }
    make_heap(ComputerWin.begin(), ComputerWin.end(), cmp);
}
//插入玩家的
void insert1_pl(int i, int j, int direction) {//插入制胜点1
    vector<dot>::iterator it = find_if(PlayerWin.begin(), PlayerWin.end(), findd(i, j));
    if (it == PlayerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 101;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        PlayerWin.push_back(*data);
    }
    else {
        it->total_score += 101 - it->score[direction];
        it->score[direction] = 101;
    }
    make_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
}
void insert1_pl2(int i, int j, int direction) {//插入制胜点1
    vector<dot>::iterator it = find_if(PlayerWin.begin(), PlayerWin.end(), findd(i, j));
    if (it == PlayerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 111;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        PlayerWin.push_back(*data);
    }
    else {
        it->total_score += 111 - it->score[direction];
        it->score[direction] = 111;
    }
    make_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
}
void insert2_pl(int i, int j, int direction) {//插入制胜点2
    vector<dot>::iterator it = find_if(PlayerWin.begin(), PlayerWin.end(), findd(i, j));
    if (it == PlayerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 1;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        PlayerWin.push_back(*data);
    }
    else {
        it->total_score += 1 - it->score[direction];
        it->score[direction] = 1;
    }
    make_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
}
void insert2_pl2(int i, int j, int direction) {//插入制胜点2
    vector<dot>::iterator it = find_if(PlayerWin.begin(), PlayerWin.end(), findd(i, j));
    if (it == PlayerWin.end()) {
        dot* data = new dot;
        data->total_score = data->score[direction] = 2;
        for (int k = 0; k < 4; ++k){
            if(k==direction)continue;
            data->score[k] = 0;
        }
        data->x = i;
        data->y = j;
        PlayerWin.push_back(*data);
    }
    else {
        it->total_score += 2 - it->score[direction];
        it->score[direction] = 2;
    }
    make_heap(PlayerWin.begin(), PlayerWin.end(), cmp);
}

void judge(int i, int j,int direction,int tag) {//tag为1则判断电脑，-1则判断对方玩家
    int x, y, big_end, small_end, big_cnt, small_cnt, big_space_cnt, samll_space_cnt, con_cnt;
    con_cnt = big_end= small_end= big_cnt= small_cnt= big_space_cnt= samll_space_cnt=0;
    //x,y遍历坐标，big_end, small_end边上是对方的棋子还是空格，big_cnt, small_cnt每一边的我方棋子数，big_space_cnt, samll_space_cnt空格数指示跳出循环，con_cnt直接相连数
    if (direction == 0) {
        for (x = i, y = j+1, big_end = 1, big_cnt = big_space_cnt = 0; y<16&&checkboard[x][y] !=(-tag); ++y) {
            big_cnt += checkboard[x][y];//统计棋子数
            if (checkboard[x][y] == 0)
                ++big_space_cnt;//统计空格数
            if (!big_space_cnt) con_cnt += checkboard[x][y];//统计连续的
            if (big_space_cnt == 2) {
                if (checkboard[x][y - 1] == 0)
                    --big_space_cnt;//连续两个空格，则只记一个
                break;
            }
        }
        if ((y==16||checkboard[x][y] == (-tag)) && (y-1==j||checkboard[x][y - 1] != 0)) big_end = 0;
        for (x = i, y = j-1, small_end = 1, small_cnt = samll_space_cnt = 0; y>=0&&checkboard[x][y] != (-tag); --y) {
            small_cnt += checkboard[x][y];
            if (checkboard[x][y] == 0)
                ++samll_space_cnt;
            if (!samll_space_cnt) con_cnt += checkboard[x][y];
            if (samll_space_cnt == 2) {
                if (checkboard[x][y + 1] == 0)
                    --samll_space_cnt;
                break;
            }
        }
        if ((y==-1||checkboard[x][y] == (-tag)) && (y + 1==j||checkboard[x][y + 1] != 0)) small_end = 0;
        big_cnt *= tag;
        small_cnt *= tag;
        con_cnt *= tag;
    }
    if (direction == 1) {
        for (x = i+1, y = j+1, big_end = 1, big_cnt = big_space_cnt = 0; x < 16 && y < 16 && checkboard[x][y] != (-tag); ++x, ++y) {
            big_cnt += checkboard[x][y];//统计棋子数
            if (checkboard[x][y] == 0)
                ++big_space_cnt;//统计空格数
            if (!big_space_cnt) con_cnt += checkboard[x][y];//统计连续的
            if (big_space_cnt == 2) {
                if (checkboard[x - 1][y - 1] == 0)
                    --big_space_cnt;//连续两个空格，则只记一个
                break;
            }
        }
        if ((x == 16 || y == 16 || checkboard[x][y] == (-tag)) && (x - 1==i||checkboard[x - 1][y - 1] != 0)) big_end = 0;
        for (x = i-1, y = j-1, small_end = 1, small_cnt = samll_space_cnt = 0; x>=0&&y>=0&&checkboard[x][y] != (-tag); --x, --y) {
            small_cnt += checkboard[x][y];
            if (checkboard[x][y] == 0)
                ++samll_space_cnt;
            if (!samll_space_cnt) con_cnt += checkboard[x][y];
            if (samll_space_cnt == 2) {
                if (checkboard[x + 1][y + 1] == 0)
                    --samll_space_cnt;
                break;
            }
        }
        if ((x == -1 || y == -1 || checkboard[x][y] == (-tag)) && (x + 1==i||checkboard[x + 1][y + 1] != 0)) small_end = 0;
        big_cnt *= tag;
        small_cnt *= tag;
        con_cnt *= tag;
    }
    if (direction == 2) {
        for (x = i+1, y = j, big_end = 1, big_cnt = big_space_cnt = 0; x<16&&checkboard[x][y] != (-tag); ++x) {
            big_cnt += checkboard[x][y];//统计棋子数
            if (checkboard[x][y] == 0)
                ++big_space_cnt;//统计空格数
            if (!big_space_cnt) con_cnt += checkboard[x][y];//统计连续的
            if (big_space_cnt == 2) {
                if (checkboard[x - 1][y] == 0)
                    --big_space_cnt;//连续两个空格，则只记一个
                break;
            }
        }
        if ((x == 16 || checkboard[x][y] == (-tag)) && (x - 1==i||checkboard[x - 1][y] != 0)) big_end = 0;
        for (x = i-1, y = j, small_end = 1, small_cnt = samll_space_cnt = 0; x>=0&&checkboard[x][y] != (-tag); --x) {
            small_cnt += checkboard[x][y];
            if (checkboard[x][y] == 0)
                ++samll_space_cnt;
            if (!samll_space_cnt) con_cnt += checkboard[x][y];
            if (samll_space_cnt == 2) {
                if (checkboard[x + 1][y] == 0)
                    --samll_space_cnt;
                break;
            }
        }
        if ((x == -1 || checkboard[x][y] == (-tag)) && (x + 1==i||checkboard[x + 1][y] != 0)) small_end = 0;
        big_cnt *= tag;
        small_cnt *= tag;
        con_cnt *= tag;
    }
    if (direction == 3) {
        for (x = i+1, y = j-1, big_end = 1, big_cnt = big_space_cnt = 0; x<16&&y>=0&&checkboard[x][y] != (-tag); ++x, --y) {
            big_cnt += checkboard[x][y];//统计棋子数
            if (checkboard[x][y] == 0)
                ++big_space_cnt;//统计空格数
            if (!big_space_cnt) con_cnt += checkboard[x][y];//统计连续的
            if (big_space_cnt == 2) {
                if (checkboard[x - 1][y + 1] == 0)
                    --big_space_cnt;//连续两个空格，则只记一个
                break;
            }
        }
        if ((x == 16 || y == -1 || checkboard[x][y] == (-tag)) && (x - 1==i||checkboard[x - 1][y + 1] != 0)) big_end = 0;
        for (x = i-1, y = j+1, small_end = 1, small_cnt = samll_space_cnt = 0; x>=0&&y<16&&checkboard[x][y] != (-tag); --x, ++y) {
            small_cnt += checkboard[x][y];
            if (checkboard[x][y] == 0)
                ++samll_space_cnt;
            if (!samll_space_cnt) con_cnt += checkboard[x][y];
            if (samll_space_cnt == 2) {
                if (checkboard[x + 1][y - 1] == 0)
                    --samll_space_cnt;
                break;
            }
        }
        if ((x==-1||y==16||checkboard[x][y] == (-tag)) && (x + 1==i||checkboard[x + 1][y - 1] != 0))small_end = 0;
        big_cnt *= tag;
        small_cnt *= tag;
        con_cnt *= tag;
    }
    if(con_cnt>3){
        if (tag == 1)insert1_cpt2(i, j, direction);
        else insert1_pl2(i, j, direction);
        return;
    }
    if (con_cnt == 3 && big_end && small_end) {//连着三个以上或者连着三个，两头不是对面。是1
        if (tag == 1)insert1_cpt(i, j, direction);
        else insert1_pl(i, j, direction);
        return;
    }
    if(con_cnt == 3&&big_end+small_end!=0){//连着三个并且一边是对面。是2
        if (tag == 1)insert2_cpt(i, j, direction);
        else insert2_pl(i, j, direction);
        return;
    }
    if (((big_end == 0 || small_end == 0)&&big_cnt + small_cnt==2)||big_cnt + small_cnt < 2){//少于两个或者是两个且至少有一边是对面
        if(tag==1){
            vector<dot>::iterator it=find_if(ComputerWin.begin(),ComputerWin.end(),findd(i,j));
            if(it!=ComputerWin.end()){
                it->total_score-=it->score[direction];
                it->score[direction]=0;
                if(it->total_score==0)
                    ComputerWin.erase(it);
                push_heap(ComputerWin.begin(),ComputerWin.end(),cmp);
            }

            return;
        }
        else{
            vector<dot>::iterator it=find_if(PlayerWin.begin(),PlayerWin.end(),findd(i,j));
            if(it!=PlayerWin.end()){
                it->total_score-=it->score[direction];
                it->score[direction]=0;
                if(it->total_score==0)
                    PlayerWin.erase(it);
                push_heap(PlayerWin.begin(),PlayerWin.end(),cmp);
            }

            return;
        }
    }
    if (big_cnt + small_cnt == 2) {//可能是2
        if (big_cnt != 1 || con_cnt) {//两个在同一侧或者一个连着的
            if (tag == 1)insert2_cpt(i, j, direction);
            else insert2_pl(i, j, direction);
        }
        else{
            if(tag==1){
                vector<dot>::iterator it=find_if(ComputerWin.begin(),ComputerWin.end(),findd(i,j));
                if(it!=ComputerWin.end())
                    ComputerWin.erase(it);
                return;
            }
            else{
                vector<dot>::iterator it=find_if(PlayerWin.begin(),PlayerWin.end(),findd(i,j));
                if(it!=PlayerWin.end())
                    PlayerWin.erase(it);
                return;
            }
        }
    }
    if (big_cnt + small_cnt > 2) {//可能是进化成必胜点的2，可能是单侧的2
        if (tag == 1)insert2_cpt(i, j, direction);
        else insert2_pl(i, j, direction);
    }
}

void find_sec(int x,int y,int tag) {//此函数双方都可以使用
    /*int x 是x坐标 int y 是y坐标 int tag 是当前下棋的一方1代表我方，-1代表敌方*/
    tag=-tag;
    for (int i = 1; y + i <= 15; i++) {//遇到超过范围或边界
        if (checkboard[x][y + i] == tag)break;//遇到敌方终止
        if (checkboard[x][y + i] == 0) {//若是空格则判断
            judge(x, y + i, 0,-tag);
        }
    }
    for (int i = 1; y - i >= 0; i++) {//第一个方向上的不同走向
        if (checkboard[x][y - i] == tag)break;
        if (checkboard[x][y - i] == 0) {
            judge(x, y - i, 0,-tag);
        }
    }
    //下面各个方向和第一个方向一致
    for (int i = 1;x + i <= 15; i++) {
        if (checkboard[x+i][y] == tag)break;
        if (checkboard[x+i][y] == 0) {
            judge(x+i, y , 2,-tag);
        }
    }
    for (int i = 1;  x - i >= 0; i++) {
        if (checkboard[x - i][y] == tag)break;
        if (checkboard[x - i][y] == 0) {
            judge(x - i, y, 2,-tag);
        }
    }
    for (int i = 1;  x - i >= 0&&y-i>=0; i++) {
        if (checkboard[x - i][y-i] == tag)break;
        if (checkboard[x - i][y-i] == 0) {
            judge(x - i, y-i, 1,-tag);
        }
    }
    for (int i = 1;  x + i <=15 && y + i <=15; i++) {
        if (checkboard[x + i][y + i] == tag)break;
        if (checkboard[x + i][y + i] == 0) {
            judge(x + i, y + i, 1,-tag);
        }
    }
    for (int i = 1; x + i <= 15 && y - i >=0; i++) {
        if (checkboard[x + i][y - i] == tag)break;
        if (checkboard[x + i][y - i] == 0) {
            judge(x + i, y - i, 3,-tag);
        }
    }
    for (int i = 1;  x - i >= 0 && y + i <= 15; i++) {
        if (checkboard[x - i][y + i] == tag)break;
        if (checkboard[x - i][y + i] == 0) {
            judge(x - i, y + i, 3,-tag);
        }
    }
}
