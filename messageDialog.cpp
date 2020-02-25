#include "messageDialog.h"
#include "ui_messagedialog.h"
#include <QString>
#include <QIcon>

messageDialog::messageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageDialog)
{
    ui->setupUi(this);

    //设置项目图标
    this->setWindowIcon(QIcon(":/res/batman.png"));
    //为主界面设置背景色
    QPalette palette=this->palette();
    palette.setColor(QPalette::Window,QColor(255,255,255));
    this->setPalette(palette);
}

void messageDialog::setLabelText(QString text){
    ui->label->setText(text);
}

messageDialog::~messageDialog()
{
    delete ui;
}
