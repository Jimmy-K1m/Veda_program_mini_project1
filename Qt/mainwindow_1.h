#ifndef MAINWINDOW_1_H
#define MAINWINDOW_1_H

#include <QWidget>
#include <QLineEdit>
#include <QVector>
#include "member.h"
#include <QFormLayout>
#include <QLabel>

class MainWindow_1 : public QWidget
{
    Q_OBJECT
public:
    MainWindow_1();
    MainWindow_1(QWidget *parent, QVector<Member>& Members);
    ~MainWindow_1();

    QLineEdit* MakeLineEdit(int maxLength,int Mode);
};

#endif // MAINWINDOW_1_H
