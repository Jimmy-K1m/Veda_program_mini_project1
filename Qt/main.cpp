#include <QApplication>
#include <QVector>

#include "mainwindow_1.h"
#include "functiondata.h"
#include "loginwidget.h"
#include "mainwindow.h"
#include "member.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //파일 불러오기
    QVector<Member> Members;

    read_data(Members);

    for(int i = 0 ; i < Members.size();i++)
        qDebug() << Members[i].get_ID();


    MainWindow* mw = new MainWindow(nullptr, Members);
    MainWindow_1* mw_1= new MainWindow_1(nullptr, Members);


    mw->hide();
    mw_1->hide();
    LoginWidget l(nullptr, mw, mw_1);
    //LoginWidget l;
    l.show();
    return a.exec();
}
