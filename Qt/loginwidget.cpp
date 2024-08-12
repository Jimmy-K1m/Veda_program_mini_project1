
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QGroupBox>
#include <QVector>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "loginwidget.h"
#include "functiondata.h"

LoginWidget::LoginWidget(){}
LoginWidget::LoginWidget(QWidget *parent, MainWindow* window, MainWindow_1* window_1)
    : QWidget(parent)
{
    read_data(Members);

    this->setWindowTitle("SignIn Window");

    // QVector<QString> answer_ID = {"test", "test1"};
    // QVector<QString> answer_password = {"1234", "1345"};
    QStringList labels;
    labels << "&ID" << "&PASSWORD";
    QLineEdit* lineEdit[2];
    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0 ; i < 2; i++)
    {
        lineEdit[i] = new QLineEdit(this);
        lineEdit[i]->setMaxLength(10);
        if(i == 1)
            lineEdit[i]->setEchoMode(QLineEdit::Password);
        formLayout->addRow(labels.at(i), lineEdit[i]);
    }


    QGroupBox *groupBox = new QGroupBox("&Banking System", this);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(groupBox);

    // Set the main layout to the LoginWidget
    this->setLayout(mainLayout);
    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *assignButton = new QPushButton("Sign Up", this);

    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(assignButton);
    //connect(lineEdit[0], &QLineEdit::textChanged, [=]()mutable{cout << string(lineEdit[0]->text());});
    QObject::connect(loginButton, &QPushButton::clicked, [=]()mutable{
        int i = 0, j = 0;
        for(; i < Members.size(); i++)
        {
            if(Members[i].get_ID() == lineEdit[0]->text())
                break;
        }

        if(i != Members.size())
        {
            if(Members[i].get_Password() == lineEdit[1]->text())
            {
                qDebug()<< "Complete";
                QMessageBox::information(this, "Assgin", "Are you sure you want to login?", QMessageBox::Ok);
                //getInformation(QString name, QString ID, QString Password, QString account, int balance)
                window->getInformation(Members[i].get_name(),Members[i].get_ID(),Members[i].get_Password(),Members[i].get_account(),Members[i].get_balance());
                window->setVisible(true);
                this->setVisible(false);
            }
            else
            {
                QMessageBox::warning(this, "Error", "Wrong ID or Password", QMessageBox::Ok);
                lineEdit[0]->clear();
                lineEdit[1]->clear();
                qDebug()<< "Fail login";
            }
        }
        else {

            QMessageBox::warning(this, "Error", "Wrong ID or Password", QMessageBox::Ok);
            lineEdit[0]->clear();
            lineEdit[1]->clear();
        }
    });

    QObject::connect(assignButton, &QPushButton::clicked, [=](){
        bool ok;
        QMessageBox::information(this, "Assign", "Do you want to join us?", QMessageBox::Ok);
        window_1->setVisible(true);
    });
    // 확인 창 만들기
}

LoginWidget::~LoginWidget() {
    qDebug() << "~LoginWidget";

}


// #include "loginwidget.h"
// #include <QPushButton>
// #include <QLineEdit>
// #include <QLabel>
// #include <QGroupBox>
// #include <QVBoxLayout>
// #include <QMenuBar>
// #include <QStatusBar>
// #include <QVector>
// #include <QDebug>

// LoginWidget::LoginWidget(QWidget *parent)
//     : QMainWindow(parent)
// {
//     this->setGeometry(0, 0, 800, 600);
//     this->setWindowTitle("Login");
//     QVector<QString> answerID = {"test1", "test2"};
//     QVector<QString> answerPW = {"1234", "2345"};

//     QWidget *centralWidget = new QWidget(this);
//     this->setCentralWidget(centralWidget);

//     // QGroupBox
//     QGroupBox *groupBox = new QGroupBox("Login Page", centralWidget);
//     groupBox->setGeometry(210, 30, 381, 501);  // 위치와 크기 설정

//     // QLabel
//     QLabel *label = new QLabel("VEDA BANK", groupBox);
//     label->setGeometry(120, 110, 141, 51);
//     QFont labelFont;
//     labelFont.setPointSize(24);
//     labelFont.setBold(true);
//     label->setFont(labelFont);

//     // QLineEdit
//     QLineEdit *lineEdit_id = new QLineEdit(groupBox);
//     lineEdit_id->setGeometry(80, 220, 211, 21);

//     QLineEdit *lineEdit_pw = new QLineEdit(groupBox);
//     lineEdit_pw->setGeometry(80, 260, 211, 21);
//     lineEdit_pw->setEchoMode(QLineEdit::Password);  // 비밀번호 필드 설정

//     // QPushButton
//     QPushButton *pushButton = new QPushButton("Login", groupBox);
//     pushButton->setGeometry(300, 220, 71, 32);

//     QPushButton *pushButton2 = new QPushButton("회원가입", groupBox);
//     pushButton2->setGeometry(220, 290, 71, 32);

//     QMenuBar *menuBar = new QMenuBar(this);
//     menuBar->setGeometry(0, 0, 800, 38);
//     this->setMenuBar(menuBar);

//     QStatusBar *statusBar = new QStatusBar(this);
//     this->setStatusBar(statusBar);

//     //connect 연결하기
//     connect(lineEdit_id, &QLineEdit::textChanged, [=]() mutable {
//         qDebug() << "ID 입력 중:" << lineEdit_id->text();
//     });

//     connect(lineEdit_pw, &QLineEdit::editingFinished, [=]() mutable {
//         int i = 0;
//         for (i = 0; i < answerID.size(); i++) {
//             if (answerID[i] == lineEdit_id->text())
//                 break;
//         }

//         if (i != answerID.size()) {
//             if (answerPW[i] == lineEdit_pw->text())
//                 qDebug() << "로그인 성공";
//             else
//                 qDebug() << "로그인 실패: 비밀번호 불일치";
//         } else {
//             qDebug() << "로그인 실패: ID 불일치";
//         }
//     });
// }
// LoginWidget::~LoginWidget()
// {

// }
