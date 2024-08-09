#include <QApplication>

#include "mainwindow_1.h"
#include "functiondata.h"
#include "loginwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //파일 불러오기
    QVector<Member> Members;
    Members.append( Member("kang1234", "1234", "kang", "11111111111"));
    Members.append( Member("kim1234", "1234", "kim", "11111111111"));
    read_data(Members);

    for(int i = 0 ; i < Members.size();i++)
        qDebug() << Members[i].get_ID();


    MainWindow* mw = new MainWindow(nullptr, Members);
    MainWindow_1* mw_1= new MainWindow_1(nullptr, Members);


    mw->hide();
    mw_1->hide();
    // LoginWidget l(nullptr, Members, mw, mw_1);
    LoginWidget l;
    l.show();
    return a.exec();
}
