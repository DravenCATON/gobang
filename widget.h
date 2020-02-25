#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "messageDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

struct point{
    int x;
    int y;
};

struct dot{
    int x;
    int y;
    int total_score;
    int score[4];
};

class findd {
public:
    findd(int a, int b) {
        x1 = a;
        y1 = b;
    }
    bool operator() (dot& d) {
        if (d.x == x1 && d.y == y1)
            return true;
        else
            return false;
    }
private:
    int x1, y1;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool eventFilter(QObject *watched, QEvent *event);
    void playerWin();
    void computerWin();
private:
    Ui::Widget *ui;
    messageDialog *mDialog;
};

#endif // WIDGET_H
