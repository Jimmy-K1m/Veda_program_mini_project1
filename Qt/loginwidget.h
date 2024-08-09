#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "mainwindow.h"
#include "mainwindow_1.h"
#include <QWidget>
#include <QMainWindow>
class LoginWidget : public QMainWindow//QWidget
{
    Q_OBJECT

public:
    LoginWidget();
    LoginWidget(QWidget *parent);
    // LoginWidget(QWidget *parent, QVector<Member>& Members , MainWindow* window, MainWindow_1* window_1);
    ~LoginWidget();
};
#endif // LOGINWIDGET_H


