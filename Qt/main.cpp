#include <QApplication>
#include <QVector>

#include "mainwindow_1.h"
#include "functiondata.h"
#include "loginwidget.h"
#include "mainwindow.h"
#include "member.h"


/**
 *
 * This system is banking system which can deposit, withdraw, transfer to other's account.
 * Also, this system serves sign up function, load data to specific text file and save data to speicific file
 *
 *
 * Initially, the first window can show login widget and buttons which can connect to sign up and main banking system
 * Sign up window shows name, ID, password fields and it serves warning which can notify filled content is proper
 * Lastly, banking system have toolbars which can connect to their functions.
 *
 *
 * You should modify your address on functiondata.cpp file
 *
 **/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QVector<Member> Members;

    //파일 불러오기
    read_data(Members);

    for(int i = 0 ; i < Members.size();i++)
        qDebug() << Members[i].get_ID();


    MainWindow* mw = new MainWindow(nullptr, Members);
    MainWindow_1* mw_1= new MainWindow_1(nullptr, Members);


    mw->hide();
    mw_1->hide();
    LoginWidget l(nullptr, mw, mw_1);

    l.show();
    return a.exec();
}
