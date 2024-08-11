#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "mainwindow.h"
#include "mainwindow_1.h"
#include <QWidget>
#include <QMainWindow>
class LoginWidget : public QWidget//QMainWindow
{
    Q_OBJECT
    QVector<Member> Members;
public:
    LoginWidget();
    LoginWidget(QWidget *parent);
    LoginWidget(QWidget *parent,  MainWindow* window, MainWindow_1* window_1);
    ~LoginWidget();
};
#endif // LOGINWIDGET_H


