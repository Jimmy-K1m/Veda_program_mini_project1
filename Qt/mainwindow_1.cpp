#include <QVector>
#include <QGroupBox>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>


#include "mainwindow_1.h"
#include "functiondata.h"

MainWindow_1::MainWindow_1(){}

MainWindow_1::MainWindow_1(QWidget *parent, QVector<Member>& Members)
    : QWidget(parent) {

    QVector<QString> answer_ID = {"test", "test1"};


    //Member::Member(QString ID, QString password, QString name, QString account)


    QLineEdit* lineEdit[3];
    QStringList labels;
    labels << "&NAME" << "&ID" << "&PASSWORD";
    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0 ; i < 3; i++) // 0은 이름 1은 아이디 2는 패스워드
    {
        lineEdit[i] = new QLineEdit(this);
        lineEdit[i]->setMaxLength(10);
        if(i == 2)
            lineEdit[i]->setEchoMode(QLineEdit::Password);
        formLayout->addRow(labels.at(i), lineEdit[i]);
    }
    QPushButton* check = new QPushButton("Complete");
    formLayout->addRow(check);
    QGroupBox *groupBox = new QGroupBox("&Assign", this);
    groupBox->move(5,5);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);

    connect(lineEdit[1], &QLineEdit::editingFinished, [=](){
        int i = 0, j = 0;
        //for(; i < answer_ID.size(); i++)
        for(; i < Members.size(); i++)
        {
            //if(answer_ID[i] == lineEdit[0]->text())
            if((Members[i].get_ID()) == (lineEdit[0]->text()))
                break;
        }
        if(i!=Members.size())
        {
            qDebug()<< "Impossible ID";
        }
        else
        {
            qDebug()<< "Possible ID";
        }

    });

    connect(check, &QPushButton::clicked,[=](){
        //Members.append(Member(lineEdit[1]->text(), lineEdit[2]->text(),lineEdit[0]->text(), "111111111", 0));
        QMessageBox::about(this, "Complete Message", "Complete making an account");
        save_data(Members);
    });

}
MainWindow_1::~MainWindow_1()
{

}
