#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QVector>

#include "member.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int balance;
    QString name;
    QString ID;
    QString Password;
    QString account;

    //QString greeting_msg = "Welcome " + name + "\n" + "How can I help you?";

    //initial->setStyleSheet("font: 18pt;");


    QAction *makeAction(QString icon, QString name, \
                        QString shortCut, QString toolTip, \
                        QObject* recv, const char* slot);

public:
    MainWindow(QWidget *parent, QVector<Member>& Members);

    ~MainWindow();
    void getInformation(QString name, QString ID, QString Password, QString account, int balance);
public slots:
    void deposit();
    void withdraw();
    void check();
    void send(QVector<Member>& Members);
    void exit(QVector<Member>& Members);

};
#endif // MAINWINDOW_H

