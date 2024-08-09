#ifndef MAINWINDOW_1_H
#define MAINWINDOW_1_H

#include <QWidget>
#include <QLineEdit>
#include <QVector>
#include "member.h"

class MainWindow_1 : public QWidget
{
    Q_OBJECT
public:
    MainWindow_1();
    MainWindow_1(QWidget *parent, QVector<Member>& Members);
    ~MainWindow_1();

    //friend class Member;
};

#endif // MAINWINDOW_1_H
